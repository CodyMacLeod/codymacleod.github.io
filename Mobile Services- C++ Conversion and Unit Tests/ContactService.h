/**
 * Name        : ContactService.h
 * Author      : Cody MacLeod
 * Description : A header file for class declarations and functions of the Contact Service class.
**/
#pragma once
#include <string>
#include <vector>
#include "Contact.h"

/**
 * Declarations for a class to manage a list of contacts.
**/
class ContactService {
private:

public:
	// Container for contacts
	std::vector<Contact> contactList;

	// Constructor and destructor
	ContactService();
	virtual ~ContactService();
	
	// A method to check and retrieve a contact by ID
	Contact& checkContact(std::string id);

	// Methods to add and remove contacts from container
	void addContact(std::string id, std::string firstName, std::string lastName, std::string phoneNumber, std::string address);
	void removeContact(std::string id);

	// Methods to update parameters of preexisting contacts
	void updateFirstName(std::string id, std::string firstName);
	void updateLastName(std::string id, std::string lastName);
	void updatePhoneNumber(std::string id, std::string phoneNumber);
	void updateAddress(std::string id, std::string address);

};
