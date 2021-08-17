## Project Description
This project reads in a file from the user that contains the data of three tables and loads, prints, manipulates, and save them. 
Specifically, it gives the user the ability to insert, update, select, delete, display those tables. 
The user-inputted file contained two types of data: CSV file names and queries. 
The CSV files had to be split up and loaded into the tables while the queries needed to be broken down and actedupon. 
To manage the data and implement these functions, each table required a hash table and a linked list for secondary index, as well as careful orchestration of hashing functions, collision avoidance, comparisons, and lots of pointers. Additionally, this project requires cooperation and communication from all group members to avoid overlap. Details of our works and responsibilities can be found in [our report](https://github.com/vinguyen-cs-project/others/blob/master/HashTable/Project%203%20Report.pdf), which is also included in this directory.

- To compile the program:
  A makefile has been included, so just cd to the project's folder and run 'make'

- To run the program:
  Copy the input file and .csv files into the project folder
  Either execute the generated 'project3' file or use the included 'make run'
  
## Project Tasks
- Kay Harris: create abstract class Table to be used by all functions and read in all tables
- Vi Nguyen: implement the rest of the functions, including creating a hash table and a linked list, for Disability table by using chaining for collision resolution and multiplicative string hashing. 
- Michael Samatas: perform same task as Vi on Geography table using mid-square hashing and quadratic probing to handle collision
- Carlyn Thomsen: perfom same task on Age table using modulo hashing and linear probing to handle collision.


