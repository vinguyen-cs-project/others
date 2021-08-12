/************************************************
 * Kay Harris
 * kayharris2@my.unt.edu
 * CSCE 2110.001 Project 3 Group 10
 * One Cpp File
************************************************/

#include <iostream>
#include <fstream>

#include "one.h"
#include "table.h"
#include "two.h"
#include "part3.h"
#include "part4.h"

// Regex to parse the queries
regex One::query("(.+?)\\((?:\\(([^\\)]+)\\),([^\\)]+)(?:\\),(.+))?)?\\)");
// Designed to handle all three cases: WRITE/DISPLAY(), MOST((2),3), PROJECT(SELECT((2),3),4)
// instr + '(' + check for:
//   '(' + tuple + '),' + name + check for:
//     '),' + bonus
// + ')'

// Regex to find the first item in a tuple
regex One::splitter("(\"[^\"]+\"|[^,]+),?(.*)");
// first word in the tuple (checking for quotes) + ignore a comma + get the rest of the line

void One::read() {
  // Construct the Tables
  Two two; part3 three; disability four;
  // Provide an easy, compact way to look the Tables up by name via lambda
  auto table = [&](string name) -> Table* {
    if (name == "geography") return &two;
    else if (name == "age") return &three;
    else if (name == "disability") return &four;
    else return nullptr;
  };

  // Ask the user for an input file and open it
  string infile;
  cout << "Please enter the main file's name:";
  getline(cin, infile);
  ifstream input(infile);

  // Read each CSV file
  for (int i = 0; i < 3; i++) {
    // Read the file name and table name
    string csvfile, name, line;
    input >> csvfile >> name;
    // Print out the processing alert
    cout << csvfile << " " << name << endl;
    cout << "Processing " << name << " table." << endl;
    // Open the file
    ifstream csv(csvfile);
    // Discard the key and scheme (I tried to give it to the others but they didn't want it T^T)
    getline(csv, line); getline(csv, line);
    // Insert the rest of the CSV file into the right Table
    for (getline(csv, line); !csv.eof(); getline(csv, line)) table(name)->insert(split(line));
  }

  // Parse all the queries
  string line; smatch match;
  getline(input, line); getline(input, line); // Ignore line break and empty line
  for (getline(input, line); !input.eof(); getline(input, line)) {
    // Parse out the instruction (1), tuple (2), table name (3), and bonus tuple (4)
    regex_match(line, match, query);
    // Find a matching instruction, get the right Table(s), and pass in the tuple(s) in an easy-to-read format
    if (match[1] == "INSERT") table(match[3])->insert(split(match[2]));
    else if (match[1] == "UPDATE") table(match[3])->update(split(match[2]));
    else if (match[1] == "SELECT") table(match[3])->select(split(match[2]));
    else if (match[1] == "DELETE") table(match[3])->del(split(match[2]));
    else if (match[1] == "DISPLAY") { cout << "DISPLAY" << endl; two.display(); three.display(); four.display(); }
    else if (match[1] == "WRITE") { cout << "WRITE" << endl; two.write(); three.write(); four.write(); }
    else if (match[1] == "PROJECT(SELECT") table(match[3])->bonus(split(match[2]), split(match[4]));
    else cout << "Cannot find instr \"" << match[1] << "\"" << endl;
  }
}

vector<string> One::split(string line) {
  // Split a tuple into a vector by repeatedly finding and removing the first item
  vector<string> out;
  // result[1] is the first item, result[2] is everything after it
  for (smatch result; regex_match(line, result, splitter); line = result[2]) out.push_back(result[1]);
  return out;
}
