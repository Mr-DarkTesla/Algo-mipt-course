#include <algorithm>
#include <iostream>

const size_t kMaxRoads = 501;
const size_t kMaxSize = 1e9 + 7;
size_t max_size[kMaxRoads][kMaxRoads];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0), std::cout.tie(0);

  size_t roads;
  std::cin >> roads;
  for (size_t i = 0; i < roads; i++) {
    for (size_t j = 0; j < roads; j++) {
      std::cin >> max_size[i][j];
      if (max_size[i][j] == -1 || i == j) {
        max_size[i][j] = kMaxSize;
      }
    }
  }

  for (size_t k = 0; k < roads; k++) {
    for (size_t i = 0; i < roads; i++) {
      for (size_t j = 0; j < roads; j++) {
        max_size[i][j] = std::max(max_size[i][j],
          std::min(max_size[i][k], max_size[k][j]));
      }
    }
  }

  for (size_t i = 0; i < roads; i++) {
    for (size_t j = 0; j < roads; j++) {
      std::cout << max_size[i][j] << " ";
    }
    std::cout << "\n";
  }
}
