#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

typedef std::pair<size_t, size_t> Pair;
typedef std::pair<int64_t, Pair> Edge;

typedef std::vector<bool> Vector1dBool;
typedef std::vector<int64_t> Vector1dInt64;
typedef std::vector<size_t> Vector1dSize;
typedef std::vector<Pair> Vector1dPair;

typedef std::vector<Vector1dInt64> Vector2d;

class Solver {
 public:
  void Input() {
    std::cin >> num_of_vertices_;
    graph_.resize(num_of_vertices_ + 1, Vector1dInt64(num_of_vertices_ + 1, 0));
    for (int64_t row = 0; row < num_of_vertices_; ++row) {
      for (int64_t col = 0; col < num_of_vertices_; ++col) {
        std::cin >> graph_[row][col];
      }
    }
    for (int64_t last = 0; last < num_of_vertices_; ++last) {
      std::cin >> graph_[num_of_vertices_][last];
      graph_[last][num_of_vertices_] = graph_[num_of_vertices_][last];
    }
  }

  void Request() { std::cout << Prim(); }

  void OutGraph() { 
    for (auto row : graph_) {
      for (auto el : row) {
        std::cout << el << " ";
      }
      std::cout << "\n";
    }
  }

 private:
  size_t num_of_vertices_{};

  Vector2d graph_{};
  Vector1dBool used_{};

  int64_t Prim() {
    used_.resize(num_of_vertices_ + 1, false);
    Edge min_edge = {graph_[0][1], {0, 1}};
    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> heap;

    for (int64_t row = 0; row < num_of_vertices_ + 1; ++row) {
      for (int64_t col = 0; col < num_of_vertices_ + 1; ++col) {
        if (row != col) {
          min_edge = std::min(min_edge, {graph_[row][col], {row, col}});
        }
      }
    }
    heap.push(min_edge);

    int64_t total_size = 0;
    int64_t total_weight = 0;

    while (total_size < num_of_vertices_ && !heap.empty()) {

      Edge cur = heap.top();
      int64_t cur_weight = cur.first;
      size_t cur_from = cur.second.first;
      size_t cur_to = cur.second.second;
      heap.pop();

      if (used_[cur_from] && used_[cur_to]) {
        continue;
      }
      total_weight += cur_weight;
      used_[cur_from] = true;
      used_[cur_to] = true;

      total_size++;
      Edge next_edge{};
      for (int64_t next = 0; next <= num_of_vertices_; ++next) {
        if (used_[next]) {
          continue;
        }
        if (next != cur_from) {
          next_edge = {graph_[cur_from][next], {cur_from, next}};
          heap.push(next_edge);
        }
        if (next != cur_to) {
          next_edge = {graph_[cur_to][next], {cur_to, next}};
          heap.push(next_edge);
        }
      }
    }
    return total_weight;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0), std::cout.tie(0);

  auto solver = Solver();
  solver.Input();
  solver.Request();
}