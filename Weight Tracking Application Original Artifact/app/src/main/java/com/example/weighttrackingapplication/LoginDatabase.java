package com.example.weighttrackingapplication;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

public class LoginDatabase extends SQLiteOpenHelper {
    // Variable declarations for SQLite DB
    private static final String DATABASE_NAME = "login.db";
    private static final int VERSION = 1;

    // Constructor
    public LoginDatabase(Context context) {
        super(context, DATABASE_NAME, null, VERSION);
    }

    // Setting up table name and columns
    private static final class LoginTable {
        private static final String TABLE = "accounts";
        private static final String COL_ID = "_id";
        private static final String COL_USERNAME = "username";
        private static final String COL_PASSWORD = "password";
        private static final String COL_FIRSTNAME = "firstname";
        private static final String COL_LASTNAME = "lastname";
    }

    // Creating table with autoincrementing Id column
    @Override
    public void onCreate(SQLiteDatabase db) {
        db.execSQL("create table " + LoginTable.TABLE + " (" + LoginTable.COL_ID + " integer primary key autoincrement, " +
                LoginTable.COL_USERNAME + " text, " + LoginTable.COL_PASSWORD + " text, " +
                LoginTable.COL_FIRSTNAME+ " text, " + LoginTable.COL_LASTNAME + " text)");
    }

    // Deleting old table if updated one exists
    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        db.execSQL("drop table if exists " + LoginTable.TABLE);
        onCreate(db);
    }

    // Adding a new account to the login table
    public long addAccount(String username, String password, String firstname, String lastname) {
        SQLiteDatabase db = getWritableDatabase();

        // Filling in columns
        ContentValues values = new ContentValues();
        values.put(LoginTable.COL_USERNAME, username);
        values.put(LoginTable.COL_PASSWORD, password);
        values.put(LoginTable.COL_FIRSTNAME, firstname);
        values.put(LoginTable.COL_LASTNAME, lastname);

        // Inserting columns to table
        long accountId = db.insert(LoginTable.TABLE, null, values);
        return accountId;
    }

    // Verify user input matches credentials in table
    public long verifyLogin(String username, String password) {
        SQLiteDatabase db = getWritableDatabase();

        // SQL statement to ensure username and password match
        String sql = "SELECT * FROM " + LoginTable.TABLE + " WHERE username = ? AND password = ?";
        Cursor cursor = db.rawQuery(sql, new String[]{username, password});

        // If an entry is found
        if (cursor.moveToFirst()) {
            // Return the account Id
            return cursor.getLong(0);
        }

        cursor.close();
        return -1;
    }

    // Verifying password is correct for changing password page
    public boolean verifyPassword(long id, String password) {
        SQLiteDatabase db = getWritableDatabase();

        // Ensuring account ID and password match
        String sql = "SELECT * FROM " + LoginDatabase.LoginTable.TABLE + " WHERE _id = ? AND password = ?";
        Cursor cursor = db.rawQuery(sql, new String[]{ Float.toString(id), password });

        // Sending confirmation
        if (cursor.moveToFirst()) {
            return true;
        }

        // Incorrect password
        cursor.close();
        return false;
    }

    // A method for the user to change their password
    public boolean updatePassword(long id, String password) {
        SQLiteDatabase db = getWritableDatabase();

        // Inserting new value into password column
        ContentValues values = new ContentValues();
        values.put(LoginDatabase.LoginTable.COL_PASSWORD, password);

        // Updating table
        int rowsUpdated = db.update(LoginDatabase.LoginTable.TABLE, values, "_id = ?", new String[] { Float.toString(id) });
        return rowsUpdated > 0;
    }

    // Returning first name of user account
    public String retrieveFirstName(long id) {
        SQLiteDatabase db = getWritableDatabase();

        // Retrieve account based on id
        String sql = "SELECT * FROM " + LoginDatabase.LoginTable.TABLE + " WHERE _id = ?";
        Cursor cursor = db.rawQuery(sql, new String[]{ Float.toString(id) });

        // If account exists
        if(cursor.moveToFirst()) {
            // Return first name column
            return cursor.getString(3);
        }
        else {
            cursor.close();
            return "";
        }
    }

    // Returning last name of user account
    public String retrieveLastName(long id) {
        SQLiteDatabase db = getWritableDatabase();

        // Retrieving account base on id
        String sql = "SELECT * FROM " + LoginDatabase.LoginTable.TABLE + " WHERE _id = ?";
        Cursor cursor = db.rawQuery(sql, new String[]{ Float.toString(id) });

        // If account exists
        if(cursor.moveToFirst()) {
            // Return last name column
            return cursor.getString(4);
        }
        else {
            cursor.close();
            return "";
        }
    }
}
