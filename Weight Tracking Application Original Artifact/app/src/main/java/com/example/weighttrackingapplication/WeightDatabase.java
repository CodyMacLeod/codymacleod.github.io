package com.example.weighttrackingapplication;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.util.Log;

import java.util.Date;

public class WeightDatabase extends SQLiteOpenHelper {
    // Naming database and version number
    private static final String DATABASE_NAME = "weight.db";
    private static final int VERSION = 1;

    // Constructor
    public WeightDatabase(Context context) {
        super(context, DATABASE_NAME, null, VERSION);
    }

    // Assigning table name and columns
    private static final class WeightTable {
        private static final String TABLE = "weights";
        private static final String COL_ID = "_id";
        private static final String COL_DATE = "date";
        private static final String COL_WEIGHT = "weight";
        private static final String COL_GOAL = "goal";
    }

    // Creating table with appropriate columns and autoincrementing id
    @Override
    public void onCreate(SQLiteDatabase db) {
        db.execSQL("create table " + WeightTable.TABLE + " (" + WeightTable.COL_ID + " integer primary key autoincrement, " +
                WeightTable.COL_DATE + " text, " + WeightTable.COL_WEIGHT + " double, "
                + WeightTable.COL_GOAL + " double)");
    }

    // Removing old table if updated one exists
    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        db.execSQL("drop table if exists " + WeightTable.TABLE);
        onCreate(db);
    }

    // Inputting new daily weight entry to table
    public long addEntry(String date, double weight, double goal) {
        SQLiteDatabase db = getWritableDatabase();

        // Assigning values to columns
        ContentValues values = new ContentValues();
        values.put(WeightTable.COL_DATE, date);
        values.put(WeightTable.COL_WEIGHT, weight);
        values.put(WeightTable.COL_GOAL, goal);

        // Inserting into table
        long entryId = db.insert(WeightTable.TABLE, null, values);
        return entryId;
    }

    // Retrieving all entries from table
    public Cursor retrieveEntries() {
        SQLiteDatabase db = getWritableDatabase();

        // SQL method to return all entries from table sorted by most recent date first
        String sql = "SELECT * FROM " + WeightTable.TABLE + " ORDER BY " + WeightTable.COL_DATE + " DESC";
        Cursor cursor = db.rawQuery(sql, null);
        return cursor;
    }

    // Method to update the weight of a specific entry
    public boolean updateWeight(long id, double weight) {
        SQLiteDatabase db = getWritableDatabase();

        // Updating weight columns
        ContentValues values = new ContentValues();
        values.put(WeightTable.COL_WEIGHT, weight);

        // Attempting to update entry in table
        int rowsUpdated = db.update(WeightTable.TABLE, values, "_id = ?", new String[] { Float.toString(id) });
        return rowsUpdated > 0;
    }

    // Method to retrieve last entered weight goal user entered
    public double getWeightGoal() {
        SQLiteDatabase db = getWritableDatabase();

        // Retrieving most recent entry
        String sql = "SELECT * FROM " + WeightTable.TABLE + " ORDER BY " + WeightTable.COL_ID + " DESC LIMIT 1";
        Cursor cursor = db.rawQuery(sql, null);

        // If entry exists
        if(cursor.moveToFirst()) {
            // Return the weight goal colunmn
            return cursor.getDouble(3);
        }
        else {
            cursor.close();
            return 0;
        }
    }

    // Removing entry from specific id
    public boolean deleteEntry(long id) {
        SQLiteDatabase db = getWritableDatabase();
        int rowsDeleted = db.delete(WeightTable.TABLE, WeightTable.COL_ID + " = ?", new String[]{ Long.toString(id)});
        return rowsDeleted > 0;
    }
}
