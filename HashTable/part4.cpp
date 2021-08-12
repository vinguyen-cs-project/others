/* Vi Nguyen CSCE2110.001
* Project 3 Group 10 Part 4
* Disability Table Cpp file
* Multiplicative String Hashing
* Chaining
* Version: 5.0
* Date: Nov 20, 2019
*/
#include "table.h"
#include "part4.h"

#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <iomanip>
#include <fstream>
using namespace std;

disability::disability() : hashTable(10), head(nullptr) {
	scheme = {"geo_name", "hearing_disability", "vision_disability", "cognitive_disability", "ambulatory_disability", "self_care_disability", "independent_living_disability"};
};
disability::~disability() {
	for (Node* current = head; current != nullptr;) {
		Node* next = current->next;
		delete current;
		current = next;
	}
}
disability::Entry::Entry(vector<string>data) : data(data){};
//overloading operator ==
bool disability::Entry::operator==(Entry e) const{ //compare entries
	return *this == e.data;
}
bool disability::Entry::operator==(vector<string> args) const{ //compare entry and data
	if (args.size() != data.size()) return false;
	for (int i = 0; i < data.size(); i++)
		if (args[i] != "*" && data[i] != "*" && args[i] != data[i]) return false;
	return true;
}
//Multiplicative String Hashing function
int disability::hash(string key, int size) {
	unsigned int pos = 0;
	for (int i = 0; i < key.length(); i++) {
		pos = (pos * 2) + key[i];
	}
	return pos%size;
}
//function that converts vector of strings to a string
string disability::toString(vector<string>args) {
	string toS = "(";
	for (int i = 0; i < args.size()-1; i++)
		toS += args[i] + ",";
	return(toS+= args[6] + ")" );
}
//modified select function that returns a vector of entries
vector<disability::Entry> disability::rSelect(vector<string> args) {
	vector<Entry> result;
	if (args[0] != "*") { //check if key is not a star
		int pos = hash(args[0], hashTable.size()); //get the position of list that data will be in
		for (list<Entry>::iterator it = hashTable[pos].begin(); it != hashTable[pos].end(); it++) //loop through this list
			if(*it == args) { //check if found entries that match data
				cout << "Found " << toString(it->data) << " in disability" << endl;
				result.push_back(*it);
			}
	}
	else for (Node* current = head; current!= nullptr; current = current->next) //if key is a star then loop through linked list
		if(*current->entry == args) result.push_back(*current->entry);
    //output messages
	switch (result.size()) {
		case 0:
			cout << "No entries match query " << toString(args) << " in disability" << endl;
			break;
		case 1:
			cout << "Found " << toString(result[0].data) << " in disability" << endl;
			break;
		default:
			cout << "Found entries: " << endl;
			for (int i = 0; i < result.size(); i++)
				cout <<  toString(result[i].data) << " in disability" << endl;
			break;
	}
	return result;
}
//function that inserts data into hash table
void disability::insert(vector<string> args) {
	int pos = hash(args[0], hashTable.size()); //get the position of list that data will be in
	for (list<Entry>::iterator i = hashTable[pos].begin(); i != hashTable[pos].end(); i++) //loop through this list
		if(*i== args) { //check if entry with data already existed
			cout << "Failed to insert " << toString(args) << " into disability" << endl;
			return;
		}
    //otherwise insert data into hash table and linked list
	Node *temp = new Node;
	hashTable[pos].push_back(Entry(args));
	temp->entry = &hashTable[pos].back();
	temp->next = head;
	head = temp;
	cout << "Inserted " << toString(args) << " into disability" << endl;
}
//function that updates an entry in table
void disability::update(vector<string> args) {
	int pos = hash(args[0], hashTable.size()); //get the position of list that data will be in
	for (list<Entry>::iterator i = hashTable[pos].begin(); i != hashTable[pos].end(); i++) //loop through this list
		if(i->data[0] == args[0]) { //check if there is entry that matches data
			i->data = args;
			cout << "Updated " << toString(i->data) << " in disability" << endl;
			return;
		}
	cout << "Failed to update " << toString(args) << " in disability" << endl;
}
//original select function
void disability::select(vector<string> args) {
	vector<Entry> temp = rSelect(args);
}
//function that delete an entry in table
void disability::del(vector<string> args) {
	vector<Entry> result;
	Node* pre = head;
	Node* temp = new Node;
	for (Node* current = head; current!= nullptr;) { //loop through linked list
		if (!(*current->entry == args)) { //if current node does not match data then move on to next one
			pre = current;
			current = current->next;
		}
		else { //if current node matches data
			temp = current;
			current = current->next;
			if (*head->entry == args) head = current; //if head matches data then set head to next node
			else pre->next = current; // else link previous node to next node
			int pos = hash(temp->entry->data[0], hashTable.size());
			Entry e = *temp->entry;
			result.push_back(e);
			hashTable[pos].remove(e); //remove data from hash table
			delete temp; //remove current node
		}
	}
    //output messages
	switch (result.size()) {
		case 0:
			cout << "Failed to delete " << toString(args) << " in disability" << endl;
			break;
		case 1:
			cout << "Deleted " << toString(args) << " in disability" << endl;
			break;
		default:
			cout << "Deleted entries: " << endl;
			for (int i = 0; i < result.size(); i++)
				cout <<  toString(result[i].data) << " in disability" << endl;
			break;
	}
}
//function that display hash table
void disability::display() {
	if (head == nullptr) return;
	vector<int> size {45, 23, 23, 23, 23, 23,30}; //hold size for set width
	cout << endl;
	for (int i = 0; i < size.size(); i++) cout<< setw(size[i]) << scheme[i]; cout << endl;
	for (Node* current = head; current!= nullptr; current = current->next) { //loop through linked list to print output
		int i = 0;
		cout << setw(size[i]) << current->entry->data[i].substr(1, current->entry->data[i].size()-2);
		for (int i = 1; i < size.size(); i++)
			cout<< setw(size[i]) << current->entry->data[i];
		cout << endl;
	}
}
//function that writes to a file
void disability::write() {
	ofstream output ("out_disability.csv");
	if (output.is_open()){
		output << scheme[0] << "\n"; //print key
		for (int i = 0; i < scheme.size(); i++) { //print schemes
			if (i == scheme.size()-1) output << scheme[i] << endl;
			else output << scheme[i] << ",";
		}
		for (Node* current = head; current!= nullptr; current = current->next) { // loop through linked list to write output
			for (int i = 0; i < scheme.size(); i++) {
                if (i == scheme.size()-1) output << current->entry->data[i] << endl;
				else output << current->entry->data[i] << ",";
			}
		}
		output.close();
	}
	else cout << "Unable to open output file" << endl;
}
//bonus function
void disability::bonus(vector<string> args, vector<string> cols) {
	vector<int> size {45, 23, 23, 23, 23, 23,30}; //hold size for set width
	vector<Entry> entries = rSelect(args);
	for (int i = 0; i < entries.size(); i++)
		for (int j = 0; j < cols.size(); j++)
			for (int k = 0; k < scheme.size(); k++)
				if (cols[j] == scheme[k]) cout << setw(size[k]) << scheme[k]; //only print schemes that listed in cols
	cout << endl;
	for (int i = 0; i < entries.size(); i++) {
		for (int j = 0; j < cols.size(); j++)
			for (int k = 0; k < scheme.size(); k++)
				if (cols[j] == scheme[k]) { //print cols
					if (k == 0) cout << setw(size[k]) << entries[i].data[k].substr(1, entries[i].data[k].size()-2);
					else cout << setw(size[k]) << entries[i].data[k];
				}
		cout << endl;
	}
}
