//=============================================================================
// C++ Supercharger Tesla Autopilot Challenge
//
//! \brief      Simple implementation of the Dijkstra algorithm
//!             to search for the closest charging station from
//!             current charging station until we reach the goal
//!             charging station
//!
//! \date       23rd Sept 2022
//!
//! \author     Kumar Ramesh - kumar.r.chakravarathy@gmail.com
//=============================================================================

#include <climits>
#include <math.h>
#include <vector>

#include "../include/network.h"

#define _USE_MATH_DEFINES

// kRange = max range or distance car can travel from one full charge
// kSpeed = max speed of car
// kStations = max number of charging stations in the network
static const int kRange = 320;
static const int kSpeed = 105;
static const int kStations = 303;


int getStationIndex(const std::array<row, 303>& network, const std::string& input_station_name) {
    // searches and returns index of input station
    int index = 0;
    for (const auto& station : network) {
        if (station.name == input_station_name)
            break;
        index++;
    }
    if (network[index].name != input_station_name)
        throw std::invalid_argument("Error: station name not found in the network");

    return index;
}


int getClosestStation(const double cost[], const bool visited[]) {
    // returns node v closest to node u based on cost
    int closest_node_index;
    double min = LONG_MAX;

    for (int v = 0; v < kStations; v++)
        if (!visited[v]) {
            if (cost[v] <= min) {
                min = cost[v];
                closest_node_index = v;
            }
        }
    return closest_node_index;
}


double CalcDistance(const row& A, const row& B) {
    // Distance is calculated from the Haversine equation
    double radius_earth = 6356.752;

    double A_lat = A.lat * M_PI / 180;
    double A_lon = A.lon * M_PI / 180;
    double B_lat = B.lat * M_PI / 180;
    double B_lon = B.lon * M_PI / 180;

    //Haversine formula calculated in radians
    double delta_lat = A_lat - B_lat;
    double delta_lon = A_lon - B_lon;
    double hav = pow(sin(delta_lat/2), 2.0) + cos(A_lat) * cos(B_lat) * pow(sin(delta_lon/2), 2.0);

    double distance = 2 * asin(sqrt(hav)) * radius_earth;

    return distance;
}


std::vector<int> Dijkstra(const int graph[kStations][kStations], const int& initial_station_index, const int& goal_station_index) {

    std::vector<int> path;
    bool visited[kStations];
    double cost[kStations];
    int parent_node[kStations];

    // initializing node data
    for (int i = 0; i < kStations; i++) {
        visited[i] = false;
        cost[i] = LONG_MAX;
        parent_node[i] = -1;
    }
    cost[initial_station_index] = 0;

    for (int i = 0; i < kStations - 1; i++) {
        // select node with lowest cost
        int u = getClosestStation(cost, visited);
        visited[u] = true;
        // relax adjacent node costs
        for (int j = 0; j < kStations; j++)
            if (graph[u][j] && !visited[j] && ( cost[j] > cost[u] + graph[u][j])) {
                cost[j] = cost[u] + graph[u][j];
                parent_node[j] = u;
            }
    }

    int cur_node_index = goal_station_index;

    path.insert(path.begin(),goal_station_index);
    while(parent_node[cur_node_index]!=-1) {
        path.insert(path.begin(),parent_node[cur_node_index]);
        cur_node_index = parent_node[cur_node_index];
    }

    return path;
}


int main(int argc, char** argv) {
    if (argc != 3)
    {
        std::cout << "Error: requires initial and final supercharger names" << std::endl;
        return -1;
    }

    std::string initial_station_name = argv[1];
    std::string goal_station_name = argv[2];

    if (initial_station_name == goal_station_name)
        throw std::invalid_argument( "Error: input and goal stations are the same" );

    int graph[kStations][kStations];

    // Initializing charging network graph with time cost = time to arrive + time to recharge
    for (int i = 0; i < kStations; i++) {
        for (int j = 0; j < kStations; j++) {
            double distance = CalcDistance(network[i], network[j]);
            graph[i][j] = (distance > kRange) ? 0 : (distance/kSpeed + distance/network[j].rate);
        }
    }

    int initial_station_index  = getStationIndex(network, initial_station_name);
    int goal_station_index = getStationIndex(network, goal_station_name);

    std::vector<int> path = Dijkstra(graph, initial_station_index, goal_station_index);

    std::string result = network[path.front()].name + ", ";

    double distance, hours;

    for(int i=0; i<path.size()-2; i++) {
        int cur_node  = path[i];
        int next_node = path[i+1];
        if (i== path.size()-3) {
            // for last station before goal, charge only until car reaches goal with 0km kRange left
            distance = CalcDistance(
                    network[next_node],
                    network[path.back()]) - (kRange - CalcDistance(network[cur_node], network[next_node]));
            hours = distance/network[next_node].rate;
        } else {
            hours = CalcDistance(network[cur_node], network[next_node])/network[next_node].rate;
        }

        result +=  network[next_node].name + ", " + std::to_string(hours)+", ";
    }


    result += network[path.back()].name;
    std::cout<<result<<std::endl;

    return 0;
}
