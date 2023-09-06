#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

typedef std::vector<bool> Vector1dBool;
typedef std::vector<size_t> Vector1dSizeT;
typedef std::vector<Vector1dSizeT> Vector2d;

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
      graph_[right].push_back(left);
    }
  }

  void Request() {
    Vector1dSizeT color(planets_, 0);
    size_t col = 1;
    for (size_t i = 1; i < planets_; ++i) {
      if (color[i] == 0) {
        Bfs(i, color, col++);
      }
    }
    std::cout << col - 1 << "\n";
    Vector2d colors(col);
    for (size_t i = 1; i < planets_; ++i) {
      colors[color[i]].push_back(i);
    }
    for (size_t i = 1; i < col; ++i) {
      std::cout << colors[i].size() << "\n";
      for (auto el : colors[i]) {
        std::cout << el << " ";
      }
      std::cout << "\n";
    }
  }

 private:
  size_t planets_{};
  size_t num_of_paths_{};
  Vector2d graph_{};

  void Bfs(size_t start, Vector1dSizeT& used, size_t col) {
    std::queue<size_t> que;
    que.push(start);
    used[start] = planets_ + 1;
    while (!que.empty()) {
      size_t cur = que.front();
      used[cur] = col;
      for (size_t next : graph_[cur]) {
        if (used[next] == 0) {
          que.push(next);
          used[next] = cur;
        }
      }
      que.pop();
    }
  }
};

int main() {
  auto solver = Solver();
  solver.Input();
  solver.Request();
}