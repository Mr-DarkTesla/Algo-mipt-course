#include <iostream>
#include <vector>

class Solver {
 public:
  //  bool TestProcessing() {
  //    int64_t ans1 = QuickSelect(0, length_ - 1, k_stat_);
  //    std::nth_element(array_.begin(), array_.begin() + k_stat_,
  //    array_.end());
  //    int64_t ans2 = array_[k_stat_];
  //    return (ans1 == ans2);
  //  }

  void RequestProcessing() {
    std::cout << QuickSelect(0, length_ - 1, k_stat_);
  }

  void Input() {
    std::cin >> length_;
    std::cin >> k_stat_;
    --k_stat_;
    int64_t tmp;
    for (size_t i = 0; i < 2; i++) {
      std::cin >> tmp;
      array_.push_back(tmp);
    }
    for (size_t i = 2; i < length_; i++) {
      tmp = (kMul1 * array_[i - 1] % kBigNumber +
             kMul2 * array_[i - 2] % kBigNumber) %
            kBigNumber;
      array_.push_back(tmp);
    }
  }

  void Tests(int64_t a0, int64_t a1, size_t n, size_t k) {
    length_ = n;
    k_stat_ = k;
    --k_stat_;
    int64_t tmp;
    array_.clear();
    array_.push_back(a0);
    array_.push_back(a1);
    for (size_t i = 2; i < length_; i++) {
      tmp = (kMul1 * array_[i - 1] % kBigNumber +
             kMul2 * array_[i - 2] % kBigNumber) %
            kBigNumber;
      array_.push_back(tmp);
    }
  }

 private:
  size_t MedianMedian(size_t left, size_t right, std::vector<int64_t>& array) {
    size_t length = right - left + 1;
    if (length == 1) {
      return array[left];
    }
    std::vector<int64_t> ans;
    for (size_t chunk = 0; chunk < length / 5; chunk++) {
      for (size_t i = 0; i < 4; i++) {
        for (size_t j = i + 1; j < 5; j++) {
          if (array[left + 5 * chunk + i] > array[left + 5 * chunk + j]) {
            std::swap(array[left + 5 * chunk + i], array[left + 5 * chunk + j]);
          }
        }
      }
      ans.push_back(array[left + 5 * chunk + 2]);
    }
    if (length % 5 != 0) {
      ans.push_back(array[right - (length % 5 / 2)]);
    }
    return MedianMedian(0, ans.size() - 1, ans);
  }

  int64_t QuickSelect(size_t left, size_t right, size_t k_stat) {
    if (left == right) {
      return array_[left];
    }
    size_t pivot_index =
        Partition(left, right, MedianMedian(left, right, array_));
    if (k_stat == pivot_index - left) {
      return array_[pivot_index];
    }
    if (k_stat < pivot_index - left) {
      return QuickSelect(left, pivot_index - 1, k_stat);
    }
    return QuickSelect(pivot_index + 1, right,
                       k_stat - (pivot_index - left) - 1);
  }

  size_t Partition(size_t left, size_t right, int64_t pivot) {
    size_t pivot_index = Find(pivot);
    std::swap(array_[pivot_index], array_[right]);
    size_t next = left;
    for (; left < right; left++) {
      if (array_[left] < pivot) {
        std::swap(array_[next], array_[left]);
        next++;
      }
    }
    std::swap(array_[next], array_[right]);
    return next;
  }

  size_t Find(int64_t target) {
    for (size_t i = 0; i < array_.size(); ++i) {
      if (array_[i] == target) {
        return i;
      }
    }
    return -1;
  }

  const int64_t kBigNumber = 10004321;
  const int64_t kMul1 = 123;
  const int64_t kMul2 = 45;
  size_t length_{};
  size_t k_stat_{};
  std::vector<int64_t> array_;
};

int main() {
  //  std::ios_base::sync_with_stdio(false);
  //  std::cin.tie(nullptr);
  //  std::cout.tie(nullptr);
  auto solver = Solver();
  solver.Input();
  solver.RequestProcessing();
  //  for (int a0 = 1; a0 < 100; a0++) {
  //    for (int a1 = 1; a1 < 100; a1++) {
  //      solver.Tests(a0, a1, 10, 5);
  //      if (!solver.TestProcessing()) {
  //        std::cout << "10 5 " << a0 << " " << a1 << "\n";
  //      }
  //    }
  //  }
}
