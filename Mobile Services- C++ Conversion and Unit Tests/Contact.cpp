/**
 * Name        : Contact.cpp
 * Author      : Cody MacLeod
 * Description : A class to set up individual contacts and ensure each
 *				 parameter meets requirements.
**/
#include "Contact.h"

#include <string>
#include <stdexcept>

using namespace std;

/**
 * Default constructor for empty contact
**/ 
Contact::Contact() {
	string id;
	string firstName;
	string lastName;
	string phoneNumber;
	string address;
}

/**
 * Constructor for filled contact
**/
Contact::Contact(string id, string firstName, string lastName, string phoneNumber, string address)
{
	// Ensuring the ID is filled in and not longer than 10 characters
	if (id.empty() || id.length() > 10) {
		throw invalid_argument("Invalid contact ID.");
	}

	contactID = id;

	// Calling setter methods for other parameters to avoid repeating requirement checks
	setFirstName(firstName);
	setLastName(lastName);
	setPhoneNumber(phoneNumber);
	setAddress(address);
}

/**
 * Getter method to return the Contact ID.
 * 
 *	@return a string containing the unique contact ID
**/
string Contact::getContactID()
{
	return contactID;
}

/**
 * Getter method to return the first name of the contact.
 *
 *	@return a string containing the first name
**/
string Contact::getFirstName()
{
	return firstName;
}

/**
 * A method to assign the first name and ensure it meets requirements.
 * First name must be filled in and cannot be longer than 10 characters.
**/
void Contact::setFirstName(string firstName)
{
	// Validating first name meets requirements
	if (firstName.empty() || firstName.length() > 10) {
		throw invalid_argument("Invalid first name.");
	}

	this->firstName = firstName;
}

/**
 * Getter method to return the last name of the contact.
 *
 *	@return a string containing the last name
**/
string Contact::getLastName()
{
	return lastName;
}

/**
 * A method to assign the last name and ensure it meets requirements.
 * Last name must be filled in and cannot be longer than 10 characters.
**/
void Contact::setLastName(string lastName)
{
	// Validating requirements are met
	if (lastName.empty() || lastName.length() > 10) {
		throw invalid_argument("Invalid last name.");
	}

	this->lastName = lastName;
}

/**
 * Getter method to return the phone number of the contact
 *
 *	@return a string containing the phone number
**/
string Contact::getPhoneNumber()
{
	return phoneNumber;
}

/**
 * A method to assign the phone number of the contact and ensure it meets requirements.
 * Phone number must be filled in and exactly 10 characters long.
**/
void Contact::setPhoneNumber(string phoneNumber)
{
	// Validating requirements
	if (phoneNumber.empty() || phoneNumber.length() != 10) {
		throw invalid_argument("Invalid phone number.");
	}

	this->phoneNumber = phoneNumber;
}

/**
 * Getter method to return the address of the contact.
 *
 *	@return a string containing the address.
**/
string Contact::getAddress()
{
	return address;
}

/**
 * A method to assign the address of the contact and ensure it meets requirements.
 * Phone number must be filled in and cannot be longer than 30 characters.
**/
void Contact::setAddress(string address)
{
	// Validating requirements
	if (address.empty() || address.length() > 30) {
		throw invalid_argument("Invalid address.");
	}

	this->address = address;
}
