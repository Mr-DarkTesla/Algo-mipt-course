#include <cstring>
#include <iostream>
#include <vector>

class Solver {
 public:
  void RequestProcessing() {
    std::cin >> length_;
    array_.resize(length_);
    for (int i = 0; i < length_; i++) {
      std::cin >> array_[i];
    }
    Sort();
    for (int i = 0; i < length_; i++) {
      std::cout << array_[i] << "\n";
    }
  }

 private:
  int64_t Digit(int64_t index) {
    return (array_[index] / val_) % (1 << kMaxValue);
  }

  void Sort() {
    std::vector<int64_t> memory(1 << kMaxValue, 0);
    std::vector<int64_t> array(array_.size(), 0);
    for (int64_t rank = 0; rank < kMaxRank; rank++) {
      for (int64_t i = 0; i < (int64_t)array.size(); i++) {
        memory[Digit(i)]++;
      }
      for (int64_t i = 1; i < 1 << kMaxValue; i++) {
        memory[i] += memory[i - 1];
      }
      for (int64_t i = (int64_t)array_.size() - 1; i >= 0; --i) {
        array[--memory[Digit(i)]] = array_[i];
      }
      memset(memory.data(), 0, memory.size() * sizeof(int64_t));
      array_ = array;
      val_ = val_ << kMaxValue;
    }
  }

  const int64_t kMaxRank = 8;
  const int64_t kMaxValue = 8;
  int64_t val_ = 1;
  int length_;
  std::vector<int64_t> array_{};
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  Solver solver;
  solver.RequestProcessing();
}