#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

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
typedef std::vector<Vector1dInt64> Vector2dInt64;
typedef std::vector<Vector1dBool> Vector2dBool;

class Solver {
 public:
  void Input() {
    std::cin >> height_ >> width_ >> acost_ >> bcost_;
    num_of_vertices_ = height_ * width_;

    board_.resize(height_, Vector1dBool(width_));
    edges_.resize(0);
    graph_.resize(num_of_vertices_ + 2, Vector1dInt64(0));
    used_.resize(num_of_vertices_ + 2, 0);

    free_ = 0;
    for (size_t y_cord = 0; y_cord < height_; ++y_cord) {
      for (size_t x_cord = 0; x_cord < width_; ++x_cord) {
        char chr;
        std::cin >> chr;
        board_[y_cord][x_cord] = (chr == '*');
        free_ += (chr == '*');
      }
    }
  }

  void Build() {
    start_ = 0;
    finish_ = num_of_vertices_ + 1;

    for (size_t y_cord = 0; y_cord < height_; ++y_cord) {
      for (size_t x_cord = 0; x_cord < width_; ++x_cord) {
        if (!board_[y_cord][x_cord]) {
          continue;
        }
        bool color = ((y_cord + x_cord) % 2 == 0);
        size_t index = Index(x_cord, y_cord);
        if (!color) {
          AddEdge(index, finish_, 1);
          continue;
        }
        if (y_cord != 0 && board_[y_cord - 1][x_cord]) {
          AddEdge(index, Index(x_cord, y_cord - 1), 1);
        }
        if (y_cord != height_ - 1 && board_[y_cord + 1][x_cord]) {
          AddEdge(index, Index(x_cord, y_cord + 1), 1);
        }
        if (x_cord != 0 && board_[y_cord][x_cord - 1]) {
          AddEdge(index, Index(x_cord - 1, y_cord), 1);
        }
        if (x_cord != width_ - 1 && board_[y_cord][x_cord + 1]) {
          AddEdge(index, Index(x_cord + 1, y_cord), 1);
        }
        AddEdge(start_, index, 1);

      }
    }
  }

  void MaxFlow() {
    size_t time = 1;
    while (Dfs(start_, kMaxCap, time++) != 0) {
    }
    OutAns();
  }

 private:
  const size_t kMaxCap = 100000;
  size_t height_{};
  size_t width_{};

  int64_t acost_{};
  int64_t bcost_{};

  size_t num_of_vertices_{};
  size_t num_left_{};
  size_t num_right_{};

  int64_t free_{};
  Vector2dBool board_{};
  Vector1dEdge edges_{};
  Vector2dInt64 graph_{};

  size_t start_;
  size_t finish_;

  Vector1dSize used_{};

  size_t Index(size_t x_cord, size_t y_cord) {
    return 1 + (y_cord * width_ + x_cord);
  }

  void AddEdge(size_t left, size_t right, size_t capacity) {
    graph_[left].emplace_back(edges_.size());
    edges_.emplace_back(Edge(left, right, capacity));
    graph_[right].emplace_back(edges_.size());
    edges_.emplace_back(Edge(right, left, 0));
  }

  void OutAns() {
    if (acost_ > 2 * bcost_) {
      std::cout << free_ * bcost_ << std::endl;
      return ;
    }
    int64_t result = 0;
    for (size_t index : graph_[start_]) {
      size_t flow = edges_[index].flow;
      result += flow;
    }
    std::cout << result * acost_ + (free_ - 2 * result) * bcost_
      << std::endl;
  }

  int64_t Dfs(size_t vertex, int64_t min_cap, size_t time) {
    if (vertex == finish_) {
      return min_cap;
    }
    used_[vertex] = time;
    for (size_t idx : graph_[vertex]) {
      size_t to = edges_[idx].to;
      int64_t cap = edges_[idx].Capacity();
      if (cap == 0) {
        continue;
      }
      if (used_[to] == time) {
        continue;
      }
      int64_t flow = Dfs(to, std::min(min_cap, cap), time);
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
        int64_t cap = edges_[index].capacity;
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
  solver.Build();
  solver.MaxFlow();
}