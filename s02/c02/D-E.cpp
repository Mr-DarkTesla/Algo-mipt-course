#include <algorithm>
#include <iostream>
#include <stack>
#include <utility>
#include <vector>

typedef std::pair<size_t, int64_t> Pair;

typedef std::vector<bool> Vector1dBool;
typedef std::vector<int64_t> Vector1dInt64;
typedef std::vector<size_t> Vector1dSize;
typedef std::vector<Pair> Vector1dPair;
typedef std::vector<Vector1dInt64> Vector2d;

class Solver {
 public:
  void Input() {
    std::cin >> planets_;
    planets_++;
    graph_.resize(planets_, Vector1dInt64(planets_, kMaxWeight_));
    prev_.resize(planets_, 0);
    used_.resize(planets_, false);
    prev_.resize(planets_, 0);
    for (size_t from = 1; from < planets_; ++from) {
      for (size_t to = 1; to < planets_; ++to) {
        int64_t weight;
        std::cin >> weight;
        graph_[from][to] = weight;
      }
    }
  }

  void Request() {
    for (size_t unused = 1; unused < planets_; ++unused) {
      if (used_[unused]) {
        continue;
      }
      Vector1dInt64 distances = BellmanFord(unused);
      for (size_t from = 1; from < planets_; ++from) {
        for (size_t to = 1; to < planets_; ++to) {
          int64_t weight = graph_[from][to];
          if (weight == kMaxWeight_) {
            continue;
          }
          if (distances[from] != kMaxWeight_ &&
              distances[from] + weight < distances[to]) {
            std::cout << "YES\n";
            OutCycle(from);
            return;
          }
        }
      }
    }
    std::cout << "NO";
  }

 private:
  size_t planets_{};
  Vector2d graph_{};
  Vector1dSize prev_{};
  Vector1dBool used_{};

  int64_t kMaxWeight_ = 100000;

  Vector1dInt64 BellmanFord(size_t start_index) {
    Vector1dInt64 path_distances = Vector1dInt64(planets_, kMaxWeight_);
    path_distances[start_index] = 0;
    used_[start_index] = true;

    for (size_t _ = 0; _ < planets_; ++_) {
      for (size_t from = 1; from < planets_; ++from) {
        for (size_t to = 1; to < planets_; ++to) {
          int64_t weight = graph_[from][to];
          if (weight == kMaxWeight_) {
            continue;
          }
          if (path_distances[from] != kMaxWeight_ &&
              path_distances[from] + weight < path_distances[to]) {
            path_distances[to] = path_distances[from] + weight;
            prev_[to] = from;
            used_[to] = true;
          }
        }
      }
    }
    return path_distances;
  }

  void OutCycle(size_t x) { 
    size_t y = x;
    for (size_t i = 0; i < planets_; ++i) {
      y = prev_[y];
    }

    std::stack<size_t> cycle;
    for (size_t cur = y;; cur = prev_[cur]) {
      if (cur == y && cycle.size() > 1) {
        break;
      }
      cycle.push(cur);
    }
    std::cout << cycle.size() + 1 << "\n";
    size_t start = cycle.top();
    while (!cycle.empty()) {
      std::cout << cycle.top() << " ";
      cycle.pop();
    }
    std::cout << start << " ";
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0), std::cout.tie(0);

  auto solver = Solver();
  solver.Input();
  solver.Request();
}