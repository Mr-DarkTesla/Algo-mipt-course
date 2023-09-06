#include <cmath>
#include <iomanip>
#include <iostream>

class Solver {
 public:
  ~Solver() { delete[] array_; }

  void RequestProcessing() {
    ReadArray();
    Logarithm();
    PrefixSum();
    int number_of_requests;
    std::cin >> number_of_requests;
    for (int i = 0; i < number_of_requests; i++) {
      int left;
      int right;
      std::cin >> left >> right;
      std::cout << std::fixed << std::setprecision(precision_);
      std::cout << GeometricMean(left, right) << "\n";
    }
  }

 private:
  void ReadArray() {
    std::cin >> length_;
    array_ = new double[length_];
    for (size_t i = 0; i < length_; i++) {
      std::cin >> array_[i];
    }
  }
  void Logarithm() {
    for (size_t i = 0; i < length_; i++) {
      array_[i] = std::log(array_[i]);
    }
  }

  void PrefixSum() {
    for (size_t i = 1; i < length_; i++) {
      array_[i] += array_[i - 1];
    }
  }

  double GeometricMean(int left, int right) {
    int degree = right + 1 - left;
    if (left == 0) {
      return std::exp(array_[right] / degree);
    }
    return std::exp((array_[right] - array_[left - 1]) / degree);
  }

  size_t length_{};
  double* array_{};
  int precision_ = 10;
};

int main() {
  auto solver = Solver();
  solver.RequestProcessing();
}
