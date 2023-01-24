#include "Graph.h"
#include <fstream>
#include <iterator>
#include <iostream>
#include <string>
#include <unordered_map>
#include "Airport.h"
#include <ctype.h>
#include "Edge.h"

/**
 * constructor to create the graph and parse the data of airports and routes into it.
 * The graph has the airports as vertices and routes as edges. In this case, we consider
 * the routes between the same source airport and destination airport as a single edge
 * between vertices.
 * @param Airport_File - data file about airport information
 * @param Route_File - data file about route information
 **/
Graph::Graph(std::string& Airport_File, std::string& Route_File){
    parseVertices(Airport_File);
    parseEdges(Route_File);
}


void Graph::parseVertices(const std::string& filename){
    std::ifstream Ap_File(filename);
    std::string ID;
    std::string Name;
    std::string City;
    std::string latitude;           
    std::string longtitude;
    /* format
    507, "London Heathrow Airport", "London", "United Kingdom", "LHR", "EGLL", 51.4706, -0.461941, 83, 0, 
    "E", "Europe/London", "airport", "OurAirports"
    */
    if (Ap_File.is_open()) {
        std::string word;
        while (getline(Ap_File, word)) {
            std::string ID;
            std::string Name;
            std::string City;
            std::string Country;
            std::string Latitude;
            std::string Longtitude;

            // to count ','
            int count0 = 0;
            // to count '"'
            int count1 = 0;
            for(int i = 0; i < (int) word.size(); i++){
                if(word.at(i) == '"') count1++;
                // count ',' outside the '"' to avoid counting ',' inside the name of the airport, country, or city
                if(word.at(i) == ',' && count1 % 2 == 0) count0++;
                // parse the information of ID
                if(count0 == 0){
                    ID.push_back(word.at(i));
                }
                // parse the information of Name
                if(count0 == 1){
                    Name.push_back(word.at(i));
                }
                // parse the information of city
                if(count0 == 2){
                    if(word.at(i) != '"' && word.at(i) != ',') City.push_back(word.at(i));
                }
                // parse the information of country
                if(count0 == 3){
                    if(word.at(i) != '"' && word.at(i) != ',') Country.push_back(word.at(i));
                }
                // parse the information of latitude
                if(count0 == 6){
                    if(word.at(i) != '"' && word.at(i) != ',') Latitude.push_back(word.at(i));
                }
                // parse the information of longtitude
                if(count0 == 7){
                    if(word.at(i) != '"' && word.at(i) != ',') Longtitude.push_back(word.at(i));
                }
                else continue;
            }
            
            // filter the comma and quotation marks before and after the name
            Name = Name.substr(2, Name.size()-3);

            // convert the string of ID to integer
            int Id = std::stoi(ID);
            // convert the string of latitude to double
            double latitude = std::stod(Latitude);
            // convert the string of longtitude to double
            double longtitude = std::stod(Longtitude);
            // create an object of the airport data we parse
            Airport airport(Id, Name, City, Country, latitude, longtitude);
            // insert the airport as a vertex;
            insertVertex(Id, airport);
            // clear the string 
            ID.clear();
            Name.clear();
            City.clear();
            Latitude.clear();           
            Longtitude.clear();
        }
    }
    Ap_File.close();

}



/**
 * insert a new airport as vertex into the graph by adding it into the map of airport 
 * @param ID - Airport ID
 * @param airport - The airport object corresponding with the Airport
**/
void Graph::insertVertex(int ID, Airport airport){
    airports[ID] = airport;   
}

/**
 * parse the data of route information into the graph
 * @param Airport_File - data file for data parsing
 **/
