#include <math.h>

#include <algorithm>
#include <iostream>
#include <vector>

namespace constants {
const double kThreshold = 1e-9;
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

  double len() const { return sqrt(x * x + y * y); }

  double crossProduct(const Point& point) {
    return this->x * point.y - this->y * point.x;
  }

  Point normalize() { return *this = *this / len(); }

  double x = 0;
  double y = 0;
};

std::istream& operator>>(std::istream& is, Point& point) {
  is >> point.x >> point.y;
  return is;
}

std::ostream& operator<<(std::ostream& os, Point& point) {
  os << point.x << point.y;
  return os;
}

class Segment : std::pair<Point, Point> {
 public:
  using std::pair<Point, Point>::pair;
  bool IsPointOn(const Point& other) {
    if (std::min(first.x, second.x) <= other.x &&
        other.x <= std::max(first.x, second.x) &&
        std::min(first.y, second.y) <= other.y &&
        other.y <= std::max(first.y, second.y)) {
      if (std::fabs((other - first).crossProduct(second - first)) <
          constants::kThreshold) {
        return true;
      }
    }
    return false;
  }
};

class Polygon {
 public:
  enum PointPosition { In, Out, On };

  std::vector<Point> vertexes;

  Polygon() = default;

  Polygon(const std::vector<Point>& points) { vertexes = points; }

  bool isConvex() {
    char flag = 0;
    for (unsigned long i = 0; i < vertexes.size(); ++i) {
      Point p1 = vertexes[i];
      Point p2 = vertexes[(i + 1) % vertexes.size()];
      Point p3 = vertexes[(i + 2) % vertexes.size()];

      if (std::fabs((p2 - p1).crossProduct(p3 - p2)) < constants::kThreshold) {
        continue;
      }
      if ((p2 - p1).crossProduct(p3 - p2) < constants::kThreshold) {
        flag |= 1;
      } else {
        flag |= 2;
      }
      if (flag == 3) {
        return false;
      }
    }
    return flag != 3;
  }

  PointPosition containsPoint(const Point& point) {
    bool is_in = false;
    unsigned long j = vertexes.size() - 1;
    for (unsigned long i = 0; i < vertexes.size(); j = i++) {
      if (Segment({vertexes[j], vertexes[i]}).IsPointOn(point)) {
        return PointPosition::On;
      }
      if (((vertexes[i].y > point.y) != (vertexes[j].y > point.y)) &&
          (point.x < (vertexes[j].x - vertexes[i].x) *
                             (point.y - vertexes[i].y) /
                             (vertexes[j].y - vertexes[i].y) +
                         vertexes[i].x)) {
        is_in = !is_in;
      }
    }
    return is_in ? PointPosition::In : PointPosition::Out;
  }
};

int main() {
  int n;
  std::cin >> n;
  std::vector<Point> points(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> points[i];
  }

  Polygon p(points);

  if (p.isConvex()) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }
}
