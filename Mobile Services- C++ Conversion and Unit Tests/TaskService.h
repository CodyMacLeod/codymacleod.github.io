/**
 * Name        : TaskService.h
 * Author      : Cody MacLeod
 * Description : A header file for class declarations and functions of the Task Service class.
**/
#pragma once
#include <string>
#include <vector>
#include "Task.h"

/**
 * Declarations for a class to manage a list of tasks.
**/
class TaskService
{
private:

public:
	// Container for tasks
	std::vector<Task> taskList;

	// Constructor and destructor
	TaskService();
	virtual ~TaskService();

	// A method to check and retrieve a task by ID
	Task& checkTask(std::string id);

	// Methods to add or remove tasks to the list
	void addTask(std::string id, std::string name, std::string description);
	void removeTask(std::string id);

	// Methods to update parameters of preexisting tasks
	void updateName(std::string id, std::string name);
	void updateDescription(std::string id, std::string description);
};

