#include <catch2/catch_test_macros.hpp>

#include <iostream>
#include <vector>
#include <unordered_map>
#include "Graph.h"
#include "Edge.h"
#include <Dijkstra.h>
#include <PageRank.h>
#include <BFS.h>
#include <chrono>


TEST_CASE("TEST insertVertex #0", "[Graph]") {
    Graph graph = Graph();
    Airport airport0 = Airport(0, "airport0", "city0", "country0", 0, 0);
    graph.insertVertex(0, airport0);
    std::unordered_map<int, Airport> target_m;
    target_m.insert({0, airport0});
    REQUIRE(graph.getairports() == target_m);
}

TEST_CASE("TEST insertVertex #1", "[Graph]") {

    Graph graph = Graph();
    Airport airport0 = Airport(0, "airport0", "city0", "country0", 0, 0);
    Airport airport1 = Airport(1, "airport1", "city1", "country0", 0, 0);
    graph.insertVertex(0, airport0);
    graph.insertVertex(1, airport1);

    std::unordered_map<int, Airport> target_m;
    target_m.insert({0, airport0});
    target_m.insert({1, airport1});
    REQUIRE(graph.getairports() == target_m);
}


TEST_CASE("TEST insertEdge", "[Graph]") {
    Graph graph = Graph();
    Route route0 = Route(0, "airline0", 0, 1, 0);
    Route route1 = Route(1, "airline1", 1, 0, 0);
    graph.insertEdge(route0, 0, 1);
    graph.insertEdge(route1, 1, 0);
    Edge edge0 = graph.getAdjacency_matrix()[0][1];
    Edge edge1 = graph.getAdjacency_matrix()[1][0];
    std::unordered_map<int, Route> target0;
    std::unordered_map<int, Route> target1;
    target0.insert({0, route0});
    target1.insert({1, route1});

    REQUIRE(edge0.getRoutes() == target0);
    REQUIRE(edge1.getRoutes() == target1);
}


TEST_CASE("TEST parseFile # small dataset", "[Graph]") {
    std::string airport_file = "../tests/Airport_test_small.dat";
    std::string route_file = "../tests/Route_test_small.dat";
    Graph graph = Graph(airport_file, route_file);

    REQUIRE (graph.getAdjacency_matrix()[0][1].getWeights() == 1);
    REQUIRE (graph.getAdjacency_matrix()[0][2].getWeights() == 1);
    REQUIRE (graph.getAdjacency_matrix()[0][3].getWeights() == 0);
    REQUIRE (graph.getAdjacency_matrix()[0][4].getWeights() == 0);
    REQUIRE (graph.getAdjacency_matrix()[1][0].getWeights() == 1);
    REQUIRE (graph.getAdjacency_matrix()[1][2].getWeights() == 1);
    REQUIRE (graph.getAdjacency_matrix()[1][3].getWeights() == 1);
    REQUIRE (graph.getAdjacency_matrix()[1][4].getWeights() == 0);
    REQUIRE (graph.getAdjacency_matrix()[2][1].getWeights() == 2);
    REQUIRE (graph.getAdjacency_matrix()[2][3].getWeights() == 1);
    REQUIRE (graph.getAdjacency_matrix()[2][4].getWeights() == 0);
    REQUIRE (graph.getAdjacency_matrix()[3][0].getWeights() == 0);
    REQUIRE (graph.getAdjacency_matrix()[3][1].getWeights() == 1);
    REQUIRE (graph.getAdjacency_matrix()[3][2].getWeights() == 1);
    REQUIRE (graph.getAdjacency_matrix()[4][0].getWeights() == 0);
    REQUIRE (graph.getAdjacency_matrix()[4][1].getWeights() == 0);
    REQUIRE (graph.getAdjacency_matrix()[4][2].getWeights() == 0);
    REQUIRE (graph.getAdjacency_matrix()[4][3].getWeights() == 0);
}


TEST_CASE("TEST find important airport # small dataset", "[PageRank]") {
    std::string airport_file = "../tests/Airport_test_small.dat";
    std::string route_file = "../tests/Route_test_small.dat";
    Graph graph = Graph(airport_file, route_file);
    PageRank pg = PageRank();
    std::unordered_map<int, double> m = pg.pageRank(graph, 10, 0.85);
    // std::unordered_map<int, double> target_m;
    std::vector<int> r = pg.getRank_AP();
    std::vector<int> target_r = {1, 2, 3, 0};
    REQUIRE(r == target_r);
}

TEST_CASE("BFS # small dataset", "[BFS]") {
    std::string airport_file = "../tests/Airport_test_small.dat";
    std::string route_file = "../tests/Route_test_small.dat";
    Graph graph = Graph(airport_file, route_file);
    BFS bfs = BFS(graph);
    std::vector<int> all0 = bfs.traverseAll(graph, 0);
    std::vector<int> all1 = bfs.traverseAll(graph, 1);
    std::vector<int> all2 = bfs.traverseAll(graph, 4);
    REQUIRE (all0.size() == all1.size());
}

TEST_CASE("TEST BFS with dest # small dataset", "[BFS]") {
    std::string airport_file = "../tests/Airport_test_small.dat";
    std::string route_file = "../tests/Route_test_small.dat";
    Graph graph = Graph(airport_file, route_file);
    BFS bfs = BFS(graph);
    std::vector<int> dest0 = bfs.traverse_with_dest(graph, 0, 3);
    std::vector<int> dest1 = bfs.traverse_with_dest(graph, 0, 4);
    REQUIRE(dest0.back() == 3);
    REQUIRE(dest1.back() != 4);
}

