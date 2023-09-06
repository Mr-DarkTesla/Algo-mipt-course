// 73589616
#include <iostream>
#include <string>

class AVLTree {
 public:
  AVLTree() : root_(nullptr) {}

  ~AVLTree() { delete root_; }

  void Insert(std::string& value, std::string& data) {
    if (!Exists(value)) {
      root_ = InsertNode(root_, value, data);
    }
  }

  bool Exists(std::string& value) { return FindNode(root_, value) != nullptr; }

  std::string Find(std::string& value) {
    Node* node = FindNode(root_, value);
    if (node == nullptr) {
      return "";
    }
    return node->data;
  }

  void Output() { Output(root_); }

 private:
  class Node {
   public:
    Node(){};
    Node(std::string value, std::string data) : value(value), data(data){};

    ~Node() {
      delete left;
      delete right;
    }

    std::string value;
    std::string data;
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

  Node* InsertNode(Node* root, std::string& value, std::string& data) {
    if (root == nullptr) {
      return new Node{value, data};
    }
    if (value < root->value) {
      root->left = InsertNode(root->left, value, data);
    } else {
      root->right = InsertNode(root->right, value, data);
    }
    return BalanceNode(root);
  }

  Node* FindNode(Node* root, std::string& value) {
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

  void Output(Node* root) {
    if (root != nullptr) {
      Output(root->left);
      std::cout << root->value << "::" << root->data << "::" << root->height
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
    Filling();
    std::cin >> requests_;
    Requests();
  }

 private:
  void Requests() {
    std::string request;
    std::string response;
    for (int i = 0; i < requests_; i++) {
      std::cin >> request;
      response = pilot_tree_.Find(request);
      if (response.empty()) {
        response = car_tree_.Find(request);
      }
      std::cout << response << "\n";
    }
  }

  void Filling() {
    std::string pilot;
    std::string car;
    for (int i = 0; i < requests_; i++) {
      std::cin >> pilot >> car;
      pilot_tree_.Insert(pilot, car);
      car_tree_.Insert(car, pilot);
    }
  }

  AVLTree pilot_tree_{};
  AVLTree car_tree_{};
  int requests_{};
};

int main() {
  auto solver = Solver();
  solver.RequestProcessing();
}