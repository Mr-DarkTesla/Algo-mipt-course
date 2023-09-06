#include <iostream>

class AVLTree {
 public:
  AVLTree() : root_(nullptr) {}

  ~AVLTree() { DeleteTree(root_); }

  void Insert(int64_t value) {
    if (!Exists(value)) {
      root_ = InsertNode(root_, value);
      UpdateSum(root_);
    }
  }

  bool Exists(int64_t value) { return FindNode(root_, value) != nullptr; }

  int64_t Sum(int64_t left, int64_t right) { 
    return Sum(root_, right) - Sum(root_, left - 1);
  }

  void Output() { Output(root_); }


 private:
  struct Node {
    int64_t value;
    int64_t sum;
    Node* left = nullptr;
    Node* right = nullptr;
    int64_t height = 1;
  };

  static int64_t GetHeight(Node* root) {
    if (root != nullptr) {
      return root->height;
    }
    return 0;
  }

  static void Height(Node* root) {
    int64_t h_left = GetHeight(root->left);
    int64_t h_right = GetHeight(root->right);
    root->height = std::max(h_left, h_right) + 1;
  }

  static int64_t GetBalance(Node* root) {
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

  Node* InsertNode(Node* root, int64_t value) {
    if (root == nullptr) {
      return new Node{value, value};
    }
    if (value < root->value) {
      root->left = InsertNode(root->left, value);
    } else {
      root->right = InsertNode(root->right, value);
    }
    return BalanceNode(root);
  }

  Node* FindNode(Node* root, int64_t value) {
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

  static Node* LowerBoundNode(Node* root, int value) {
    Node* res = nullptr;
    while (root != nullptr) {
      if (root->value > value) {
        root = root->left;
      } else {
        res = root;
        root = root->right;
      }
    }
    if (res != nullptr && res->value >= value) {
      return nullptr;
    }
    return res;
  }

  static int64_t Sum(Node* root, int value) {
    int64_t res = root->sum;
    while (root != nullptr) {
      if (root->value == value) {
        if (root->right != nullptr) {
          res -= root->right->sum;
        }
        return res;
      }
      if (root->value > value) {
        if (root->right != nullptr) {
          res -= root->right->sum;
        }
        root = root->left;
      } else {
        root = root->right;
      }
    }
    return res;
  }

  int64_t UpdateSum(Node* root) {
    if (root != nullptr) {
      return root->sum = root->value + UpdateSum(root->left) + UpdateSum(root->right);
    }
    return 0;
  }

  void DeleteTree(Node* root) {
    if (root != nullptr) {
      DeleteTree(root->left);
      DeleteTree(root->right);
      delete root;
    }
  }

  void Output(Node* root) {
    if (root != nullptr) {
      Output(root->left);
      std::cout << root->value << "::" << root->sum << "::" << root->height
                << std::endl;
      Output(root->right);
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
    int64_t delta = 0;
    for (int64_t i = 0; i < requests_; i++) {
      char request;
      std::cin >> request;
      int64_t left;
      std::cin >> left;
      if (request == '+') {
        if (delta != 0) {
          tree_.Insert((left + delta) % kBigNumber_);
          delta = 0;
        } else {
          tree_.Insert(left);
        }
      }
      if (request == '?') {
        tree_.Output();
        int64_t right;
        std::cin >> right;
        delta = tree_.Sum(left, right);
        std::cout << delta << std::endl;
      }
    }
  }

  AVLTree tree_{};
  int64_t requests_;
  int64_t kBigNumber_ = 1000000000;
};

int main() {
  auto solver = Solver();
  solver.RequestProcessing();
}
