#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

typedef std::pair<size_t, size_t> Pair;

typedef std::vector<bool> Vector1dBool;
typedef std::vector<int64_t> Vector1dInt64;
typedef std::vector<size_t> Vector1dSize;
typedef std::vector<Pair> Vector1dPair;
typedef std::vector<Vector1dInt64> Vector2d;

class Solver {
 public:
  void Input() {
    std::cin >> num_of_vertices_ >> num_of_edges_;
    num_of_vertices_++;

    graph_.resize(num_of_vertices_,
      Vector1dInt64(num_of_vertices_, kMaxWeight_));

    for (size_t i = 0; i < num_of_edges_; ++i) {
      size_t left, right;
      int64_t new_weight, old_weight;
      std::cin >> left >> right >> new_weight;
      old_weight = graph_[left][right];
      new_weight = std::min(new_weight, old_weight);
      graph_[left][right] = new_weight;
      graph_[right][left] = new_weight;
    }
  }

  void Request() {
    std::cout << MST();
  }

 private:
  size_t num_of_vertices_{};
  size_t num_of_edges_{};
  int64_t kMaxWeight_ = 1000000;

  Vector2d graph_{};

  int64_t MST() {
    Vector1dBool used(num_of_vertices_, false);
    Vector1dInt64 min_edge(num_of_vertices_, kMaxWeight_);
    Vector1dInt64 edge(num_of_vertices_, 0);

    int64_t weight = 0;

    min_edge[1] = 0;
    for (size_t i = 1; i < num_of_vertices_; ++i) {
      size_t cur = 0;
      for (size_t next = 1; next < num_of_vertices_; ++next) {
        if (!used[next] && (cur == 0 || min_edge[next] < min_edge[cur])) {
          cur = next;
        }
      }
      used[cur] = true;
      if (edge[cur] != 0) {
        weight += graph_[cur][edge[cur]];
      }
      for (int to = 1; to < num_of_vertices_; ++to) {
        if (graph_[cur][to] < min_edge[to]) {
          min_edge[to] = graph_[cur][to];
          edge[to] = cur;
        }
      }
    }
    return weight;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0), std::cout.tie(0);

  auto solver = Solver();
  solver.Input();
  solver.Request();
}