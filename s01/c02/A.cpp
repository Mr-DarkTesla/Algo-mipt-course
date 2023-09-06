#include <iostream>
#include <vector>

class Pair {
 public:
  int64_t l;
  int64_t r;
};

class Solver {
 public:
  void RequestProcessing() {
    ReadArray();
    Quicksort(0, length_ - 1);
    FindTracks();
    Output();
  }

 private:
  void ReadArray() {
    std::cin >> length_;
    Pair temp_pair{};
    for (size_t i = 0; i < length_; i++) {
      std::cin >> temp_pair.l >> temp_pair.r;
      array_.push_back(temp_pair);
    }
  }

  static bool CmpLs(Pair left_op, Pair right_op) {
    return (left_op.l < right_op.l);
  }

  static bool CmpGr(Pair left_op, Pair right_op) {
    return (left_op.l > right_op.l);
  }

  auto Partition(int left, int right, int pivot_index) {
    int i = left;
    int j = right;
    auto pivot = array_[pivot_index];
    while (i <= j) {
      while (CmpLs(array_[i], pivot)) {
        ++i;
      }
      while (CmpGr(array_[j], pivot)) {
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

  //  size_t Partition(size_t left, size_t right) {
  //    size_t pivot_index = (left + right) / 2;
  //    Pair pivot = array_[pivot_index];
  //    std::swap(array_[pivot_index], array_[right]);
  //    size_t next = left;
  //    while (left < right) {
  //      if (Cmp(array_[left], pivot)) {
  //        std::swap(array_[next], array_[left]);
  //        next++;
  //      }
  //      left++;
  //    }
  //    std::swap(array_[next], array_[right]);
  //    return next;
  //  }
  //
  //  void Quicksort(size_t left, size_t right) {
  //    if (left < right) {
  //      size_t divisor = Partition(left, right);
  //      Quicksort(left, divisor);
  //      Quicksort(divisor + 1, right);
  //    }
  //  }

  void FindTracks() {
    int64_t most_left = array_[0].l;
    int64_t most_right = array_[0].r;
    for (size_t i = 1; i < length_; i++) {
      int64_t left = array_[i].l;
      int64_t right = array_[i].r;
      if (left > most_right) {
        ans_.push_back(Pair{most_left, most_right});
        most_left = left;
        most_right = right;
        continue;
      }
      most_right = std::max(most_right, right);
    }
    ans_.push_back(Pair{most_left, most_right});
  }

  void Output() {
    std::cout << ans_.size() << "\n";
    for (auto& element : ans_) {
      std::cout << element.l << " " << element.r << "\n";
    }
  }

  size_t length_{};
  std::vector<Pair> array_;
  std::vector<Pair> ans_;
};

int main() {
  auto solver = Solver();
  solver.RequestProcessing();
}
