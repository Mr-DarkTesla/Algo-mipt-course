#include <algorithm>
#include <iostream>
#include <vector>

namespace constants {
const int64_t kINF = 1e9;
}

typedef std::vector<int64_t> Vector1d;
typedef std::vector<std::vector<int64_t>> Vector2d;

class Solver {
 public:
  Solver() = default;
  ~Solver() = default;

  void Input() { array1_ = ReadSequence(); }
  
  void Process() {

  }

 private:
  std::vector<int64_t> ReadSequence() {
    int64_t sequence_length;
    std::cin >> sequence_length;

    std::vector<int64_t> sequence(sequence_length);
    for (int i = 0; i < sequence_length; i++) {
      std::cin >> sequence[i];
    }
    return sequence;
  }

  std::vector<int64_t> array1_{};
};

int main() {
  Solver solver;
  solver.Input();
}