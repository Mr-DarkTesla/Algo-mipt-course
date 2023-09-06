#include <algorithm>
#include <iostream>
#include <queue>
#include <tuple>
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
      size_t left, right, weight;
      std::cin >> left >> right >> weight;
      graph_[left].push_back(Pair(right, weight, i));
      graph_[right].push_back(Pair(left, weight, i));
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

  struct RoomInHeap {
    size_t room;
    size_t prev_room;
    size_t index;
    int64_t weight;
    bool is_virus;

    bool operator<(const RoomInHeap& right) const {
      if (weight == right.weight) {
        return !is_virus;
      }
      return weight > right.weight;
    }
  };

  void Bfs(size_t start, size_t finish) {
    std::priority_queue<RoomInHeap, std::vector<RoomInHeap>> heap;
    int64_t time = 0;
    Vector1dBool used(num_of_rooms_, false);
    heap.push({start, 0, 0, time, false});
    for (size_t virus_start : virus_) {
      heap.push({virus_start, 0, 0, time, true});
    }
    while (!heap.empty()) {
      RoomInHeap cur = heap.top();
      heap.pop();
      time = cur.weight;
      if (used[cur.room]) {
        continue;
      }
      used[cur.room] = true;
      if (cur.room == finish) {
        if (cur.is_virus) {
          std::cout << -1;
        } else {
          std::cout << time;
        }
        return;
      }
      if (cur.is_virus && cur.prev_room != 0) {
        graph_[cur.room].erase(
            std::find(graph_[cur.room].begin(), graph_[cur.room].end(),
                      Pair(cur.prev_room, cur.weight, cur.index)));
        graph_[cur.prev_room].erase(std::find(
            graph_[cur.prev_room].begin(), graph_[cur.prev_room].end(),
            Pair(cur.room, cur.weight, cur.index)));
      }
      for (Pair next_pair : graph_[cur.room]) {
        size_t next_room = std::get<0>(next_pair);
        int64_t weight = std::get<1>(next_pair);
        size_t index = std::get<2>(next_pair);
        if (!used[next_room]) {
          heap.push({next_room, cur.room, index, time + weight, cur.is_virus});
        }
      }
    }
    std::cout << -1;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0), std::cout.tie(0);

  auto solver = Solver();
  solver.Input();
  solver.Request();
}