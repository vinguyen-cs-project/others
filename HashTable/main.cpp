#include <iostream>

#include "one.h"

using namespace std;

int main() {
  // Print basic group info
  cout << "Project 3 Group 10" << endl;
  cout << "Carlyn Thomsen, Kay Harris, Vi Nguyen, Michael Samatas" << endl << endl;
  // So the tables look right
  cout << left;

  // Read and process everything
  One::read();

  // Finish
  cout << "Processing complete!" << endl;
  return 0;
}
