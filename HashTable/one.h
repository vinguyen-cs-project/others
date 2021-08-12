/************************************************
 * Kay Harris
 * kayharris2@my.unt.edu
 * CSCE 2110.001 Project 3 Group 10
 * One Header File
************************************************/

#ifndef one_h
#define one_h

#include <string>
#include <vector>
#include <regex>

using namespace std;

class One {
  private:
    static regex query, splitter;
    static vector<string> split(string line);
  public:
    static void read();
};

#endif
