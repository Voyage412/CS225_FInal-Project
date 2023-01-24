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
// #include <pair>

class PageRank{
    public:
        // Default constructor
        PageRank() {};

        /**
         * get the number of routes departed from the sourcce airport with the given ID
         * @param srcID- source airport ID
        */
        int getOutDegree(int srcID);

        /**
         * Use PageRank algorithms to do the estimation of the importance of airports. Return the rank 
         * correpsonding with each airport. The key is the airport ID and the corresponding value is 
         * the rank
         * @param graph - the graph of airports we want to estimate
         * @param time - the number of iteration for page rank
         * @param damping_factor - the damping factor for page rank, normally is 0.85
        */
        std::unordered_map<int, double> pageRank(const Graph & graph, int time, double damping_factor);

        /**
         * based on the estimation we get, sort the rank result and return the most improtant airport
        */
        Airport findImportantAP();

        // get the rank of the airport ID from high to low
        std::vector<int> getRank_AP();

        /**
         * compare operator to compare the second term of two pairs. For example, there are two pairs <a,b> and <c,d>.
         * If b > d, return true. Else, return false;
        */
        struct compare {
            bool operator() (const std::pair<int, double> &a, const std::pair<int, double> &b) const {
                return a.second > b.second;
            }
        } cmp;

       


    private:
        
        Graph graph_;
        std::unordered_map<int, std::unordered_map<int, Edge>> adj_matrix_;
        std::unordered_map<int, Airport> airports; 
        int number_ap;
        //      apID, rank
        std::unordered_map<int, double> rank_;
        // bool compare(std::pair<>)
        
};

