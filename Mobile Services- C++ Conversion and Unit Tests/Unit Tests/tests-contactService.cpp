/**
 * Name        : tests-contactService.cpp
 * Author      : Cody MacLeod
 * Description : A set of tests to ensure the contact service class meets all requirements using Catch2 unit testing framework.
**/
#include "catch.hpp"

#include "ContactService.h"
#include "Contact.h"
#include <stdexcept>
#include <iostream>

TEST_CASE("Testing adding contacts to the contact service.", "[ContactServiceAddContact]") {
	SECTION("Contact is added to the list.") {
		ContactService service = ContactService();
		service.addContact("1", "firstName", "lastName", "1234567890", "address");
		REQUIRE(service.checkContact("1").getContactID() == "1");
	}

	SECTION("Contact must have unique ID to be added.") {
		ContactService service = ContactService();
		service.addContact("1", "firstName", "lastName", "1234567890", "address");
		REQUIRE_THROWS_AS(service.addContact("1", "Contact", "ID", "1234567890", "Not Unique"), std::invalid_argument);
	}
}

TEST_CASE("Testing removing contacts from the task service.", "[ContactServiceRemoveContact]") {
	SECTION("Contact can be removed from list.") {
		ContactService service = ContactService();
		service.addContact("1", "firstName", "lastName", "1234567890", "address");
		service.removeContact("1");
		REQUIRE(service.contactList.size() == 0);
	}
}

TEST_CASE("Testing update functionality for contacts from contact service.", "[ContactServiceUpdateContact]") {
	SECTION("Contact can have it's first name updated.") {
		ContactService service = ContactService(); 
		service.addContact("1", "firstName", "lastName", "1234567890", "address");
		service.updateFirstName("1", "New Name");
		REQUIRE(service.checkContact("1").getFirstName() == "New Name");
	}

	SECTION("Contact can have it's last name updated.") {
		ContactService service = ContactService();
		service.addContact("1", "firstName", "lastName", "1234567890", "address");
		service.updateLastName("1", "New Name");
		REQUIRE(service.checkContact("1").getLastName() == "New Name");
	}

	SECTION("Contact can have it's phone number updated.") {
		ContactService service = ContactService();
		service.addContact("1", "firstName", "lastName", "1234567890", "address");
		service.updatePhoneNumber("1", "0987654321");
		REQUIRE(service.checkContact("1").getPhoneNumber() == "0987654321");
	}

	SECTION("Contact can have it's address updated.") {
		ContactService service = ContactService();
		service.addContact("1", "firstName", "lastName", "1234567890", "address");
		service.updateAddress("1", "New Address");
		REQUIRE(service.checkContact("1").getAddress() == "New Address");
	}
}