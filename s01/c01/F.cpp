#include <cctype>
#include <iostream>

class Stack {
 public:
  ~Stack() { Clear(); }

  void Push(int value) {
    if (root_ == nullptr) {
      root_ = new Node;
      root_->val = value;
    } else {
      Node* node = new Node;
      node->val = value;
      node->prev = root_;
      root_ = node;
    }
    number_of_elements_++;
  }

  void Pop() {
    if (root_ == nullptr) {
      throw "error";
    }
    Node* root = root_->prev;
    number_of_elements_--;
    delete root_;
    root_ = root;
  }

  int Back() {
    if (root_ == nullptr) {
      throw "error";
    }
    return root_->val;
  }

  size_t Size() const { return number_of_elements_; }

  bool Empty() const { return root_ == nullptr; }

  void Clear() {
    while (root_ != nullptr) {
      this->Pop();
    }
  }

 private:
  struct Node {
    int val = 0;
    Node* prev = nullptr;
  };

  Node* root_ = nullptr;
  int number_of_elements_ = 0;
};

class Solver {
 public:
  static void RequestProcessing() {
    Stack stack;
    char input;
    while ((std::cin.peek() != '\n') && std::cin >> input) {
      if (std::isdigit(input) == 0) {
        int right = stack.Back();
        stack.Pop();
        int left = stack.Back();
        stack.Pop();
        stack.Push(Operation(left, right, input));
      }
      if (std::isdigit(input) == 1) {
        stack.Push(int(input - '0'));
      }
    }
    std::cout << stack.Back();
  }

 private:
  static int Operation(int left, int right, char operator_to_compute) {
    if (operator_to_compute == '*') {
      return left * right;
    }
    if (operator_to_compute == '+') {
      return left + right;
    }
    if (operator_to_compute == '-') {
      return left - right;
    }
    throw "error";
  }
};

int main() { Solver::RequestProcessing(); }
