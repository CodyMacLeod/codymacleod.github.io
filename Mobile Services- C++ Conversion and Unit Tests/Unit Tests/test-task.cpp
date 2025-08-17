/**
 * Name        : tests-task.cpp
 * Author      : Cody MacLeod
 * Description : A set of tests to ensure the task class meets all requirements using Catch2 unit testing framework.
**/
#include "catch.hpp"

#include "Task.h"
#include <stdexcept>

TEST_CASE("Testing setter methods for Task", "[TaskSetter]") {
	Task task = Task("1", "name", "description");
	REQUIRE(task.getTaskID() == "1");
	REQUIRE(task.getName() == "name");
	REQUIRE(task.getDescription() == "description");
}

TEST_CASE("Testing to ensure the task ID meets requirements.", "[TaskID]") {
	SECTION("ID must be filled in.") {
		CHECK_THROWS_AS(Task("", "name", "description"), std::invalid_argument);
	}

	SECTION("ID cannot be longer than 10 characters.") {
		CHECK_THROWS_AS(Task("123456890000", "name", "description"), std::invalid_argument);
	}
}

TEST_CASE("Testing to ensure the Tasks name meets requirements.", "[TaskName]") {
	SECTION("Name has to be filled in.") {
		CHECK_THROWS_AS(Task("1", "", "description"), std::invalid_argument);
	}

	SECTION("Name cannot be larger than 10 characters.") {
		CHECK_THROWS_AS(Task("2", "This is way too many characters", "description"), std::invalid_argument);
	}
}

TEST_CASE("Testing to ensure Tasks description meets requirements.", "[TaskDescription]") {
	SECTION("Description has to be filled in.") {
		CHECK_THROWS_AS(Task("1", "name", ""), std::invalid_argument);
	}

	SECTION("Last name cannot be larger than 50 characters.") {
		CHECK_THROWS_AS(Task("2", "name", "This description is far larger than the allowed fifty characters."), std::invalid_argument);
	}
}
