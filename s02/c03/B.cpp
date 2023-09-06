#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

typedef std::pair<size_t, size_t> Pair;
typedef std::pair<char, Pair> Edge;

typedef std::vector<bool> Vector1dBool;
typedef std::vector<size_t> Vector1dSizeT;
typedef std::vector<Edge> Vector1dEdge;

struct vertex {
  size_t index;
  vertex* root = this;
};

typedef std::vector<vertex> Vector1dVertex;

struct Graph {
  Vector1dVertex vertices{};
  Vector1dSizeT size{};
  Graph(size_t num_of_vertices) {
    vertices = Vector1dVertex(num_of_vertices);
    for (size_t index = 0; index < num_of_vertices; ++index) {
      vertices[index].index = index;
    }
    size = Vector1dSizeT(num_of_vertices, 1);
  }

  vertex* Root(size_t i) {
    vertex& cur_vertex = vertices[i];
    if (cur_vertex.root != &cur_vertex) {
      cur_vertex.root = Root(cur_vertex.root->index);
    }
    return cur_vertex.root;
  }

  bool SameRoot(size_t i, size_t j) {
    return Root(i) == Root(j);
  }

  void Merge(size_t i, size_t j) {
    if (size[i] < size[j]) {
      Root(i)->root = Root(j);
    } else {
      Root(j)->root = Root(i);
    }
  }
};


class Solver {
 public:
  void Input() {
    std::cin >> num_of_ver_ >> num_of_edges_ >> num_of_que_;
    for (size_t i = 0; i < num_of_edges_; ++i) {
      size_t _;
      std::cin >> _ >> _;
    }
    graph_ = Graph(num_of_ver_);
  }
  void Request() {
    Process();
    for (int i = answers_.size() - 1; i >= 0; --i) {
      if (answers_[i]) {
        std::cout << "YES\n";
      } else {
        std::cout << "NO\n";
      }
    }
  }

 private:
  int64_t num_of_ver_{};
  int64_t num_of_edges_{};
  int64_t num_of_que_{};
  Graph graph_ = Graph(0);
  Vector1dEdge queries_;
  Vector1dBool answers_;

  void Process() {
    for (int query = 0; query < num_of_que_; ++query) {
      char ch_1, ch_2, ch_3;
      std::cin >> ch_1 >> ch_2 >> ch_3;
      size_t v1, v2;
      std::cin >> v1 >> v2;
      Edge new_edge = {ch_1, {--v1, --v2}};
      queries_.push_back(new_edge);
    }
    for (size_t query = num_of_que_ - 1; query < num_of_que_; --query) {
      size_t from = queries_[query].second.first;
      size_t to = queries_[query].second.second;
      char query_type = queries_[query].first;
      if (query_type == 'a') {
        answers_.push_back(graph_.SameRoot(from, to));
      } 
      else if (query_type == 'c') {
        graph_.Merge(from, to);
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