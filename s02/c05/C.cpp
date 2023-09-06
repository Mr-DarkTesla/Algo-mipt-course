#include <iostream>
#include <set>
#include <map>
#include <string>
#include <vector>

class Solver {
 public:
  void Input() {
    std::cin >> str_1_;
    std::cin >> str_2_;
  }

  void Request() {
    if (str_1_.length() > str_2_.length()) {
      std::cout << 0;
      return;
    }

    Prepare();

    size_t ans = 0;
    for (size_t i = 0; i <= str_2_.length() - str_1_.length(); ++i) {
      int64_t hash = 0;
      if (i == 0) {
        hash = hashes_[str_1_.length() - 1];
      } else {
        hash =
            abs_mod(abs_mod(hashes_[i + str_1_.length() - 1] - hashes_[i - 1]) *
                    inverts_[i]);
      }
      if (set_.find(hash) != set_.end() && check(hash, i)) {
        ans += 1;
      }
    }
    std::cout << ans;
  }

 private:
  void Prepare() {
    size_t len1 = str_1_.length();

    inverts_.resize(str_2_.length(), 1);
    powers_.resize(str_2_.length(), 1);
    for (size_t p = 1; p < str_2_.length(); ++p) {
      powers_[p] = abs_mod(kBase * powers_[p - 1]);
      inverts_[p] = invert(powers_[p]);
    }

    hashes_.resize(str_2_.length(), 0);
    hashes_[0] = str_2_[0] - 'a';
    for (size_t i = 1; i < str_2_.length(); ++i) {
      char x = str_2_[i] - 'a';
      hashes_[i] = abs_mod(hashes_[i - 1] + (powers_[i] * x));
    }

    int64_t hash = Hash(str_1_, 0, len1);
    set_.insert(hash);
    map_[hash] = str_1_;
    for (size_t i = 1; i < len1; ++i) {
      char x = str_1_[i - 1] - 'a';
      hash = abs_mod(abs_mod((hash - x) * inverts_[1]) + x * powers_[len1 - 1]);
      set_.insert(hash);
      map_[hash] = (str_1_ + str_1_).substr(i, len1);
    }
  }

  bool check(int64_t hash, size_t index) {
    //return map_[hash] == str_2_.substr(index, str_1_.length());
    for (size_t i = 0; i < str_1_.length(); ++i) {
      if (map_[hash][i] != str_2_[index + i]) {
        return false;
      }
    }
    return true;
  }

  int64_t Hash(std::string &s, size_t from, size_t to) {
    int64_t hash = 0;
    for (size_t i = from; i < to; i++) {
      char x = s[i] - 'a';
      hash = abs_mod(hash + x * powers_[i - from]);
    }
    return hash;
  }

  int64_t invert(int64_t element) {
    if (element < 1) {
      return -1;
    }

    int64_t uu1 = kMod;
    int64_t uu2 = 0;
    int64_t vv1 = element;
    int64_t vv2 = 1;

    while (vv1 != 0) {
      int64_t qqq = uu1 / vv1;
      int64_t tt1 = uu1 - qqq * vv1;
      int64_t tt2 = uu2 - qqq * vv2;
      uu1 = vv1;
      uu2 = vv2;
      vv1 = tt1;
      vv2 = tt2;
    }

    return uu1 == 1 ? (uu2 + kMod) % kMod : -1;
  }

  int64_t abs_mod(int64_t element) {
    int64_t mod = element % kMod;
    if (mod < 0) {
      return kMod + mod;
    }
    return mod;
  }

  const int64_t kBase = 31;
  const int64_t kMod = 1e9 + 7;

  std::string str_1_ = {};
  std::string str_2_ = {};
  std::string str_3_ = {};
  std::set<size_t> set_{};
  std::map<size_t, std::string> map_{};

  std::vector<int64_t> powers_ = {};
  std::vector<int64_t> inverts_ = {};

  std::vector<int64_t> hashes_ = {};

  std::vector<int64_t> prefix_func_ = {};
  size_t dict_size{};
};

int main() {
  auto solver = Solver();
  solver.Input();
  solver.Request();
}