TEST_CASE("TEST shortest path # small dataset", "[Dijkstra]") {
    std::string airport_file = "../tests/Airport_test_small.dat";
    std::string route_file = "../tests/Route_test_small.dat";
    Graph graph = Graph(airport_file, route_file);
    Dijkstra dijkstra = Dijkstra(graph);
    std::string str0 = dijkstra.getshortpath(graph, 0, 3);
    std::string str1 = dijkstra.getshortpath(graph, 0, 1);
    REQUIRE(str0 == "0 1 3 ");
    REQUIRE(str1 == "0 1 ");
}

TEST_CASE("TEST construct graph # real data", "[Graph]") {
    std::string airport_file = "../data/airports.dat";
    std::string route_file = "../data/routes.dat";
    Graph graph = Graph(airport_file, route_file);
    int route = 0;
    for (auto it : graph.getAdjacency_matrix()) {
        for (auto b : it.second) {
            route += b.second.getWeights();
            
        }
    }
    int invalid = graph.getInvalidRoute();
    REQUIRE(graph.getAirports().size() > 3000);
    REQUIRE(route + invalid == 67663);
}

TEST_CASE("TEST BFS # real data", "[Graph]") {
    std::string airport_file = "../data/airports.dat";
    std::string route_file = "../data/routes.dat";
    Graph graph = Graph(airport_file, route_file);
    BFS bfs = BFS(graph);
    std::vector<int> all0 = bfs.traverseAll(graph, 3364);
    REQUIRE(all0.size() == 3166);
}



TEST_CASE("Find shortest path # real data", "[Dijkstra]") {
    std::string airport_file = "../data/airports.dat";
    std::string route_file = "../data/routes.dat";
    Graph graph = Graph(airport_file, route_file);
    Dijkstra dij = Dijkstra(graph);

    std::string path1 = dij.getshortpath(graph, 3364, 3406);
    std::string path2 = dij.getshortpath(graph, 3364, 3484);
    std::string path3 = dij.getshortpath(graph, 3373, 3484);
    std::string path4 = dij.getshortpath(graph, 3373, 4049);
    REQUIRE(path1 == "3364 3406 ");
    REQUIRE(path2 == "3364 3484 ");
    REQUIRE(path3 == "3373 3370 3484 ");
    REQUIRE(path4 == "3373 3406 3830 4049 ");
}

TEST_CASE("TEST parseFile # large dataset", "[Graph]") {
    std::string airport_file = "../tests/Airport_test_large.dat";
    std::string route_file = "../tests/Route_test_large.dat";
    Graph graph = Graph(airport_file, route_file);
    std::cout << "large dataset Airport number: " << graph.getAirports().size() << std::endl;
    BFS bfs = BFS(graph);
    std::vector<int> bfsResult = bfs.traverseAll(graph, 220);
    REQUIRE(bfsResult.size() == 30);
}

TEST_CASE("TEST page rank # large dataset", "[Graph]") {
    std::string airport_file = "../tests/Airport_test_large.dat";
    std::string route_file = "../tests/Route_test_large.dat";
    Graph graph = Graph(airport_file, route_file);
    PageRank pg = PageRank();
    std::unordered_map<int, double> map = pg.pageRank(graph, 100, 0.75);
    std::vector<int> v = pg.getRank_AP();
    for (auto i : v) {
        std:: cout << i << "\t";
    }
    Airport air = pg.findImportantAP();
    std::cout << air.getName() << std::endl;
    REQUIRE(air.getName() == "Houari Boumediene Airport");
    
}

// This test consume so much time. Maybe reduce the time diffculty in next phase

/*
TEST_CASE("Find important airpors # real data", "[PageRank]") {
    std::string airport_file = "../data/airports.dat";
    std::string route_file = "../data/routes.dat";
    Graph graph = Graph(airport_file, route_file);
    PageRank pr = PageRank();
    auto start = std::chrono::steady_clock::now();
    pr.pageRank(graph, 10, 0.85);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

    std::vector<int> v = pr.getRank_AP();
    int j = 0;
    for (auto i : v) {
        std:: cout << i << "\t";
        j++;
        if(j > 10) break;
    }
    std::cout << std::endl;
    Airport air = pr.findImportantAP();
    std::cout << air.getName() << std::endl;
}
*/



TEST_CASE("TEST bfsshortest step # small dataset", "[BFS]") {
    std::string airport_file = "../tests/Airport_test_small.dat";
    std::string route_file = "../tests/Route_test_small.dat";
    Graph graph = Graph(airport_file, route_file);
    BFS bfs = BFS(graph);
    
    std::string str0 = bfs.bfsGetShortstep(0, 3);
    std::string str1 = bfs.bfsGetShortstep(0, 1);
    REQUIRE(str0 == "0 1 3 ");
    REQUIRE(str1 == "0 1 ");
}

TEST_CASE("TEST bfsshortest step # real data", "[BFS]") {
    std::string airport_file = "../data/airports.dat";
    std::string route_file = "../data/routes.dat";
    Graph graph = Graph(airport_file, route_file);
    BFS bfs = BFS(graph);

    std::string path1 = bfs.bfsGetShortstep(3364, 3406);
    std::string path2 = bfs.bfsGetShortstep(3364, 3484);
    std::string path3 = bfs.bfsGetShortstep(3373, 3484);
    std::string path4 = bfs.bfsGetShortstep(3373, 4049);
    REQUIRE(path1 == "3364 3406 ");
    REQUIRE(path2 == "3364 3484 ");
    REQUIRE(path3 == "3373 2276 3484 ");
    REQUIRE(path4 == "3373 3406 3830 4049 ");
}