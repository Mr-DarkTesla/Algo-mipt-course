#include <iostream>
#include <string>
#include <vector>

class Solver {
 public:
  void Input() {
    std::cin >> dict_size;
    std::cin >> str_1_;
  }

  void Request() {
    for (size_t i = 1; i < dict_size; ++i) {
      std::cin >> str_2_;
      Compress();
    }
    std::cout << str_1_;
  }

 private:
  void Compress() {
    size_t len1 = str_1_.length();
    size_t len2 = str_2_.length();
    if (len1 > len2) {
      str_3_ = str_2_ + "#" + str_1_.substr(len1 - len2, len2);
    } else {
      str_3_ = str_2_.substr(0, len1) + "#" + str_1_;
    }
    size_t len3 = str_3_.length();
    prefix_func_.resize(len3);
    PrefixFunction(str_3_);
    size_t intersection = prefix_func_[len3 - 1];
    for (size_t i = intersection; i < len2 - intersection; ++i) {
      str_1_ += str_2_[i];
    }
    //    str_1_ += str_2_.substr(intersection, len2 - intersection);
    //    std::cout << str_1_ << "\n";
  }

  void PrefixFunction(std::string &s) {
    prefix_func_[0] = 0;
    for (size_t i = 1; i < s.length(); i++) {
      size_t k = prefix_func_[i - 1];
      while (k > 0 && s[i] != s[k]) {
        k = prefix_func_[k - 1];
      }
      if (s[i] == s[k]) {
        k++;
      }
      prefix_func_[i] = k;
    }
  }

  std::string str_1_ = {};
  std::string str_2_ = {};
  std::string str_3_ = {};
  std::vector<size_t> prefix_func_ = {};
  size_t dict_size{};
};

int main() {
  auto solver = Solver();
  solver.Input();
  solver.Request();
}