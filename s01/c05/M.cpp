#include <algorithm>
#include <iostream>
#include <vector>

namespace constants {
const int64_t kINF = 1e8;
}

typedef std::vector<int> Vector1d;
typedef std::vector<std::vector<int64_t>> Vector2d;
typedef std::vector<bool> Vector1dbool;

class Solver {
 public:
  Solver() = default;
  ~Solver() = default;

  void Input() {
    std::cin >> length_;
    weight_.resize(length_, std::vector<int64_t>(length_));
    for (int i = 0; i < length_; ++i) {
      for (int j = 0; j < length_; ++j) {
        std::cin >> weight_[i][j];
      }
    }
  }

  void Process() {
    Vector1dbool mask(length_, false);
    Vector1d prev{};
    for (int start = 0; start < length_; ++start) {
      mask[start] = true;
      prev.push_back(start);
      BFS(start, start, mask, 0, prev);
      mask[start] = false;
      prev.pop_back();
    }
    std::cout << ans_ << " ";
    Output(prev_ans_);
  }

 private:
  int64_t BFS(int start, int last, Vector1dbool& mask, int64_t dist,
              Vector1d& prev) {
    int size = prev.size();
    if (size == length_) {
      if (dist < ans_) {
        ans_ = dist;
        prev_ans_ = prev;
      }
      return dist;
    }
    if (dist > ans_) {
      return constants::kINF;
    }
    int64_t tmp = constants::kINF;
    for (int v = 0; v < length_; ++v) {
      if (!mask[v]) {
        mask[v] = true;
        prev.push_back(v);
        tmp = std::min(tmp, BFS(start, v, mask, dist + weight_[last][v], prev));
        mask[v] = false;
        prev.pop_back();
      }
    }
    return dist + tmp;
  }

  void Output(Vector1d& array) {
    for (auto el : array) {
      std::cout << el + 1 << " ";
    }
    std::cout << std::endl;
  }

  int64_t ans_ = constants::kINF;
  Vector1d prev_ans_{};
  int64_t length_{};
  Vector2d weight_{};
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  Solver solver;
  solver.Input();
  solver.Process();
}