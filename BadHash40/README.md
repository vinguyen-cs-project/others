This work was done by Farhan Almufleh, Tanvi Mehta and Vi Nguyen. Vi wrote the pseudocode while Farhan and Tanvi implemented it.


## Project Task

Write a program that runs the birthday attack against a hash function defined next. This hash function is called “BadHash40” – it is constructed using SHA256 as a subroutine. 
Specifically, BadHash40(x) := SHA256(x)[1..40], i.e., it takes the first 40 bits of the output of SHA256. Our task was to find two (arbitrary) inputs to the function BadHash40 which result in the same output, i.e., to find a collision for BadHash40. 
Our program must compute such the two inputs and the corresponding output for BadHash40 and use the hex format when reporting all these values.

## Program Description

Our birthday attack will only need to run at most two times before it detects a collision in BadHash40. Each time it runs, it will generate 2^20 random messages with size in the range of [0...256] bits. 
This is because the output of BadHash40 will be 40 bits in size. Our program will use BadHash40 on the random messages to get encrypted messages, then it will store the inputs and outputs to a 2D array. 
Then it will perform heap sort on the second row of the array, which stores the output. Finally, it will look for duplicate outputs in the array and print them to the console along with their inputs. 
The array also gets written into a “hash.txt” file.
  
To run and compile, do *python solution.py*.

## Output

<img src="https://user-images.githubusercontent.com/70772170/129392947-e11fdb9d-cc70-4949-b8c6-463ca2a6107b.png" width="500" height="250">


