package com.example.weighttrackingapplication;

public interface RecyclerViewInterface {
    // Setting up interactions within individual entries in recyclerView
    void deleteButtonClicked(int position);
    void updateEntry(int position, double weightEntry);
}
