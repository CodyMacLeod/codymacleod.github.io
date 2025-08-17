package com.example.weighttrackingapplication;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;


public class SettingsActivity extends AppCompatActivity {
    // Variable declarations
    LoginDatabase database;
    TextView textFirstName, textLastName;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.settings_activity);

        // Connecting to login database
        database = new LoginDatabase(SettingsActivity.this);

        // Connecting first name field and setting it to first name tied to the account id
        textFirstName = (TextView)findViewById(R.id.textFirstName);
        textFirstName.setText("First Name: " + database.retrieveFirstName(LoginActivity.accountId));

        // Connecting to last name field and setting it to last name tied to the account id
        textLastName = (TextView)findViewById(R.id.textLastName);
        textLastName.setText("Last Name: " + database.retrieveLastName(LoginActivity.accountId));

        // Setting up toolbar with up button to return to main page
        Toolbar myToolbar = (Toolbar)findViewById(R.id.toolbar);
        setSupportActionBar(myToolbar);
        getSupportActionBar().setDisplayHomeAsUpEnabled(true);

        // Button to log out user and return to log in page
        Button logoutButton = (Button)findViewById(R.id.buttonLogOut);
        logoutButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                toLoginPage();
            }
        });

        // Button to prompt user to change password
        Button changePasswordButton = (Button)findViewById(R.id.buttonChangePassword);
        changePasswordButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                toChangePasswordPage();
            }
        });
    }

    // Functionality for logging out user
    private void toLoginPage() {
        // Clearing assigned account ID
        LoginActivity.accountId = -1;

        // Returning to login page
        Intent intent = new Intent(this, LoginActivity.class);
        startActivity(intent);
    }

    // Sending user to change password page
    private void toChangePasswordPage() {
        Intent intent = new Intent(this, ChangePasswordActivity.class);
        startActivity(intent);
    }
}