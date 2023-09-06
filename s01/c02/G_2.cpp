#include <iostream>
#include <vector>

#include <iterator>
#include <algorithm>
#include <random>

class Solver {
 public:
  void RequestProcessing() {
    Quicksort(0, length_ - 1);
//    MedianMedian(0, length_ - 1, array_);
    for (size_t i = 0; i < length_; i++) {
      std::cout << array_[i] << " ";
    }
  }

  bool Test() {
    array_ = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(array_.begin(), array_.end(), g);
    std::copy(array_.begin(), array_.end(), std::ostream_iterator<int>(std::cout, " "));
    Quicksort(0, 10);
    for (size_t i = 0; i < 10; i++) {
      if (array_[i] != i) {
//        std::cout << array_[i];
        return false;
      }
    }
    return true;
  }

  void ReadArray() {
    std::cin >> length_;
    int tmp;
    for (size_t i = 0; i < length_; i++) {
      std::cin >> tmp;
      array_.push_back(tmp);
    }
  }

 private:
  size_t Partition(size_t left, size_t right, size_t pivot_index) {
    int pivot = array_[left + pivot_index];
    std::swap(array_[left + pivot_index], array_[right]);
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

  size_t MedianChunk(size_t left, size_t right, std::vector<size_t>& array) {
    for (size_t i = left; i < right; i++) {
      for (size_t j = i + 1; j <= right; j++) {
        if (array_[array[i]] > array_[array[j]]) {
          std::swap(array[i], array[j]);
        }
      }
    }
    return array[(left + right) / 2];
  }

  size_t MedianMedian(size_t left, size_t right, std::vector<size_t> array) {
    size_t length = right - left + 1;
    size_t num_of_chunks = (length + kChunk - 1) / kChunk;
    std::vector<size_t> medians(num_of_chunks, 0);
    for (size_t i = 0; i < num_of_chunks; i++) {
      medians[i] = MedianChunk(left + i * kChunk, std::min(left + (i + 1) * kChunk - 1, right), array);
    }
    if (num_of_chunks == 1) {
      return medians[0];
    }
    return MedianMedian(0, num_of_chunks, medians);
  }

  void Quicksort(size_t left, size_t right) {
    std::vector<size_t> index(right - left + 1, 0);
    for (size_t i = left; i <= right; i++) {
      index[i] = i;
    }

    size_t pivot_index = MedianMedian(left, right, index);
    pivot_index = Partition(left, right, pivot_index);
    if (left != pivot_index) {
      Quicksort(left, pivot_index - 1);
    }
    if (right != pivot_index) {
      Quicksort(pivot_index + 1, right);
    }
  }

  const int64_t kChunk = 5;
  size_t length_{};
  std::vector<int> array_{};
};

int main() {
  auto solver = Solver();
  solver.ReadArray();
  solver.RequestProcessing();
//  for (int i = 0; i < 1000; i++) {
//    if (!solver.Test()){
//      std::cout << "--------------!\n";
//    }
//    std::cout << "\n";
//  }
}