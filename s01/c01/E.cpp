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

  bool Empty() const { return root_ == nullptr; }

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

class DequeueOnStacks {
 public:
  ~DequeueOnStacks() { Clear(); }

  void Enqueue(int value) { stack1_.Push(value); }

  int Front() {
    if (stack2_.Empty()) {
      if (stack1_.Empty()) {
        throw "error";
      }
      while (!stack1_.Empty()) {
        int last = stack1_.Back();
        stack1_.Pop();
        stack2_.Push(last);
      }
    }
    return stack2_.Back();
  }

  void Dequeue() {
    if (stack2_.Empty()) {
      if (stack1_.Empty()) {
        throw "error";
      }
    }
    stack2_.Pop();
  }

  size_t Size() { return stack1_.Size() + stack2_.Size(); }

  int Min() {
    if (stack1_.Empty() && stack2_.Empty()) {
      throw "error";
    }
    if (stack1_.Empty()) {
      return stack2_.Min();
    }
    if (stack2_.Empty()) {
      return stack1_.Min();
    }
    return std::min(stack1_.Min(), stack2_.Min());
  }

  void Clear() {
    stack1_.Clear();
    stack2_.Clear();
  }

 private:
  Stack stack1_ = Stack();
  Stack stack2_ = Stack();
};

void HandlePush(DequeueOnStacks* dequeue_on_stacks) {
  int value;
  std::cin >> value;
  dequeue_on_stacks->Enqueue(value);
  std::cout << "ok\n";
}

void RequestProcessing() {
  std::string request;
  DequeueOnStacks dequeue_on_stacks;
  int number_of_requests;
  std::cin >> number_of_requests;
  for (int i = 0; i < number_of_requests; i++) {
    std::cin >> request;
    if (request == "enqueue") {
      HandlePush(&dequeue_on_stacks);
    } else if (request == "size") {
      std::cout << dequeue_on_stacks.Size() << "\n";
    } else if (request == "clear") {
      dequeue_on_stacks.Clear();
      std::cout << "ok\n";
    } else {
      try {
        if (request == "min") {
          std::cout << dequeue_on_stacks.Min() << "\n";
        } else if (request == "dequeue") {
          std::cout << dequeue_on_stacks.Front() << "\n";
          dequeue_on_stacks.Dequeue();
        } else if (request == "front") {
          std::cout << dequeue_on_stacks.Front() << "\n";
        }
      } catch (...) {
        std::cout << "error\n";
      }
    }
  }
}

int main() { RequestProcessing(); }
