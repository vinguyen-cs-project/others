/************************************************
 * Carlyn Thomsen
 * CarlynThomsen@my.unt.edu
 * CSCE 2110.001 Project 3 Group 10
 * Part 3 .cpp File
************************************************/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <regex>
#include <string>
#include <vector>
#include <list>
#include "table.h"

#include "part3.h"

using namespace std;

part3::part3() : hashMap(10), size(10)
{
	//constructor
	head = NULL;
	tail = NULL;
}


part3::~part3()
{
	//deconstructor
	for (Node* current = head; current != nullptr;)
	{
		Node* next = current->next;
		delete current;
		current = next;
	}

}

int part3::hashf(string key)	//hash function using Modulo Hashing
{
	key = key.substr(7);
	return stoi(key) % size;
}
void part3::insert(vector<string> args)
{
	int pos = hashf(args[0]);//sets pos to value returned by hash function
	int probed = 0;

	//searches through hash function
	while (probed < hashMap.capacity())
	{
		if(hashMap[pos].isEmpty)	//if a spot is open
		{
			//sets args to spot
			hashMap[pos].geoid = args[0];
	 		hashMap[pos].under5 = stoi(args[1]);
	 		hashMap[pos].under18 = stoi(args[2]);
	 		hashMap[pos].over65 = stoi(args[3]);
	 		hashMap[pos].isEmpty = false;
	 		cout << "Inserted: (" << hashMap[pos].geoid << ", " << hashMap[pos].under5 << ", " << hashMap[pos].under18 << ", " << hashMap[pos].over65 << ") in Age. " << endl;

	 		//sets spot to value with linked list
	 		Node *temp = new Node;
            temp->entry = &hashMap[pos];
			temp->next = NULL;
			if(head == NULL && tail == NULL)
      		{
        		head = temp;
        		tail = temp;
      		}
      		else
      		{
        		tail->next = temp;
        		tail = temp;
      		}
	 		return;
	 	}
	 	else if(args[0] == hashMap[pos].geoid)	//displayes if failed to insert
	 	{
	 		cout << "Failed to Insert: (" << args[0] << ", " << args[1] << ", " << args[2] << ", " << args[3] << ") in Age." << endl;
	 		return;
	 	}
	 	pos = (pos + 1) % size;
	 	probed++;
	}
	//table is full and must add more space
	size = size * 2;
	vector<Entry> hashArray(size);
	for(int i = 0; i < size; i++)
	{
		if(hashMap[i].isEmpty == false)
		{
	 		int tmp = hashf(hashMap[i].geoid);
	 		hashArray[tmp].geoid = hashMap[i].geoid;
	 		hashArray[tmp].under5 = hashMap[i].under5;
		 	hashArray[tmp].under18 = hashMap[i].under18;
	 		hashArray[tmp].over65 = hashMap[i].over65;
	 		hashArray[tmp].isEmpty = false;
	 	}
	}
	hashMap = hashArray;
	insert(args);
	return;
}

void part3::update(vector<string> args)
{
	int probed = 0;
	int pos = hashf(args[0]);
	bool exists = false;

	while (probed < hashMap.capacity())	//searches through hash table
	{
		if(args[0] == hashMap[pos].geoid)
		{
			exists = true;
			cout << "Updated: (" << args[0] << ", " << args[1] << ", " << args[2] << ", " << args[3] << ") in Age." << endl;
				//updates values
				hashMap[pos].geoid = args[0];
				hashMap[pos].under5 = stoi(args[1]);
				hashMap[pos].under18 = stoi(args[2]);
				hashMap[pos].over65 = stoi(args[3]);
				hashMap[pos].isEmpty = false;
		 	}

	 	pos = (pos + 1) % size;	//linear probing
	 	probed++;
	}
	if(exists == false)
	{
		//displays to user if failed to update
	 	cout << "Failed to Update: (" << args[0] << ", " << args[1] << ", " << args[2] << ", " << args[3] << ") in Age." << endl;
	}
}

vector<part3::Entry> part3::rSelect(vector<string> args)
{
	vector<Entry> result;	//result vector for bonus
	int tableSize = hashMap.size();
	int numMatches = 0;
	bool matched = false;
	vector<string> rowMatches;

	if(args[0] == "*")
	{
		Node *current = head;
		//searches linked list for a match
		while(current != NULL)
		{
			//searches for a match
			if((args[0] == current->entry->geoid || args[0] == "*") && ( args[1] == "*" || stoi(args[1]) == current->entry->under5) && (args[2] == "*" || stoi(args[2]) == current->entry->under18) && (args[3] == "*" || stoi(args[3]) == current->entry->over65))
			{
				matched = true;
				result.push_back(*current->entry); //push data to vector for bonus
				rowMatches.push_back(current->entry->geoid + to_string(current->entry->under5) + ", " + to_string(current->entry->under18) + " ," + to_string(current->entry->over65));
			}
			current = current->next;
		}

	}
	else // got through hash table like normal
	{
		for(int i = 0; i < tableSize; i++)
		{
			//searches for a match
			if((args[0] == hashMap[i].geoid || args[0] == "*") && ( args[1] == "*" || stoi(args[1]) == hashMap[i].under5) && (args[2] == "*" || stoi(args[2]) == hashMap[i].under18) && (args[3] == "*" || stoi(args[3]) == hashMap[i].over65))	//fix with stars!
			{
	 			matched = true;
	 			cout << "Found: (" << args[0] << ", " << args[1] << ", " << args[2] << ", " << args[3] << ") in Age." <<  endl;
	 			result.push_back(hashMap[i]);
	 			numMatches++;
	 			rowMatches.push_back(hashMap[i].geoid + "," + to_string(hashMap[i].under5) + ", " + to_string(hashMap[i].under18) + " ," + to_string(hashMap[i].over65));
	 		}
	 	}
	}
	if(matched == false)	//if no matches matched the query
	{
		cout << "No entries match query: (" << args[0] << ", " << args[1] << ", " << args[2] << ", " << args[3] << " in Age." << endl;
	}

	return result;
}
void part3::select(vector<string> args)
{
	vector<Entry> temp = rSelect(args);
}

