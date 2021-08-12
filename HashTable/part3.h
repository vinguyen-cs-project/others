/************************************************
 * Carlyn Thomsen
 * CarlynThomsen@my.unt.edu
 * CSCE 2110.001 Project 3 Group 10
 * Part 3 Header File
 -- Hashing Function = Modulo Hashing --
 -- Collision Strategy = Linear Probing --
************************************************/
#ifndef part3_h
#define part3_h

#include <iostream>
#include <fstream>
#include <iomanip>
#include <regex>
#include <string>
#include <vector>
#include <list>
#include "table.h"

using namespace std;

class part3: public Table
{
private:
	struct Entry {
		string geoid;
		int under5, under18, over65;
		bool isEmpty = true;
	};
	struct Node {
			Entry* entry;
			Node* next;
	};
	vector<list<Entry>> hashList;
	Node *head;
	Node *tail;
	vector<string> scheme;
	vector<Entry> rSelect(vector<string> args);
	vector<Entry> hashMap;	//hash table
	int size;
public:

	part3();
	~part3();

	int hashf(string key);

	void insert(vector<string> args);
	void update(vector<string> args);

	void select(vector<string> args);
	void del(vector<string> args);
	void display();
	void write();
	void bonus(vector<string> args, vector<string> cols);

};

#endif
