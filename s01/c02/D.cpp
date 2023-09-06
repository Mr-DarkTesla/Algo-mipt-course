#include <algorithm>
#include <iostream>
#include <vector>

class Heap {
 public:
  void Insert(int64_t value) {
    nodes_.emplace_back(value);
    SiftUp(GetSize() - 1);
  }

  int64_t GetMax() { return nodes_[0]; }

  void Sort() { std::sort(nodes_.begin(), nodes_.end()); }

  void Output() {
    for (auto element : nodes_) {
      std::cout << element << " ";
    }
    std::cout << "\n";
  }

  void ExtractMin() {
    nodes_[0] = nodes_.back();
    nodes_.pop_back();
    SiftDown(0);
  }

 private:
  void SiftDown(size_t index) {
    while (GetLeftChild(index) < GetSize()) {
      size_t left_child = GetLeftChild(index);
      size_t right_child = GetRightChild(index);
      size_t child = left_child;
      if (right_child < GetSize() && nodes_[right_child] > nodes_[left_child]) {
        ++child;
      }
      if (nodes_[index] >= nodes_[child]) {
        break;
      }
      std::swap(nodes_[index], nodes_[child]);
      index = child;
    }
  }

  void SiftUp(size_t index) {
    while ((index != 0) && nodes_[index] > nodes_[GetParent(index)]) {
      std::swap(nodes_[index], nodes_[GetParent(index)]);
      index = GetParent(index);
    }
  }

  size_t GetSize() { return nodes_.size(); }

  static size_t GetParent(size_t node_index) { return (node_index - 1) / 2; }

  static size_t GetLeftChild(size_t node_index) { return 2 * node_index + 1; }

  static size_t GetRightChild(size_t node_index) { return 2 * node_index + 2; }

  std::vector<int64_t> nodes_{};
};

class Solver {
 public:
  void RequestProcessing() {
    std::cin >> number_of_elements_ >> k_elements_;
    std::cin >> a_start_ >> mul_ >> bias_;
    int64_t a_cur = a_start_;
    for (int64_t i = 0; i < k_elements_; i++) {
      int64_t a_new = (a_cur * mul_ + bias_) % kMOD;
      a_cur = a_new;
      heap_.Insert(a_new);
    }
    for (int64_t i = 0; i < number_of_elements_ - k_elements_; i++) {
      int64_t a_new = (a_cur * mul_ + bias_) % kMOD;
      a_cur = a_new;
      heap_.Insert(a_new);
      heap_.ExtractMin();
    }
    heap_.Sort();
    heap_.Output();
  }

 private:
  const int64_t kMOD = 1073741824;
  Heap heap_;
  int64_t number_of_elements_{};
  int64_t k_elements_{};
  int64_t a_start_{};
  int64_t mul_{};
  int64_t bias_{};
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  Solver solver;
  solver.RequestProcessing();
}