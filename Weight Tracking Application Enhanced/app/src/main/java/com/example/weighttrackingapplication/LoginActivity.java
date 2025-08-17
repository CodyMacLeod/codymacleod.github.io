package com.example.weighttrackingapplication;

import android.content.Intent;
import android.os.Bundle;
import android.Manifest;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

import com.google.android.material.textfield.TextInputEditText;

public class LoginActivity extends AppCompatActivity {
    // variable declarations
    private final int REQUEST_WRITE_CODE = 0;
    Button loginButton, registerButton;
    TextInputEditText usernameText, passwordText;
    String username, password;
    LoginDatabase database;

    // variable containing account id to be accessed by other pages
    public static long accountId;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.login);
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.login), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });

        // Asking for SMS permissions
        getPermission();

        // Connecting to login database or creating one if not already existing
        database = new LoginDatabase(LoginActivity.this);

        // Connecting to input fields
        usernameText = (TextInputEditText)findViewById(R.id.textUsername);
        passwordText = (TextInputEditText)findViewById(R.id.textPassword);

        // login button setup
        loginButton = (Button)findViewById(R.id.buttonLogin);
        loginButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                toMainPage();
            }
        });

        // Register button setup
        registerButton = (Button)findViewById(R.id.buttonRegister);
        registerButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                toRegisterPage();
            }
        });
    }

    // A method to ask the user for permission to send text messages
   private void getPermission() {
        // Checking if we've already asked for permission
        if(PermissionsUtil.hasPermission(this, Manifest.permission.SEND_SMS, R.string.write_rationale, REQUEST_WRITE_CODE)) {
            // Requesting permissions
            requestPermissions(new String[]{Manifest.permission.SEND_SMS}, 1);
        }
   }

   // Navigating to register page
   private void toRegisterPage() {
        Intent intent = new Intent(this, RegisterActivity.class);
        startActivity(intent);
   }

   // Method to confirm login and enter main page
    private void toMainPage() {
        // Retrieving values of input fields
        username = String.valueOf(usernameText.getText());
        password = String.valueOf(passwordText.getText());

        // Confirming all input fields are filled
        if(username.isEmpty() || password.isEmpty()) {
            Toast.makeText(LoginActivity.this, "Please enter all fields.", Toast.LENGTH_SHORT).show();
            return;
        }

        // Confirming username and password matches database
        if(database.verifyLogin(username, password) != -1) {
            // Setting accountId for other pages
            accountId = database.verifyLogin(username, password);

            // With confirmation, sending user to main page
            Intent intent = new Intent(this, MainActivity.class);
            startActivity(intent);
        }
        else {
            // Alerting user invalid credentials
            Toast.makeText(LoginActivity.this, "Incorrect login credentials.", Toast.LENGTH_SHORT).show();
            return;
        }
    }
}