//
// Created by Kumar Chakravarthy on 10/30/2022.
//
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>


class Graph {
public:
    std::unordered_map<int, std::vector<int>> adjacency_list; // hash-map : key(vertex), value(vector of neighbouring vertices)
    std::unordered_set<int> visited_set; // hash-set of visited_set vertices
    std::vector<int> bfs_queue; // BFS queue, I need to change this to a linked list

public:
    Graph();
    void addEdge(int src, int dest);
    void addToQueue(int vertex);
    void BFS(int start_vertex);
};


Graph::Graph() {
    std::cout<<"Constructor called\n";
}


//build the adjacency list
void Graph::addEdge(int src, int dest) { // undirected graph
    std::cout<<"Add edge called\n";
    if(src != dest) { // not creating an edge to self
        if(std::find(adjacency_list[src].begin(), adjacency_list[src].end(), dest) == adjacency_list[src].end()) // edge not already added
            adjacency_list[src].push_back(dest);
        if(std::find(adjacency_list[dest].begin(), adjacency_list[dest].end(), src) == adjacency_list[dest].end()) // edge not already added
            adjacency_list[dest].push_back(src);
    }
}


void Graph::addToQueue(int vertex) {
    if(visited_set.find(vertex) == visited_set.end()) { // vertex not in visited_set
        visited_set.insert(vertex);
        bfs_queue.push_back(vertex);
        std::cout<<vertex<<" ";
    }
}


//iterative and queue (FIFO)
//maintain visited_set
/*
add start vertex to queue
    mark as visited_set
while queue not empty
 add adj elements to queue
    mark as visited_set
 pop front ele out of queue
 */
void Graph::BFS(int start_vertex) {
    addToQueue(start_vertex);

    while(!bfs_queue.empty()) { // queue not empty
        int current_vertex = bfs_queue.front(); // retrieve first ele in queue
        //add all adjacent vertices of current vertex to queue
        for (int i = 0; i < adjacency_list[current_vertex].size(); ++i)
            addToQueue(adjacency_list[current_vertex][i]);
        bfs_queue.erase(bfs_queue.begin()); // pop first ele from queue
    }
}


int main() {
    Graph g;
    g.addEdge(0,1);
    g.addEdge(0,2);
    g.addEdge(1,2);
    g.addEdge(2,0);
    g.addEdge(2,3);
    g.addEdge(3,3);

    for(auto it:g.adjacency_list) {
        std::cout<<it.first<<": ";
        for(auto vertex:it.second) {
            std::cout<<vertex<<" ";
        }
        std::cout<<std::endl;
    }

    g.BFS(3);

    return 0;
}
