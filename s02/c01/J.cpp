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
      for (size_t i = 0; i < num_of_paths_; ++i) {
        size_t left, right;
        std::cin >> left >> right;
        graph_[left].push_back(right);
        graph_[right].push_back(left);
      }
    }

    void Request() {
      if (planets_ == 3) {
        std::cout << 1;
        return;
      }
      FindBridges();
      used_.assign(planets_, false);
      colors_.resize(planets_, 0);
      size_t color = 1;
      for (size_t i = 1; i < planets_; ++i) {
        if (!used_[i]) {
          ColorGraph(i, color++);
        }
      }
      planets_cond_ = color;
      graph_cond_.resize(planets_cond_, Vector1dSizeT(0));
      num_of_paths_ = ans_.size() / 2;
      for (size_t i = 0; i < ans_.size(); ++i) {
        size_t left = colors_[ans_[i].first];
        size_t right = colors_[ans_[i].second];
        graph_cond_[left].push_back(right);
      }
      int leafs = 0;
      for (size_t i = 1; i < planets_cond_; ++i) {
        if (graph_cond_[i].size() == 1) {
          leafs++;
        }
      }
      std::cout << (leafs / 2 + 1);
    }

   private:
    size_t planets_{};
    size_t num_of_paths_{};
    Vector2d graph_{};

    size_t planets_cond_{};
    size_t num_of_paths_cond_{};
    Vector2d graph_cond_{};

    Vector1dSizeT colors_{};

    Vector1dSizeT t_in_{};
    Vector1dSizeT t_up_{};
    Vector1dPair ans_{};
    Vector1dBool used_{};

    void ColorGraph(size_t cur, size_t color) {
      used_[cur] = true;
      colors_[cur] = color;
      for (size_t next : graph_[cur]) {
        if (!used_[next] &&
            std::count(ans_.begin(), ans_.end(), Pair(cur, next)) == 0) {
          ColorGraph(next, color);
        }
      }
    }

    void FindBridges() {
      t_in_.resize(planets_);
      t_up_.resize(planets_);
      used_.resize(planets_, false);

      size_t time = 0;
      for (size_t i = 1; i < planets_; ++i) {
        if (!used_[i]) {
          Dfs(i, 0, time);
        }
      }
    }

    void Dfs(size_t cur, size_t prev, size_t time) {
      used_[cur] = true;
      t_in_[cur] = t_up_[cur] = time++;
      for (size_t next : graph_[cur]) {
        if (next == prev) {
          continue;
        }
        if (used_[next]) {
          t_up_[cur] = std::min(t_up_[cur], t_in_[next]);
        } else {
          Dfs(next, cur, time);
          t_up_[cur] = std::min(t_up_[cur], t_up_[next]);
          if (t_up_[next] > t_in_[cur]) {
            Bridge(cur, next);
          }
        }
      }
    }

    void Bridge(size_t from, size_t to) {
      ans_.push_back(Pair(from, to));
      ans_.push_back(Pair(to, from));
    }
  };

  int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0), std::cout.tie(0);
    auto solver = Solver();
    solver.Input();
    solver.Request();
  }