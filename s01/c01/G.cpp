#include <iostream>

enum class Brackets {
  CubicOpen,
  CubicClose,
  FigureOpen,
  FigureClose,
  CircleOpen,
  CircleClose,
  Kek
};

class Stack {
 public:
  ~Stack() { Clear(); }

  void Push(Brackets value) {
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

  Brackets Back() {
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
    Brackets val;
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
      Brackets right = Encode(input);
      if ((!stack.Empty()) && IsOk(stack.Back(), right)) {
        stack.Pop();
      } else {
        stack.Push(right);
      }
    }
    std::cout << ((stack.Empty()) ? "YES" : "NO");
  }

 private:
  static Brackets Encode(char symbol) {
    switch (symbol) {
      case '[':
        return Brackets::CubicOpen;
      case '{':
        return Brackets::FigureOpen;
      case '(':
        return Brackets::CircleOpen;
      case ']':
        return Brackets::CubicClose;
      case '}':
        return Brackets::FigureClose;
      case ')':
        return Brackets::CircleClose;
    }
    return Brackets::Kek;
  }
  static bool IsOk(Brackets left, Brackets right) {
    return (left == Brackets::CubicOpen && right == Brackets::CubicClose) ||
           (left == Brackets::FigureOpen && right == Brackets::FigureClose) ||
           (left == Brackets::CircleOpen && right == Brackets::CircleClose);
  }
};

int main() { Solver::RequestProcessing(); }
