#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>
#include <tuple>

typedef std::pair<size_t, int64_t> Pair;
typedef std::tuple<size_t, size_t, int64_t> Tuple;

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
      int64_t capacity;
      std::cin >> left >> right >> capacity;
      AddEdge(--left, --right, capacity);
    }
  }

  void Request() {
    start_ = 0;
    finish_ = num_of_vertices_ - 1;

//    int64_t max_flow = 0;
    while (Bfs()) {
      used_.assign(num_of_vertices_, 0);
      int64_t flow = Dfs(start_, kMaxCap);
      while (flow != 0) {
//        max_flow += flow;
        flow = Dfs(start_, kMaxCap);

      }
    }
    OutAns();
  }

 private:
  const size_t kMaxCap = 10000000000;
  size_t num_of_vertices_{};
  size_t num_of_edges_{};

  Vector1dEdge edges_{};
  Vector2d graph_{};

  size_t start_ = 0;
  size_t finish_ = 0;

  Vector1dSize used_{};
  Vector1dInt64 dist_{};

  void AddEdge(size_t left, size_t right, int64_t capacity) {
    graph_[left].emplace_back(edges_.size());
    edges_.emplace_back(Edge(left, right, capacity));
    graph_[right].emplace_back(edges_.size());
    edges_.emplace_back(Edge(right, left, 0));
  }

  int64_t Dfs(size_t vertex, int64_t flow_push) {
    if (vertex == finish_ || flow_push == 0) {
      return flow_push;
    }
    for (size_t idx : graph_[vertex]) {
      size_t to = edges_[idx].to;
      int64_t cap = edges_[idx].Capacity();
      if (dist_[to] != dist_[vertex] + 1) {
        continue;
      }
      size_t flow = Dfs(to, std::min(flow_push, cap));
      if (flow != 0) {
        edges_[idx].flow += flow;
        edges_[idx ^ 1].flow -= flow;
        return flow;
      }
      used_[vertex]++;
    }
    return 0;
  }

  bool Bfs() { 
    dist_.assign(num_of_vertices_, -1);

    std::queue<size_t> queue;
    queue.push(start_);
    dist_[start_] = 0;

    while (!queue.empty()) {
      size_t cur = queue.front();
      queue.pop();

      for (size_t idx : graph_[cur]) {
        size_t to = edges_[idx].to;
        int64_t cap = edges_[idx].Capacity();
        if (cap > 0 && dist_[to] == -1) {
          dist_[to] = dist_[cur] + 1;
          queue.push(to);
        }
      }
    }
    return dist_[finish_] != -1;
  }

  void OutGraph() {
    for (size_t vertex = 0; vertex < num_of_vertices_; vertex++) {
      for (size_t index : graph_[vertex]) {
        size_t from = edges_[index].from;
        size_t to = edges_[index].to;
        int64_t cap = edges_[index].capacity;
        if (cap != 0) {
          std::cout << from << " -" << cap << "> " << to << std::endl;
        }
      }
    }
  }

  void OutAns() {
    int result = 0;
    for (int index : graph_[start_]) {
      result += edges_[index].flow;
    }
    std::cout << result << std::endl;
    for (Edge edge : edges_) {
      if (edge.capacity > 0) {
        std::cout << edge.flow << std::endl;
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