/**
 * Name        : Contact.h
 * Author      : Cody MacLeod
 * Description : A header file for class declarations and functions of the Contact class.
**/
#pragma once

#include <string>
#include <stdexcept>

class Contact {
private:
	// Private parameters
	std::string firstName;
	std::string lastName;
	std::string phoneNumber;
	std::string address;
	std::string contactID;


public:
	// Constructors
	Contact(std::string id, std::string firstName, std::string lastName, std::string phoneNumber, std::string address);
	Contact();

	// Getter methods
	std::string getContactID();
	std::string getFirstName();
	std::string getLastName();
	std::string getPhoneNumber();
	std::string getAddress();

	// Setter methods
	void setFirstName(std::string firstName);
	void setLastName(std::string lastName);
	void setPhoneNumber(std::string phoneNumber);
	void setAddress(std::string address);
};