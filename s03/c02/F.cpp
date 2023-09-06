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
    for (int l = 1; (kConstMod - 1) % l == 0; l <<= 1) {
      root.push_back(Power(a, (kConstMod - 1) / l));
      invRoot.push_back(Power(root.back(), kConstMod - 2));
    }
  }
  void FFT(CArray& a) { FFT(a, false); }

  void ifft(CArray& a) { FFT(a, true); }

 private:
  void FFT(CArray& array, bool invert) {
    int n = array.size();
    assert((kConstMod - 1) % n == 0);

    int ln = 0;
    while ((1 << ln) < n) {
      ln++;
    }
    assert((1 << ln) == n);

    for (int i = 0; i < n; i++) {
      int x = i;
      int y = 0;
      for (int j = 0; j < ln; j++) {
        y = (y << 1) | (x & 1);
        x >>= 1;
      }
      if (y < i) {
        std::swap(array[y], array[i]);
      }
    }

    for (int e = 1; (1 << e) <= n; e++) {
      size_t len = (1 << e);
      size_t half = len >> 1;
      int step = root[e];
      if (invert) {
        step = invRoot[e];
      }
      for (size_t i = 0; i < n; i += len) {
        int w = 1;
        for (size_t j = 0; j < half; j++) {
          int u = array[i + j];
          int v = times(array[i + j + half], w);
          array[i + j] = u;
          plus(array[i + j], v);
          array[i + j + half] = u;
          plus(array[i + j + half], kConstMod - v);
          w = times(w, step);
        }
      }
    }

    if (invert) {
      int in = Power(n, kConstMod - 2);
      for (int i = 0; i < n; i++) {
        array[i] = times(array[i], in);
      }
    }
  }

 private:
  int times(int a, int b) { return (long long)a * b % kConstMod; }

  int Power(int x, int n) {
    int y = 1;
    while (n) {
      if (n & 1) {
        y = times(y, x);
      }
      x = times(x, x);
      n >>= 1;
    }
    return y;
  }

  void square(CArray& P) {
    FFT(P, false);
    for (int i = 0; i < P.size(); i++) {
      P[i] = times(P[i], P[i]);
    }
    FFT(P, true);
  }

  CArray times(CArray P, CArray Q) {
    int n = 1;
    while (n < P.size() + Q.size() - 1) {
      n <<= 1;
    }
    P.resize(n);
    Q.resize(n);
    FFT(P, false);
    FFT(Q, false);
    for (int i = 0; i < n; i++) {
      P[i] = times(P[i], Q[i]);
    }
    FFT(P, true);
    return P;
  }

  void plus(int& a, int b) {
    a += b;
    if (a >= kConstMod) {
      a -= kConstMod;
    }
  }

  CArray plus(const CArray& P, const CArray& Q) {
    CArray R(std::max(P.size(), Q.size()));
    for (int i = 0; i < R.size(); i++) {
      if (i < P.size()) {
        plus(R[i], P[i]);
      }
      if (i < Q.size()) {
        plus(R[i], Q[i]);
      }
    }
    return R;
  }

  CArray Inverse(CArray P, int m) {
    if (P[0] == 0) {
      return CArray();
    }
    int c = Power(P[0], kConstMod - 2);
    if (m == 1) {
      return CArray(1, c);
    }
    int n = 1;
    while (n < m) {
      n <<= 1;
    }

    P.resize(n);
    for (int i = 0; i < n; i++) {
      P[i] = times(P[i], c);
    }

    CArray Q(n);
    Q[0] = 0;
    for (int i = 1; i < n; i++) {
      Q[i] = kConstMod - P[i];
      if (Q[i] == kConstMod) {
        Q[i] = 0;
      }
    }

    CArray R(1, 1);
    int e = 1;
    while (e < n) {
      assert(Q[0] == 0);
      Q[0] = 1;
      R = times(R, Q);
      R.resize(n);
      Q[0] = 0;
      Q = times(Q, Q);
      Q.resize(n);
      e <<= 1;
    }

    auto S = times(R, P);

    assert(S[0] == 1);
    for (int i = 1; i < n; i++) {
      assert(S[i] == 0);
    }

    for (int i = 0; i < n; i++) {
      R[i] = times(R[i], c);
    }
    R.resize(m);
    return R;
  }
  CArray root;
  CArray invRoot;
  const int kConstMod = 7340033;
};

class Solver {
 public:
  void Input() {
    std::cin >> pow_;
    ReadArray(array_a_, length_a_);

  }

  void Process() {
    FFTConverter converter;
    converter.FFT(array_a_);
    OutAns(array_b_);
  }

  void Output() {
    OutputArray(array_a_);
  }

 private:
  void ReadArray(CArray& array, size_t& length) {
    std::cin >> length;
    array.resize(length);
    for (size_t i = 0; i < length + 1; ++i) {
      std::cin >> array[i];
    }
  }

  static void OutputArray(CArray& array) {
    std::cout << array.size() << " ";
    for (auto& el : array) {
      std::cout << el << " ";
    }
    std::cout << std::endl;
  }

  void OutAns(CArray& array) {
    if (!array.size()) {
      std::cout << "The ears of a dead donkey\n";
    } else {
      for (size_t i = 0; i < pow_; i++) {
        std::cout << array[i];
        if (i + 1 < pow_) {
          std::cout << " ";
        }
      }
      std::cout << std::endl;
    }
  }

  int pow_{};
  CArray array_a_{};
  size_t length_a_{};

  CArray array_b_{};
  size_t length_b_{};
};

int main() {
  Solver solver;
  solver.Input();
  solver.Process();
}