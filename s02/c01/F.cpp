#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <utility>
#include <vector>

typedef std::pair<size_t, int64_t> Pair;

typedef std::vector<bool> Vector1dBool;
typedef std::vector<size_t> Vector1dSizeT;
typedef std::vector<Pair> Vector1dPair;
typedef std::vector<Vector1dSizeT> Vector2d;

class Solver {
 public:
  void Input() {
    std::cin >> planets_ >> num_of_paths_;
    planets_++;
    graph_.resize(planets_, Vector1dSizeT(0));
    graph_r_.resize(planets_, Vector1dSizeT(0));
    for (size_t i = 0; i < num_of_paths_; ++i) {
      size_t left, right;
      std::cin >> left >> right;
      graph_[left].push_back(right);
      graph_r_[right].push_back(left);
    }
  }

  void Request() {
    ans_.resize(planets_);

    used_.resize(planets_, false);
    size_t color = 1;
    for (size_t i = 1; i < planets_; ++i) {
      if (!used_[i]) {
        Dfs1(i);
      }
    }

    used_.assign(planets_, false);
    for (size_t i = 1; i < planets_; ++i) {
      size_t cur = ord_[planets_ - i - 1];
      if (!used_[cur]) {
        Dfs2(cur);
        for (auto el : component_) {
          ans_[el] = color;
        }
        ++color;
        component_.clear();
      }
    }
    std::cout << color - 1 << "\n";
    for (size_t i = 1; i < planets_; ++i) {
      std::cout << ans_[i] << " ";
    }
  }

 private:
  size_t planets_{};
  size_t num_of_paths_{};
  Vector2d graph_{};
  Vector2d graph_r_{};

  Vector1dBool used_{};
  Vector1dSizeT ord_{};
  Vector1dSizeT component_{};

  Vector1dSizeT ans_{};

  void Dfs1(size_t cur) {
    used_[cur] = true;
    for (size_t next : graph_[cur]) {
      if (!used_[next]) {
        Dfs1(next);
      }
    }
    ord_.push_back(cur);
  }

  void Dfs2(size_t cur) {
    used_[cur] = true;
    component_.push_back(cur);
    for (size_t next : graph_r_[cur]) {
      if (!used_[next]) {
        Dfs2(next);
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