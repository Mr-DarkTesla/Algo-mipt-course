#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <utility>
#include <vector>

typedef std::vector<bool> Vector1dBool;
typedef std::vector<size_t> Vector1dSizeT;
typedef std::vector<Vector1dSizeT> Vector2d;

typedef std::pair<size_t, size_t> Pair;

class Solver {
 public:
  void Input() {
    std::cin >> planets_ >> num_of_paths_;
    planets_++;
    graph_.resize(planets_, Vector1dSizeT(0));
    for (size_t i = 0; i < num_of_paths_; ++i) {
      size_t left, right;
      std::cin >> left >> right;
      graph_[left].push_back(right);
    }
  }

  void Request() {
    Vector1dSizeT prev(planets_, 0);
    Vector1dSizeT colors(planets_, 0);
    for (size_t i = 1; i < planets_; ++i) {
      if (colors[i] == 0) {
        size_t cyc_v = Dfs(i, prev, colors);
        if (cyc_v != 0) {
          std::cout << "YES\n";
          OutCycle(cyc_v, prev);
          return;
        }
      }
    }
    std::cout << "NO";
  }

 private:
  size_t planets_{};
  size_t num_of_paths_{};
  Vector2d graph_{};

  size_t Dfs(size_t cur, Vector1dSizeT& prev, Vector1dSizeT& colors) {
    colors[cur] = 1;
    for (size_t next : graph_[cur]) {
      if (colors[next] == 0) {
        prev[next] = cur;
        size_t cyc = Dfs(next, prev, colors);
        if (cyc != 0) {
          return cyc;
        }
      } else if (colors[next] == 1) {
        prev[next] = cur;
        return next;
      }
    }
    colors[cur] = 2;
    return 0;
  }

  void OutCycle(size_t start, Vector1dSizeT& prev) {
    std::stack<size_t> stack;
    size_t cur = start;
    stack.push(cur);
    while (prev[cur] != start) {
      cur = prev[cur];
      stack.push(cur);
    }
    while (!stack.empty()) {
      cur = stack.top();
      stack.pop();
      std::cout << cur << " ";
    }
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0), std::cout.tie(0);

  auto solver = Solver();
  solver.Input();
  solver.Request();
}