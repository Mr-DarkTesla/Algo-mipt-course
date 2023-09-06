#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

typedef std::pair<int64_t, size_t> Pair;
typedef std::pair<int64_t, Pair> Edge;

typedef std::vector<bool> Vector1dBool;
typedef std::vector<int64_t> Vector1dInt64;
typedef std::vector<size_t> Vector1dSize;
typedef std::vector<Pair> Vector1dPair;

typedef std::vector<Vector1dInt64> Vector2dInt64;
typedef std::vector<Vector1dPair> Vector2dPair;

class Solver {
 public:
  void Input() {
    std::cin >> num_of_vertices_ >> num_of_edges_ >> num_of_pairs_;
    graph_.resize(num_of_vertices_, Vector1dInt64(num_of_vertices_, 0));
    for (size_t i = 0; i < num_of_edges_; ++i) {
      size_t left, right;
      int64_t weight;
      std::cin >> left >> right >> weight;
      left--;
      right--;
      graph_[left][right] = std::min(graph_[left][right], -weight);
      graph_[right][left] = std::min(graph_[left][right], -weight);
    }
    graph_pair_.resize(num_of_vertices_, Vector1dPair());
  }

  void Request() {
    Process();
    // OutGraphs();
    for (size_t i = 0; i < num_of_pairs_; ++i) {
      size_t left, right;
      std::cin >> left >> right;
      left--;
      right--;
      std::fill(used_.begin(), used_.end(), false);
      std::cout << -Dfs(left, right, used_) << "\n";
    }
  }

  void OutGraphs() {
    for (auto row : graph_) {
      for (auto el : row) {
        std::cout << el << " ";
      }
      std::cout << "\n";
    }
    for (auto row : graph_pair_) {
      for (auto el : row) {
        std::cout << "(" << el.first << " " << el.second << ") ";
      }
      std::cout << "\n";
    }
  }

 private:
  size_t num_of_vertices_{};
  size_t num_of_edges_{};
  size_t num_of_pairs_{};

  Vector2dInt64 graph_{};
  Vector2dPair graph_pair_{};
  Vector1dBool used_{};

  void Process() {
    int64_t total_used = 0;
    while (total_used < num_of_vertices_) {
      used_.resize(num_of_vertices_, false);
      std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> heap;

      int min_row = 0, min_col = 1;
      for (int row = 0; row < num_of_vertices_; ++row) {
        for (int col = 0; col < num_of_vertices_; ++col) {
          if (row != col && !used_[row] && !used_[col] &&
              graph_[row][col] < graph_[min_row][min_col]) {
            min_row = row, min_col = col;
          }
        }
      }
      Edge next_edge = {graph_[min_row][min_col], {min_row, min_col}};
      heap.push(next_edge);
      for (int next = 0; next < num_of_vertices_; ++next) {
        if (next != min_row && next != min_col) {
          if (graph_[min_row][next] != 0) {
            next_edge = {graph_[min_row][next], {min_row, next}};
            heap.push(next_edge);
          }
          if (graph_[min_col][next] != 0) {
            next_edge = {graph_[min_col][next], {min_col, next}};
            heap.push(next_edge);
          }
        }
      }
      graph_pair_[min_row].push_back({graph_[min_row][min_col], min_col});
      graph_pair_[min_col].push_back({graph_[min_col][min_row], min_row});
      used_[min_row] = true;
      used_[min_col] = true;
      total_used += 2;

      while (!heap.empty()) {
        Edge cur = heap.top();
        size_t cur_from = cur.second.first;
        size_t cur_to = cur.second.second;
        heap.pop();
        if (used_[cur_to]) {
          continue;
        }
        used_[cur_to] = true;
        total_used++;
        Edge next_edge;
        for (int y = 0; y < num_of_vertices_; ++y) {
          if (!used_[y] && y != cur_to) {
            next_edge = {graph_[cur_to][y], {cur_to, y}};
            heap.push(next_edge);
          }
        }
        graph_pair_[cur_from].push_back({graph_[cur_from][cur_to], cur_to});
        graph_pair_[cur_to].push_back({graph_[cur_to][cur_from], cur_from});
      }
    }
  }

  int64_t Dfs(size_t start, size_t finish, Vector1dBool& used) {
    used[start] = true;
    for (auto next_pair : graph_pair_[start]) {
      size_t next = next_pair.second;
      int64_t weight = next_pair.first;
      if (!used[next]) {
        if (next == finish) {
          return weight;
        }
        int64_t max_waight = Dfs(next, finish, used);
        if (max_waight < 0) {
          return std::max(weight, max_waight);
        }
      }
    }
    return 0;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0), std::cout.tie(0);

  auto solver = Solver();
  solver.Input();
  solver.Request();
}