#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

int *mas, *c, **dp;
std::vector<int> res;

void Recover(int i, int j) {
  if (dp[i][j] == 0) {
    return;
  }
  if (dp[i - 1][j] == dp[i][j]) {
    Recover(i - 1, j);
  } else {
    Recover(i - 1, j - mas[i]);
    res.push_back(i);
  }
}

int main(void) {
  int n, m;

  std::cin >> n >> m;
  ++n, ++m;
  mas = new int[n];
  for (int i = 1; i < n; ++i) {
    std::cin >> mas[i];
  }
  c = new int[n];
  for (int i = 1; i < n; ++i) {
    std::cin >> c[i];
  }

  dp = new int*[n];
  for (int i = 0; i < n; i++) {
    dp[i] = new int[m];
    memset(dp[i], 0, sizeof(int) * m);
  }

  for (int i = 1; i < n; ++i) {
    for (int j = 1; j < m; ++j) {
      if (j >= mas[i]) {
        dp[i][j] = std::max(dp[i - 1][j], dp[i - 1][j - mas[i]] + c[i]);
      } else {
        dp[i][j] = dp[i - 1][j];
      }
    }
  }

  Recover(n - 1, m - 1);
  for (size_t i = 0; i < res.size(); ++i) {
    std::cout << res[i] << " ";
  }
}
