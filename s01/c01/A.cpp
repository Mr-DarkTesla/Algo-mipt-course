#include <iostream>

class Solver {
 public:
  ~Solver() { delete[] array_; }

  void ReadArray() {
    int number_of_elements;
    std::cin >> number_of_elements;
    array_ = new int[number_of_elements];
    for (int i = 0; i < number_of_elements; i++) {
      std::cin >> array_[i];
    }
  }

  void RequestProcessing() {
    int number_of_requests;
    int begin;
    int end;
    int target;
    std::cin >> number_of_requests;
    for (int i = 0; i < number_of_requests; i++) {
      std::cin >> begin >> end >> target;
      (std::cout << (BinarySearch(array_ + begin, array_ + end, target) ? "YES"
                                                                        : "NO")
                 << "\n");
    }
  }

 private:
  static bool BinarySearch(const int* begin, const int* end, int target) {
    const int* lower = begin;
    const int* upper = end - 1;
    while (upper - lower > 1) {
      const int* middle = lower + ((upper - lower) / 2);
      if (*middle == target) {
        return true;
      }
      if (*middle < target) {
        lower = middle + 1;
      } else {
        upper = middle;
      }
    }
    return *lower == target || *upper == target;
  }

  int* array_;
};

int main() {
  auto solver = Solver();
  solver.ReadArray();
  solver.RequestProcessing();
}
