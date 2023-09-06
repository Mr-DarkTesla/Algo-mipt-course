#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

class Bor {
 public:
  Bor() {
    nodes_.resize(1);
    nodes_[0].parent = nodes_[0].link = -1;
    size_ = 1;
  }

  void add_string(const std::string& str, size_t terminal) {
    int64_t v = 0;
    for (size_t i = 0; i < str.length(); ++i) {
      char c = str[i] - 'a';
      if (nodes_[v].next.find(c) == nodes_[v].next.end()) {
        nodes_.push_back(vertex(v, c));
        nodes_[v].next[c] = size_++;
      }
      v = nodes_[v].next[c];
    }
    nodes_[v].terminal.push_back(terminal);
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

  int64_t get_shortlink(int64_t v) {
    if (nodes_[v].short_link == -1)
      if (v == 0) {
        nodes_[v].short_link = 0;
      } else if (nodes_[get_link(v)].terminal.size() > 0)
        nodes_[v].short_link = nodes_[v].link;
      else
        nodes_[v].short_link = get_shortlink(get_link(v));
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

  std::vector<int64_t> is_terminal(int64_t v) { return nodes_[v].terminal; }

 private:
  struct vertex {
    std::map<char, int64_t> next{};
    std::vector<int64_t> terminal{};
    int64_t parent{};
    char parent_char{};
    int64_t link{};
    int64_t short_link{};
    std::map<char, int64_t> go{};

    vertex() = default;

    ~vertex() = default;

    vertex(size_t v, char c) {
      link = -1;
      short_link = -1;
      parent = v;
      parent_char = c;
    }
  };

  std::vector<vertex> nodes_;
  size_t size_{};
  static const size_t kAlph_ = 38;
};

class Solver {
 public:
  void Input() {
    std::cin >> text_;
    std::cin >> num_;
    for (size_t i = 0; i < num_; ++i) {
      std::cin >> str_1_;
      bor_.add_string(str_1_, i);
      strings_.push_back(str_1_);
    }
  }

  void Request() {
    int64_t state = 0;
    std::vector<std::vector<int64_t>> ans(num_);
    for (size_t i = 0; i < text_.length(); ++i) {
      state = bor_.go(state, text_[i]);
      int64_t link = state;
      while (link > 0) {
        std::vector<int64_t> terminal = bor_.is_terminal(link);
        for (auto index : terminal)
          ans[index].push_back(i + 1 - strings_[index].length());
        link = bor_.get_shortlink(link);  
      }
    }
    for (auto row : ans) {
      std::cout << row.size() << " ";
      for (auto el : row){
        std::cout << el + 1 << " ";
      }
      std::cout << "\n";
    }
  }

 private:
  size_t num_;
  std::string text_ = {};
  std::string str_1_ = {};
  std::vector<std::string> strings_ = {};

  Bor bor_{};
};

int main() {
  auto solver = Solver();
  solver.Input();
  solver.Request();
}