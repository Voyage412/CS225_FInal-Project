#include "Edge.h"
#include <unordered_map>
#include <iostream>

// Default constructor
Edge::Edge(){
    weights_ = 0;
}

/**
 * Constructor with a set of route and its weight
 * @param Routes
 * @param weights
 */
Edge::Edge(std::unordered_map<int, Route> Routes, int weights) {
    Routes_ = Routes;
    weights_ = weights;
}

/**
 * Constructor with initial route
 * @param Route
*/
Edge::Edge(Route Route){
    int AirlineID = Route.getAirlineID();
    Routes_[AirlineID] = Route;
    weights_ = 1;
    srcID_ = Route.getsrcID();
    dstID_ = Route.getdstID();
}

/**
 * add one route to the edge and add weight of the edge
 * @param Route
 */
void Edge::addRoute(Route Route){
    // if the source and destination airport of the adding route are not the same as the route in this edge, return
    if(Route.getsrcID() != srcID_ || Route.getdstID() != dstID_) return;
    int AirlineID = Route.getAirlineID();
    // if(Routes_.find(AirlineID) != Routes_.end()) return;
    Routes_[AirlineID] = Route;
    weights_++;
    // std::cout << weights_ << std::endl;
}

// get weight of the edge
int Edge::getWeights(){
    return weights_;
}
// calculate the weight of edge by count the number of route
void Edge::calculateWeights(){
    weights_ = Routes_.size();
}

// get the routes of the edge with the given source and destination
std::unordered_map<int, Route> Edge::getRoutes() {
    return Routes_;
}

/**
 * Equality operator
 * @param other
 */
bool Edge::operator==(const Edge & other) {
    return Routes_ == other.Routes_ && weights_ == other.weights_ && srcID_ == other.srcID_ && dstID_ == other.dstID_;
}