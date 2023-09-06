#include <iostream>

struct Node {
  int data_ = 0;
  Node* left_ = nullptr;
  Node* right_ = nullptr;
  int balance_ = 0;
  int height_ = 0;
};

int GetHeight(Node* root) {
  if (root != nullptr) {
    return root->height_;
  }
  return 0;
}
void Height(Node* root) {
  if (GetHeight(root->right_) > GetHeight(root->left_)) {
    root->height_ = GetHeight(root->right_) + 1;
  } else {
    root->height_ = 1 + GetHeight(root->left_);
  }
}

void Balance(Node* root) {
  if (root != nullptr) {
    root->balance_ = GetHeight(root->right_) - GetHeight(root->left_);
  }
}

Node* TurnLeft(Node* root) {
  Node* rightSubtree;
  Node* rightSubtreeLeftSubtree;
  rightSubtree = root->right_;
  rightSubtreeLeftSubtree = rightSubtree->left_;
  rightSubtree->left_ = root;
  root->right_ = rightSubtreeLeftSubtree;
  root = rightSubtree;
  Height(root->left_);
  Height(root);
  Balance(root->left_);
  Balance(root);
  return root;
}
Node* TurnRight(Node*(&root)) {
  Node *leftSubtree, *leftSubtreeRightSubtree;
  leftSubtree = root->left_;
  leftSubtreeRightSubtree = leftSubtree->right_;
  leftSubtree->right_ = root;
  root->left_ = leftSubtreeRightSubtree;
  root = leftSubtree;
  Height(root->right_);
  Height(root);
  Balance(root->right_);
  Balance(root);
  return root;
}
Node* Insert(Node* root, int newData) {
  if (root == nullptr) {
    root = new Node;
    root->data_ = newData;
    root->left_ = nullptr;
    root->right_ = nullptr;
    root->balance_ = 0;
    root->height_ = 0;
  } else {
    if (newData > root->data_) {
      root->right_ = Insert(root->right_, newData);
      Height(root->right_);
      if (GetHeight(root->right_) - GetHeight(root->left_) > 1) {
        if (GetHeight(root->right_->right_) < GetHeight(root->right_->left_)) {
          root->right_ = TurnRight(root->right_);
        }
        root = TurnLeft(root);
      }
    } else if (newData < root->data_) {
      root->left_ = Insert(root->left_, newData);
      Height(root->left_);
      if (GetHeight(root->left_) - GetHeight(root->right_) > 1) {
        if (GetHeight(root->left_->left_) < GetHeight(root->left_->right_)) {
          root->left_ = TurnLeft(root->left_);
        }
        root = TurnRight(root);
      }
    }
    Balance(root);
  }
  return root; 
}
int Find(Node* root, int element) {
  while (root != nullptr && root->data_ < element) {
    if (root->data_ >= element) {
      return Find(root->left_, element);
    }
    return Find(root->right_, element);
  }
  if (root == nullptr) {
    return 0;
  }
  return root->data_;
}

void PostorderWalk(Node* root) {
  if (root != nullptr) {
    PostorderWalk(root->left_);
    PostorderWalk(root->right_);
    delete root;
  }
}

int main() {
  const int Divider = 1000000000;
  Node* root = nullptr;
  bool is_next = false;
  int number = 0;
  std::cin >> number;
  int value = 0;
  for (int i = 0; i < number; i++) {
    char symbol;
    std::cin >> symbol;
    int element = 0;
    std::cin >> element;
    if (symbol == '+') {
      if (is_next) {
        root = Insert(root, (element + value) % Divider);
        value = 0;
        is_next = false;
      } else {
        root = Insert(root, element);
      }
    } else {
      is_next = true;
      int find = 0;
      find = Find(root, element);
      if (find != 0) {
        value = find;
        std::cout << value << std::endl;
      } else {
        value = -1;
        std::cout << value << std::endl;
      }
    }
  }
  PostorderWalk(root);
}

