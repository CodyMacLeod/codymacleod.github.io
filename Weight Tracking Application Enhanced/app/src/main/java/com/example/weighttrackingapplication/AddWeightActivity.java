package com.example.weighttrackingapplication;

import android.Manifest;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.telephony.SmsManager;
import android.view.View;
import android.widget.Button;
import android.widget.DatePicker;
import android.widget.EditText;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;
import androidx.core.content.ContextCompat;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Calendar;

public class AddWeightActivity extends AppCompatActivity {
    // Declaring variables
    EditText textNewWeight;
    DatePicker datePicker;
    Button buttonSubmit;
    WeightDatabase database;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.add_weight);

        // Retrieving weight goal from main activity to add to database
        Bundle extras = getIntent().getExtras();
        double goalWeight = extras.getDouble("weightGoal");


        // Creating toolbar with up button to return back to main screen
        Toolbar myToolbar = (Toolbar)findViewById(R.id.toolbar);
        setSupportActionBar(myToolbar);
        getSupportActionBar().setDisplayHomeAsUpEnabled(true);

        // Connecting to the weight database or creating one if it doesn't exist
        database = new WeightDatabase(AddWeightActivity.this);

        // Creating widget for users to pick the date to enter
        datePicker = (DatePicker)findViewById(R.id.datePicker);
        Calendar today = Calendar.getInstance();
        datePicker.init(
                today.get(Calendar.YEAR),
                today.get(Calendar.MONTH),
                today.get(Calendar.DAY_OF_MONTH),
                new DatePicker.OnDateChangedListener() {
                    @Override
                    public void onDateChanged(DatePicker view, int year, int month, int day) {

                    }
                }
        );

        // Widget for user to type in weight
        textNewWeight = (EditText)findViewById(R.id.textNewWeight);

        // Button to submit new entry to database
        buttonSubmit = (Button)findViewById(R.id.buttonSubmit);
        buttonSubmit.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v) {
                addNewEntry(goalWeight);
            }
        });
    }

    //Method to insert new entry into our database of daily weights
    public void addNewEntry(double goalWeight) {
        // Retrieving data from datePicker
        int day = datePicker.getDayOfMonth();
        int month = datePicker.getMonth();
        int year = datePicker.getYear();
        Calendar calendar = Calendar.getInstance();
        calendar.set(year, month, day);

        // Setting data to appropriate format to sort in our SQL database
        Date chosenDate = calendar.getTime();
        String dateString = new SimpleDateFormat("yyyy-MM-dd").format(chosenDate);
        double weightText = Double.parseDouble(textNewWeight.getText().toString());

        // Attempting to input data into database
        long insertAttempt = database.addEntry(dateString, weightText, goalWeight);
        if(insertAttempt != -1) {
            // Confirming entry to user
            Toast.makeText(AddWeightActivity.this, "Entry Added.", Toast.LENGTH_SHORT).show();

            // Checking if goal was met
            if(weightText <= goalWeight) {
                // Confirming SMS permissions
                if(ContextCompat.checkSelfPermission(this, Manifest.permission.SEND_SMS) == PackageManager.PERMISSION_GRANTED) {
                    //Sending SMS message
                    sendSMS(goalWeight);
                }
            }

            // Returning to main screen
            Intent intent = new Intent(this, MainActivity.class);
            startActivity(intent);
        }
        else {
            // Alerting user invalid entry and remaining on screen for user to fix
            Toast.makeText(AddWeightActivity.this, "Invalid entry.", Toast.LENGTH_SHORT).show();
            return;
        }
    }

    // A method to send the user a SMS message on achieving their weight goal
    private void sendSMS(double goalWeight) {
        //Set up SMS manager
        SmsManager messageManager = SmsManager.getDefault();

        // Send message
        messageManager.sendTextMessage(String.valueOf(getDeviceId()), null, "Congratulations on meeting your goal of " + String.valueOf(goalWeight), null, null);

    }
}