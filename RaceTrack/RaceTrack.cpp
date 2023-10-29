#ifndef __PROGTEST__
#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cstdint>
#include <deque>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <optional>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

enum Point : size_t
{
};

struct Path
{
  Point from, to;
  unsigned length;

  Path(size_t f, size_t t, unsigned l) : from{f}, to{t}, length{l} {}

  friend bool operator==(const Path &a, const Path &b)
  {
    return std::tie(a.from, a.to, a.length) == std::tie(b.from, b.to, b.length);
  }

  friend bool operator!=(const Path &a, const Path &b) { return !(a == b); }
};

#endif
using namespace std;

vector<Path> TopologicalSort(const std::unordered_map<size_t, std::vector<Path>>& graph) {
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
    // std::cout << "Nejdelší cesta: ";
    // for (const Path& edge : longest_path_edges) {
    //     std::cout << "{" << edge.from << ", " << edge.to << ", " << edge.length << "} ";
    // }
    // std::cout << "Celková délka: " << max_length << std::endl;
    return longest_path_edges;
}

vector<Path> longest_track(size_t points, const vector<Path> &all_paths)
{
  unordered_map<size_t, vector<Path>> graph;
  for (const Path &path : all_paths)
  {
    // Přidejte hranu ze "from" do "to" do seznamu hran v mapě "graph".
    graph[path.from].push_back(path);
    // Pokud vrchol "to" není v mapě "graph", přidejte ho s prázdným seznamem hran.
    if (graph.find(path.to) == graph.end())
    {
      graph[path.to] = vector<Path>();
    }
  }

  vector<Path> result;
  result = TopologicalSort(graph);
  return result;
}

#ifndef __PROGTEST__

struct Test
{
  unsigned longest_track;
  size_t points;
  vector<Path> all_paths;
};

inline const Test TESTS[] = {
    {13, 5, {{3, 2, 10}, {3, 0, 9}, {0, 2, 3}, {2, 4, 1}}},
    {11, 5, {{3, 2, 10}, {3, 1, 4}, {1, 2, 3}, {2, 4, 1}}},
    {16, 8, {{3, 2, 10}, {3, 1, 1}, {1, 2, 3}, {1, 4, 15}}},
};

#define CHECK(cond, ...)          \
  do                              \
  {                               \
    if (cond)                     \
      break;                      \
    printf("Fail: " __VA_ARGS__); \
    printf("\n");                 \
    return false;                 \
  } while (0)

bool run_test(const Test &t)
{
  auto sol = longest_track(t.points, t.all_paths);

  unsigned length = 0;
  for (auto [_, __, l] : sol)
    length += l;

  CHECK(t.longest_track == length,
        "Wrong length: got %u but expected %u", length, t.longest_track);

  for (size_t i = 0; i < sol.size(); i++)
  {
    CHECK(count(t.all_paths.begin(), t.all_paths.end(), sol[i]),
          "Solution contains non-existent path: %zu -> %zu (%u)",
          sol[i].from, sol[i].to, sol[i].length);

    if (i > 0)
      CHECK(sol[i].from == sol[i - 1].to,
            "Paths are not consecutive: %zu != %zu", sol[i - 1].to, sol[i].from);
  }

  return true;
}
#undef CHECK

int main()
{
  int ok = 0, fail = 0;

  for (auto &&t : TESTS)
    (run_test(t) ? ok : fail)++;

  if (!fail)
    printf("Passed all %i tests!\n", ok);
  else
    printf("Failed %u of %u tests.\n", fail, fail + ok);
}

#endif
