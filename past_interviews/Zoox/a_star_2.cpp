#include <algorithm>
#include <cstdint>
#include <queue>
#include <vector>

struct Edge {
    uint8_t to_node_id;
    uint8_t weight;
};

struct Node {
    uint8_t my_id;
    uint8_t g_cost;
    uint8_t f_cost;
    bool operator>(const Node& rhs) const {
        return this->f_cost > rhs.f_cost;
    }
};

struct AStarResult {
    std::vector<uint8_t> solution;
    std::vector<uint8_t> path;
};

auto AStar(const uint8_t source_node_id, const uint8_t target_node_id, const std::vector<std::vector<Edge>>& graph, const std::vector<uint8_t>& h_cost) -> AStarResult {
    const auto no_of_nodes{graph.size()};
    std::vector<uint8_t> solution(no_of_nodes, UINT8_MAX);
    solution[source_node_id] = static_cast<uint8_t>(0);
    std::priority_queue<Node, std::vector<Node>, std::greater<>> node_pq;
    node_pq.push({source_node_id, 0, h_cost[source_node_id]});
    bool target_reached{false};
    std::vector<uint8_t> parent(no_of_nodes, UINT8_MAX);

    while (!node_pq.empty()) {
        const auto current_node{node_pq.top()};
        node_pq.pop();

        if (current_node.my_id == source_node_id) {
            target_reached = true;
            break;
        }

        if (current_node.g_cost > solution[current_node.my_id]) {
            continue;
        }

        for (const auto& edge : graph[current_node.my_id]) {
            if (solution[current_node.my_id] + edge.weight < solution[edge.to_node_id]) {
                solution[edge.to_node_id] = solution[current_node.my_id]  + edge.weight;
                const auto f_cost = static_cast<uint8_t>(solution[edge.to_node_id] + h_cost[edge.to_node_id]);
                node_pq.push({edge.to_node_id, solution[edge.to_node_id], f_cost});
                parent[edge.to_node_id] = current_node.my_id;
            }
        }
    }

    std::vector<uint8_t> path;
    if (target_reached && solution[target_node_id]!=UINT8_MAX) {
        auto current_node_id{target_node_id};
        while (current_node_id != source_node_id) {
            path.push_back(current_node_id);
            current_node_id = path[current_node_id];
        }
        path.push_back(source_node_id);
        std::ranges::reverse(path);
    }

    return {solution, path};
}