void part3::del(vector<string> args)
{
	int probed = 0;
	int numMatches = 0;
	//if it matches
	bool isSame = false;
	bool matched = false;
	vector<string> rowMatches;

	Node *current = head;
	Node *temp = NULL;
		//goes through the linked-list to search for a match and delete
	while(current != NULL)	//goes through linked list
	{
		//searches for a match
		if((args[0] == current->entry->geoid || args[0] == "*") && ( args[1] == "*" || stoi(args[1]) == current->entry->under5) && (args[2] == "*" || stoi(args[2]) == current->entry->under18) && (args[3] == "*" || stoi(args[3]) == current->entry->over65))
		{
			matched = true;
			current->entry->isEmpty = true;
			rowMatches.push_back(current->entry->geoid + ", " + to_string(current->entry->under5) + ", " + to_string(current->entry->under18) + " ," + to_string(current->entry->over65));

			if(current == head && current == tail)
			{
				current->entry->isEmpty = true;
				delete current;
				head = NULL;
				tail = NULL;
				break;
			}
			else if(current == head)
			{
				current->entry->isEmpty = true;
				temp = current;
				current = current->next;
				delete temp;
				head = current;
			}
			else if (current == tail)
			{
				current->entry->isEmpty = true;
				tail = temp;
				temp->next = NULL;
				delete current;
				break;
			}
			else
			{
				current->entry->isEmpty = true;
				temp->next = current->next;
				delete current;
				current = temp->next;
			}
		}
		else
		{
			temp = current;
			current = current->next;
		}
	}

	if(matched == false)	//if no entries match the query
	{
		cout << "No entries match query: (" << args[0] << ", " << args[1] << ", " << args[2] << " ," << args[3] << " from Age." << endl;
	}
	else
	{	//displays to user the deleted entries
		cout << "Deleted Entries:" << endl;
		for(int i = 0; i < rowMatches.size(); i++)
		{
			cout << "(" << rowMatches.at(i) << ") from Age." << endl;
		}
	}
}

void part3::display()	//PASSES ALL TESTS
{
	Node *current = head;
	Node *temp = NULL;
	//displays data sections
	cout << setw(20) << "geo_geoid";
	cout << setw(20) << "under_5";
	cout << setw(20) << "under_18";
	cout << setw(20) << "over_65" << endl;

	if (head == nullptr)
		return;

	for (Node* current = head; current!= nullptr; current = current->next)
	{ //loop through linked list to print output
		cout << setw(20) << current->entry->geoid;
		cout << setw(20) << current->entry->under5;
		cout << setw(20) << current->entry->under18;
		cout << setw(20) << current->entry->over65;
		cout << endl;
	}

}

void part3::write()	//writes information to an output file!!
{
	ofstream out("out_age.csv");

	if(out.is_open())	//checks that the file opens
	{
		Node *current = head;
		Node *temp = NULL;
		//displays data sections
		out << "geo_geoid" << endl;
		out << "geo_geoid,";
		out << "under_5,";
		out << "under_18,";
		out << "over_65" << endl;

		if (head == nullptr)
			return;

		for (Node* current = head; current!= nullptr; current = current->next)
		{ //loop through linked list to print output
			out << current->entry->geoid << ",";
			out << current->entry->under5 << ",";
			out << current->entry->under18 << ",";
			out << current->entry->over65;
			out << endl;
		}
	}
	else
	{	//informs the user if the file fails to open
		out << "Unable to open output file" << endl;
	}
	out.close();	//closes output file

}

void part3::bonus(vector<string> args, vector<string> cols)
{
	vector<Entry> temp = rSelect(args);
	string scheme[] = { "geo_geoid", "under_5", "under_18", "over_65" };

	for (int j = 0; j < 4; j++)
		for (int k = 0; k < cols.size(); k++)
			if (scheme[j] == cols[k])
				cout << setw(20) << scheme[j];
	cout << endl;
	for (int i = 0; i < temp.size(); i++) {
		for (int j = 0; j < 4; j++)
			for (int k = 0; k < cols.size(); k++)
				if (scheme[j] == cols[k]) switch (j) {
					case 0: cout << setw(20) << temp[i].geoid; break;
					case 1: cout << setw(20) << temp[i].under5; break;
					case 2: cout << setw(20) << temp[i].under18; break;
					case 3: cout << setw(20) << temp[i].over65; break;
				}
		cout << endl;
	}
	cout << endl;
}
