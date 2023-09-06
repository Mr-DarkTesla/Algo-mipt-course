#include <complex>
#include <iostream>
#include <vector>
#include <utility>
#include <cmath>

template <class T>
class Point {
 public:
  Point() : x(0), y(0) { }
  Point(T new_x, T new_y) {
    x = new_x;
    y = new_y;
  }

  T Length() {
    return std::sqrt(x * x + y * y);
  }

  void Out() {
    std::cout << x << " " << y << std::endl;
  }

  Point operator+(const Point& p) const { return Point(x + p.x, y + p.y); }
  Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); }
  T operator*(const Point& p) const { return x * p.x + y * p.y; }
  T operator%(const Point& p) const { return x * p.y - p.x * y; }
 private:
  T x;
  T y;
};

template <class T>
class Solver {
 public:
  void Input() {
    ReadVector(vector_a_);
    ReadVector(vector_b_);
  }

  void Process() { 
    std::cout << vector_a_.Length() << " " << vector_b_.Length()
              << std::endl;
    (vector_a_ + vector_b_).Out();
    std::cout << (vector_a_ * vector_b_) << " " << (vector_a_ % vector_b_) << std::endl;
    std::cout << std::abs((vector_a_ % vector_b_)) / 2 << std::endl;
  }

 private:
  void ReadVector(Point<T>& vector) {
    T sx, sy, ex, ey;
    std::cin >> sx >> sy >> ex >> ey;
    vector = Point<T>(ex - sx, ey - sy);
  }

  Point<T> vector_a_{};
  Point<T> vector_b_{};
};

int main() {
  auto solver = Solver<long double>{};
  solver.Input();
  solver.Process();
}