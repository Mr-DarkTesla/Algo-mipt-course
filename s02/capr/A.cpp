#include <iostream>
#include <string>
#include <utility>

std::string str;

int main() {
  std::cin >> str;
  size_t index = 0;
  for (char chr : str) {
    bool flag = true;
    for (char chrx : str.substr(0, index)) {
      if (chr == chrx) {
        flag = false;
      }
    }
    if (flag) {
      std::cout << chr << " : " << index + 1 << "\n";
    }
    index++;
  }
}