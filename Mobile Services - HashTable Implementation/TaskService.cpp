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
	tableSize = DEFAULT_SIZE;
	nodes.resize(tableSize);

}

/**
 * Constructor to modify size of hash table
**/
TaskService::TaskService(unsigned int size)
{
	this->tableSize = size;
	nodes.resize(tableSize);
}

/**
 * Destructor to remove tasks from program
**/
TaskService::~TaskService()
{
	nodes.erase(nodes.begin());
}

/**
 * Calculate the hash value of a given key.
 *
 * @return The calculated hash
 */
unsigned int TaskService::hash(int key)
{
	return key % tableSize;
}

/**
 * Searching through our hash table to find a specific task by
 * unique task ID.
 *
 * @return Reference to task within hash table
 */
Task& TaskService::checkTask(string id)
{
	Task task;

	// Creating a key
	unsigned key = hash(atoi(id.c_str()));

	// Checking if node exists at key
	Node* node = &(nodes.at(key));

	// If node matching key does exist, return the task
	if (node != nullptr && node->key != UINT_MAX && node->task.getTaskID().compare(id) == 0) {
		return node->task;
	}

	// If a node matching key does not exist, return empty task
	if (node == nullptr || node->key == UINT_MAX) {
		return task;
	}

	// walk through chaining
	while (node != nullptr) {
		// if current node matches return it
		if (node->key != UINT_MAX && node->task.getTaskID().compare(id) == 0) {
			return node->task;
		}

		//setting to next node
		node = node->next;
	}

	return task;
}

/**
 * Adding a new task to the hash table as long as it has a unique task ID.
 */
void TaskService::addTask(string id, string name, string description)
{
	// Calculate key for the task and check if bucket already exists
	unsigned key = hash(atoi(id.c_str()));
	Node* existingNode = &(nodes.at(key));

	// Attempt to create task
	Task task = Task(id, name, description);

	// If node doesn't already exist
	if (existingNode == nullptr) {
		Node* newNode = new Node(task, key);
		nodes.insert(nodes.begin() + key, (*newNode));
	}
	else {
		// If node exists but isn't being used
		if (existingNode->key == UINT_MAX) {
			existingNode->key = key;
			existingNode->task = task;
			existingNode->next = nullptr;
		}
		else {
			// Ensure task ID is unique
			if (existingNode->task.getTaskID() == id) {
				throw invalid_argument("Task ID already exists.");
			}
			// Walk through the chain to find next opening
			while (existingNode->next != nullptr) {
				// Ensure task ID is not already being used
				if (existingNode->task.getTaskID() == id) {
					throw invalid_argument("Task ID already exists.");
				}

				existingNode = existingNode->next;
			}

			// Adding the task to the end of the bucket
			existingNode->next = new Node(task, key);
		}
	}
}

void TaskService::removeTask(string id)
{
	// calculate the key of node to remove
	int key = hash(atoi(id.c_str()));

	// Remove from hash table
	nodes.erase(nodes.begin() + key);
}


/**
 * A method to update the name of the task.
**/
void TaskService::updateName(string id, string name)
{
	// Getting reference to task if it exists
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
	// Getting reference to task if it exists
	Task& task = checkTask(id);
	if (task.getTaskID() == id) {
		// Updating description
		task.setDescription(description);
	}
}

/**
 * A method to go through the hash table and store all tasks
 * into a vector that to more efficiently quick sort through to
 * sort all tasks alphabetically.
 *
 * @return A vector of all tasks from the hash table
**/
vector<Task> TaskService::convertToVector() {
	vector<Task> taskList;

	// Loop through the nodes of the hash table
	for (unsigned int i = 0; i < tableSize; ++i) {
		// Set the current node
		Node* node = &nodes.at(i);

		// Ensuring the node has been changed from default values
		if (node->key != UINT_MAX) {
			// Adding task to vector
			taskList.push_back(node->task);
		}

		// Continue through other nodes in buckets due to collisions
		while (node->next != nullptr) {
			// Progress to next node
			node = node->next;
			taskList.push_back(node->task);
		}
	}

	return taskList;
}

/**
 * A method to to partition the vector into lower and higher halves.
 *
 * @return Ending index of partition
**/
int TaskService::partition(vector<Task>& tasks, int begin, int end) {
	// Variable declarations and initializations
	bool done = false;
	int low = begin;
	int high = end;

	// Calculate the middle element in task vector
	int middlePoint = low + (high - low) / 2;

	// Setting the middle element as pivot point
	Task pivot = tasks.at(middlePoint);

	// Continue looping until we finish sorting
	while (!done) {
		// Increase lower bound until we find pivot
		while (tasks[low].getName() < pivot.getName()) {
			low += 1;
		}

		// Decrease the upper bound until we find pivot
		while (pivot.getName() < tasks[high].getName()) {
			high -= 1;
		}

		// Checking to see if we are fully sorted
		if (low >= high) {
			done = true;
		}
		// Swapping at the lower and upper bounds then tightening bounds on both sides
		else {
			swap(tasks[low], tasks[high]);
			low += 1;
			high -= 1;
		}
	}

	return high;
}

/**
 * A method to perform a quick sort on list of tasks to sort alphabetically by first name.
 * Average performance: O(n log(n))
 * Worst case performance: O(n^2)
**/
void TaskService::quickSort(vector<Task>& tasks, int begin, int end) {
	int mid = 0;

	// Checking if vector is already sorted
	if (begin >= end) {
		return;
	}

	// Get midpoint from last element in lower half
	mid = partition(tasks, begin, end);

	// Recursively sort low partition
	quickSort(tasks, begin, mid);

	// Recursively sort high partition
	quickSort(tasks, mid + 1, end);
}

/**
 * A method to return the alphabetically organized list of tasks.
 *
 * @return A vector of tasks sorted alphabetically
**/
vector<Task> TaskService::organizeAlphabetically() {
	vector<Task> taskList = convertToVector();

	// Sort alphabetically
	quickSort(taskList, 0, taskList.size() - 1);

	return taskList;
}