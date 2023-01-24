#include <fstream>
#include <iterator>
#include <iostream>
#include <string>
#include <set>
#include <unordered_map>
#include "Dijkstra.h"
#include <utility>
typedef std::pair<int, double> PAP; // pair path
Dijkstra::Dijkstra(Graph graph) 
{
    insertAdjacencymatrix(graph);
    insertAirports(graph);
    insertWeightmatrix();
    g_ = graph;
}

void Dijkstra::insertAdjacencymatrix(Graph graph)
{
    std::unordered_map<int, std::unordered_map<int, Edge>> temp = graph.getAdjacency_matrix();
    std::unordered_map<int, std::unordered_map<int, Edge>>::iterator itr1;
    for (itr1 = temp.begin(); itr1 != temp.end(); ++itr1)
    {
        int srcid = itr1->first;
        std::unordered_map<int, Edge> tempdest = itr1->second;
        for (auto itr2 : tempdest)
        {
            int desid = itr2.first;
            adjac_matrix[srcid][desid] = itr2.second;
        }
    }
    return;
}
void Dijkstra::insertAirports(Graph graph)
{
    std::unordered_map<int, Airport> temp = graph.getAirports();
    for (auto itr1 : temp)
    {
        Airports_[itr1.first] = itr1.second;
    }
    return;
}

void Dijkstra::insertWeightmatrix()
{
    for (auto itr1 : adjac_matrix)
    {
        int srcid = itr1.first;
        std::unordered_map<int, Edge> tempdest = itr1.second;
        for (auto itr2 : tempdest)
        {
            int desid = itr2.first;
            Edge tempedge = itr2.second;
            double weight = 0.0;
            if (tempedge.getWeights() != 0)
            {
                weight = (double)(1 / (double)(tempedge.getWeights())); //get the value of 1/number of routes in map
            }
            else
            {
                weight = 0;
            }
            weight_matrix[srcid][desid] = weight;
        }
    }
}

std::unordered_map<int, std::string> Dijkstra::dijkstra(int srcID)
{
    std::unordered_map<int, std::string> dist;//store the path
    std::unordered_map<int, double> distweight;//store the route weight 
    std::unordered_map<int, bool> sptSet; // iterator or not
    std::unordered_map<int, int> step;//the number of transfer steps
    std::queue<PAP> priorityQ;
    for (auto itr : Airports_)        //initialize data
    {
        int tempid = itr.first;
        sptSet[tempid] = false;
        dist[tempid] = std::to_string(srcID) + ' ';
        distweight[tempid] = 5.0;
        step[tempid] = 200;
    }
    distweight[srcID] = 0.0;
    step[srcID] = 0;
    priorityQ.push(PAP(srcID, 0.0));
    while (!priorityQ.empty())
    {
        while (priorityQ.empty() == false && sptSet[(priorityQ.front()).first] == true) //each airport only take one time
            priorityQ.pop();
        if (priorityQ.empty() == true)
            return dist;

        PAP temppair = priorityQ.front();
        priorityQ.pop();
        int tmepid = temppair.first;
        double tempvalue = distweight[tmepid];
        sptSet[tmepid] = true;
        std::unordered_map<int, double> adjmap = weight_matrix[tmepid]; 

        for (auto itr2 : adjmap) //iterater the weight_matrix
        {
            double tempminvalue = weight_matrix[tmepid][itr2.first];
            double minvalue;
            double deter = 1 / weight_matrix[tmepid][itr2.first];
            if (tempminvalue != 0 && tempvalue != 0)
            {
                minvalue = tempminvalue + tempvalue;
                deter = (double)(1 / tempminvalue) + (double)(1 / tempvalue);
            }
            else if (tempminvalue == 0)
            {
                minvalue = tempvalue;
                deter = 1 / tempvalue;
            }
            else
            {
                minvalue = tempminvalue;
                deter = 1 / tempminvalue;
            } //get the past weight and new weight
            int tempstep = step[tmepid] + 1;
            if (tempstep < step[itr2.first]) //if new step is smaller than past step
            {
                step[itr2.first] = tempstep;
                distweight[itr2.first] = minvalue;
                dist[itr2.first] = dist[tmepid] + std::to_string(itr2.first) + ' ';
                priorityQ.push(PAP(itr2.first, minvalue));
            }
            else if (tempstep == step[itr2.first]) //if new step is equal to past step
            {
                if (deter > (double)(1 / tempminvalue)) //we want the larger number of airline with same transfer steps number
                {
                    distweight[itr2.first] = minvalue;
                    dist[itr2.first] = dist[tmepid] + std::to_string(itr2.first) + ' ';
                    priorityQ.push(PAP(itr2.first, minvalue));
                }
            }
        }
    }
    return dist;
}

std::string Dijkstra::getshortpath(Graph graph, int srcID, int dstID)
{
    srcID_ = srcID;
    dstID_ = dstID;
    std::unordered_map<int, std::string> result = dijkstra(srcID);
    std::string path = result[dstID];
    return path;
}
std::unordered_map<int, std::unordered_map<int, double>> Dijkstra::getadjacmatrix()
{
    return weight_matrix;
}