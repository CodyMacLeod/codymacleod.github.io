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

using namespace std;

/**
 * Default constructor
**/
ContactService::ContactService()
{
	tableSize = DEFAULT_SIZE;
	nodes.resize(tableSize);
	
}

/**
 * Constructor to modify size of hash table
**/
ContactService::ContactService(unsigned int size) 
{
	this->tableSize = size;
	nodes.resize(tableSize);
}

/**
 * Destructor to remove contacts from program
**/
ContactService::~ContactService() 
{
	nodes.erase(nodes.begin());
}

/**
 * Calculate the hash value of a given key.
 *
 * @return The calculated hash
 */
unsigned int ContactService::hash(int key)
{
	return key % tableSize;
}

/**
 * Searching through our hash table to find a specific contact by 
 * unique contact ID.
 *
 * @return Reference to contact within hash table
 */
Contact& ContactService::checkContact(string id)
{
	Contact contact;

	// Creating a key
	unsigned key = hash(atoi(id.c_str()));
	
	// Checking if node exists at key
	Node* node = &(nodes.at(key));

	// If node matching key does exist, return the contact
	if (node != nullptr && node->key != UINT_MAX && node->contact.getContactID().compare(id) == 0) {
		return node->contact;
	}

	// If a node matching key does not exist, return empty contact
	if (node == nullptr || node->key == UINT_MAX) {
		return contact;
	}

	// walk through chaining
	while (node != nullptr) {
		// if current node matches return it
		if (node->key != UINT_MAX && node->contact.getContactID().compare(id) == 0) {
			return node->contact;
		}

		//setting to next node
		node = node->next;
	}

	return contact;
}

/**
 * Adding a new contact to the hash table as long as it has a unique contact ID.
 */
void ContactService::addContact(string id, string firstName, string lastName, string phoneNumber, string address)
{
	// Calculate key for the contact and check if bucket already exists
	unsigned key = hash(atoi(id.c_str()));
	Node* existingNode = &(nodes.at(key));

	// Attempt to create contact
	Contact contact = Contact(id, firstName, lastName, phoneNumber, address);

	// If node doesn't already exist
	if (existingNode == nullptr) {
		Node* newNode = new Node(contact, key);
		nodes.insert(nodes.begin() + key, (*newNode));
	}
	else {
		// If node exists but isn't being used
		if (existingNode->key == UINT_MAX) {
			existingNode->key = key;
			existingNode->contact = contact;
			existingNode->next = nullptr;
		}
		else {
			// Ensure contact ID is unique
			if (existingNode->contact.getContactID() == id) {
				throw invalid_argument("Contact ID already exists.");
			}
			// Walk through the chain to find next opening
			while (existingNode->next != nullptr) {
				// Ensure contact ID is not already being used
				if (existingNode->contact.getContactID() == id) {
					throw invalid_argument("Contact ID already exists.");
				}

				existingNode = existingNode->next;
			}

			// Adding the contact to the end of the bucket
			existingNode->next = new Node(contact, key);
		}
	}
}

void ContactService::removeContact(string id)
{
	// calculate the key of node to remove
	int key = hash(atoi(id.c_str()));

	// Remove from hash table
	nodes.erase(nodes.begin() + key);
}


/**
 * A method to update the first name of the contact.
**/
void ContactService::updateFirstName(string id, string firstName)
{
	// Getting reference to contact if it exists
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
	// Getting reference to contact if it exists
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
	// Getting reference to contact if it exists
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
	// Getting reference to contact if it exists
	Contact& contact = checkContact(id);
	if (contact.getContactID() == id) {
		// Updating address
		contact.setAddress(address);
	}
}

/**
 * A method to go through the hash table and store all contacts
 * into a vector that to more efficiently quick sort through to
 * sort all contacts alphabetically.
 * 
 * @return A vector of all contacts from the hash table
**/
vector<Contact> ContactService::convertToVector() {
	vector<Contact> contactList;

	// Loop through the nodes of the hash table
	for (unsigned int i = 0; i < tableSize; ++i) {
		// Set the current node
		Node* node = &nodes.at(i);

		// Ensuring the node has been changed from default values
		if (node->key != UINT_MAX) {
			// Adding contact to vector
			contactList.push_back(node->contact);
		}

		// Continue through other nodes in buckets due to collisions
		while (node->next != nullptr) {
			// Progress to next node
			node = node->next;
			contactList.push_back(node->contact);
		}
	}

	return contactList;
}

/**
 * A method to to partition the vector into lower and higher halves.
 * 
 * @return Ending index of partition
**/
int ContactService::partition(vector<Contact>& contacts, int begin, int end) {
	// Variable declarations and initializations
	bool done = false;
	int low = begin;
	int high = end;

	// Calculate the middle element in contact vector
	int middlePoint = low + (high - low) / 2;

	// Setting the middle element as pivot point
	Contact pivot = contacts.at(middlePoint);

	// Continue looping until we finish sorting
	while (!done) {
		// Increase lower bound until we find pivot
		while (contacts[low].getFirstName() < pivot.getFirstName()) {
			low += 1;
		}

		// Decrease the upper bound until we find pivot
		while (pivot.getFirstName() < contacts[high].getFirstName()) {
			high -= 1;
		}

		// Checking to see if we are fully sorted
		if (low >= high) {
			done = true;
		}
		// Swapping at the lower and upper bounds then tightening bounds on both sides
		else {
			swap(contacts[low], contacts[high]);
			low += 1;
			high -= 1;
		}
	}

	return high;
}

/**
 * A method to perform a quick sort on list of contacts to sort alphabetically by first name.
 * Average performance: O(n log(n))
 * Worst case performance: O(n^2)
**/
void ContactService::quickSort(vector<Contact>& contacts, int begin, int end) {
	int mid = 0;

	// Checking if vector is already sorted
	if (begin >= end) {
		return;
	}

	// Get midpoint from last element in lower half
	mid = partition(contacts, begin, end);

	// Recursively sort low partition
	quickSort(contacts, begin, mid);

	// Recursively sort high partition
	quickSort(contacts, mid + 1, end);
}

/**
 * A method to return the alphabetically organized list of contacts.
 * 
 * @return A vector of contacts sorted alphabetically
**/
vector<Contact> ContactService::organizeAlphabetically() {
	vector<Contact> contactList = convertToVector();
	
	// Sort alphabetically
	quickSort(contactList, 0, contactList.size() - 1);
	
	return contactList;
}