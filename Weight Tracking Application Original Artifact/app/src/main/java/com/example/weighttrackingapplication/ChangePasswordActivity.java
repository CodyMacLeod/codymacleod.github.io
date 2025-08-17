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

public class ChangePasswordActivity extends AppCompatActivity {
    // Variable declarations
    Button confirmButton;
    TextInputEditText  oldPasswordText, newPasswordText, confirmPasswordText;
    String oldPassword, newPassword, confirmPassword;
    LoginDatabase database;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.change_password);
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.changePassword), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });

        // Creating toolbar with up button to return to settings page
        Toolbar myToolbar = (Toolbar)findViewById(R.id.toolbar);
        setSupportActionBar(myToolbar);
        getSupportActionBar().setDisplayHomeAsUpEnabled(true);

        // Connecting to login database
        database = new LoginDatabase(ChangePasswordActivity.this);

        // Attaching to text fields to retrieve data from
        oldPasswordText = (TextInputEditText)findViewById(R.id.textOldPassword);
        newPasswordText = (TextInputEditText)findViewById(R.id.textNewPassword);
        confirmPasswordText = (TextInputEditText)findViewById(R.id.textConfirmPassword);

        // Setting up the confirm button
        confirmButton = (Button)findViewById(R.id.buttonConfirm);
        confirmButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                updatePassword();
            }
        });
    }

    // Method to attempt to update password after hitting confirm button
    private void updatePassword() {
        // Getting values of the text input fields
        oldPassword = String.valueOf(oldPasswordText.getText());
        newPassword = String.valueOf(newPasswordText.getText());
        confirmPassword = String.valueOf(confirmPasswordText.getText());

        // Confirming all fields have been filled
        if(oldPassword.isEmpty() || newPassword.isEmpty() || confirmPassword.isEmpty()) {
            Toast.makeText(ChangePasswordActivity.this, "Please enter all fields.", Toast.LENGTH_SHORT).show();
            return;
        }

        // Ensuring the new password matches the confirmation field
        if(!newPassword.equals(confirmPassword)) {
            Toast.makeText(ChangePasswordActivity.this, "Password must match.", Toast.LENGTH_SHORT).show();
            return;
        }

        // Ensuring old password was correct
        if(database.verifyPassword(LoginActivity.accountId, oldPassword)) {
            // Updating to new password
            database.updatePassword(LoginActivity.accountId, newPassword);
            Toast.makeText(ChangePasswordActivity.this, "Password updated.", Toast.LENGTH_SHORT).show();

            // Returning to settings page
            Intent intent = new Intent(this, SettingsActivity.class);
            startActivity(intent);
        }
        else {
            // Alerting user their old password was incorrect
            Toast.makeText(ChangePasswordActivity.this, "Incorrect current password.", Toast.LENGTH_SHORT).show();
        }
    }
}