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
    Vector1dSizeT colors(planets_, 0);
    std::stack<size_t> stack;
    for (size_t i = 1; i < planets_; ++i) {
      if (colors[i] == 0) {
        bool cyc_v = Dfs(i, colors, stack);
        if (cyc_v) {
          std::cout << "-1";
          return;
        }
      }
    }
    while (!stack.empty()) {
      std::cout << stack.top() << " ";
      stack.pop();
    }
  }

 private:
  size_t planets_{};
  size_t num_of_paths_{};
  Vector2d graph_{};

  bool Dfs(size_t cur, Vector1dSizeT& colors, std::stack<size_t>& stack) {
    colors[cur] = 1;
    for (size_t next : graph_[cur]) {
      if (colors[next] == 0) {
        if (Dfs(next, colors, stack)) {
          return true;
        }
      } else if (colors[next] == 1) {
        return true;
      }
    }
    colors[cur] = 2;
    stack.push(cur);
    return false;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0), std::cout.tie(0);

  auto solver = Solver();
  solver.Input();
  solver.Request();
}