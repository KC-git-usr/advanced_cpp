#include <cstdint>
#include <cstdio>
#include <queue>
#include <vector>

struct Edge {
    std::uint8_t to_node_id;
    std::uint8_t weight;
};

struct Node {
    std::uint8_t my_id;
    std::uint8_t distance;

    bool operator>(const Node& rhs) const {
        return distance > rhs.distance;
    }
};

auto Dijstra(const std::uint8_t source_node_id, const std::vector<std::vector<Edge>>& graph) -> std::vector<uint8_t> {
    const auto num_of_nodes{graph.size()};
    std::vector<uint8_t> solution(num_of_nodes, UINT8_MAX);
    solution[source_node_id] = 0;
    std::priority_queue<Node, std::vector<Node>, std::greater<>> node_pq;
    node_pq.push({source_node_id, 0});

    while (!node_pq.empty()) {
        auto current_node = node_pq.top();
        node_pq.pop();

        if (current_node.distance > solution[current_node.my_id]) {
            continue;
        }

        // relax neighbors
        for (const auto& edge : graph[current_node.my_id]) {
            if (solution[current_node.my_id] + edge.weight < solution[edge.to_node_id]) {
                solution[edge.to_node_id] = solution[current_node.my_id] + edge.weight;
                node_pq.push({edge.to_node_id, solution[edge.to_node_id]});
            }
        }
    }

    return solution;
}

int main(int argc, char const *argv[]) {
    constexpr std::uint8_t num_nodes{5};
    std::vector<std::vector<Edge>> graph(num_nodes);

    graph[0].push_back({1, 4});
    graph[0].push_back({2, 2});
    graph[1].push_back({2, 3});
    graph[1].push_back({3, 2});
    graph[1].push_back({4, 3});
    graph[2].push_back({1, 1});
    graph[2].push_back({3, 4});
    graph[2].push_back({4, 5});
    graph[4].push_back({3, 1});

    constexpr uint8_t source_node_id{0};
    const auto solution = Dijstra(source_node_id, graph);

    // Print the output to verify correctness
    for (std::size_t i = 0; i < solution.size(); ++i) {
        printf("Distance to %lu: %d\n", i, solution[i]);
    }
}
