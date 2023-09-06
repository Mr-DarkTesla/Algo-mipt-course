#include <iostream>
#include <vector>

typedef std::vector<int64_t> Vector1d;
typedef std::vector<Vector1d> Vector2d;
typedef std::vector<Vector2d> Vector3d;

class Solver {
 public:
  void Process() {
    std::cin >> length_;

    tree_.resize(length_, Vector2d(length_, Vector1d(length_, 0)));

    while (true) {
      std::cin >> request_;
      if (request_ == 1) {
        int64_t x, y, z, value;
        std::cin >> x >> y >> z >> value;

        for (size_t i = x; i < tree_.size(); i = (i | (i + 1))) {
          for (size_t j = y; j < tree_.size(); j = (j | (j + 1))) {
            for (size_t k = z; k < tree_.size(); k = (k | (k + 1))) {
              tree_[i][j][k] += value;
            }
          }
        }
      } else if (request_ == 2) {
        int64_t x1, y1, z1, x2, y2, z2;
        std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;

        int64_t ans;
        ans = Sum(x2, y2, z2) - Sum(x1 - 1, y1 - 1, z1 - 1) +
              Sum(x1 - 1, y1 - 1, z2) - Sum(x2, y2, z1 - 1) +
              Sum(x1 - 1, y2, z1 - 1) - Sum(x2, y1 - 1, z2) +
              Sum(x2, y1 - 1, z1 - 1) - Sum(x1 - 1, y2, z2);
        std::cout << ans << '\n';
      } else if (request_ == 3) {
        break;
      }
    }
  }

 private:
  int64_t Sum(int64_t x, int64_t y, int64_t z) {
    int64_t res = 0;
    for (int64_t i = x; i >= 0; i = (i & (i + 1)) - 1) {
      for (int64_t j = y; j >= 0; j = (j & (j + 1)) - 1) {
        for (int64_t k = z; k >= 0; k = (k & (k + 1)) - 1) {
          res += tree_[i][j][k];
        }
      }
    }
    return res;
  }

  int64_t request_;
  int64_t length_;
  Vector3d tree_;
};

int main() {
  auto solver = Solver();
  solver.Process();
  return 0;
}