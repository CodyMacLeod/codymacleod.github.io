package com.example.weighttrackingapplication;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

import com.google.android.material.textfield.TextInputEditText;

public class RegisterActivity extends AppCompatActivity {
    // Variable declarations
    Button registerButton;
    TextInputEditText usernameText, passwordText, confirmPasswordText, firstNameText, lastNameText;
    String username, password, confirmPassword, firstName, lastName;
    LoginDatabase database;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.register);
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.register), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });

        // Setting up app bar with up button to return to login screen
        Toolbar myToolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(myToolbar);
        getSupportActionBar().setDisplayHomeAsUpEnabled(true);

        // Connecting to login database or creating new one if it doesnt exist
        database = new LoginDatabase(RegisterActivity.this);

        // Connecting to all input fields
        usernameText = (TextInputEditText)findViewById(R.id.textUsername);
        passwordText = (TextInputEditText)findViewById(R.id.textPassword);
        confirmPasswordText = (TextInputEditText)findViewById(R.id.textConfirmPassword);
        firstNameText = (TextInputEditText)findViewById(R.id.textFirstName);
        lastNameText = (TextInputEditText)findViewById(R.id.textLastName);

        // Setting up register button
        registerButton = (Button)findViewById(R.id.buttonRegister);
        registerButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                registerAccount();
            }
        });
    }

    // Functionality for creating new account after pressing register button
    private void registerAccount(){
        // Retrieving input from all text input fields
        username = String.valueOf(usernameText.getText());
        password = String.valueOf(passwordText.getText());
        confirmPassword = String.valueOf(confirmPasswordText.getText());
        firstName = String.valueOf(firstNameText.getText());
        lastName = String.valueOf(lastNameText.getText());

        // Ensuring all fields have been filled
        if(username.isEmpty() || password.isEmpty() || firstName.isEmpty() || lastName.isEmpty()) {
            Toast.makeText(RegisterActivity.this, "Please enter all fields.", Toast.LENGTH_SHORT).show();
            return;
        }

        // Ensuring passwords match
        if(!password.equals(confirmPassword)) {
            Toast.makeText(RegisterActivity.this, "Password must match.", Toast.LENGTH_SHORT).show();
            return;
        }

        // Creating new account and setting account ID for other pages to use
        LoginActivity.accountId = database.addAccount(username,  password, firstName, lastName);

        // Letting user know account creation was successful
        Toast.makeText(RegisterActivity.this, "Account registered.", Toast.LENGTH_SHORT).show();

        // Sending user to main page
        Intent intent = new Intent(this, MainActivity.class);
        startActivity(intent);
    }
}
