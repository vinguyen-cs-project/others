/* Vi Nguyen CSCE2110.001
 * Project 3 Group 10 Part 4
 * Disability table header file
 * Multiplicative String Hashing
 * Chaining
 * Version: 4.0
 * Date: Nov 20, 2019, 2019
 */
#ifndef PART4_H
#define PART4_H

#include "table.h"

#include <vector>
#include <string>
#include <list>
using namespace std;

class disability : public Table {
	private:
		struct Entry {
			vector<string> data;
			Entry(vector<string> data);
			bool operator==(vector<string> args) const;
			bool operator==(Entry e) const;
		};
		struct Node {
			Entry* entry;
			Node* next;
		};
		vector<list<Entry>> hashTable;
		Node *head;
		vector<string> scheme;
		int hash(string key, int size);
		string toString(vector<string> args);
		vector<Entry> rSelect(vector<string> args);
	public:
		disability();
		~disability();
		void insert(vector<string> args);
		void update(vector<string> args);
		void select(vector<string> args);
		void del(vector<string> args);
		void display();
		void write();
		void bonus(vector<string> args, vector<string> cols);
};
#endif
