#include <algorithm>
#include <iostream>

class Solver {
 public:
  ~Solver() { delete[] array_; }

  void ReadInput() {
    std::cin >> length_;
    std::cin >> max_spells_;
    array_ = new int64_t[length_];
    for (size_t i = 0; i < length_; i++) {
      std::cin >> array_[i];
    }
    std::sort(array_, array_ + length_);
  }

  void Solve() {
    std::cout << BinarySearch(array_, array_ + length_ - 1, max_spells_);
  }

 private:
  static bool TestCastRange(const int64_t* begin, const int64_t* end,
                            int64_t max_spells, int64_t cast_range) {
    int used_casts = 0;
    const int64_t* iterator = begin;
    int64_t border = *begin - 1;
    while (iterator <= end) {
      if (*iterator <= border) {
        iterator++;
      } else {
        border = *iterator + cast_range;
        used_casts++;
      }
    }
    return (used_casts <= max_spells);
  }

  static int64_t BinarySearch(const int64_t* begin, const int64_t* end,
                              int64_t max_spells) {
    int64_t lower = 0;
    int64_t upper = (int64_t)(*end - *begin);
    while (upper - lower > 1) {
      int64_t middle = lower + ((upper - lower) / 2);
      bool middle_test = TestCastRange(begin, end, max_spells, middle);
      bool lower_test = TestCastRange(begin, end, max_spells, lower);
      if (middle_test != lower_test) {
        upper = middle;
      } else if (lower_test) {
        return lower;
      } else {
        lower = middle;
      }
    }
    bool lower_test = TestCastRange(begin, end, max_spells, lower);
    return (lower_test) ? lower : upper;
  }

  size_t length_;
  int64_t max_spells_;
  int64_t* array_;
};

int main() {
  auto solver = Solver();
  solver.ReadInput();
  solver.Solve();
}
