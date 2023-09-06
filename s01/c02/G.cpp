#include <iostream>
#include <utility>
#include <vector>

class Solver {
 public:
  void ReadArray() {
    std::cin >> length_;
    array_.resize(length_, 0);
    for (int i = 0; i < length_; ++i) {
      std::cin >> array_[i];
    }
  }

  void RequestProcessing() {
    Quicksort(0, length_ - 1);
    for (int i = 0; i < length_; i++) {
      std::cout << array_[i] << " ";
    }
  }

  auto Partition(int left, int right, int pivot_index) {
    int i = left;
    int j = right;
    int pivot = array_[pivot_index];
    while (i <= j) {
      while (array_[i] < pivot) {
        ++i;
      }
      while (array_[j] > pivot) {
        --j;
      }
      if (i <= j) {
        std::swap(array_[i], array_[j]);
        ++i;
        --j;
      }
    }
    return std::make_pair(j, i);
  }

  void Quicksort(int left, int right) {
    auto pivot_index = Partition(left, right, (left + right) / 2);
    if (pivot_index.first > left) {
      Quicksort(left, pivot_index.first);
    }
    if (pivot_index.second < right) {
      Quicksort(pivot_index.second, right);
    }
  }

 private:
  const int kChunk = 5;
  int length_ = 0;
  std::vector<int> array_;
};

int main() {
  auto solver = Solver();
  solver.ReadArray();
  solver.RequestProcessing();
}