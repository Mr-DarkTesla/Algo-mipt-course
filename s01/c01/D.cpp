#include <iostream>
#include <string>

class Stack {
 public:
  ~Stack() { Clear(); }

  void Push(int value) {
    if (root_ == nullptr) {
      root_ = new Node;
      root_->val = value;
      root_->min = root_->val;
    } else {
      Node* node = new Node;
      node->val = value;
      node->min = std::min(root_->min, value);
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

  int Min() {
    if (root_ == nullptr) {
      throw "error";
    }
    return root_->min;
  }

  void Clear() {
    while (root_ != nullptr) {
      this->Pop();
    }
  }

 private:
  struct Node {
    int val = 0;
    int min = 0;
    Node* prev = nullptr;
  };

  Node* root_ = nullptr;
  int number_of_elements_ = 0;
};

void HandlePush(Stack* stack) {
  int value;
  std::cin >> value;
  stack->Push(value);
  std::cout << "ok\n";
}

void RequestProcessing() {
  std::string request;
  Stack stack;
  int number_of_requests;
  std::cin >> number_of_requests;
  for (int i = 0; i < number_of_requests; i++) {
    std::cin >> request;
    if (request == "push") {
      HandlePush(&stack);
    } else if (request == "size") {
      std::cout << stack.Size() << "\n";
    } else if (request == "clear") {
      stack.Clear();
      std::cout << "ok\n";
    } else {
      try {
        if (request == "min") {
          std::cout << stack.Min() << "\n";
        } else if (request == "pop") {
          std::cout << stack.Back() << "\n";
          stack.Pop();
        } else if (request == "back") {
          std::cout << stack.Back() << "\n";
        }
      } catch (...) {
        std::cout << "error\n";
      }
    }
  }
}

int main() { RequestProcessing(); }
