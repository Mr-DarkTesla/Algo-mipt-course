#include <complex>
#include <iostream>
#include <vector>

typedef std::complex<double> Complex;
typedef std::vector<Complex> CArray;


class FFTConverter {
 public:
  void FFT(CArray& a) { FFT(a, false); }

  void ifft(CArray& a) { FFT(a, true); }

 private:
  void FFT(CArray& a, bool invert) {
    int length = (int)a.size();
    if (length == 1) return;

    CArray a0(length / 2);
    CArray a1(length / 2);
    for (size_t i = 0, j = 0; i < length; i += 2, ++j) {
      a0[j] = a[i];
      a1[j] = a[i + 1];
    }
    FFT(a0, invert);
    FFT(a1, invert);

    double ang = 2 * kConstPI / length * (invert ? -1 : 1);
    Complex omega(1), wn(cos(ang), sin(ang));
    for (size_t i = 0; i < length / 2; ++i) {
      a[i] = a0[i] + omega * a1[i];
      a[i + length / 2] = a0[i] - omega * a1[i];
      if (invert) a[i] /= 2, a[i + length / 2] /= 2;
      omega *= wn;
    }
  }

 private:
  const double kConstPI = 3.141592653589793238460;
};


class Solver {
 public:
  void Input() { 
    ReadArray(array_a_, length_a_);
    ReadArray(array_b_, length_b_);
    FillArrays();
  }

  void Process() { 
    FFTConverter converter;
    converter.FFT(array_a_);
    converter.FFT(array_b_);
    MultArray();
    converter.ifft(array_c_);
    OutAns();
  }

  void Output() { 
    OutputArray(array_a_);
    OutputArray(array_b_);
  }

 private:
  void ReadArray(CArray& array, size_t& length) {
    length;
    std::cin >> length;
    length += 1;
    array.resize(length);
    for (size_t i = 0; i < length; ++i) {
      std::cin >> array[i];
    }
  }

  void FillArrays() { 
    length_c_ = (length_a_ + length_b_ - 1);
    int pow = 1;
    while (pow < 2 * std::max(length_a_, length_b_)) {
      pow = pow << 1;
    }

    for (int i = 0; i < pow - length_a_; ++i) {
      array_a_.push_back(0);
    }
    length_a_ = pow;
    for (int i = 0; i < pow - length_b_; ++i) {
      array_b_.push_back(0);
    }
    length_b_ = pow;
    array_c_.resize(pow, 0);
  }

  static void OutputArray(CArray& array) {
    std::cout << array.size() << " ";
    for (auto& el : array) {
      std::cout << el << " ";
    }
    std::cout << std::endl;
  }

  void OutAns() {
    std::cout << length_c_ - 1 << " ";
    for (size_t i = 0; i < length_c_; ++i) {
      int out = std::round(array_c_[i].real());
      std::cout << out << " ";
    }
  }

  void MultArray() {
    if (length_a_ != length_b_) {
      throw("Lenght error");
      return;
    }
    for (size_t i = 0; i < length_a_; ++i) {
      array_c_[i] = array_a_[i] * array_b_[i];
    }
  };


  CArray array_a_{};
  size_t length_a_{};
  CArray array_b_{};
  size_t length_b_{};
  CArray array_c_{};
  size_t length_c_{};
};

int main() { 
  Solver solver;
  solver.Input();
  solver.Process();
}