/**
 * Name        : TaskService.h
 * Author      : Cody MacLeod
 * Description : A header file for class declarations and functions of the Task Service class.
**/
#pragma once
#include <string>
#include <vector>
#include "Task.h"

// Setting a table size for default constructor
const unsigned int DEFAULT_SIZE = 128;

/**
 * Declarations for a class to manage a list of tasks.
**/
class TaskService {
private:
	// Creating nodes to store tasks and pointer to next in bucket for hash table
	struct Node {
		Task task;
		unsigned int key;
		Node* next;

		// Empty node
		Node() {
			key = UINT_MAX;
			next = nullptr;
		}

		// Node with task
		Node(Task inputTask) : Node() {
			task = inputTask;
		}

		// Node with task and key
		Node(Task inputTask, unsigned int inputKey) : Node(inputTask) {
			key = inputKey;
		}
	};

	// A vector to store all the buckets in hash table
	std::vector<Node> nodes;
	unsigned int tableSize;

public:
	// A vector of tasks for sorting alphabetically
	std::vector<Task> taskList;

	// Constructor and destructors
	TaskService();
	TaskService(unsigned int tablesSize);
	virtual ~TaskService();

	// Methods to create and modify hash table
	unsigned int hash(int key);
	Task& checkTask(std::string id);
	void addTask(std::string id, std::string name, std::string description);
	void removeTask(std::string id);

	// Methods to udpate parameters of existing tasks
	void updateName(std::string id, std::string name);
	void updateDescription(std::string id, std::string description);

	// Methods to convert hash table to sort alphabetically
	std::vector<Task> convertToVector();
	int partition(std::vector<Task>& tasks, int begin, int end);
	void quickSort(std::vector<Task>& tasks, int begin, int end);
	std::vector<Task> organizeAlphabetically();

};
