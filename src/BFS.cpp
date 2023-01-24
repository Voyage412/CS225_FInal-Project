#include "BFS.h"
#include "Graph.h"
#include <vector>
#include <unordered_map>
#include <queue>
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
using namespace std;
typedef std::pair<int, int> PAP; // pair path
BFS::BFS(const Graph &graph)
{
    airport_graph_ = graph;
    number = airport_graph_.getAirportNum();
}

std::vector<int> BFS::traverseAll(const Graph &graph, int srcID)
{
    
    std::map<int, bool> visited; // create map to record visited vertices   
    vector<int> airports; // the return vector
    std::queue<int> BFS_queue; //create queue for BFS
    matrix_ = airport_graph_.getAdjacency_matrix(); // get unordered map adjacency_matrix of the graph 

    // Check whether the source airport is valid. If not, return the empty vector and warn that 
    // "Airport isn't found!!!" on the terminal
    if(matrix_.find(srcID) == matrix_.end()) {
        std::cout << "Airport isn't found!!!" << std::endl;
        return airports;
    }

    visited[srcID] = true; //mark index srcId as "visited", change false to true
    BFS_queue.push(srcID);//enqueue the srcID as start
    airport_graph_ = graph; // get graph
    
    
    while (!BFS_queue.empty())
    {
        srcID = BFS_queue.front(); //start from the front of the queue
        airports.push_back(srcID); // push the vertex into return vector
        BFS_queue.pop(); // Dequeue this vertex from queue

        for (auto it : matrix_[srcID]) // Get all the adjacent vertices of that dequeued vertex. 
        {
            if (visited.find(it.first) == visited.end())
            {
                visited[it.first] = true; //if there are adjacent vertices that haven't been visited, mark it as "visited"
                BFS_queue.push(it.first);//and enqueue it
            }
        }
    }
    return airports; //return vector
}

std::vector<int> BFS::traverse_with_given_step(const Graph &graph, int srcID, int step)
{
    
    std::map<int, bool> visited; // create map to record visited vertices   
    vector<int> airports; // the return vector
    std::queue<int> BFS_queue; //create queue for BFS
    matrix_ = airport_graph_.getAdjacency_matrix(); // get unordered map adjacency_matrix of the graph 

    // Check whether the source airport is valid. If not, return the empty vector and warn that 
    // "Airport isn't found!!!" on the terminal
    if(matrix_.find(srcID) == matrix_.end()) {
        std::cout << "Airport isn't found!!!" << std::endl;
        return airports;
    }

    visited[srcID] = true; //mark index srcId as "visited", change false to true
    BFS_queue.push(srcID);//enqueue the srcID as start
    airport_graph_ = graph; // get graph
    
    int count = 0;
    
    while (!BFS_queue.empty() && count < step)
    {
        srcID = BFS_queue.front(); //start from the front of the queue
        airports.push_back(srcID); // push the vertex into return vector
        count++;
        BFS_queue.pop(); // Dequeue this vertex from queue

        for (auto it : matrix_[srcID]) // Get all the adjacent vertices of that dequeued vertex. 
        {
            if (visited.find(it.first) == visited.end())
            {
                visited[it.first] = true; //if there are adjacent vertices that haven't been visited, mark it as "visited"
                BFS_queue.push(it.first);//and enqueue it
                
            }
        }
    }
    return airports; //return vector
}


 std::vector<int> BFS::traverse_with_dest(const Graph &graph, int srcID, int destID)
 {   
    

    std::map<int, bool> visited; // create map to record visited vertices   
    std::vector<int> airports; // the return vector
    std::queue<int> BFS_queue; //create queue for BFS
    matrix_ = airport_graph_.getAdjacency_matrix(); // get unordered map adjacency_matrix of the graph 
    
    // Check whether the source airport is valid. If not, return the empty vector and warn that 
    // "Airport isn't found!!!" on the terminal
    if(matrix_.find(srcID) == matrix_.end()) {
        std::cout << "Airport isn't found!!!" << std::endl;
        return airports;
    }

    visited[srcID] = true; //mark index srcId as "visited", change false to true
    BFS_queue.push(srcID);//enqueue the srcID as start
    airport_graph_ = graph; // get graph
    
    
        
    while (!BFS_queue.empty())
    {
        srcID = BFS_queue.front(); //start from the front of the queue
        airports.push_back(srcID); // push the vertex into return vector
        BFS_queue.pop(); // Dequeue this vertex from queue
        if (srcID == destID) // if the current srcID is equal to the destID, BFS stop and return vector
         {
            return airports;
        }

        for (auto it : matrix_[srcID]) // Get all the adjacent vertices of that dequeued vertex. 
        {
            if (visited.find(it.first) == visited.end())
            {
                visited[it.first] = true; //if there are adjacent vertices that haven't been visited, mark it as "visited"
                BFS_queue.push(it.first); //and enqueue it
            }
        }

        
    }
    if(airports.back() != destID){
        std::cout << "the source and destination airport are not connected !! "<< std::endl;
    }
    return airports; //return vector
 }

 void BFS::insertAmatrix(Graph graph){
    std::unordered_map<int, std::unordered_map<int, Edge>> temp = graph.getAdjacency_matrix();
    std::unordered_map<int, std::unordered_map<int, Edge>>::iterator itr1;
    for (itr1 = temp.begin(); itr1 != temp.end(); ++itr1)
    {
        int srcid = itr1->first;
        std::unordered_map<int, Edge> tempdest = itr1->second;
        for (auto itr2 : tempdest)
        {
            int desid = itr2.first;
            matrix_[srcid][desid] = itr2.second;
        }
    }
    return;
 }

 void BFS::insertAirports(Graph graph){
    std::unordered_map<int, Airport> temp = graph.getAirports();
    for (auto itr1 : temp)
    {
        Airports_[itr1.first] = itr1.second;
    }
    return;
 }

    std::unordered_map<int, std::string> BFS::bfsHelper(int srcID){
    std::unordered_map<int, std::string> dist;//store the path
    std::unordered_map<int, bool> sptSet; // iterator or not
    std::unordered_map<int, int> step;//the number of transfer steps
    std::queue<PAP> priorityQ;
    for (auto itr : Airports_)        //initialize data
    {
        int tempid = itr.first;
        sptSet[tempid] = false;
        dist[tempid] = std::to_string(srcID) + ' ';
        step[tempid] = 200;
    }
    step[srcID] = 0;
    priorityQ.push(PAP(srcID, 0));
    while (!priorityQ.empty())
    {
        while (priorityQ.empty() == false && sptSet[(priorityQ.front()).first] == true) //each airport only take one time
            priorityQ.pop();
        if (priorityQ.empty() == true)
            return dist;

        PAP temppair = priorityQ.front();
        priorityQ.pop();
        int tmepid = temppair.first;
        sptSet[tmepid] = true;
        std::unordered_map<int, Edge> adjmap = matrix_[tmepid]; 

        for (auto itr2 : adjmap) //iterater the matrix_
        {
            int tempstep = step[tmepid] + 1;
            if (tempstep < step[itr2.first]) //if new step is smaller than past step
            {
                step[itr2.first] = tempstep;
                dist[itr2.first] = dist[tmepid] + std::to_string(itr2.first) + ' ';
                priorityQ.push(PAP(itr2.first, step[itr2.first]));
            }
        }
    }
    return dist;
 }

 std::string BFS::bfsGetShortstep(int srcID, int dstID){
    insertAmatrix(airport_graph_);
    insertAirports(airport_graph_);
    std::unordered_map<int, std::string> result = bfsHelper(srcID);
    std::string path = result[dstID];
    return path;
 }
