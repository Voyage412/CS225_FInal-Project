#pragma once
#include "Graph.h"
#include <iterator>
#include <iostream>
#include <string>
#include <unordered_map>
#include "Airport.h"
#include "Edge.h"
#include <queue>
#include <vector>

class BFS{
public:
    //constructor of BFS
    BFS(const Graph & graph);
    std::vector<int> traverseAll(const Graph & graph, int srcID);                           // traverse vertices(airports)
    std::vector<int> traverse_with_dest(const Graph & graph, int srcID, int destID);        // traverse airports between two airports
    std::vector<int> traverse_with_given_step(const Graph & graph, int srcID, int step);    // traverse vertices(airports) with given step
    std::unordered_map<int, std::string> bfsHelper(int srcID);
    std::string bfsGetShortstep(int srcID, int dstID);
    void insertAmatrix(Graph graph);
    void insertAirports(Graph graph);

private:
    Graph airport_graph_; // the graph with all the data
    int number; // number of airports
    std::unordered_map<int, std::unordered_map<int, Edge>> matrix_;// a matrix of graph which contains srcID of all the airports
    mutable std::unordered_map<int, Airport> Airports_;
};
