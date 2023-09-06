#include <complex>
#include <iostream>
#include <vector>
#include <cassert>

typedef std::vector<int> CArray;

class FFTConverter {
 public:
  FFTConverter() {
    int a = 2;
    while (Power(a, (kConstMod - 1) / 2) != kConstMod - 1) {
      a++;
    }
    for (int i = 1; (kConstMod - 1) % i == 0; i <<= 1) {
      root.push_back(Power(a, (kConstMod - 1) / i));
      invRoot.push_back(Power(root.back(), kConstMod - 2));
    }
  }

  void Plus(int& a, int b) { a = (a + b) % kConstMod; }

  int Times(int a, int b) { return (int64_t)a * b % kConstMod; }

  int Power(int x, int n) {
    int y = 1;
    while (n) {
      if (n & 1) {
        y = Times(y, x);
      }
      x = Times(x, x);
      n >>= 1;
    }
    return y;
  }

  void FFT(CArray& array, bool invert) {
    int n = array.size();

    int log = 0;
    while ((1 << log) < n) {
      log++;
    }

    for (int i = 0; i < n; i++) {
      int x = i;
      int y = 0;
      for (int j = 0; j < log; j++) {
        y = (y << 1) | (x & 1);
        x >>= 1;
      }
      if (y < i) {
        std::swap(array[y], array[i]);
      }
    }

    for (int e = 1; (1 << e) <= n; e++) {
      int length = (1 << e);
      size_t middle = length >> 1;
      int step = root[e];
      if (invert) {
        step = invRoot[e];
      }
      for (size_t i = 0; i < n; i += length) {
        int omega = 1;
        for (size_t j = 0; j < middle; j++) {
          int left = array[i + j];
          int right = Times(array[i + j + middle], omega);
          array[i + j] = left;
          Plus(array[i + j], right);
          array[i + j + middle] = left;
          Plus(array[i + j + middle], kConstMod - right);
          omega = Times(omega, step);
        }
      }
    }
    if (invert) {
      int inv = Power(n, kConstMod - 2);
      for (int i = 0; i < n; i++) {
        array[i] = Times(array[i], inv);
      }
    }
  }

  CArray Inverse(CArray array_a, int mod) {
    if (array_a[0] == 0) {
      return CArray();
    }
    int c = Power(array_a[0], kConstMod - 2);
    if (mod == 1) {
      return CArray(1, c);
    }

    int power2 = 1;
    while (power2 < mod) {
      power2 <<= 1;
    }

    array_a.resize(power2);
    for (int i = 0; i < power2; i++) {
      array_a[i] = Times(array_a[i], c);
    }

    CArray array_b(power2);
    array_b[0] = 0;
    for (int i = 1; i < power2; i++) {
      array_b[i] = kConstMod - array_a[i];
      if (array_b[i] == kConstMod) {
        array_b[i] = 0;
      }
    }

    CArray array_c(1, 1);
    int e = 1;
    while (e < power2) {
      array_b[0] = 1;
      array_c = Times(array_c, array_b);
      array_c.resize(power2);
      array_b[0] = 0;
      array_b = Times(array_b, array_b);
      array_b.resize(power2);
      e <<= 1;
    }

    for (int i = 0; i < power2; i++) {
      array_c[i] = Times(array_c[i], c);
    }
    array_c.resize(mod);
    return array_c;
  }

 private:
  CArray Times(CArray array_a, CArray array_b) {
    int n = 1;
    while (n < array_a.size() + array_b.size() - 1) {
      n <<= 1;
    }
    array_a.resize(n);
    array_b.resize(n);
    FFT(array_a, false);
    FFT(array_b, false);
    for (int i = 0; i < n; i++) {
      array_a[i] = Times(array_a[i], array_b[i]);
    }
    FFT(array_a, true);
    return array_a;
  }

  CArray root;
  CArray invRoot;
  const int kConstMod = 7340033;
};


class Solver {
 public:
  void Input() {
    std::cin >> pow_;
    ReadArray(array_);
    array_.resize(pow_);
  }

  void Process() { 
    FFTConverter FFT{};
    auto Q = FFT.Inverse(array_, pow_);
    OutAns(Q);
  }
 private:
  void ReadArray(CArray& array) {
    size_t length;
    std::cin >> length;
    array.resize(length + 1);
    for (auto& el : array) {
      std::cin >> el;
    }
  }

  void OutAns(CArray& array) {
    if (!array.size()) {
      std::cout << "The ears of a dead donkey\n";
    } else {
      for (int i = 0; i < pow_; i++) {
        std::cout << array[i];
        if (i + 1 < pow_) {
          std::cout << " ";
        }
      }
      std::cout << std::endl;
    }
  }
  
  int pow_{};
  CArray array_{};
};

int main() { 
  Solver solver;
  solver.Input();
  solver.Process();
}