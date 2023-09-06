#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <utility>
#include <vector>

typedef std::pair<size_t, int64_t> Pair;

typedef std::vector<bool> Vector1dBool;
typedef std::vector<int64_t> Vector1dInt64;
typedef std::vector<size_t> Vector1dSize;
typedef std::vector<Pair> Vector1dPair;
typedef std::vector<Vector1dBool> Vector2d;

class Solver {
 public:
  void Input() {
    std::cin >> planets_;
    planets_++;
    graph_.resize(planets_, Vector1dBool(planets_, false));
    used_.resize(planets_, false);
    for (size_t from = 1; from < planets_; ++from) {
      for (size_t to = 1; to < planets_; ++to) {
        bool bool_connection;
        std::cin >> bool_connection;
        graph_[from][to] = bool_connection;
      }
    }
  }

  void Request() {
    for (size_t unused = 1; unused < planets_; ++unused) {
      Vector1dBool mask = Vector1dBool(planets_, false);
      Bfs(unused, mask);
      for (size_t i = 1; i < planets_; ++i) {
        std::cout << int(mask[i]) << " ";
      }
      std::cout << "\n";
    }
  }

 private:
  size_t planets_{};
  Vector2d graph_{};
  Vector1dBool used_{};

  void Bfs(size_t start, Vector1dBool& mask) {
    std::queue<size_t> que;
    que.push(start);
    while (!que.empty()) {
      size_t cur = que.front();
      for (size_t next = 1; next < planets_; ++next) {
        if (graph_[cur][next] && !mask[next]) {
          que.push(next);
          mask[next] = true;
        }
      }
      que.pop();
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