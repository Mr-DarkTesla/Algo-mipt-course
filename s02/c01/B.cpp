#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

typedef std::pair<size_t, size_t> Pair;
typedef std::vector<bool> Vector1dBool;
typedef std::vector<Pair> Vector1dPair;

typedef std::vector<std::queue<size_t>> Vector1dQueue;
typedef std::vector<Vector1dPair> Vector2d;

class Solver {
 public:
  void Input() {
    std::cin >> planets_ >> num_of_paths_;
    planets_++;
    graph_.resize(planets_, Vector1dPair(0));
    std::cin >> start_ >> finish_;
    for (size_t i = 0; i < num_of_paths_; ++i) {
      size_t left, right, weight;
      std::cin >> left >> right >> weight;
      graph_[left].push_back(Pair(right, weight));
    }
  }

  void Request() { std::cout << Bfs(start_, finish_); }

 private:
  size_t planets_{};
  size_t num_of_paths_{};
  Vector2d graph_{};

  size_t start_{};
  size_t finish_{};

  size_t kMaxWeight_ = 31;

  int64_t Bfs(size_t start, size_t finish) {
    Vector1dBool used(planets_ + 1, false);
    Vector1dQueue v_que(kMaxWeight_, std::queue<size_t>());
    size_t range = 0;
    v_que[0].push(start);
    size_t que_size = 1;
    while (que_size != 0) {
      while (!v_que[range % kMaxWeight_].empty()) {
        size_t cur = v_que[range % kMaxWeight_].front();
        if (cur == finish) {
          return range;
        }
        used[cur] = true;
        for (Pair next_pair : graph_[cur]) {
          size_t next_v = next_pair.first;
          size_t next_w = next_pair.second;
          if (!used[next_v]) {
            v_que[(range + next_w) % kMaxWeight_].push(next_v);
            que_size++;
          }
        }
        v_que[range % kMaxWeight_].pop();
        que_size--;
      }
      range++;
    }
    return -1;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0), std::cout.tie(0);

  auto solver = Solver();
  solver.Input();
  solver.Request();
}