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
}

TEST_CASE("Testing removing tasks from the task service.", "[TaskServiceRemoveTask]") {
	SECTION("Task can be removed from list.") {
		TaskService service = TaskService();
		service.addTask("1", "name", "description");
		service.removeTask("1");
		REQUIRE(service.taskList.size() == 0);
	}
}
	
TEST_CASE("Testing update functionality for tasks from task service.", "[TaskServiceUpdateTask]") {
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