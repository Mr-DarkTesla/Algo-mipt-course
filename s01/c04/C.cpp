#include <algorithm>
#include <iostream>
#include <vector>

struct Segment {
  int64_t start{};
  int64_t end{};
  int64_t count{1};
};

bool operator<(const Segment& left, const Segment& right) {
  if (left.start == right.start) {
    return left.end > right.end;
  }
  return left.start < right.start;
} 

class BinaryTree {
 public:
  void Init(std::vector<int64_t> data) {
    data = std::move(data);
    sum_.resize(data.size(), 0);
    for (size_t i = 0; i < data.size(); ++i) {
      UpdateDelta(i, data[i]);
    }
  }

  void UpdateValue(int64_t index, int64_t value) {
    UpdateDelta(index, value - data[index]);
    data[index] = value;
  }

  int64_t PrefixSum(int64_t index) {
    int64_t res = 0;
    for (int64_t i = index; i >= 0; i = GetPrev(i) - 1) {
      res += sum_[i];
    }
    return res;
  }

 private:
  void UpdateDelta(int64_t index, int64_t delta) {
    for (int64_t i = index; i < sum_.size(); i = GetNext(i)) {
      sum_[i] += delta;
    }
  }

  static int64_t GetPrev(int64_t i) { return i & (i + 1); }

  static int64_t GetNext(int64_t i) { return i | (i + 1); }

  std::vector<int64_t> data;
  std::vector<int64_t> sum_;
};

class Solver {
 public:
  void Input() {
    std::cin >> length_;
    data.resize(length_);
    scan_line_.resize(length_);

    seg_data_.resize(length_);
    tree_data_.resize(length_);

    for (int64_t i = 0; i < length_; ++i) {
      std::cin >> data[i].start >> data[i].end;
      scan_line_[i] = i;
    }
  }

  void Process() { 
    std::sort(data.begin(), data.end());
    scans_ = 0;
    for (int64_t i = 0; i < length_; ++i, ++scans_) {
      seg_data_[scans_] = data[i];
      if (i < length_ - 1 && data[i].start == data[i + 1].start &&
          data[i].end == data[i + 1].end) {
        int64_t repeat_start = i;
        i++;
        while (i < length_ && data[repeat_start].start == data[i].start &&
               data[repeat_start].end == data[i].end) {
          seg_data_[scans_].count++;
          ++i;
        }
        --i;
      }
      tree_data_[scans_] = seg_data_[scans_].count;
    }
    tree_data_.resize(scans_);
    seg_data_.resize(scans_);
    scan_line_.resize(scans_);
    std::sort(scan_line_.begin(), scan_line_.end(),
              [&](int64_t ind_a, int64_t ind_b) {
                auto a = seg_data_[ind_a];
                auto b = seg_data_[ind_b];
                return a < b;
              });
    tree_.Init(tree_data_);
    std::cout << CalcAns() << std::endl;
  }

 private:
  int64_t CalcAns() {
    int64_t res = 0;
    for (int64_t i = 0; i < scans_; ++i) {
      res += tree_.PrefixSum(scan_line_[i] - 1) *
             seg_data_[scan_line_[i]].count;
      tree_.UpdateValue(scan_line_[i], 0);
    }
    return res;
  }

  int64_t length_;
  int64_t scans_;
  std::vector<Segment> data;
  std::vector<int64_t> scan_line_;
  std::vector<Segment> seg_data_;
  std::vector<int64_t> tree_data_;
  BinaryTree tree_;
};

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0), std::cout.tie(0);

  auto solver = Solver();
  solver.Input();
  solver.Process();

}