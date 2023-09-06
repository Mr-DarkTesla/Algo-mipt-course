// have to find path for which minimal edge is maximal
// all_weights *= -1
// now: find path for which maximal edge is minimal
// distance is maximal edge
// it can only increase, and we have to find minimal
#include <iostream>
#include <queue>
#include <vector>

using dist = int;

int N, M, K;
std::vector<std::vector<dist>> adj;

void OutGraphs(std::vector<std::vector<dist>>& adj,
               std::vector<std::vector<std::pair<dist, int>>>& adj2) {
  for (auto row : adj2) {
    for (auto el : row) {
      std::cout << "(" << el.first << " " << el.second << ") ";
    }
    std::cout << "\n";
  }
}

int DFS(std::vector<std::vector<std::pair<dist, int>>>& adj2,
        std::vector<bool>& used, size_t vertex, size_t destination) {
  used[vertex] = true;
  for (auto nhb : adj2[vertex]) {  // short for neighbor
    std::cout << "(" << nhb.first << ' ' << nhb.second << ") ";
    size_t nindex = nhb.second;    // neighbor index
    dist nweight = nhb.first;      // neighbor weight
    if (!used[nindex]) {
      if (nindex == destination) { /*std::cout << "can reach " << destination <<
                                      " from " << vertex << "\n";*/
        //std::cout << "can reach " << destination << " from " << vertex << "\n";
        return nweight;
      }
      std::cout << "try reach " << destination+1 << " from " << nindex+1 << "\n";
      int result = DFS(adj2, used, nindex, destination);
      if (result < 0) {
        return std::max(nweight, result);
      }
    }
  }
  // std::cout << "can't reach " << destination+1 << " from " << vertex+1 <<
  // "\n";
  return 0;
}

int main() {
  std::cin >> N >> M >> K;
  adj = std::vector<std::vector<dist>>(N, std::vector<dist>(N, 0));
  for (int i = 0; i < M; ++i) {
    int f, s;
    dist w;
    std::cin >> f >> s >> w;
    --f;
    --s;
    adj[f][s] = std::min(adj[f][s], -w);
    adj[s][f] = adj[f][s];
  }
  for (int i = 0; i < N; ++i) {
    adj[i][i] = 0;
  }
  // MST
  // DFS
  std::vector<std::vector<std::pair<dist, int>>> adj2(
      N, std::vector<std::pair<dist, int>>());

  {  // scope for pending, used and used_counter
    int used_counter = 0;
    while (used_counter < N) {

      std::vector<bool> used(N, false);
      std::priority_queue<std::pair<dist, std::pair<int, int>>,
                          std::vector<std::pair<dist, std::pair<int, int>>>,
                          std::greater<std::pair<dist, std::pair<int, int>>>>
          pending;
      int bx = 0, by = 1;
      for (int x = 0; x < N; ++x) {
        for (int y = 0; y < N; ++y) {
          if (x != y && !used[x] && !used[y] && adj[x][y] < adj[bx][by])
            bx = x, by = y;
        }
      }
      if (used[bx]) {
        if (!used[by]) ++used_counter;
        used[by] = true;
        continue;
      }
      if (used[by]) {
        if (!used[bx]) ++used_counter;
        used[bx] = true;
        continue;
      }
      pending.push({adj[bx][by], {bx, by}});
      for (int u = 0; u < N; ++u) {
        if (u != bx && u != by) {
          if (adj[bx][u] < 0) {
            pending.push({adj[bx][u], {bx, u}});
          }
          if (adj[by][u] < 0) {
            pending.push({adj[by][u], {by, u}});
          }
        }
      }
      used[bx] = true;
      used[by] = true;
      used_counter += 2;
      adj2[bx].push_back({adj[bx][by], by});
      adj2[by].push_back({adj[by][bx], bx});
      std::cout << "init: pick " << bx+1 << "<->" << by+1 << "\n";
      while (!pending.empty()) {
        std::pair<dist, std::pair<int, int>> current = pending.top();
        pending.pop();
        if (used[current.second.second]) continue;
        used[current.second.second] = true;
        ++used_counter;
        for (int y = 0; y < N; ++y) {
          if (!used[y] && y != current.second.second) {
            pending.push(
                {adj[current.second.second][y], {current.second.second, y}});
          }
        }
        adj2[current.second.first].push_back(
            {adj[current.second.first][current.second.second],
             current.second.second});
        adj2[current.second.second].push_back(
            {adj[current.second.first][current.second.second],
             current.second.first});
        // std::cout << "pick " << current.second.first+1 << "<->" <<
        // current.second.second+1 << "\n";
      }
    }
  }  // scope for pending, used and used_counter

  for (int k = 0; k < K; ++k) {
    int f, s;
    std::cin >> f >> s;
    --f, --s;

    std::vector<bool> used(N, false);
    std::cout << -DFS(adj2, used, f, s) << "\n";
  }
}

