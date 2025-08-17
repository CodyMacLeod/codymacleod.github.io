/**
 * Name        : ContactService.h
 * Author      : Cody MacLeod
 * Description : A header file for class declarations and functions of the Contact Service class.
**/
#pragma once
#include <string>
#include <vector>
#include "Contact.h"

// Setting a table size for default constructor
const unsigned int DEFAULT_SIZE = 128;

/**
 * Declarations for a class to manage a list of contacts.
**/
class ContactService {
private:
	// Creating nodes to store contacts and pointer to next in bucket for hash table
	struct Node {
		Contact contact;
		unsigned int key;
		Node* next;

		// Empty node
		Node() {
			key = UINT_MAX;
			next = nullptr;
		}

		// Node with contact
		Node(Contact inputContact) : Node() {
			contact = inputContact;
		}

		// Node with contact and key
		Node(Contact inputContact, unsigned int inputKey) : Node(inputContact) {
			key = inputKey;
		}
	};

	// A vector to store all the buckets in hash table
	std::vector<Node> nodes;
	unsigned int tableSize;

public:
	// A vector of contacts for sorting alphabetically
	std::vector<Contact> contactList;

	// Constructor and destructors
	ContactService();
	ContactService(unsigned int tablesSize);
	virtual ~ContactService();

	// Methods to create and modify hash table
	unsigned int hash(int key);
	Contact& checkContact(std::string id);
	void addContact(std::string id, std::string firstName, std::string lastName, std::string phoneNumber, std::string address);
	void removeContact(std::string id);

	// Methods to udpate parameters of existing contacts
	void updateFirstName(std::string id, std::string firstName);
	void updateLastName(std::string id, std::string lastName);
	void updatePhoneNumber(std::string id, std::string phoneNumber);
	void updateAddress(std::string id, std::string address);

	// Methods to convert hash table to sort alphabetically
	std::vector<Contact> convertToVector();
	int partition(std::vector<Contact>& contacts, int begin, int end);
	void quickSort(std::vector<Contact>& contacts, int begin, int end);
	std::vector<Contact> organizeAlphabetically();

};
