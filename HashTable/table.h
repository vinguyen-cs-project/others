/************************************************
 * Kay Harris
 * kayharris2@my.unt.edu
 * CSCE 2110.001 Project 3 Group 10
 * Table Header File
************************************************/

#ifndef table_h
#define table_h

#include <string>
#include <vector>

using namespace std;

class Table {
  public:
    virtual ~Table() {};
    virtual void insert(vector<string> args) = 0;
    virtual void update(vector<string> args) = 0;
    virtual void select(vector<string> args) = 0;
    virtual void del(vector<string> args) = 0;
    virtual void display() = 0;
    virtual void write() = 0;
    virtual void bonus(vector<string> args, vector<string> cols) = 0;
};

#endif
