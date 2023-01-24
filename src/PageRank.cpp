#include "PageRank.h"
#include "Graph.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include "Airport.h"
#include "Edge.h"
#include <queue>
#include <vector>
#include <algorithm>

/**
 * get the number of routes departed from the sourcce airport with the given ID
 * @param srcID- source airport ID
 */
int PageRank::getOutDegree(int srcID) {
    return (int) adj_matrix_[srcID].size();
}

/**
 * Use PageRank algorithms to do the estimation of the importance of airports. Return the rank 
 * correpsonding with each airport. The key is the airport ID and the corresponding value is 
 * the rank
 * @param graph - the graph of airports we want to estimate
 * @param time - the number of iteration for page rank
 * @param damping_factor - the damping factor for page rank, normally is 0.85
 */
std::unordered_map<int, double> PageRank::pageRank(const Graph & graph, int time, double damping_factor) {
    graph_ = graph;
    adj_matrix_ = graph_.getAdjacency_matrix();
    airports = graph_.getAirports();
    number_ap = graph_.getAirportNum();
    // initailize the page rank value to 1/size of airports
    for(auto it : airports){
        rank_[it.first] = 1.0 / (double) number_ap;
    }
    // calculate the damping value
    double damping_value = (1.0 - damping_factor) / (double) airports.size();
    // start the iterations for PageRank
    for(int i = 0; i < time; i++){
        // calculate page rank value of airport x 
        for(auto x : airports){
            double rank = 0.0;
            for(auto y : adj_matrix_){
                // y.first srcID ; y.second destID Edge
                // x.first destID(we want) 
                if(y.second.find(x.first) != y.second.end()) {
                    // find the number of routes from the airport x
                    int deg = getOutDegree(y.first);
                    //          destID             srcID
                    rank += damping_factor * rank_[y.first] / (double) deg;
                }
                

            rank += damping_value;
            rank_[x.first] = rank;
            }
        }
    }
    return rank_;
}

/**
 * based on the estimation we get, sort the rank result and return the most improtant airport
 */
Airport PageRank::findImportantAP() {
    int max = 0;
    int ap;
    // find airport with the maximum page rank value
    for(auto it : rank_) {
        if(it.second > max){
            max = it.second;
            ap = it.first;
        }
    }
    return airports[ap];
}

// get the rank of the airport ID from high to low
std::vector<int> PageRank::getRank_AP() {
    std::vector<std::pair<int, double>> rank;
    std::vector<int> rankAP;
    for(auto &it : rank_){
        rank.push_back(it);
    }
    // sort the airports from high page rank value to low page rank value
    std::sort(rank.begin(), rank.end(), cmp);
    for(auto &it : rank){
        // std::cout << it.first << " " << it.second << std::endl;
        rankAP.push_back(it.first);
    }
    return rankAP;
}

