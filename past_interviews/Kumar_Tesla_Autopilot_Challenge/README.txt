Developed platform: Ubuntu 22.04

Solution:
* The charging stations can be seen as a network of nodes, and we need to find the shortest time
  that it takes to travel between any 2 given nodes/stations
* I implement Dijkstra's algorithm to find the shortest time path
* The cost function is the time taken to travel the distance + the time taken to charge at a station
* The distance between 2 stations is calculated through the Haversine's formula

Assumption:
* There will be zero charge when we reach the destination station.

Comment on performance of solution:
* Dijkstra's algorithm is a greedy algorithm, it takes the path that is the local optimal choice
  to reach the next node. Constantly pursuing the local optimal choice may not give us the global
  optimal choice, i.e., the global shortest route. Hence, the solution may be suboptimal.

Instructions to run the solution:
* Please run these commands from the same folder level at this README file (root workspace)
* To compile the candidate solution please run:
    g++ -std=c++11 -O1 src/main.cpp src/network.cpp -o bin/candidate_solution
* To obtain a route from the candidate solution please run:
    ./bin/candidate_solution Council_Bluffs_IA Cadillac_MI

Reference used:
* https://en.wikipedia.org/wiki/Haversine_formula