void Graph::parseEdges(const std::string& filename) { 
    std::ifstream Route_File(filename);
    std::string word;
    if (Route_File.is_open()) {

        /* Reads a line from `wordsFile` into `word` until the file ends. */
        // Route(int AirlineID, std::string Airline, int srcID, int dstID, int stop){
        // BA,1355,SIN,3316,LHR,507,,0,744 777
        while (getline(Route_File, word)) {
            // split the words in lines by ","
            std::vector<std::string> v = split(word, ",");
            // if source and destination airport ID aren't found, the route isn't valid
            if(v[3].find("\\N") != std::string::npos || v[5].find("\\N") != std::string::npos){
                // j++;
                invalid++;
                continue;
            } 
            // split the lines into airline, airlineID, sourceID, destinationID, and stop
            std::string Airline = v[0];
            std::string AirlineID = v[1];
            std::string srcID = v[3];
            std::string dstID = v[5];
            std::string stop = v[7];
            // if airlineID isn't found, set it to 0 since airline name still exists, the route is still valid.
            int AirlineId = 0;
            if(AirlineID.find("\\N") == std::string::npos) AirlineId = std::stoi(AirlineID);
            // convert string to integer
            int srcId = std::stoi(srcID);
            int dstId = std::stoi(dstID);
            int stop_int = std::stoi(stop);
            // set up the route
            Route route(AirlineId, Airline, srcId, dstId, stop_int);
            // check whether source and destination airport exist. If not, the route is invalid
            if(airports.find(srcId) != airports.end() && airports.find(dstId) != airports.end()){
                Airports[srcId] = airports[srcId];
                Airports[dstId] = airports[dstId];
                insertEdge(route, srcId, dstId);
            }
            else{
                invalid++;
            }
            
        }

    }
    Route_File.close();
}

/**
 * splits the string into pieces of strings by the pattern given. Return the vector of
 * splitted strings
 * @param str the strings needed to split
 * @param pattern the pattern we want to split
 */
std::vector<std::string> Graph::split(std::string str,std::string pattern)
{   
    std::string::size_type position;
    std::vector<std::string> words;
    str += pattern;
    int size = str.size();
    for(int i = 0; i < size; i++){
        // find the position of the pattern
        position = str.find(pattern,i);
        if((int) position < size){
            // return the portion of strings from index i to the pattern
            std::string s = str.substr(i, position - i);
            words.push_back(s);
            i = position + pattern.size()-1;
        }
    }
    return words;
}

/**
 * insert a new route as an edge into the graph by adding it into adjacency matrix
 * @param route - the route we want to add in the graph
 * @param srcID - the source airport ID of the route
 * @param dstID - the destination airport ID of the route
 **/
void Graph::insertEdge(Route route, int srcID, int dstID){
    // if srcID not found, initialize the correspdoning value of the adjacency matrix
    if (adjacency_matrix.find(srcID) == adjacency_matrix.end()) {    
        adjacency_matrix[srcID] = std::unordered_map<int, Edge>();
    }
    // if srcID found, dstID not found, initialize the edge with the given source and destination airport
    if(adjacency_matrix[srcID].find(dstID) == adjacency_matrix[srcID].end()){    
        adjacency_matrix[srcID][dstID] = Edge(route);
    } 
    // add route to the existed edge with the given source and destination airport
    else {
        adjacency_matrix[srcID][dstID].addRoute(route);
    }    

}

// get the number of the airports connected in the graph
int Graph::getAirportNum() {
    return (int) Airports.size();
}
// get the airports that are connected in the graph
const std::unordered_map<int, Airport> Graph::getAirports() {
   return Airports;
}
// get the airports that are not connected in the graph
const std::unordered_map<int, Airport> Graph::getairports() {
   return airports;
}

// get airport information
void Graph::printAirportInfo() {
    for (auto air : Airports) {
        std::cout << air.second.getID() << "\t" << air.second.getName() << std::endl;
    }
}

// get the adjacency matrix of the graph related to the routes and their connected 
std::unordered_map<int, std::unordered_map<int, Edge>> Graph::getAdjacency_matrix() {
    return adjacency_matrix;
}



