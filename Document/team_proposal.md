## Leading Question 
   
Our group decided to do the project "Open flight". Our goal is to find the most convenient path and the most important airport based on the given data. It is very useful and applicable. Finding the most convenient routes between two areas can help people find the best travel path that is much easier to get the tickets. Working on the datasets of the open flights can help us better understand connectivity and human geography. Throughout this final project, we will use BFS, Dijkstra's algorithm, and PageRank.

Find the most convenient path: given the starting place and the destination, the code base will return the most convenient path between these two locations. Traveling in this path, there are more routes or airlines for the travelers to choose such that it is much easier to buy a ticket. This will be implemented by Dijkstra's algorithm, which finds the shortest paths in a directed weighted graph. The nodes of our graph will be the airports, the edges will be the routes, and the weights will be considered as 1/numbers of routes such that more routes means less weights and the path we want as the “shortest” path.
Find the most important airport: given the routes and airport resources from the data, the code will return the most important airport which is passed through by the most routes. This will be implemented by PageRank algorithms using the graph we create to demonstrate the relationship between airports and routes and map them out.
If we still have time: we want to make the graphical output to visualize the result and data, including the convenient path between the given starting point and destination and the most important airports by the graphing related algorithms in c++ or layered graph layout to help illustrate the situation nowadays in aviation.

## Dataset Acquisition and Processing
### Dataset Acquisition

We use data of airport and route: 
https://raw.githubusercontent.com/jpatokal/openflights/master/data/airports.dat
https://raw.githubusercontent.com/jpatokal/openflights/master/data/routes.dat

### Data Format

Our data airports.dat and routes.dat comes from https://openflights.org/data.html. It is entered into the program via the .dat file format. We will transform the dataset into object-facing programming objects via Graph Algorithm to facilitate later utilization and processing. The route.dat dataset contains 9 columns: Airline, Airline ID, Source airport, Source airport ID, Destination airport, Destination Airport ID, Codeshare, Stops and Equipment. The airport.dat dataset contains 15 columns: Airport ID, Name, City, Country, IATA, ICAO, Latitude, Longitude, Altitude, Timezone, DST, Tz database time zone, Type, Source. We plan to input part of the data into the directed graph, with the airport data as the vertex of the graph and the edge between the two vertices as the routes with the fraction of the number of all flights from both airports as the weights. The vertices will contain Airport ID, Name, City, Longitude and Altitude. 

The first data airports.dat is about 1.08MB and the second data routes.data is about 2.27MB. In order to best achieve our goals, we will use the entire dataset.


### Data Correction

The two inputs will be the departure airport and the landing airport. First, we will use the data of airports to check whether those two airports exist. If the departure airport or landing airport doesn't exist, we will return messages like "can't find departure airport" or "can't find landing airport". If those two airports exist, we will use BFS to check whether the route exists between the two airports using the data of routes. The BFS will return all the airports that the route has and we store those airports into a vector. Also, during using the BFS, we will count the number of visited airports on each route and use this number as the weight of Dijkstra’s Algorithm to calculate the shortest path. To test whether the algorithm is correct or not, we will write test cases that contain only one route, and check whether the content of the vector matches the route. If a direct flight route between the two airports doesn't exist, it will search transit airports using route data. We will use Dijkstra’s algorithm to determine which transit airport we will use to find the shortest path. If there are no transit airports in the route, we return messages like "no route exists". In addition, we will use the PageRank algorithm to find the most important airport in the route we choose. To test whether this algorithm works correctly, we will write a test case that contains several airports which have different numbers of routes passing them, and check whether the PageRank algorithm chooses the airport with the largest number of routes passing it. 

### Data Storage

The main goals of our project require a graph where airports as vertices are obtained from airport.dat and the routes as edges are obtained from routes.dat. We implement class Graph, Edge, Airport, and Route . This graph is using an adjacency matrix, using an unordered_map. Its key is the departure airport and the value is another unordered_map where the key is the destination airport and value is the routes(class Edge) between them. The space complexity of the adjacency matrix is O(2*number of airports). We will use a queue (space complexity: O(number of airports)) when we use BFS to store the temporary data. We will use the queue and the vector with the space complexity of O(number of airports) as priority to store the data when using Dijkstra's algorithm. And for the PageRank, we will use vectors(space complexity: O(number of airports)) as priority to store the data used for this algorithm.

## Algorithm 

###Function Inputs and Outputs
Our project will utilize Dijkstra’s Algorithm and Page Rank algorithm to measure and calculate the data and find the most convenient path and the most important airport. SInce our dataset already separates information about airports and routes into several files, we can use these files as input to build the graph into an adjacency matrix. To solve it, we will implement graph data structure containing the airports as vertices and the routes as edges to solve the problem. The weights of the route between the departure and destination airport can be obtained by the edge class and therefore find the most convenient path by the weights of paths based on Dijkstra’s Algorithm. Furthermore, the adjacency matrix in the class graph with the weights of the paths can also easily be obtained to help us find the most important airport by the Page Rank algorithm.

Implement BFS traversal in order to traverse the graph data structure to visit the airport and routes among them. We will then use Djikstra’s algorithm to find the most convenient path between the start point and the destination. Then, we will use the Page Rank algorithm to find the most important airport, which has been visited by the most routes . If we still have time, we want to make the graphical output to visualize the result and data, including the convenient path between the given starting point and destination and the most important airports.

BFS: BFS traversal is implemented to help traverse graph data structure to find the information we want about the airports and routes. If it is useful, we may create several functions of BFS in order to help the implementation of the other algorithms to find the most convenient path and airports.

Dijkstra’s Algorithm: In order to find the most convenient path between the given departure airport and the destination airport, we will use Dijkstra’s Algorithm. The most convenient path is the one in which the traveler has more routes to choose when they want to travel. With more routes to choose among this path, the ticker is easier for travelers to buy, which is more flexible. To check whether it is the most convenient, we count the number of routes on each edge, consider its weight as 1/number of routes, and compare the weights with the other edges. In this way, we can find the most convenient path between the starting point and the end point. We will store all the roads taken to achieve this most convenient path and visualize the output by printing out the list of roads (return the vector containing the edge as the path between two places).

Page Rank: We want to implement the Page Rank algorithm in order to find the most important airport based on the given data and visualize it on the map if we still have time. Given by the directed graph from our graph data structure, we want to use the adjacency matrix to calculate the result based on the Page Rank algorithm and finally get the most important airport from the result. It will return the airport with its information.

###Function Efficiency
Based on the graph data structure which our group wants to use, E represents the number of Edges, V represents the number of Vertex. The target Big(O) of BFS should be O(|V|+|E|). The target Big(O) of Djikstra’s algorithm should be Big O: O(|E| + |V|*log|V| ). The target Big(O) of the Page Rank algorithm should be O(V·E⋅k) where k is the number of iterations.


## Timeline

Data acquisition and processing (due: 11.6)

Design openflight algorithms and write all the preliminary code except the algorithm(due: 11.13)

Write BFS and Dijkstra’s Algorithm(due: 11.20)

Write Page Rank algorithm and other code completely(due: 11.27)

Write descriptive README and final report(due: 12.4)

Project close-out, inspection and final presentation(due: 12.8)