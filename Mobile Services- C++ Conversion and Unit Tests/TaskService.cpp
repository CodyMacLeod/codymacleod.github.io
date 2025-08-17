/**
 * Name        : TaskService.cpp
 * Author      : Cody MacLeod
 * Description : This class handles the collection of tasks, allows the addition of new ones,
 *				 the ability to delete, and to modify the name and description of the tasks.
**/
#include "TaskService.h"
#include "Task.h"
#include <string>
#include <vector>

using namespace std;

/**
 * Default constructor
**/
TaskService::TaskService()
{
}

/**
 * Default destructor
**/
TaskService::~TaskService()
{
}

/**
 * A method to see if a task already exists on the list.
 * This is used to verify that a task's ID is unique.
 * 
 * @return A reference to the task in the TaskList vector
**/
Task& TaskService::checkTask(string id)
{
	// Iterating through list of tasks
	for (int i = 0; i < taskList.size(); i++) {
		// Checking if the ID already matches
		if (taskList.at(i).getTaskID() == id) {
			return taskList.at(i);
		}
	}

	// Returning empty task if none is found
	Task task;
	return task;
}

/**
 * A method to add a new task to the list.
**/
void TaskService::addTask(string id, string name, string description)
{
	Task task;

	// Ensuring task ID is unique
	if (checkTask(id).getTaskID() != id) {
		// Creating new task and adding to vector
		task = Task(id, name, description);
		taskList.push_back(task);
	}
	else {
		throw invalid_argument("Task ID already exists.");
	}
}

/**
 * A method to remove a task from our list.
**/
void TaskService::removeTask(string id)
{
	// Getting reference to task if one exists at this ID
	Task& task = checkTask(id);
	if (task.getTaskID() == id) {
		// Finding task at matching ID, moving it to end, then shrinking vector size to delete it
		taskList.erase(remove_if(taskList.begin(), taskList.end(), [id](Task& t) {
			return t.getTaskID() == id;
		}), taskList.end());
	}
}

/**
 * A method to update the name of the task.
**/
void TaskService::updateName(string id, string name)
{
	// Getting reference to task if one already exists at this id
	Task& task = checkTask(id);
	if (task.getTaskID() == id) {
		// Updating name
		task.setName(name);
	}
}

/**
 * A method to update the description of the task.
**/
void TaskService::updateDescription(string id, string description)
{
	// Getting reference to task if one already exists at this id
	Task& task = checkTask(id);
	if (task.getTaskID() == id) {
		// Updating description
		task.setDescription(description);
	}
}
