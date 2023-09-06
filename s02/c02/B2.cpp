#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

typedef std::tuple<size_t, int64_t, size_t> Pair;

typedef std::vector<bool> Vector1dBool;
typedef std::vector<int64_t> Vector1dInt64;
typedef std::vector<size_t> Vector1dSize;
typedef std::vector<Pair> Vector1dPair;
typedef std::vector<Vector1dPair> Vector2d;

class Solver {
 public:
  void Input() {
    std::cin >> num_of_rooms_ >> num_of_paths_ >> num_of_viruses_;
    num_of_rooms_++;

    graph_.resize(num_of_rooms_, Vector1dPair(0));
    virus_.resize(0);

    for (size_t i = 0; i < num_of_viruses_; ++i) {
      size_t virus;
      std::cin >> virus;
      virus_.push_back(virus);
    }
    for (size_t i = 0; i < num_of_paths_; ++i) {
      size_t left, right;
      int64_t weight;
      std::cin >> left >> right >> weight;
      if (std::count(virus_.begin(), virus_.end(), left) == 0 &&
          std::count(virus_.begin(), virus_.end(), right) == 0) {

        graph_[left].push_back(Pair(right, weight, i));
        graph_[right].push_back(Pair(left, weight, i));
      }
    }
  }

  void Request() {
    size_t start, finish;
    std::cin >> start >> finish;
    Bfs(start, finish);
  }

 private:
  size_t num_of_rooms_{};
  size_t num_of_paths_{};
  size_t num_of_viruses_{};

  Vector2d graph_{};
  Vector1dSize virus_{};

  void Bfs(size_t start, size_t finish) {
    std::priority_queue<Pair, Vector1dPair, std::greater<>> heap;
    int64_t time = 0;
    Vector1dBool used(num_of_rooms_, false);
    heap.push({start, time});

    while (!heap.empty()) {
      Pair cur = heap.top();
      used[cur.first] = true;
      heap.pop();
      time = cur.second;

      if (cur.first == finish) {
        std::cout << time;
        return;
      }

      for (Pair next_pair : graph_[cur.first]) {
        size_t next_room = next_pair.first;
        int64_t weight = next_pair.second;
        if (!used[next_room] && weight > time) {
          heap.push({next_room, time + weight});
        }
      }
    }
    std::cout << -1;
    return;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0), std::cout.tie(0);

  auto solver = Solver();
  solver.Input();
  solver.Request();
}