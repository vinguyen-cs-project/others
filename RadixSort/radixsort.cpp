/* Vi Nguyen -- EUID: 11300388
* CSCE3110
* HW #5
* Radix Sort
* Version: 5.0
* Date: Apr 20, 2020
*/

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>
#include <chrono>

using namespace std;
using namespace std::chrono;
//convert a digit to type char and match proper base
char decToChar(int x) {
    return char ( (x<10) ? (x + '0') : (x - 10 + 'A'));
}
//convert a digit in type char to type int and base 10
int charToDec(char a) {
    return isalpha(a) ? (a - 'A' + 10) : (a - '0');
}
//find index of max number
int findMax(vector<int> &A) {
    int max = A[0];
    int index = 0;
    for (int i = 1; i < A.size(); i++)
        if (A[i] > max) {
        max = A[i];
            index = i;
        }
    return index;
}
//convert a number to a base
void convertToBase(string &s, int x, int base) {
    while (x > 0) {
        s.push_back(decToChar(x%base));
        x/= base;
    }
    reverse(s.begin(), s.end());
}
//convert a number in string type to base 10
void convertToDec(string &s, int base) {
    int tmp = 0;
    int count = 0;
    for (int i = s.length(); i> 0; i--) {
        int x = charToDec(s.back());
        tmp +=  x * pow(base, count);
        s.pop_back();
        count++;
    }
    s = to_string(tmp);
}
//radix sort strings with same length
void radixSort(vector<string> &arr, int max) {
    const int BUCKETS = 256;
    vector<vector<string>> buckets( BUCKETS );

    for( int pos = max - 1; pos >= 0; --pos )
    {
        for( string & s : arr )
            buckets[ s[ pos ] ].push_back( std::move( s ) );

        int idx = 0;
        for( auto & thisBucket : buckets )
        {
            for( string & s : thisBucket )
                arr[ idx++ ] = std::move( s );

            thisBucket.clear( );
        }
    }}


int main(int argc, char* argv[]) {
    if (argc != 2) cout << "Usage: " << argv[0] << " <base>" << endl;
    else {
        srand(time(NULL)); //seed
        for (int count = 10; count <= 10000; count *= 10) {
            cout << "Radix Sort: base = " << argv[1] << " size = " << count << endl;
            vector<double> run(10); //store all run time
            for (int c = 1; c <= 10; c++) { //run sort 10 times
            vector<int> A; //store random number
            for (int i = 0; i < count; i++) A.push_back(rand()%10000); //create sequence of random number
            vector<string> B; //store random number in proper base
            for (int i = 0; i < count; i++) B.push_back("");
            for (int i = 0; i < count; i++) convertToBase( B[i], A[i], stoi(argv[1]));
            int max = B[findMax(A)].size();
            for (int i = 0; i < count; i++)
                if (B[i].size() != max)
                    for (int j = max - B[i].size(); j >= 0; j--) B[i].insert(0, "0"); //add 'O' to front of numbers to matches all length
            auto start = high_resolution_clock::now();
            radixSort(B, max);
            auto stop = high_resolution_clock::now();
            run[c-1] = duration_cast<nanoseconds>(stop - start).count();
            if (count == 10 && c == 1) { //print output for first run time
                cout << "Unsorted: ";
                for (int i = 0; i <A.size(); i++) cout << A[i] << " ";
                for (int i = 0; i < count; i++) convertToDec( B[i], stoi(argv[1]));
                cout << endl << "Sorted: ";
                for (int i = 0; i < B.size(); i++) cout << B[i] << " ";
                cout << endl << endl;
            }
            printf("Pass %d: %.2f nanoseconds. \n", c, run[c-1]);
            }
            double avg = 0;
            for (int i = 0; i < 10; i++) avg += run[i];
            printf("Average: %.2f nanoseconds. \n\n", (double) avg/10);
        }
    }
    return 0;
}

