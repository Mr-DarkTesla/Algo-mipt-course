#include <iostream>
#include <cmath>
#include <vector>

typedef std::vector<int64_t> Vector1d;
typedef std::vector<Vector1d> Vector2d;


class SparseTable {
 public:
  void Init(Vector1d data) {
    size_t length_ = data.size();
    table_.resize(kInf, Vector1d(kInf));
    for (size_t i = 0; i < length_; i++) {
      table_[i][0] = data[i];
    }
    for (size_t i = 1; i < length_; i++) {
      table_[i][0] = data[i];
    }
    for (size_t j = 1; (size_t)(1 << j) <= length_; j++) {
      for (size_t i = 0; (size_t)(i + (1 << j) - 1) < length_; i++) {
        if (table_[i][j - 1] < table_[i + (1 << (j - 1))][j - 1]) {
          table_[i][j] = table_[i][j - 1];
        } else {
          table_[i][j] = table_[i + (1 << (j - 1))][j - 1];
        }
      }
    }
  }

  int64_t RMQ(int64_t left, int64_t right) {
    int64_t j = (int64_t)std::log2(right - left + 1);
    if (table_[left][j] <= table_[right - (1 << j) + 1][j])
      return table_[left][j];

    else
      return table_[right - (1 << j) + 1][j];
  }

  void Output() {
    for (auto& mass : table_) {
      for (auto& el : mass) {
        std::cout << el << " ";
      }
      std::cout << std::endl;
    }
  }

 private:
  size_t length_;
  Vector2d table_;
  int64_t kInf = 1000;
};

class Solver {
 public:
  void Input() {
    std::cin >> length_;
    std::cin >> requests_;
    data_.resize(length_);

    for (int64_t i = 0; i < length_; ++i) {
      std::cin >> data_[i];
    }
    table_.Init(data_);
    //table_.Output();
  }

  void Process() { 
    for (int i = 0; i < requests_; ++i) {
      int64_t left, right;
      std::cin >> left >> right;
      std::cout << table_.RMQ(left, right - 1) << std::endl;
    }
  }

 private:
  SparseTable table_;
  int64_t length_;
  int64_t requests_;
  Vector1d data_;
};

int main() {
  auto solver = Solver();
  solver.Input();
  solver.Process();
  return 0;
}