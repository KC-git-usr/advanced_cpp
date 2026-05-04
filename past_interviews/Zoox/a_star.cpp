#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <queue>
#include <vector>

struct Edge {
    uint8_t to_node_id;
    uint8_t weight;
};

struct Node {
    uint8_t my_id;
    uint8_t g;
    uint8_t f;  // f = g + h

    bool operator>(const Node& rhs) const {
        return f > rhs.f;
    }
};

struct AStarResult {
    std::vector<uint8_t> distances;
    std::vector<uint8_t> path;
};

auto AStar(const uint8_t source_node_id, const uint8_t target_node_id, const std::vector<std::vector<Edge>>& graph, const std::vector<uint8_t>& h) -> AStarResult{
    const auto num_of_nodes{graph.size()};
    std::vector<uint8_t> g_solution(num_of_nodes, UINT8_MAX);
    g_solution[source_node_id] = 0;
    std::vector<uint8_t> parent(num_of_nodes, UINT8_MAX);
    bool target_reached{false};
    std::priority_queue<Node, std::vector<Node>, std::greater<>> node_pq;
    const auto source_f_cost = static_cast<uint8_t>(g_solution[source_node_id] + h[source_node_id]);
    node_pq.push({source_node_id, g_solution[source_node_id], source_f_cost});

    while (!node_pq.empty()) {
        auto current_node = node_pq.top();
        node_pq.pop();

        if (current_node.my_id == target_node_id) {
            target_reached = true;
            break;
        }

        if (current_node.g > g_solution[current_node.my_id]) {
            continue;
        }

        for (const auto& edge : graph[current_node.my_id]) {
            if (g_solution[current_node.my_id] + edge.weight < g_solution[edge.to_node_id]) {
                g_solution[edge.to_node_id] = g_solution[current_node.my_id] + edge.weight;
                const auto f = static_cast<uint8_t>(g_solution[edge.to_node_id] + h[edge.to_node_id]);
                node_pq.push({edge.to_node_id, g_solution[edge.to_node_id], f});
                parent[edge.to_node_id] = current_node.my_id;
            }
        }
    }

    std::vector<uint8_t> path;
    if (target_reached && g_solution[target_node_id] != UINT8_MAX) {
        uint8_t current_node_id = target_node_id;
        while (current_node_id != source_node_id) {
            path.push_back(current_node_id);
            current_node_id = parent[current_node_id];
        }
        path.push_back(source_node_id);

        std::ranges::reverse(path);
    }

    return {g_solution, path};
}

int main(int argc, char const *argv[]) {
    constexpr auto kNumOfNodes{5};
    std::vector<std::vector<Edge>> graph(kNumOfNodes);

    graph[0].push_back({1, 4});
    graph[0].push_back({2, 2});
    graph[1].push_back({2, 3});
    graph[1].push_back({3, 2});
    graph[1].push_back({4, 3});
    graph[2].push_back({1, 1});
    graph[2].push_back({3, 4});
    graph[2].push_back({4, 5});
    graph[4].push_back({3, 1});

    // Dummy heuristic values: estimated distance from node i to target node 3.
    // For the heuristic to be valid, it must be admissible (never overestimate).
    std::vector<std::uint8_t> heuristic = {3, 2, 2, 0, 1};

    constexpr uint8_t source_node_id{0};
    constexpr uint8_t target_node_id{3};
    const auto solution = AStar(source_node_id, target_node_id, graph, heuristic);

    printf("Shortest distance to target %d is: %d\n", target_node_id, solution.distances[target_node_id]);
    printf("The path is: ");
    for (auto node : solution.path) {
        printf("%d ", node);
    }

    return 0;
}
