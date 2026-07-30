#include <cstdint>
#include <queue>
#include <vector>

struct Edge {
    uint8_t to_node_id;
    uint8_t weight;
};

struct Node {
    uint8_t my_id;
    uint8_t distance;

    bool operator>(const Node& rhs) const {
        return this->distance > rhs.distance;
    }
};

auto Dijstra(const uint8_t source_node_id, const std::vector<std::vector<Edge>>& graph) -> std::vector<uint8_t> {
    const auto no_of_nodes{graph.size()};
    std::vector<uint8_t> solution(no_of_nodes, UINT8_MAX);
    solution[source_node_id] = 0;
    std::priority_queue<Node, std::vector<Node>, std::greater<>> node_pq;
    node_pq.push({source_node_id, 0});

    while (!node_pq.empty()) {
        const auto current_node{node_pq.top()};
        node_pq.pop();

        if (current_node.distance > solution[current_node.my_id]) {
            continue;
        }

        for (const auto& edge : graph[current_node.my_id]) {
            if (solution[current_node.my_id] + edge.weight < solution[edge.to_node_id]) {
                solution[edge.to_node_id] = solution[current_node.my_id] + edge.weight;
                node_pq.push({edge.to_node_id, solution[edge.to_node_id]});
            }
        }
    }
    return solution;
}
