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
typedef std::vector<Vector1dPair> Vector2d;

class Solver {
 public:
  void Input() {
    std::cin >> planets_ >> num_of_paths_;
    planets_++;
    graph_.resize(planets_, Vector1dPair(0));
    for (size_t i = 0; i < num_of_paths_; ++i) {
      size_t left, right;
      std::cin >> left >> right;
      graph_[left].push_back(Pair(right, i + 1));
      graph_[right].push_back(Pair(left, i + 1));
    }
  }

  void Request() {
    t_in_.resize(planets_);
    t_up_.resize(planets_);
    used_.resize(planets_, false);

    size_t time = 0;
    for (size_t i = 1; i < planets_; ++i) {
      if (!used_[i]) {
        Dfs(i, 0, time);
      }
    }
    std::cout << ans_.size() << "\n";
    for (auto el : ans_) {
      std::cout << el << " ";
    }
  }

 private:
  size_t planets_{};
  size_t num_of_paths_{};
  Vector2d graph_{};

  Vector1dSizeT t_in_{};
  Vector1dSizeT t_up_{};
  Vector1dSizeT ans_{};
  Vector1dBool used_{};

  void Dfs(size_t cur, size_t prev, size_t time) {
    used_[cur] = true;
    t_in_[cur] = t_up_[cur] = time++;
    for (Pair next_pair : graph_[cur]) {
      size_t next = next_pair.first;
      size_t edge_idx = next_pair.second;
      if (next == prev) {
        continue;
      }
      if (used_[next]) {
        t_up_[cur] = std::min(t_up_[cur], t_in_[next]);
      } else {
        Dfs(next, cur, time);
        t_up_[cur] = std::min(t_up_[cur], t_up_[next]);
        if (t_up_[next] > t_in_[cur]) {
          Bridge(cur, next, edge_idx);
        }
      }
    }
  }

  void Bridge(size_t from, size_t to, size_t edge_idx) {
    for (Pair next_pair : graph_[from]) {
      size_t neighbor = next_pair.first;
      size_t index = next_pair.second;
      if (neighbor == to && index != edge_idx) {
        return;
      }
    }
    auto it = std::upper_bound(ans_.cbegin(), ans_.cend(), edge_idx);
    ans_.insert(it, edge_idx);
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0), std::cout.tie(0);
  auto solver = Solver();
  solver.Input();
  solver.Request();
}