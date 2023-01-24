# CS225-Final-project

### The final project in UIUC Fall 2022

## Leading Question 

Our group decided to do the project "Open flight". Our goal is to find the most convenient path and the most important airport based on the given data. Throughout this final project, we used BFS, Dijkstra's algorithm, and PageRank to achieve our goal.

   
## Document

Our team contract, team proposal and FP_Log can be find in [`/document`](https://github.com/2476327115/CS225-Final-project/tree/main/Document) directory.

## Deliverables
All code we have done can be found in [`/src`](https://github.com/2476327115/CS225-Final-project/tree/main/src)

Report: https://github.com/2476327115/CS225-Final-project/blob/main/result.md

Presentation Video: https://youtu.be/23VsYPCS8CU

Presentation Slides: https://github.com/2476327115/CS225-Final-project/blob/main/Final%20Project.pdf

## Dataset Acquisition

We use data of airport and route:


https://raw.githubusercontent.com/jpatokal/openflights/master/data/airports.dat
https://raw.githubusercontent.com/jpatokal/openflights/master/data/routes.dat

which can be find in [`/data`](https://github.com/2476327115/CS225-Final-project/tree/main/data) directory.

## How to run the program
The program can be ran by using the 'main' executable:
```
make main
./main
```
The user would be prompted with instructions on how to run the various operations:
```
[0] Use BFS to traverse all the graph
[1] Use BFS to find shortest path between two airports
[2] Use Dijkstra to find shortest path between two airports
[3] Use pagerank to find the most important airport in the dataset
[4] Use pagerank to find the most important airport in a given range
[9] Quit
```  
The operations may require the user to provide custom inputs i.e. airport ID.  
After computation, the result would be printed out in the terminal.  


## Test Description
Our testcase can be found in [`/tests`](https://github.com/2476327115/CS225-Final-project/tree/main/tests) 

Our tests can be run with
```
make test
./test
```  

## Timeline

Data acquisition and processing (due: 11.6)

Design openflight algorithms and write all the preliminary code except the algorithm(due: 11.13)

Write BFS and Dijkstra’s Algorithm(due: 11.20)

Write Page Rank algorithm and other code completely(due: 11.27)

Write descriptive README and final report(due: 12.4)

Project close-out, inspection and final presentation(due: 12.8)

## Team
- Jin Fan (jinf2)
- Gezhi Zou (gezhiz2)
- Xiaoyang Tian (xt12)
- Yanxin Jiang (yanxinj2)
