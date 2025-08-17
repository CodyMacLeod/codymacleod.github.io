/**
 * Name        : Task.cpp
 * Author      : Cody MacLeod
 * Description : A class to set up individual tasks and ensure each
 *				 parameter meets requirements.
**/
#include "Task.h"

#include <string>
#include <stdexcept>

using namespace std;

/**
 * Default constructor for empty contact
**/
Task::Task() {
	string id;
	string name;
	string description;
}

/**
 * Constructor for filled task
**/
Task::Task(string id, string name, string description)
{
	// Ensuring the ID is filled in and not longer than 10 characters
	if (id.empty() || id.length() > 10) {
		throw std::invalid_argument("Invalid task ID.");
	}

	taskID = id;

	// Calling setter methods for other parameters to avoid repeating requirement checks
	setName(name);
	setDescription(description);
}

/**
 * Getter method to return the Task ID.
 *
 *	@return a string containing the unique task ID
**/
string Task::getTaskID()
{
	return taskID;
}

/**
 * A method to assign the name and ensure it meets requirements.
 * Name must be filled in and cannot be longer than 20 characters.
**/
void Task::setName(string name)
{
	// Validating name meets requirements
	if (name.empty() || name.length() > 20) {
		throw invalid_argument("Invalid task name.");
	}

	this->name = name;
}

/**
 * Getter method to return the  name of the task.
 *
 *	@return a string containing the name
**/
string Task::getName()
{
	return name;
}

/**
 * A method to assign the description and ensure it meets requirements.
 * Description must be filled in and cannot be longer than 50 characters.
**/
void Task::setDescription(string description)
{
	// Validating description meets requirements
	if (description.empty() || description.length() > 50) {
		throw invalid_argument("Invalid task description.");
	}

	this->description = description;
}

/**
 * Getter method to return the description of the task.
 *
 *	@return a string containing the description
**/
string Task::getDescription()
{
	return description;
}
