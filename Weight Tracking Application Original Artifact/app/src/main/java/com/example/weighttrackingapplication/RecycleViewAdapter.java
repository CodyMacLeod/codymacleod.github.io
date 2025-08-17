package com.example.weighttrackingapplication;

import android.content.Context;
import android.text.Editable;
import android.text.TextWatcher;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageButton;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import java.util.ArrayList;

public class RecycleViewAdapter extends RecyclerView.Adapter<RecycleViewAdapter.MyViewHolder> {
    // Variable declarations
    private final RecyclerViewInterface recyclerViewInterface;
    private Context context;
    private ArrayList id, dateText, weightText;

    // Constructor including interface for individual entry interaction
    public RecycleViewAdapter(Context context, ArrayList id, ArrayList dateText, ArrayList weightText,
                              RecyclerViewInterface recyclerViewInterface) {
        this.context = context;
        this.id = id;
        this.dateText = dateText;
        this.weightText = weightText;
        this.recyclerViewInterface = recyclerViewInterface;
    }


    @NonNull
    @Override
    public MyViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View v = LayoutInflater.from(context).inflate(R.layout.daily_weight, parent, false);
        return new MyViewHolder(v, recyclerViewInterface);
    }

    @Override
    public void onBindViewHolder(@NonNull MyViewHolder holder, int position) {
        holder.dateText.setText(String.valueOf(dateText.get(position)));
        holder.weightText.setText(String.valueOf(weightText.get(position)));
    }

    // Getting side of entries in our recycler view
    @Override
    public int getItemCount() {
        return dateText.size();
    }

    // Invididual components of recycler view
    public class MyViewHolder extends RecyclerView.ViewHolder {
        // Variables for each component in each entry
        TextView dateText, weightText;
        ImageButton deleteButton;
        public MyViewHolder(@NonNull View itemView, RecyclerViewInterface recyclerViewInterface) {
            super(itemView);

            // Connecting to date text in each entry
            dateText = itemView.findViewById(R.id.dateText);

            // Connecting to weight text in each entry
            weightText = itemView.findViewById(R.id.weightText);
            // Functionality to update weight field
            weightText.addTextChangedListener(new TextWatcher() {
                @Override
                public void beforeTextChanged(CharSequence s, int start, int count, int after) {

                }

                @Override
                public void onTextChanged(CharSequence s, int start, int before, int count) {

                }

                // After user has modified weight field, call method to update database
                @Override
                public void afterTextChanged(Editable s) {
                    // Ensuring interface exists
                    if(recyclerViewInterface != null) {
                        int position = getAdapterPosition();

                        // Ensuring component exists
                        if(position != RecyclerView.NO_POSITION){
                            // Calling to update this specific entry with new weight
                            recyclerViewInterface.updateEntry(position, Double.parseDouble(weightText.getText().toString()));
                        }
                    }
                }
            });

            // Connecting to button to delete entry
            deleteButton = itemView.findViewById(R.id.deleteButton);
            deleteButton.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    // Ensuring interface exists
                    if(recyclerViewInterface != null) {
                        int position = getAdapterPosition();

                        // Ensuring component exists
                        if(position != RecyclerView.NO_POSITION){
                            // Calling to delete this specific entry
                            recyclerViewInterface.deleteButtonClicked(position);
                        }
                    }
                }
            });
        }
    }
}
