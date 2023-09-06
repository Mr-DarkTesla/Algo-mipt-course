#include <iostream>
#include <string>
#include <vector>

class Heap {
 public:
  bool Empty() { return nodes_.empty(); }

  void Insert(int value, int step) {
    nodes_.emplace_back(value, step);
    SiftUp(GetSize() - 1);
  }

  int GetMinVal() { return nodes_[0].value; }

  size_t GetMinIndex() { return nodes_[0].step_added; }

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
      if (right_child < GetSize() && nodes_[right_child] < nodes_[left_child]) {
        ++child;
      }
      if (nodes_[index] <= nodes_[child]) {
        break;
      }
      std::swap(nodes_[index], nodes_[child]);
      index = child;
    }
  }

  void SiftUp(size_t index) {
    while ((index != 0) && nodes_[index] < nodes_[GetParent(index)]) {
      std::swap(nodes_[index], nodes_[GetParent(index)]);
      index = GetParent(index);
    }
  }

  size_t GetSize() { return nodes_.size(); }

  static size_t GetParent(size_t node_index) { return (node_index - 1) / 2; }

  static size_t GetLeftChild(size_t node_index) { return 2 * node_index + 1; }

  static size_t GetRightChild(size_t node_index) { return 2 * node_index + 2; }

  class Node {
   public:
    Node(int value, int step) : value(value), step_added(step) {}

    int value{};
    size_t step_added{};

    bool operator<(Node& node) const { return this->value < node.value; }

    bool operator<=(Node& node) const { return this->value <= node.value; }
  };

  std::vector<Node> nodes_{};
};

class Solver {
 public:
  void RequestProcessing() {
    std::cin >> length_;
    array_.resize(length_, 0);
    ans_.resize(length_, 0);
    used_.resize(length_, false);
    for (size_t i = 0; i < length_; i++) {
      std::cin >> array_[i];
      heap_.Insert(array_[i], i);
    }
    while (!heap_.Empty()) {
      size_t index = heap_.GetMinIndex();
      int val = heap_.GetMinVal();
      heap_.ExtractMin();
      for (size_t i = 0; i < index; i++) {
        if (!used_[i] && array_[i] != val) {
          ans_[i]++;
        }
      }
      used_[index] = true;
    }
    for (auto element : ans_) {
      std::cout << element << " ";
    }
  }

 private:
  std::vector<int> array_;
  std::vector<int> ans_;
  std::vector<bool> used_;
  Heap heap_;
  size_t length_{};
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  Solver solver;
  solver.RequestProcessing();
}