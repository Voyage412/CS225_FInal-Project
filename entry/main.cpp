#include <iostream>
#include <algorithm>
#include <Graph.h>
#include <BFS.h>
#include <Dijkstra.h>
#include <PageRank.h>

void wait() {
    std::cout << "Press any key to return to menu..";
    std::string w;
    std::cin >> w;
}

int main() {
    system("clear");
    std::cout << "CS225 FINAL PROJECT" << std::endl;
    std::cout << "OPENFLIGHT" << std::endl;
            std::string airport_file = "../data/airports.dat";
        std::string route_file = "../data/routes.dat";
        Graph graph = Graph(airport_file, route_file);
    while (true) {
        std::cout << "[0] Use BFS to traverse all the graph" << std::endl;
        std::cout << "[1] Use BFS to find shortest path between two airports" << std::endl;
        std::cout << "[2] Use Dijkstra to find shortest path between two airports" << std::endl;
        std::cout << "[3] Use pagerank to find the most important airport in the dataset" << std::endl;
        std::cout << "[4] Use pagerank to find the most important airport in a given range" << std::endl;
        std::cout << "[9] Quit";
        std::cout << std::endl;
        std::cout << "Enter a number to select an operation: ";
        int in;
        std::cin >> in;
        
        if (in == 9) {
            std::cout << "Ending the program..." << std::endl;
            break;
        }


        switch (in)
        {
        case 0: {
            std::cout << "Please enter an airport ID as source airport: ";
            int airportId;
            std::cin >> airportId;
            BFS bfs = BFS(graph);
            std::vector<int> v = bfs.traverseAll(graph, airportId);
            for (int i = 0; i < (int) v.size(); i += 5) {
                for (int ii = i; ii < std::min((int) v.size(), i + 5); ii++) {
                    std::cout << v[ii] << "\t";
                }
                std::cout<< std::endl;
            }
            break;
        }

        case 1: {
            int srcID;
            int destID;
            std::cout << "Please enter an airport ID as source airport: ";
            std::cin >> srcID;
            std::cout << "Please enter an airport ID as destination airport: ";
            std::cin >> destID;
            BFS bfs = BFS(graph);
            std::string s = bfs.bfsGetShortstep(srcID, destID);
            std::cout << s << std::endl;
            break;
        }

        case 2: {
            int srcID;
            int destID;
            std::cout << "Please enter an airport ID as source airport: ";
            std::cin >> srcID;
            std::cout << "Please enter an airport ID as destination airport: ";
            std::cin >> destID;
            Dijkstra dijkstra = Dijkstra(graph);
            std::string s = dijkstra.getshortpath(graph, srcID, destID);
            std::cout << s << std::endl;
            break;
        }

        case 3: {
            PageRank pageRank = PageRank();
            pageRank.pageRank(graph, 10, 0.75);
            std::vector<int> v = pageRank.getRank_AP();
            for (int i = 0; i < (int) v.size(); i += 5) {
                for (int ii = i; ii < std::min((int) v.size(), i + 5); ii++) {
                    std::cout << v[ii] << "\t";
                }
                std::cout<< std::endl;
            }
            break;        
        }

        case 4: {
            std::cout << "Please enter an airport ID as source airport: ";
            int srcID;  
            int step;
            BFS bfs = BFS(graph);
            std::cin >> srcID;
            std::cout << "Please enter the range you want to calculate: ";
            std::cin >> step;
            std::vector<int> new_graph = bfs.traverse_with_given_step(graph, srcID, 50);
            auto ori_airports = graph.getairports();
            std::unordered_map<int, Airport> airports;
            std::unordered_map<int, std::unordered_map<int, Edge>> adjacency_matrix;
            for (unsigned i = 0; i < new_graph.size(); i++) {
                Airport a = ori_airports[new_graph[i]];
                airports[new_graph[i]] = a;
            }

            for (auto i : graph.getAdjacency_matrix()) {
                if (airports.count(i.first) != 0) {
                    adjacency_matrix.insert(i);
                }
            }
            
            Graph g = Graph(adjacency_matrix, airports);
            PageRank pageRank = PageRank();
            pageRank.pageRank(g, 10, 0.75);
            std::vector<int> v = pageRank.getRank_AP();
            for (int i = 0; i < (int) v.size(); i += 5) {
                for (int ii = i; ii < std::min((int) v.size(), i + 5); ii++) {
                    std::cout << v[ii] << "\t";
                }
                std::cout<< std::endl;
            }
            break;        
        }

        default:
            std::cout << "Please check your input and input again" << std::endl;
            break;
        }
        wait();
        system("clear");
    }
    return 0;
}

