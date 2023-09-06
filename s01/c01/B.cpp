#include <iostream>

class Solver {
 public:
  ~Solver() { delete[] array_; }

  void ReadArray() {
    std::cin >> length_;
    array_ = new int[length_];
    for (size_t i = 0; i < length_; i++) {
      std::cin >> array_[i];
    }
  }

  void Solve() { std::cout << BinarySearchMin(array_, array_ + length_ - 1); }

 private:
  static size_t BinarySearchMin(const int* begin, const int* end) {
    if (*begin < *end) {
      return 0;
    }
    const int* lower = begin;
    const int* upper = end;
    while (upper - lower > 1) {
      const int* middle = lower + ((upper - lower) / 2);
      if (*middle > *lower) {
        lower = middle;
      } else {
        upper = middle;
      }
    }
    return (((*upper < *lower) ? upper : lower) - begin) % (end - begin + 1);
  }

  size_t length_;
  int* array_;
};

int main() {
  auto solver = Solver();
  solver.ReadArray();
  solver.Solve();
}
