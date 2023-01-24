#pragma once
#include <string>
#include <vector>
#include <queue>
#include <string>
#include <utility>
#include <unordered_map>
#include "Graph.h"
#include "Airport.h"
#include "Edge.h"

class Dijkstra {
    public:
    /*Default constructor*/
    Dijkstra (Graph graph);
    /* Dijkstra's Algorithm:the input is the start airport, the output is unordered_map that store the shortest 
     * way go to all other airport 
     */
    std::unordered_map<int,std::string> dijkstra(int srcID);

    /*insert weight_matrix */
    void insertWeightmatrix();

    /*insert Adjacency matrix from graph*/
    void insertAdjacencymatrix(Graph graph);

    /*insert Airports from graph*/
    void insertAirports(Graph graph);

    /*Enter the start and end airports, find the shortest pass*/
    std::string getshortpath(Graph graph, int srcID, int dstID); 
    
    /*return the Weightmatrix*/
    std::unordered_map<int, std::unordered_map<int, double>> getadjacmatrix();

    private:
    mutable std::unordered_map<int, std::unordered_map<int, Edge>> adjac_matrix;
    mutable std::unordered_map<int, std::unordered_map<int, double>> weight_matrix;
    mutable std::unordered_map<int, Airport> Airports_;
    // int NumAirports;
    Graph g_;
    int srcID_;
    int dstID_;

};
