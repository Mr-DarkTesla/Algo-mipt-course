#include <iostream>
#include <string>
#include <vector>

class Heap {
 public:
  void Insert(int64_t value, int64_t step) {
    nodes_.emplace_back(value, step);
    SiftUp(GetSize() - 1);
  }

  int64_t GetMax() { return nodes_[0].value; }

  void ExtractMin() {
    nodes_[0] = nodes_.back();
    nodes_.pop_back();
    SiftDown(0);
  }

  void DecreaseKey(int64_t step, int64_t delta) {
    for (size_t i = 0; i < GetSize(); i++) {
      if (nodes_[i].step_added == step) {
        nodes_[i].value -= delta;
        SiftUp(i);
        break;
      }
    }
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
    Node(int64_t value, int64_t step) : value(value), step_added(step) {}

    int64_t value{};
    int64_t step_added{};

    bool operator<(Node& node) const { return this->value < node.value; }

    bool operator<=(Node& node) const { return this->value <= node.value; }
  };

  std::vector<Node> nodes_{};
};

class Solver {
 public:
  void RequestProcessing() {
    std::cin >> number_of_requests_;
    int64_t passed_request = 0;
    for (int64_t i = 0; i < number_of_requests_; i++) {
      std::cin >> request_;
      ++passed_request;
      if (request_ == "insert") {
        int64_t new_value;
        std::cin >> new_value;
        heap_.Insert(new_value, passed_request);
      }
      if (request_ == "decreaseKey") {
        int64_t key;
        int64_t delta;
        std::cin >> key >> delta;
        heap_.DecreaseKey(key, delta);
      }
      if (request_ == "extractMin") {
        heap_.ExtractMin();
      }
      if (request_ == "getMin") {
        std::cout << heap_.GetMax() << '\n';
      }
    }
  }

 private:
  Heap heap_;
  int64_t number_of_requests_;
  std::string request_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  Solver solver;
  solver.RequestProcessing();
}