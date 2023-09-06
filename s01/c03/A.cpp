#include <iostream>
#include <utility>
#include <vector>

class DecTree {
 public:
  DecTree() = default;

  ~DecTree() { DeleteTree(root_); }

  void AddNode(int key, int prior) {
    if (size_ == 0) {
      root_->key = key;
      root_->prior = prior;
      root_->index = size_ + 1;
      theright_ = root_;
      ++size_;
      return;
    }
    Node* new_node = new Node{key, prior, size_ + 1};
    Node* current = theright_;
    if (new_node->prior > current->prior) {
      new_node->parent = current;
      current->right = new_node;
      theright_ = new_node;
      ++size_;
      return;
    }
    while (new_node->prior < current->prior && current->parent != nullptr) {
      current = current->parent;
    }
    if (current->parent == nullptr) {
      if (new_node->prior > current->prior) {
        new_node->left = root_->right;
        root_->right->parent = new_node;
        root_->right = new_node;
        new_node->parent = root_;
      } else {
        new_node->left = root_;
        root_->parent = new_node;
        root_ = new_node;
        new_node->parent = nullptr;
      }
    } else {
      new_node->left = current->right;
      current->right->parent = new_node;
      current->right = new_node;
      new_node->parent = current;
    }
    theright_ = new_node;
    ++size_;
  }

  void Output() { OutTree(root_); }

 private:
  struct Node {
    int key;
    int prior;
    size_t index;
    Node* parent = nullptr;
    Node* left = nullptr;
    Node* right = nullptr;
  };

  void OutNodeStatus(Node* node) {
    std::cout << (node->parent == nullptr ? 0 : node->parent->index) << " "
              << (node->left == nullptr ? 0 : node->left->index) << " "
              << (node->right == nullptr ? 0 : node->right->index) << "\n";
  }

  void OutTree(Node* root) {
    if (root != nullptr) {
      OutTree(root->left);
      OutNodeStatus(root);
      OutTree(root->right);
    }
  }

  void DeleteTree(Node* root) {
    if (root != nullptr) {
      DeleteTree(root->left);
      DeleteTree(root->right);
      delete root;
    }
  }

  size_t size_ = 0;
  Node* root_ = new Node{};
  Node* theright_ = root_;
};

class Solver {
 public:
  void RequestProcessing() {
    ReadArray();
    Requests();
  }

 private:
  void ReadArray() {
    std::cin >> length_;
    int tmp_left;
    int tmp_right;
    for (size_t i = 0; i < length_; i++) {
      std::cin >> tmp_left >> tmp_right;
      array_.push_back(std::make_pair(tmp_left, tmp_right));
    }
  }

  void Requests() {
    DecTree tree{};
    for (auto& el : array_) {
      tree.AddNode(el.first, el.second);
    }
    std::cout << "YES\n";
    tree.Output();
  }

  size_t length_{};
  std::vector<std::pair<int, int>> array_;
};

int main() {
  auto solver = Solver();
  solver.RequestProcessing();
}
