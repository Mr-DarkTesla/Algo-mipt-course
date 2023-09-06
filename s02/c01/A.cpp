#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <queue>

typedef std::vector<bool> Vector1dBool;
typedef std::vector<size_t> Vector1dSize;
typedef std::vector<Vector1dBool> Vector2d;

class Solver {
 public:
  void Input() {
    std::cin >> planets_ >> num_of_paths_;
    planets_++;
    graph_.resize(planets_, Vector1dBool(planets_, false));
    std::cin >> start_ >> finish_;
    for (size_t i = 0; i < num_of_paths_; ++i) {
      size_t left, right;
      std::cin >> left >> right;
      graph_[left][right] = true;
      graph_[right][left] = true;
    }
  }

  void Request() { 
    Vector1dSize ans(planets_, 0);
    bfs(start_, ans);
    if (ans[finish_] != 0) {
      Vector1dSize path(0);
      size_t length = 0;
      size_t cur = finish_;
      while (cur != start_) {
        ++length;
        path.push_back(cur);
        cur = ans[cur];
      }
      path.push_back(cur);
      std::cout << length << std::endl;
      for (int64_t i = length; i >= 0; i--) {
        std::cout << path[i] << " ";
      }
    } else {
      std::cout << -1;
    }
  }

 private:
  size_t planets_{};
  size_t num_of_paths_{};
  Vector2d graph_{};

  size_t start_{};
  size_t finish_{};

  void bfs(size_t start, Vector1dSize & used) { 
    std::queue<size_t> que;
    que.push(start);
    used[start] = planets_ + 1; 
    while (!que.empty()) {
      size_t cur = que.front();
      for (size_t next = 0; next < planets_; ++next) {
        if (graph_[cur][next] && used[next] == 0) {
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