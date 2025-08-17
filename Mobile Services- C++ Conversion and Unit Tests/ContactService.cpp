/**
 * Name        : ContactService.cpp
 * Author      : Cody MacLeod
 * Description : This class handles the collection of contacts, allows the addition of new ones,
 *				 the ability to delete, and to modify the names, phone number, and address.
**/
#include "ContactService.h"
#include "Contact.h"

#include <string>
#include <vector>
#include <iostream>

using namespace std;

/**
 * Default constructor
**/
ContactService::ContactService()
{
}

/**
 * Default destructor
**/
ContactService::~ContactService() 
{
}

/**
 * A method to see if a contact already exists on the list.
 * This is used to verify that a contact's ID is unique.
 *
 * @return A reference to the contact in the contactList vector
**/
Contact& ContactService::checkContact(string id)
{
	// Iterating through list of contacts
	for (int i = 0; i < contactList.size(); i++) {
		// Checking if one already exists with unique id
		if (contactList.at(i).getContactID() == id) {
			return contactList.at(i);
		}
	}

	// Returning empty contact if one doesn't already exist
	Contact contact;
	return contact;
}

/**
 * A method to add a new contact to the list.
**/
void ContactService::addContact(string id, string firstName, string lastName, string phoneNumber, string address)
{
	Contact contact;

	// Ensuring the contact id is unique
	if (checkContact(id).getContactID() != id) {
		// Adding contact to list
		contact = Contact(id, firstName, lastName, phoneNumber, address);
		contactList.push_back(contact);
	}
	else {
		throw invalid_argument("Contact ID already exists.");
	}
}

/**
 * A method to remove a contact from the list.
**/
void ContactService::removeContact(string id)
{
	// Getting reference to contact if one already exists with this id
	Contact& contact = checkContact(id);
	if (contact.getContactID() == id) {
		// Finding contact at matching ID, moving it to end, then shrinking vector size to delete it
		contactList.erase(remove_if(contactList.begin(), contactList.end(), [id](Contact& t) {
			return t.getContactID() == id;
			}), contactList.end());
	}
}

/**
 * A method to update the first name of the contact.
**/
void ContactService::updateFirstName(string id, string firstName)
{
	// Getting reference to contact if it already exists
	Contact& contact = checkContact(id);
	if (contact.getContactID() == id) {
		// Updating first name
		contact.setFirstName(firstName);
	}
}

/**
 * A method to update the last name of the contact.
**/
void ContactService::updateLastName(string id, string lastName)
{
	// Getting reference to contact if it already exists
	Contact& contact = checkContact(id);
	if (contact.getContactID() == id) {
		// Updating last name
		contact.setLastName(lastName);
	}
}

/**
 * A method to update the phone number of the contact.
**/
void ContactService::updatePhoneNumber(string id, string phoneNumber)
{
	// Getting reference to contact if it already exists
	Contact& contact = checkContact(id);
	if (contact.getContactID() == id) {
		// Updating phone number
		contact.setPhoneNumber(phoneNumber);
	}
}

/**
 * A method to update the address of the contact.
**/
void ContactService::updateAddress(string id, string address)
{
	// Getting reference to the contact if it already exists
	Contact& contact = checkContact(id);
	if (contact.getContactID() == id) {
		// Updating address
		contact.setAddress(address);
	}
}
