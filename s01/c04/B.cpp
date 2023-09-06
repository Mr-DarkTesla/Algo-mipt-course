#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

class BinaryTree {
 public:
  void Init(std::vector<int64_t> data) {
    array_ = std::move(data);
    sum_.resize(array_.size(), 0);
    for (size_t i = 0; i < array_.size(); ++i) {
      UpdateDelta(i, array_[i]);
    }
  }

  void UpdateValue(int64_t index, int64_t value) {
    UpdateDelta(index, value - array_[index]);
    array_[index] = value;
  }

  int64_t Sum(int64_t left, int64_t right) {
    if (left == 0) {
      return PrefixSum(right);
    }
    if (left % 2 == 0) {
      return PrefixSum(right) - PrefixSum(left - 1);
    }
    return -(PrefixSum(right) - PrefixSum(left - 1));
  }

 private:
  int64_t GetPrev(int64_t index) { return index & (index + 1); }

  int64_t GetNext(int64_t index) { return index | (index + 1); }

  int64_t PrefixSum(int64_t index) {
    int64_t res = 0;
    for (int64_t i = index; i >= 0; i = GetPrev(i) - 1) {
      res += sum_[i];
    }
    return res;
  }

  void UpdateDelta(int64_t index, int64_t delta) {
    for (size_t i = index; i < sum_.size(); i = GetNext(i)) {
      sum_[i] += delta;
    }
  }

  std::vector<int64_t> array_;
  std::vector<int64_t> sum_;
};

class Solver {
 public:
  void Input() {
    std::cin >> length_;
    array_.resize(length_);
    for (int64_t i = 0; i < length_; ++i) {
      std::cin >> array_[i];
    }
    tree_.Init(array_);
  }

  void Request() {
    std::cin >> num_of_requests_;
    for (int64_t i = 0; i < num_of_requests_; ++i) {
      int64_t request, left_request, right_request;
      std::cin >> request >> left_request >> right_request;
      if (request == 0) {
        tree_.UpdateValue(left_request - 1, right_request);
      } else if (request == 1) {
        std::cout << tree_.Sum(left_request - 1, right_request - 1)
                  << std::endl;
      }
    }
  }

 private:
  int64_t length_;
  std::vector<int64_t> array_;
  BinaryTree tree_;
  int64_t num_of_requests_;
};

int main() {
  auto solver = Solver();
  solver.Input();
  solver.Request();
}