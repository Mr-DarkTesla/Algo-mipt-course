#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

typedef std::vector<bool> Vector1dbool;
typedef std::vector<size_t> Vector1dsizeT;
typedef std::vector<Vector1dsizeT> Vector2d;

// typedef std::pair<size_t, size_t> pair_s;

template <typename vertex_t = size_t,
          typename edge_t = std::pair<size_t, size_t>>
class Graph {
  using iterator = typename std::vector<vertex_t>::iterator;
 public:
  using vertex_type = vertex_t;
  using edge_type = edge_t;
  virtual size_t GetVertexiesSize() = delete;
  virtual size_t GetEdgesSize() = delete;
  virtual std::vector<vertex_t> GetNeigbours(size_t /*vertex_index*/) = delete;
  virtual iterator GetNeigboursIter(size_t /*vertex_index*/) = delete;
};

template <typename vertex_t = size_t,
          typename edge_t = std::pair<size_t, size_t>>
class GraphMatrix : Graph<vertex_t, edge_t> {
 public:
  size_t GetVertexiesSize() override {}
  size_t GetEdgesSize() override {}
  std::vector<vertex_t> GetNeigbours(size_t /*vertex_index*/) override {}
  iterator GetNeigboursIter(size_t /*vertex_index*/) override {}
};

template <typename vertex_t = size_t,
          typename edge_t = std::pair<size_t, size_t>>
class GraphList : Graph<vertex_t, edge_t> {

  std::vector<std::vector<vertex_t>> AdjacencyList;

 public:
  GraphList(size_t vertexies_number)
      : edges_count(0), AdjacencyList(vertexies_number) override {}
  size_t GetVertexiesSize() override { return AdjacencyList.size(); }
  size_t GetEdgesSize() override { return edges_count; }
  std::vector<vertex_t> GetNeigbours(size_t vertex_index) override {
    AdjacencyList[vertex_index];
  }
  iterator GetNeigboursIter(size_t vertex_index) {
    return AdjacencyList[vertex_index].begein();
  }

 private:
  size_t edges_count;
};

template<typename vertex_t, typename edge_t>
class Visitor {

};

class Solver {
 public:
  void Input() {
    std::cin >> planets_ >> num_of_paths_;
    planets_++;
    graph_.resize(planets_, Vector1dsizeT(0));
    std::cin >> start_ >> finish_;
    for (size_t i = 0; i < num_of_paths_; ++i) {
      size_t left, right;
      std::cin >> left >> right;
      graph_[left].push_back(right);
      graph_[right].push_back(left);
    }
  }

  void Request() {
    Vector1dsizeT ans(planets_, 0);
    BFS(start_, ans);
    if (ans[finish_] != 0) {
      Vector1dsizeT path(0);
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

  void BFS(size_t start, Vector1dsizeT& used) {
    std::queue<size_t> que;
    que.push(start);
    used[start] = planets_ + 1;
    while (!que.empty()) {
      size_t cur = que.front();
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