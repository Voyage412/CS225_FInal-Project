#pragma once
#include <string>
#include <vector>
#include <queue>
#include <string>
#include <utility>
#include <unordered_map>
#include "Airport.h"
#include "Edge.h"

class Graph {
    private:    
        // the adjacency matrix which maps the ID of the source airport into the 
        std::unordered_map<int, std::unordered_map<int, Edge>> adjacency_matrix;
        //                        sourseID                destID
        // The data of airports which are included in both airports.dat and routes.dat
        std::unordered_map<int, Airport> Airports;
        // The airports data parsed from airports.dat
        std::unordered_map<int, Airport> airports;
        
        /**
         * splits the string into pieces of strings by the pattern given. Return the vector of
         * splitted strings
         * @param str the strings needed to split
         * @param pattern the pattern we want to split
        */
        std::vector<std::string> split(std::string str, std::string pattern);
        // the number of invalid routes
        int invalid;
        

    public:
        //default constructor
        Graph() {};

        Graph(std::unordered_map<int, std::unordered_map<int, Edge>> a, std::unordered_map<int, Airport> b) {
            adjacency_matrix = a;
            airports = b;
            Airports = b;
        }

        /**
        * constructor to create the graph and parse the data of airports and routes into it.
        * The graph has the airports as vertices and routes as edges. In this case, we consider
        * the routes between the same source airport and destination airport as a single edge
        * between vertices.
        * @param Airport_File - data file about airport information
        * @param Route_File - data file about route information
        **/
        Graph(std::string& Airport_File, std::string& Route_File);

        /**
        * parse the data of airport information into the graph
        * @param Airport_File - data file for data parsing
        **/
        void parseVertices(const std::string& filename);

        /**
        * parse the data of route information into the graph
        * @param Airport_File - data file for data parsing
        **/
        void parseEdges(const std::string& filename);

        /**
         * insert a new airport as vertex into the graph by adding it into the map of airport 
         * @param ID - Airport ID
         * @param airport - The airport object corresponding with the Airport
        **/
        void insertVertex(int ID, Airport airport);
       
        /**
         * insert a new route as an edge into the graph by adding it into adjacency matrix
         * @param route - the route we want to add in the graph
         * @param srcID - the source airport ID of the route
         * @param dstID - the destination airport ID of the route
        **/
        void insertEdge(Route route, int srcID, int dstID);

        // get airport information
        void printAirportInfo();

        // get the number of the airports connected in the graph
        int getAirportNum();

        // get the airports that are connected in the graph
        const std::unordered_map<int, Airport> getAirports();

        // get the airports that are not connected in the graph
        const std::unordered_map<int, Airport> getairports();

        // get the airport name given by the airport id
        std::string getAirportName(int id);

        // get the airport id given by its name
        int getAirportId(std::string name);

        // get the adjacency matrix of the graph related to the routes and their connected 
        std::unordered_map<int, std::unordered_map<int, Edge>> getAdjacency_matrix();
        
        // equality operator
        bool operator==(const Graph & other);

        // get the number of invalid routes
        int getInvalidRoute() {return invalid;}; 
    };