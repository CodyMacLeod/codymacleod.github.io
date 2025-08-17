/**
 * Name        : Task.h
 * Author      : Cody MacLeod
 * Description : A header file for class declarations and functions of the Task class.
**/
#pragma once

#include <string>
#include <stdexcept>

class Task {
private:
	// Private parameters
	std::string taskID;
	std::string name;
	std::string description;

	

public:
	// Constructors
	Task();
	Task(std::string id, std::string name, std::string description);

	// Getter methods
	std::string getTaskID();
	std::string getName();
	std::string getDescription();

	// Setter methods
	void setName(std::string name);
	void setDescription(std::string description);
};

