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


enum Point : size_t {};

struct Path {
  Point from, to;
  unsigned length;

  Path(size_t f, size_t t, unsigned l) : from{f}, to{t}, length{l} {}

  friend bool operator == (const Path& a, const Path& b) {
    return std::tie(a.from, a.to, a.length) == std::tie(b.from, b.to, b.length);
  }
  
  friend bool operator != (const Path& a, const Path& b) { return !(a == b); }
};

#endif
using namespace std;

std::vector<Path> longest_track(size_t points, const std::vector<Path>& all_paths){
std::unordered_map<size_t, std::vector<Path>> graph;
    for (const Path& path : all_paths) {
        graph[path.from].push_back(path);
    }

    // Funkce pro topologické seřazení grafu (DFS).
    std::vector<bool> visited(points, false);
    std::vector<size_t> topological_order;

    std::function<void(size_t)> dfs = [&](size_t v) {
        visited[v] = true;
        for (const Path& edge : graph[v]) {
            if (!visited[edge.to]) {
                dfs(edge.to);
            }
        }
        topological_order.push_back(v);
    };

    // Pro každou křižovatku spustíme DFS, abychom získali topologické seřazení.
    for (size_t i = 0; i < points; ++i) {
        if (!visited[i]) {
            dfs(i);
        }
    }

    std::vector<unsigned> max_length(points, 0);
    std::vector<size_t> prev(points, points);

    // Procházíme topologické seřazení a hledáme nejdelší cesty.
    for (size_t v : topological_order) {
        for (const Path& edge : graph[v]) {
            if (max_length[v] + edge.length > max_length[edge.to]) {
                max_length[edge.to] = max_length[v] + edge.length;
                prev[edge.to] = v;
            }
        }
    }

    // Hledáme křižovatku, na které končí nejdelší trať.
    size_t end_point = 0;
    unsigned max_path_length = 0;
    for (size_t i = 0; i < points; ++i) {
        if (max_length[i] > max_path_length) {
            max_path_length = max_length[i];
            end_point = i;
        }
    }

    // Rekonstruujeme nejdelší trať od konce zpět.
    std::vector<Path> result;
    size_t current_point = end_point;
    while (current_point != points) {
        size_t previous_point = prev[current_point];
        for (const Path& edge : graph[previous_point]) {
            if (edge.to == current_point) {
                result.push_back(edge);
                break;
            }
        }
        current_point = previous_point;
    }

    // Obrátíme cesty, aby směřovaly z kopce dolů.
    std::reverse(result.begin(), result.end());

  for (const Path& path : result) {
    std::cout << "From " << path.from << " to " << path.to << ", Length: " << path.length << std::endl;
}
    return result;

}


#ifndef __PROGTEST__


struct Test {
  unsigned longest_track;
  size_t points;
  std::vector<Path> all_paths;
};

inline const Test TESTS[] = {
  {13, 5, { {3,2,10}, {3,0,9}, {0,2,3}, {2,4,1} } },
  {11, 5, { {3,2,10}, {3,1,4}, {1,2,3}, {2,4,1} } },
  {16, 8, { {3,2,10}, {3,1,1}, {1,2,3}, {1,4,15} } },
};

#define CHECK(cond, ...) do { \
    if (cond) break; \
    printf("Fail: " __VA_ARGS__); \
    printf("\n"); \
    return false; \
  } while (0)

bool run_test(const Test& t) {
  auto sol = longest_track(t.points, t.all_paths);

  unsigned length = 0;
  for (auto [ _, __, l ] : sol) length += l;

  CHECK(t.longest_track == length,
    "Wrong length: got %u but expected %u", length, t.longest_track);

  for (size_t i = 0; i < sol.size(); i++) {
    CHECK(std::count(t.all_paths.begin(), t.all_paths.end(), sol[i]),
      "Solution contains non-existent path: %zu -> %zu (%u)",
      sol[i].from, sol[i].to, sol[i].length);

    if (i > 0) CHECK(sol[i].from == sol[i-1].to,
      "Paths are not consecutive: %zu != %zu", sol[i-1].to, sol[i].from);
  }

  return true;
}
#undef CHECK

int main() {
  int ok = 0, fail = 0;

  for (auto&& t : TESTS) (run_test(t) ? ok : fail)++;
  
  if (!fail) printf("Passed all %i tests!\n", ok);
  else printf("Failed %u of %u tests.\n", fail, fail + ok);
}

#endif


