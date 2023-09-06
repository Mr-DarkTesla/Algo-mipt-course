#include <algorithm>
#include <iostream>
#include <vector>

typedef std::vector<std::vector<int64_t>> Vector2d;

class Solver {
 public:
  Solver() = default;
  ~Solver() = default;

  std::vector<int64_t> ReadSequence() {
    int64_t sequence_length;
    std::cin >> sequence_length;

    std::vector<int64_t> sequence(sequence_length);
    for (int i = 0; i < sequence_length; i++) {
      std::cin >> sequence[i];
    }
    return sequence;
  }

  void Process() {
    array1_ = ReadSequence();
    array2_ = ReadSequence();
    for (auto el : LCS()) {
      std::cout << el << " ";
    }
    std::cout << std::endl;
  }

 private:
  std::vector<int64_t> LCS() {
    auto max_weight = Vector2d(array1_.size() + 1,
                               std::vector<int64_t>(array2_.size() + 1, 0));
    for (uint64_t i = 0; i <= array1_.size(); i++) {
      for (uint64_t j = 0; j <= array2_.size(); j++) {
        if (i != 0 && j != 0) {
          if (array1_[i - 1] == array2_[j - 1]) {
            max_weight[i][j] = max_weight[i - 1][j - 1] + 1;
          } else {
            max_weight[i][j] =
                std::max(max_weight[i - 1][j], max_weight[i][j - 1]);
          }
        }
      }
    }
    auto last_s1 = int64_t(array1_.size());
    auto last_s2 = int64_t(array2_.size());

    while (last_s1 > 0 && last_s2 > 0) {
      if (array1_[last_s1 - 1] == array2_[last_s2 - 1]) {
        ans_.push_back(array1_[last_s1 - 1]);
        last_s1--;
        last_s2--;
      } else if (max_weight[last_s1 - 1][last_s2] >
                 max_weight[last_s1][last_s2 - 1]) {
        last_s1--;
      } else {
        last_s2--;
      }
    }
    std::reverse(ans_.begin(), ans_.end());
    return ans_;
  }

  std::vector<int64_t> array1_{};
  std::vector<int64_t> array2_{};
  std::vector<int64_t> ans_{};
};

int main() {
  Solver solver;
  solver.Process();
}