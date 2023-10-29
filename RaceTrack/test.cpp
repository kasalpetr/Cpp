#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include<algorithm>

struct Path {
    size_t from, to;
    unsigned length;
};

void TopologicalSort(const std::unordered_map<size_t, std::vector<Path>>& graph) {
    std::unordered_map<size_t, int> in_degree;
    std::queue<size_t> zero_in_degree;

    for (const auto& entry : graph) {
        for (const Path& edge : entry.second) {
            in_degree[edge.to]++;
        }
    }

    for (const auto& entry : graph) {
        size_t node = entry.first;
        if (in_degree.find(node) == in_degree.end() || in_degree[node] == 0) {
            zero_in_degree.push(node);
        }
    }

    // Inicializace délky nejdelší cesty do každého vrcholu.
    std::unordered_map<size_t, unsigned> longest_path;
    for (const auto& entry : graph) {
        longest_path[entry.first] = 0;
    }

    // Inicializace předchůdců pro rekonstrukci nejdelší cesty.
    std::unordered_map<size_t, size_t> predecessors;

    while (!zero_in_degree.empty()) {
        size_t node = zero_in_degree.front();
        zero_in_degree.pop();

        for (const Path& edge : graph.at(node)) {
            size_t neighbor = edge.to;
            if (longest_path[node] + edge.length > longest_path[neighbor]) {
                longest_path[neighbor] = longest_path[node] + edge.length;
                predecessors[neighbor] = node;
            }

            in_degree[neighbor]--;
            if (in_degree[neighbor] == 0) {
                zero_in_degree.push(neighbor);
            }
        }
    }

    // Rekonstrukce nejdelší cesty od posledního vrcholu zpět k prvnímu.
    size_t current_node = 0;  // První vrchol
    unsigned max_length = 0;
    for (const auto& entry : longest_path) {
        if (entry.second > max_length) {
            max_length = entry.second;
            current_node = entry.first;
        }
    }

    std::vector<Path> longest_path_edges;
    while (predecessors.find(current_node) != predecessors.end()) {
        size_t predecessor = predecessors[current_node];
        for (const Path& edge : graph.at(predecessor)) {
            if (edge.to == current_node) {
                longest_path_edges.push_back(edge);
                break;
            }
        }
        current_node = predecessor;
    }
    
   std::reverse(longest_path_edges.begin(), longest_path_edges.end());
    // Výpis nejdelší cesty a její délky.
    std::cout << "Nejdelší cesta: ";
    for (const Path& edge : longest_path_edges) {
        std::cout << "{" << edge.from << ", " << edge.to << ", " << edge.length << "} ";
    }
    std::cout << "Celková délka: " << max_length << std::endl;
}

int main() {
    std::unordered_map<size_t, std::vector<Path>> graph;
    std::vector<Path> all_paths = {{3, 2, 10}, {3, 1, 1}, {1, 2, 3}, {1, 4, 15}};

    for (const Path& path : all_paths) {
        graph[path.from].push_back(path);

        if (graph.find(path.to) == graph.end()) {
            graph[path.to] = std::vector<Path>();
        }
    }

    TopologicalSort(graph);
    return 0;
}
