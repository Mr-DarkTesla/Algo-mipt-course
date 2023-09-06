#include <iostream>

class AVLTree {
 public:
  AVLTree() : root_(nullptr) {}

  ~AVLTree() { DeleteTree(root_); }

  void Insert(int value) {
    if (!Exists(value)) {
      root_ = InsertNode(root_, value);
    }
  }

  bool Exists(int value) { return FindNode(root_, value) != nullptr; }

  int UpperBound(int value) {
    Node* res = UpperBoundNode(root_, value);
    if (res != nullptr) {
      return res->value;
    }
    return -1;
  }

 private:
  struct Node {
    int value;
    Node* left = nullptr;
    Node* right = nullptr;
    int height = 1;
  };

  static int GetHeight(Node* root) {
    if (root != nullptr) {
      return root->height;
    }
    return 0;
  }

  static void Height(Node* root) {
    int h_left = GetHeight(root->left);
    int h_right = GetHeight(root->right);
    root->height = std::max(h_left, h_right) + 1;
  }

  static int GetBalance(Node* root) {
    return GetHeight(root->right) - GetHeight(root->left);
  }

  static Node* TurnLeft(Node* root) {
    Node* tmp = root->right;
    root->right = tmp->left;
    tmp->left = root;
    Height(root);
    Height(tmp);
    return tmp;
  }

  static Node* TurnRight(Node* root) {
    Node* tmp = root->left;
    root->left = tmp->right;
    tmp->right = root;
    Height(root);
    Height(tmp);
    return tmp;
  }

  static Node* BalanceNode(Node* root) {
    Height(root);
    if (GetBalance(root) == 2) {
      if (GetBalance(root->right) < 0) {
        root->right = TurnRight(root->right);
      }
      return TurnLeft(root);
    }
    if (GetBalance(root) == -2) {
      if (GetBalance(root->left) > 0) {
        root->left = TurnLeft(root->left);
      }
      return TurnRight(root);
    }
    return root;
  }

  Node* InsertNode(Node* root, int value) {
    if (root == nullptr) {
      return new Node{value};
    }
    if (value < root->value) {
      root->left = InsertNode(root->left, value);
    } else {
      root->right = InsertNode(root->right, value);
    }
    return BalanceNode(root);
  }

  Node* FindNode(Node* root, int value) {
    if (root == nullptr) {
      return nullptr;
    }
    if (value < root->value) {
      return FindNode(root->left, value);
    }
    if (value > root->value) {
      return FindNode(root->right, value);
    }
    return root;
  }

  static Node* UpperBoundNode(Node* root, int value) {
    Node* res = nullptr;
    while (root != nullptr) {
      if (root->value > value) {
        res = root;
        root = root->left;
      } else {
        root = root->right;
      }
    }
    if (res != nullptr && res->value <= value) {
      return nullptr;
    }
    return res;
  }

  void DeleteTree(Node* root) {
    if (root != nullptr) {
      DeleteTree(root->left);
      DeleteTree(root->right);
      delete root;
    }
  }

  Node* root_;
};

class Solver {
 public:
  void RequestProcessing() {
    std::cin >> requests_;
    Requests();
  }

 private:
  void Requests() {
    int delta = 0;
    for (int i = 0; i < requests_; i++) {
      delta = Request(delta);
    }
  }

  int Request(int delta) {
    char request;
    std::cin >> request;
    int value;
    std::cin >> value;
    if (request == '+') {
      if (delta != 0) {
        tree_.Insert((value + delta) % kBigNumber_);
        delta = 0;
      } else {
        tree_.Insert(value);
      }
    }
    if (request == '?') {
      delta = tree_.UpperBound(value - 1);
      std::cout << delta << std::endl;
    }
    return delta;
  }

  AVLTree tree_{};
  int requests_;
  int kBigNumber_ = 1000000000;
};

int main() {
  auto solver = Solver();
  solver.RequestProcessing();
}
