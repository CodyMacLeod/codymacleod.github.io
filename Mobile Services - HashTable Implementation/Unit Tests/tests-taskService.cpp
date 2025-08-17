/**
 * Name        : tests-taskService.cpp
 * Author      : Cody MacLeod
 * Description : A set of tests to ensure the task service class meets all requirements using Catch2 unit testing framework.
**/
#include "catch.hpp"

#include "TaskService.h"
#include "Task.h"
#include <stdexcept>
#include <iostream>

TEST_CASE("Testing adding tasks to the task service.", "[TaskServiceAddTask]") {
	SECTION("Task is added to the list.") {
		TaskService service = TaskService();
		service.addTask("1", "name", "description");
		REQUIRE(service.checkTask("1").getTaskID() == "1");
	}

	SECTION("Task must have unique ID to be added.") {
		TaskService service = TaskService();
		service.addTask("1", "name", "description");
		REQUIRE_THROWS_AS(service.addTask("1", "name", "This id is not unique."), std::invalid_argument);
	}


	SECTION("Task can be removed from list.") {
		TaskService service = TaskService();
		service.addTask("1", "name", "description");
		service.removeTask("1");
		REQUIRE(service.taskList.size() == 0);
	}
	
	SECTION("Task can have it's name updated.") {
		TaskService service = TaskService();
		service.addTask("1", "name", "description");
		service.updateName("1", "New Name");
		REQUIRE(service.checkTask("1").getName() == "New Name");

	}

	SECTION("Task can have it's description updated.") {
		TaskService service = TaskService();
		service.addTask("1", "name", "description");
		service.updateName("1", "New description");
		REQUIRE(service.checkTask("1").getName() == "New description");
	}
}

TEST_CASE("Testing that the list of tasks can be sorted alphabetically.", "[TaskSorting]") {
	TaskService service = TaskService();

	// Filling with tasks in a random order.
	service.addTask("1", "Homework", "Finish second artifact enhancement.");
	service.addTask("129", "Laundry", "Wash and dry laundry.");
	service.addTask("2", "Dishes", "Clean dishes in sink");
	service.addTask("130", "Workout", "Go to the gym and exercise.");
	service.addTask("3", "Work", "Work at place of employment.");
	service.addTask("131", "Jobhunt", "Search for new job opportunities.");

	std::vector<Task> contactList = service.organizeAlphabetically();

	// Printing organized task list to show alphabetical order
	std::cout << "Outputting tasks in alphabetical order:" << std::endl;
	for (int i = 0; i < contactList.size(); ++i) {
		std::cout << contactList[i].getName() << std::endl;
	}

	std::cout << std::endl;
}