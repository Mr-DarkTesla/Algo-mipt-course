#include <math.h>

#include <algorithm>
#include <iostream>
#include <vector>

namespace constants {
  const int64_t kThreshold = 1e-6;
}

class Point {
 public:
  Point() = default;

  Point(double x, double y) : x(x), y(y) {}

  bool operator==(const Point& point) const {
    return abs(point.x - x) < constants::kThreshold &&
           abs(point.x - y) < constants::kThreshold;
  }

  bool operator!=(const Point& point) const {
    return !(abs(point.x - x) < constants::kThreshold &&
             abs(point.x - y) < constants::kThreshold);
  }

  Point operator+(const Point& point) const {
    return {x + point.x, y + point.y};
  }

  Point operator-(const Point& point) const {
    return {x - point.x, y - point.y};
  }

  double operator*(const Point& point) const {
    return x * point.x + y * point.y;
  }

  Point operator*(const double alpha) const { return {x * alpha, y * alpha}; }

  Point operator/(const double alpha) const { return {x / alpha, y / alpha}; }

  double len() const { return x * x + y * y; }

  double crossProduct(const Point& point) {
    return this->x * point.y - this->y * point.x;
  }

  static bool compareX(const Point& point1, const Point& point2) {
    if (abs(point1.x - point2.x) < constants::kThreshold) {
      return point1.y < point2.y;
    }
    return point1.x < point2.x;
  }

  double x = 0;
  double y = 0;
};

std::istream& operator>>(std::istream& is, Point& point) {
  is >> point.x >> point.y;
  return is;
}

std::ostream& operator<<(std::ostream& os, const Point& point) {
  os << point.x << ' ' << point.y;
  return os;
}

void ConvexHull(std::vector<Point>& points, std::vector<Point>& hull) {
  Point p0 = points[0];
  for (auto& point : points) {
    if (Point::compareX(point, p0)) {
      p0 = point;
    }
  }

  auto comp = [&](const Point& point1, const Point& point2) {
    int64_t res = (point1 - p0).crossProduct(point2 - p0);
    if (res == 0) {
      return (point1 - p0).len() < (point2 - p0).len();
    }
    return res > 0;
  };

  std::sort(points.begin(), points.end(), comp);

  for (size_t i = 0; i < points.size(); ++i) {
    while (hull.size() >= 2 &&
           (hull.back() - hull[hull.size() - 2])
                   .crossProduct(points[i] - hull.back()) < 0) {
      hull.pop_back();
    }
    hull.push_back(points[i]);
  }
}

class Solver {
 public:
  Solver() = default;
  ~Solver() = default;

  void Input() {
    std::cin >> length_;
    points.resize(length_);
    for (int i = 0; i < length_; ++i) {
      std::cin >> points[i];
    }
  }

  void Process() {
    ConvexHull(points, hull);
    std::cout << hull.size() << std::endl;
    for (auto& point : hull) {
      std::cout << point << std::endl;
    }
  }

 private:
  int length_{};
  Point pockeymon{};
  std::vector<Point> points{};
  std::vector<Point> hull{};
};

int main() {
  Solver solver;
  solver.Input();
  solver.Process();
}