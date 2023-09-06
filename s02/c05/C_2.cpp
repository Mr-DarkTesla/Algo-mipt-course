#include <iostream>
#include <set>
#include <map>
#include <string>
#include <vector>

class Bor {
 public:
   Bor() {
    nodes_.resize(1);
    nodes_[0].parent = nodes_[0].link = -1;
    size_ = 1;
  }

  void add_string(const std::string& str) {
    int64_t v = 0;
    for (size_t i = 0; i < str.length(); ++i) {
      char c = str[i] - 'a';
      if (nodes_[v].next.find(c) == nodes_[v].next.end()) {
        nodes_.push_back(vertex(v, c));
        nodes_[v].next[c] = size_++;
      }
      v = nodes_[v].next[c];
    }
    nodes_[v].terminal = true;
  }

  int64_t get_link(int64_t v) {
    if (nodes_[v].link == -1)
      if (v == 0 || nodes_[v].parent == 0)
        nodes_[v].link = 0;
      else
        nodes_[v].link =
            go(get_link(nodes_[v].parent), nodes_[v].parent_char + 'a');
    return nodes_[v].link;
  }

  int64_t go(int64_t v, char c) {
    c = c - 'a';
    if (nodes_[v].go.find(c) == nodes_[v].go.end())
      if (nodes_[v].next.find(c) != nodes_[v].next.end())
        nodes_[v].go[c] = nodes_[v].next[c];
      else
        nodes_[v].go[c] = v == 0 ? 0 : go(get_link(v), c + 'a');
    return nodes_[v].go[c];
  }

  bool is_terminal(int64_t v) { return nodes_[v].terminal; }

 private:
  struct vertex {
    std::map<char, int64_t> next{};
    bool terminal = false;
    int64_t parent{};
    char parent_char{};
    int64_t link{};
    std::map<char, int64_t> go{};

    vertex() = default;

    ~vertex() = default;

    vertex(size_t v, char c) {
      link = -1;
      parent = v;
      parent_char = c;
    }
  };

  std::vector<vertex> nodes_;
  size_t size_{};
  static const size_t kAlph_ = 28;
};

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
    for (size_t i = 0; i < str_1_.length(); ++i) {
      bor_.add_string((str_1_ + str_1_).substr(i, str_1_.length()));
    }

    int64_t state = 0;
    size_t ans = 0;
    for (size_t i = 0; i < str_2_.length(); ++i) {
      state = bor_.go(state, str_2_[i]);
      ans += bor_.is_terminal(state);
    }
    std::cout << ans;
  }

 private:

  std::string str_1_ = {};
  std::string str_2_ = {};

  Bor bor_{};
};

int main() {
  auto solver = Solver();
  solver.Input();
  solver.Request();
}