/**
 * Name        : tests-contact.cpp
 * Author      : Cody MacLeod
 * Description : A set of tests to ensure the contact class meets all requirements using Catch2 unit testing framework.
**/
#include "catch.hpp"

#include "Contact.h"
#include <stdexcept>

TEST_CASE("Testing setter methods for contacts", "[ContactSetter]") {
	Contact contact = Contact("1", "firstName", "lastName", "1234567890", "address");
	REQUIRE(contact.getContactID() == "1");
	REQUIRE(contact.getFirstName() == "firstName");
	REQUIRE(contact.getLastName() == "lastName");
	REQUIRE(contact.getPhoneNumber() == "1234567890");
	REQUIRE(contact.getAddress() == "address");
}

TEST_CASE("Testing to ensure the contact ID meets requirements.", "[ContactID]") {
	SECTION("ID must be filled in.") {
		CHECK_THROWS_AS(Contact("", "firstName", "lastName", "1234567890", "address"), std::invalid_argument);
	}

	SECTION("ID cannot be longer than 10 characters.") {
		CHECK_THROWS_AS(Contact("123456890000", "firstName", "lastName", "1234567890", "address"), std::invalid_argument);
	}
}

TEST_CASE("Testing to ensure the contacts first name meets requirements.", "[ContactFirstName]") {
	SECTION("First name has to be filled in.") {
		CHECK_THROWS_AS(Contact("1", "", "lastName", "1234567890", "address"), std::invalid_argument);
	}
	
	SECTION("First name cannot be larger than 10 characters.") {
		CHECK_THROWS_AS(Contact("2", "This is way too many characters", "lastName", "1234567890", "address"), std::invalid_argument);
	}
}

TEST_CASE("Testing to ensure contacts last name meets requirements.", "[ContactLastName]") {
	SECTION("Last name has to be filled in.") {
		CHECK_THROWS_AS(Contact("1", "firstName", "", "1234567890", "address"), std::invalid_argument);
	}

	SECTION("Last name cannot be larger than 10 characters.") {
		CHECK_THROWS_AS(Contact("2", "firstName", "This is way too many characters", "1234567890", "address"), std::invalid_argument);
	}
}

TEST_CASE("Testing to ensure contacts phone number meets requirements.", "[ContactPhoneNumber]") {
	SECTION("Phone number has to be filled in.") {
		CHECK_THROWS_AS(Contact("1", "firstName", "lastName", "", "address"), std::invalid_argument);
	}

	SECTION("Phone number has to be exactly 10 characters.") {
		CHECK_THROWS_AS(Contact("2", "firstName", "lastName", "12", "address"), std::invalid_argument);
	}
}

TEST_CASE("Testing to ensure contacts address meets requirements.", "[ContactAddress]") {
	SECTION("Address has to be filled in.") {
		CHECK_THROWS_AS(Contact("1", "firstName", "lastName", "1234567890", ""), std::invalid_argument);
	}

	SECTION("Address cannot be larger than 30 characters.") {
		CHECK_THROWS_AS(Contact("2", "firstName", "lastName", "1234567890", "This address is much longer than 30 characters"), std::invalid_argument);
	}
}
