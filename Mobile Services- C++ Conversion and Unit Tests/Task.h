#pragma once

#include <string>
#include <stdexcept>

class Task {
private:
	std::string taskID;
	std::string name;
	std::string description;

	

public:
	Task();
	Task(std::string id, std::string name, std::string description);
	std::string getTaskID();
	std::string getName();
	std::string getDescription();
	void setName(std::string name);
	void setDescription(std::string description);
};

