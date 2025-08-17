package com.example.weighttrackingapplication;

import android.content.Intent;
import android.database.Cursor;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.Toast;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.google.android.material.floatingactionbutton.FloatingActionButton;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity implements RecyclerViewInterface {
    // Variable declarations
    private final int REQUEST_WRITE_CODE = 0;

    ImageButton settingButton;
    FloatingActionButton addDailyWeightButton;
    WeightDatabase database;
    RecyclerView recyclerView;
    ArrayList<String> id, date, weight;
    RecycleViewAdapter adapter;
    EditText textWeightGoal;
    static String displayGoal;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_main);
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });

        // Connecting to weight database or creating if one doesn't exist
        database = new WeightDatabase(MainActivity.this);

        // Setting up arrays for each weight entry
        id = new ArrayList<>();
        date = new ArrayList<>();
        weight = new ArrayList<>();

        // Creating recycler view to display individual entries
        recyclerView = findViewById(R.id.weightList);
        adapter = new RecycleViewAdapter(this, id, date, weight,this);
        recyclerView.setAdapter(adapter);
        recyclerView.setLayoutManager(new LinearLayoutManager(this));
        displayWeight();

        // Connecting to input text for user weight goal
        textWeightGoal = findViewById(R.id.textGoalWeight);
        // Displaying last entered user weight goal
        if(displayGoal != null){
            textWeightGoal.setText(displayGoal);
        }

        // Settings button functionality
        settingButton = (ImageButton)findViewById(R.id.settingButton);
        settingButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                toSettingsPage();
            }
        });

        // Add new entry button functionality
        addDailyWeightButton = (FloatingActionButton)findViewById(R.id.addWeightButton);
        addDailyWeightButton.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v) {
                addNewWeight();
            }
        });
    }

    // Method to populate recycler view with entries from our database
    private void displayWeight() {
        // Retrieving data from our database
        Cursor cursor = database.retrieveEntries();

        // Closing if database is empty
        if(cursor.getCount() == 0) {
            cursor.close();
            return;
        }
        else {
            // Setting weight goal value to users last entered weight goal
            if(database.getWeightGoal() > 0) {
                displayGoal = String.valueOf(database.getWeightGoal());
            }

            // Going through database to populate recycler view
            while(cursor.moveToNext()) {
                // Filling arrays with columns from database for recycler view
                id.add(String.valueOf(cursor.getString(0)));
                date.add(cursor.getString(1));
                weight.add(String.valueOf(cursor.getDouble(2)));
            }
        }
        cursor.close();
    }

    // Navigation to settings page
    private void toSettingsPage() {
        // Ensuring user input for weight goal remains in case they've set a goal, but
        // Not input any entries to database yet
        String weightGoal = String.valueOf(textWeightGoal.getText());
        if(!weightGoal.isEmpty()) {
            displayGoal = weightGoal;
        }

        // Sending user to settings page
        Intent intent = new Intent(this, SettingsActivity.class);
        startActivity(intent);
    }

    // Sending user to page to input new daily weight entry
    private void addNewWeight() {
        // Ensuring user has set a weight goal before being allowed to input
        String weightGoal = String.valueOf(textWeightGoal.getText());
        if(weightGoal.isEmpty()) {
            Toast.makeText(MainActivity.this, "Please enter a goal weight.", Toast.LENGTH_SHORT).show();
            return;
        }

        // Maintaining display goal value in case user enters and leaves page without submitting entry
        displayGoal = weightGoal;

        // Sending value for weight to be input in table despite being in a seperate activity
        double goal = Double.parseDouble(weightGoal);
        Intent intent = new Intent(this, AddWeightActivity.class);
        intent.putExtra("weightGoal", goal);
        startActivity(intent);
    }

    // Functionality for removing an entry from the recycler view
    @Override
    public void deleteButtonClicked(int position) {
        // Removing entry from database
        database.deleteEntry(Long.parseLong(id.get(position)));

        // Removing from recycler view
        id.remove(position);
        date.remove(position);
        weight.remove(position);
        adapter.notifyItemRemoved(position);
    }

    // Method to allow user to modify the weight value of previous entries
    @Override
    public void updateEntry(int position, double weightEntry) {
        // Updating database with new weight value
        database.updateWeight(Long.parseLong(id.get(position)), weightEntry);
    }
}