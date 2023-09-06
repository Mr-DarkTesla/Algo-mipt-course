#include <math.h>
#include <algorithm>
#include <iostream>
#include <vector>

namespace constants {
const int64_t kINF = 1e9;
}  // namespace constants

class Solver {
 public:
  Solver() = default;
  ~Solver() = default;

  void Input() {
    std::cin >> length_;
    array_.resize(length_);
    for (int64_t i = 0; i < length_; ++i) {
      std::cin >> array_[i];
    }
  }

  void Process() {
    std::vector<int64_t> dp(length_, constants::kINF);
    dp[0] = -constants::kINF;
    for (int i = 0; i < length_; ++i) {
      int j =
          int(std::upper_bound(dp.begin(), dp.end(), array_[i]) - dp.begin());
      if (dp[j - 1] < array_[i] && array_[i] < dp[j]) {
        dp[j] = array_[i];
      }
    }
    for (int i = length_ - 1; 0 <= i; --i) {
      if (dp[i] < constants::kINF) {
        std::cout << i;
        break;
      }
    }
  }

 private:
  int64_t length_{};
  std::vector<int64_t> array_{};
};

int main() {
  Solver solver;
  solver.Input();
  solver.Process();
}