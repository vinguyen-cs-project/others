## Project Description

For this project, we’re required to detect a deadlock state in a resource allocation graph of which an adjacent matrix is specified by an input file. The format of the input file is specified in InputExample.txt. 
There are two approaches that we can take to solve this: use the graph reduction algorithm or create an algorithm to detect a knot in the graph. The latter approach can be easily implemented, but it has a major drawback as the existence of a knot shows that the graph has deadlock but the lack of a knot doesn’t guarantee that the graph doesn’t have a deadlock state. 
Thus, the first approach was decided upon.

## Project Explanation

To implement the first approach, we first read in the input file and store the number of processes, the number of resources and their units and the matrix accordingly. 
We then process the matrix to get the number of assigned resources and requested resources that each process holds. With this information, we can start the graph reduction algorithm. 
The idea of graph reduction is that for this situation, since all the resources are assigned to processes, if a process requests for resources and this request can be fulfilled based on the number of currently available resources, the system grants this request so the process can be completed.
As it’s completed, the resources that it holds will be returned to the system, so the number of currently available resources will be updated. This will be repeated until all the processes are completed, which indicates a deadlock-free graph, or there’s no longer any process of which requests can be granted, which indicates a deadlock state. 
Applying this to our project, as we have the information of allocated resources and total number of units of each resource, we can easily calculate the number of currently available units (available = total - allocated). We then proceed to implement the rest of the algorithm.

## Project Execution:

- To execute, do: *g++ 4600Project2.cpp*
- To run, do: *a.out*.

The program will prompt the user for the name of the input file. The user can enter its name through their keyboard.

## Discussion:

The advantages of this approach are that it can accurately predict if a graph has a deadlock and points out where this deadlock state happens. It has no disadvantages for this particular project.

## Group member list and contribution:
- Vi Nguyen: design pseudocode for the solution and project report (team leader).
- Huy Le: implement functionalities to read input files
- Kha Nguyen: implement functionalities to read input files
- Desere Crawford: implement functionalities to process data from input files and graph reduction algorithm
- Manasa Nimmagadda: implement functionalities for graph reduction algorithm

