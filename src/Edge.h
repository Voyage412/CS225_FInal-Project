#pragma once
#include "Route.h"
#include <vector>
#include <unordered_map>


// to do
class Edge {
    public:
    // Default constructor
    Edge();
    /**
     * Constructor with initial route
     * @param Route
    */
    Edge(Route Route);

    /**
     * Constructor with a set of route and its weight
     * @param Routes
     * @param weights
    */
    Edge(std::unordered_map<int, Route> Routes, int weights);

    /**
     * add one route to the edge and add weight of the edge
     * @param Route
    */
    void addRoute(Route Route);

    // get weight of the edge
    int getWeights();

    // calculate the weight of edge by count the number of route
    void calculateWeights();

    // get the routes of the edge with the given source and destination
    std::unordered_map<int, Route> getRoutes();

    /**
     * Equality operator
    */
    bool operator==(const Edge & other);

    private:

    std::unordered_map<int, Route> Routes_;
    //           AirlineID  Corresponding route 
    int weights_;
    int srcID_;
    int dstID_;

};
