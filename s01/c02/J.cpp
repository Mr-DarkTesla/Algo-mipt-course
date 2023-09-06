#include <iostream>
#include <queue>
#include <vector>

class Solver {
 public:
  void Input() {
    std::cin >> number_of_arrays_;
    int length = 0;
    for (int i = 0; i < number_of_arrays_; i++) {
      std::cin >> length;
      std::vector<int> array(length, 0);
      for (int j = 0; j < length; j++) {
        std::cin >> array[j];
      }
      queue_.push(array);
    }
  }

  void RequestProcessing() {
    Input();
    while (queue_.size() > 1) {
      array1_ = queue_.front();
      queue_.pop();
      array2_ = queue_.front();
      queue_.pop();
      Merge();
    }
    for (auto element : queue_.front()) {
      std::cout << element << " ";
    }
  }

  void Merge() {
    size_t length = array1_.size() + array2_.size();
    std::vector<int> res(length);
    for (size_t i = 0, j = 0, k = 0; i < length; i++) {
      if (k >= array2_.size() ||
          (j < array1_.size() && array1_[j] < array2_[k])) {
        res[i] = array1_[j++];
      } else {
        res[i] = array2_[k++];
      }
    }
    queue_.push(res);
  }

 private:
  std::vector<int> array1_;
  std::vector<int> array2_;
  int number_of_arrays_{};
  std::queue<std::vector<int>> queue_;
};

int main() {
  Solver solver;
  solver.RequestProcessing();
  return 0;
}