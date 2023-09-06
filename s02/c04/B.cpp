#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

typedef std::pair<size_t, int64_t> Pair;

struct Edge {
  size_t from;
  size_t to;
  size_t flow;
  size_t capacity;

  Edge(size_t from, size_t to, size_t cap)
      : from(from), to(to), flow(0), capacity(cap) {}

  Edge() : from(0), to(0), flow(0), capacity(0) {}

  size_t Capacity() const { return capacity - flow; }
};

typedef std::vector<bool> Vector1dBool;
typedef std::vector<int64_t> Vector1dInt64;
typedef std::vector<size_t> Vector1dSize;
typedef std::vector<Pair> Vector1dPair;

typedef std::vector<Edge> Vector1dEdge;
typedef std::vector<Vector1dInt64> Vector2d;

class Solver {
 public:
  void Input() {
    std::cin >> num_left_ >> num_right_;

    edges_.resize(0);
    graph_.resize(num_left_ + num_right_ + 2, Vector1dInt64(0));
    used_.resize(num_left_ + num_right_ + 2, 0);

    for (size_t left = 0; left < num_left_; ++left) {
      size_t right;
      std::cin >> right;
      while (right != 0) {
        AddEdge(1 + left, num_left_ + right, 1);
        std::cin >> right;
      } 
    }
  }

  void Request() {
    start_ = 0;
    finish_ = num_left_ + num_right_ + 1;
    for (size_t left = 0; left < num_left_; ++left) {
      AddEdge(start_, 1 + left, 1);
    }
    for (size_t right = 0; right < num_right_; ++right) {
      AddEdge(num_left_ + right + 1, finish_, 1);
    }
    MaxFlow();
    OutAns();
  }

  

 private:
  const size_t kMaxCap = 100000;
  size_t num_left_{};
  size_t num_right_{};

  Vector1dEdge edges_{};
  Vector2d graph_{};

  size_t start_;
  size_t finish_;

  Vector1dSize used_{};

  void AddEdge(size_t left, size_t right, size_t capacity) {
    graph_[left].emplace_back(edges_.size());
    edges_.emplace_back(Edge(left, right, capacity));
    graph_[right].emplace_back(edges_.size());
    edges_.emplace_back(Edge(right, left, 0));
  }

  void MaxFlow() {
    size_t time = 1;
    while (Dfs(start_, kMaxCap, time++) != 0) {
    }
  }

  void OutAns() {
    size_t result = 0;
    for (size_t index : graph_[start_]) {
      size_t flow = edges_[index].flow;
      result += flow;
    }
    std::cout << result << std::endl;
    for (size_t from = 1; from < num_left_ + 1; ++from) {
      for (size_t index : graph_[from]) {
        size_t to = edges_[index].to - num_left_;
        size_t flow = edges_[index].flow;
        if (flow == 1) {
          std::cout << from << " " << to << std::endl;
        }
      }
    }
  }

  size_t Dfs(size_t vertex, size_t min_cap, size_t time) {
    if (vertex == finish_) {
      return min_cap;
    }
    used_[vertex] = time;
    for (size_t idx : graph_[vertex]) {
      size_t to = edges_[idx].to;
      size_t cap = edges_[idx].Capacity();
      if (cap == 0) {
        continue;
      }
      if (used_[to] == time) {
        continue;
      }
      size_t flow = Dfs(to, std::min(min_cap, cap), time);
      if (flow != 0) {
        edges_[idx].flow += flow;
        edges_[idx ^ 1].flow -= flow;
        return flow;
      }
    }
    return 0;
  }

  void OutGraph() {
    for (size_t vertex = 0; vertex < num_left_ + num_right_ + 2; vertex++) {
      for (size_t index : graph_[vertex]) {
        size_t from = edges_[index].from;
        size_t to = edges_[index].to;
        size_t cap = edges_[index].capacity;
        if (cap != 0) {
          std::cout << from << " -" << cap << "> " << to << std::endl;
        }
      }
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