#include <iostream>

class Solver {
 public:
  ~Solver() {
    delete[] array_;
    delete[] prefix_array_;
    delete[] suffix_array_;
  }

  void RequestProcessing() {
    ReadArray();
    SuffPreffMin();
    int number_of_requests;
    std::cin >> number_of_requests;
    for (int i = 0; i < number_of_requests; i++) {
      int left;
      int right;
      std::cin >> left >> right;
      left--;
      right--;
      std::cout << std::min(prefix_array_[left], suffix_array_[right]) << "\n";
    }
  }

 private:
  void ReadArray() {
    std::cin >> length_;
    array_ = new int[length_];
    prefix_array_ = new int[length_];
    suffix_array_ = new int[length_];
    for (size_t i = 0; i < length_; i++) {
      std::cin >> array_[i];
    }
  }
  void SuffPreffMin() {
    prefix_array_[0] = array_[0];
    suffix_array_[length_ - 1] = array_[length_ - 1];
    for (size_t i = 1; i < length_; i++) {
      prefix_array_[i] = std::min(array_[i], prefix_array_[i - 1]);
      suffix_array_[length_ - 1 - i] =
          std::min(array_[length_ - 1 - i], suffix_array_[length_ - i]);
    }
  }

  size_t length_{};
  int* array_{};
  int* prefix_array_{};
  int* suffix_array_{};
};

int main() {
  auto solver = Solver();
  solver.RequestProcessing();
}
