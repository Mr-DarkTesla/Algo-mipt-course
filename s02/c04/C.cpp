#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>
#include <set>

typedef std::pair<size_t, int64_t> Pair;

struct Edge {
  size_t from;
  size_t to;
  int64_t flow;
  int64_t capacity;

  Edge(size_t from, size_t to, int64_t cap)
      : from(from), to(to), flow(0), capacity(cap) {}

  Edge() : from(0), to(0), flow(0), capacity(0) {}

  int64_t Capacity() const { return capacity - flow; }
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
    std::cin >> num_of_vertices_ >> num_of_edges_;

    edges_.resize(0);
    graph_.resize(num_of_vertices_, Vector1dInt64(0));
    used_.resize(num_of_vertices_, 0);

    for (size_t i = 0; i < num_of_edges_; ++i) {
      size_t left;
      size_t right;
      size_t capacity;
      std::cin >> left >> right >> capacity;
      AddEdge(--left, --right, capacity);
    }
  }

  void Request() {
    start_ = 0;
    finish_ = num_of_vertices_ - 1;

    size_t time = 1;
    while (Dfs(start_, kMaxCap, time++) != 0) {
    }
    MinCut();  
  }

 private:
  const int64_t kMaxCap = 10000000;
  size_t num_of_vertices_{};
  size_t num_of_edges_{};

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

  void MinCut() {
    std::set<size_t> droped;
    int64_t sum = 0;

    while (true) {
      Vector1dBool color(num_of_vertices_, true);

      std::queue<size_t> queue;
      queue.push(start_);
      color[start_] = false;

      while (!queue.empty()) {
        size_t cur = queue.front();
        queue.pop();
        color[cur] = false;

        for (size_t idx : graph_[cur]) {
          size_t to = edges_[idx].to;
          int64_t cap = edges_[idx].Capacity();
          if (cap > 0) {
            queue.push(to);
          }
        }
      }

      size_t idx = 0;
      for (Edge edge : edges_) {
        size_t to = edge.to;
        size_t from = edge.from;
        if (color[to] != color[from] && idx % 2 == 0) {
          droped.insert(idx);
          sum += edge.capacity;
          edges_[idx].capacity = edges_[idx].flow;
          edges_[idx ^ 1].capacity = edges_[idx].flow;
        }
        idx++;
      }

      if (color[finish_]) {
        std::cout << droped.size() << " " << sum << std::endl;
        for (size_t idx : droped) {
          if (idx % 2 != 0) {
            throw "idx !2";
          }
          std::cout << idx / 2 + 1 << " ";
        }
        return;
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