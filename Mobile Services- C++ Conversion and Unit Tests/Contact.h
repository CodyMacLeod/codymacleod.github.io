#pragma once

#include <string>
#include <stdexcept>

class Contact {
private:
	std::string firstName;
	std::string lastName;
	std::string phoneNumber;
	std::string address;
	std::string contactID;


public:
	Contact(std::string id, std::string firstName, std::string lastName, std::string phoneNumber, std::string address);
	Contact();
	std::string getContactID();
	std::string getFirstName();
	std::string getLastName();
	std::string getPhoneNumber();
	std::string getAddress();
	void setFirstName(std::string firstName);
	void setLastName(std::string lastName);
	void setPhoneNumber(std::string phoneNumber);
	void setAddress(std::string address);
};