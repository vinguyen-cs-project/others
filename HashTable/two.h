/**************************
 * Michael Smaatas
 * two header file
**************************/


#ifndef two_h
#define two_h
#include <vector>
#include <regex>
#include <list>
#include "table.h"

class Two : public Table {
	private:
		struct Entry{
			string replan_id, geo_name, geo_stusab, geo_sumlev, geo_state, geo_county, geo_geoid, population;
			bool isEmpty = true;
			bool operator == (const vector<string>& vec) const;
			bool operator == (Entry const &obj) const;
			void GetEntry(vector<string> args);
		};
		struct Node{
			Entry* entry;
			Node* Next;
		};
		vector<list<Entry>> hashList;
		Node *head;
		Node *tail;
		vector<Entry> hashMap;
		vector<Entry> rSelect(vector<string> args);
		int size;
		void print(int pos);
		void print(vector<string> args);
	public:
		Two();
		~Two();
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
