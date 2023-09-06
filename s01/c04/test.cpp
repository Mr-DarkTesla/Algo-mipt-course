#include <climits>
#include <cmath>
#include <iostream>
#include <vector>

const int64_t kInf = 1 << 63;
const int64_t kHeightOfTable = 26;

long long CountLog(int64_t size_of_array) {
  return floor(log(size_of_array) / log(2));
}

struct StatisticsIndexes {
  long long first;
  long long second;
};

void RemoveMinusOnes(std::vector<long long>& array) {
  if (array.size() > 0 && array.front() == -1) {
    array.erase(array.begin());
  }
  if (array.size() > 0 && array.back() == -1) {
    array.erase(array.begin() + array.size() - 1);
  }
}

void RemoveSameElements(std::vector<long long>& vec_element_1,
                        std::vector<long long>& vec_element_2) {
  int64_t iterator_1 = 0;
  while (iterator_1 < vec_element_1.size()) {
    if (vec_element_1[iterator_1] == vec_element_2.front()) {
      vec_element_2.erase(vec_element_2.begin());
    }
    if (vec_element_1[iterator_1] == vec_element_2.back()) {
      vec_element_2.erase(vec_element_2.begin() + 1);
    }
    ++iterator_1;
  }
}

StatisticsIndexes NewElement(StatisticsIndexes& element_1,
                             StatisticsIndexes& element_2,
                             std::vector<long long>& array) {
  std::vector<long long> vec_element_1{element_1.first, element_1.second};
  std::vector<long long> vec_element_2{element_2.first, element_2.second};
  RemoveSameElements(vec_element_1, vec_element_2);
  RemoveMinusOnes(vec_element_1);
  RemoveMinusOnes(vec_element_2);
  std::vector<long long> new_element;
  int64_t iterator_1 = 0;
  int64_t iterator_2 = 0;
  while (iterator_1 < vec_element_1.size() &&
         iterator_2 < vec_element_2.size()) {
    if (array[vec_element_1[iterator_1]] > array[vec_element_2[iterator_2]]) {
      new_element.push_back(vec_element_2[iterator_2]);
      ++iterator_2;
    } else {
      new_element.push_back(vec_element_1[iterator_1]);
      ++iterator_1;
    }
  }
  while (iterator_1 < vec_element_1.size()) {
    new_element.push_back(vec_element_1[iterator_1]);
    ++iterator_1;
  }
  while (iterator_2 < vec_element_2.size()) {
    new_element.push_back(vec_element_2[iterator_2]);
    ++iterator_2;
  }
  return {new_element[0], new_element[1]};
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int64_t size_of_array;
  int64_t amount_of_queries;
  std::cin >> size_of_array >> amount_of_queries;
  std::vector<std::vector<StatisticsIndexes>> sparse_table(
      size_of_array, std::vector<StatisticsIndexes>(kHeightOfTable));
  std::vector<long long> array(size_of_array);
  for (int64_t iterator = 0; iterator < size_of_array; ++iterator) {
    std::cin >> array[iterator];
  }
  for (int64_t iterator = 0; iterator < size_of_array; ++iterator) {
    sparse_table[iterator][0].first = iterator;
    sparse_table[iterator][0].second = -1;
  }
  for (int64_t iterator_1 = 1; iterator_1 <= kHeightOfTable; ++iterator_1) {
    for (int64_t iterator_2 = 0;
         iterator_2 + (1 << iterator_1) <= size_of_array; ++iterator_2) {
      sparse_table[iterator_2][iterator_1] = NewElement(
          sparse_table[iterator_2][iterator_1 - 1],
          sparse_table[iterator_2 + (1 << (iterator_1 - 1))][iterator_1 - 1],
          array);
    }
  }
  for (int64_t iterator = 0; iterator < amount_of_queries; ++iterator) {
    int64_t left;
    int64_t right;
    std::cin >> left >> right;
    long long temp = CountLog(right - left + 1);
    std::cout
        << array[NewElement(sparse_table[left - 1][temp],
                            sparse_table[right - (1 << temp)][temp], array)
                     .second]
        << '\n';
  }
}