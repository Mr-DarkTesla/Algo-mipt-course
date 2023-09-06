#include <iostream>
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
    ReadArray();
    std::cout << MergeSort(0, static_cast<int>(array_.size()));
  }

  int Merge(int left, int mid, int length) {
    int number_of_inversions = 0;
    for (int i = 0, j = 0, k = mid; i < length; i++) {
      if (k >= length || (j < mid && array_[left + j] < array_[left + k])) {
        array_copy_[i] = array_[left + j++];
      } else {
        array_copy_[i] = array_[left + k++];
        number_of_inversions += mid - j;
      }
    }
    for (int i = 0; i < length; i++) {
      array_[left + i] = array_copy_[i];
    }
    return number_of_inversions;
  }

  int MergeSort(int left, int current_length) {
    if (current_length < 2) {
      return 0;
    }
    int number_of_inversions = 0;
    array_copy_.resize(current_length, 0);
    int mid = current_length / 2;

    number_of_inversions += MergeSort(left, mid);
    number_of_inversions += MergeSort(left + mid, current_length - mid);

    return number_of_inversions + Merge(left, mid, current_length);
  }

 private:
  int length_ = 0;
  std::vector<int> array_;
  std::vector<int> array_copy_;
};

int main() {
  Solver s;
  s.RequestProcessing();
  return 0;
}