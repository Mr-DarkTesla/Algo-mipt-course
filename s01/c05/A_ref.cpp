#include <math.h>

#include <algorithm>
#include <iostream>
#include <vector>

namespace constants {
const int64_t kPi = 3.14159265358979323846;  // NOLINT
const int64_t kThreshold = 1e-6;             // NOLINT
}  // namespace constants

class Point {
 public:
  Point() = default;

  Point(int64_t x, int64_t y) : x(x), y(y) {}

  bool operator==(const Point& point) const {
    return abs(point.x - x) < constants::kThreshold &&
           abs(point.y - y) < constants::kThreshold;
  }

  bool operator!=(const Point& point) const {
    return !(abs(point.x - x) < constants::kThreshold ||
             abs(point.y - y) < constants::kThreshold);
  }

  Point operator+(const Point& point) const {
    return {x + point.x, y + point.y};
  }

  Point operator-(const Point& point) const {
    return {x - point.x, y - point.y};
  }

  int64_t operator*(const Point& point) const {
    return x * point.x + y * point.y;
  }

  Point operator*(const int64_t scale_factor) const {
    return {x * scale_factor, y * scale_factor};
  }

  Point operator/(const int64_t scale_factor) const {
    return {x / scale_factor, y / scale_factor};
  }

  int64_t len2() const { return x * x + y * y; }

  int64_t len() const { return sqrt(x * x + y * y); }

  Point rotate(const Point& rotation_center, int64_t alpha) const {
    Point ang(cos(alpha), sin(alpha));
    Point tmp = rotation_center - *this;
    int64_t tmp_len = tmp.len();

    if (tmp_len < constants::kThreshold) {
      return rotation_center;
    }
    tmp = tmp / tmp_len;
    return *this +
           Point(tmp.x * ang.x - tmp.y * ang.y, tmp.x * ang.y + tmp.y * ang.x) *
               tmp_len;
  }

  Point scale(const Point& homotetia_center, int64_t k) const {
    return homotetia_center + (*this - homotetia_center) * k;
  }

  int64_t crossProduction(const Point& point) {
    return x * point.y - y * point.x;
  }

  int64_t crossProduction3(const Point& point1, const Point& point2) {
    return x * (point1.y - point2.y) + point1.x * (point2.y - y) +
           point2.x * (y - point1.y);
  }

  static bool compareX(const Point& point1, const Point& point2) {
    if (abs(point1.x - point2.x) < constants::kThreshold) {
      return point1.y < point2.y;
    }
    return point1.x < point2.x;
  }

  static bool compareY(const Point& point1, const Point& point2) {
    if (abs(point1.y - point2.y) < constants::kThreshold) {
      return point1.x < point2.x;
    }
    return point1.y < point2.y;
  }

  static bool compareOnlyX(const Point& point1, const Point& point2) {
    return point1.x < point2.x;
  }

  Point normalize() { return *this = *this / len(); }

  int64_t x = 0;
  int64_t y = 0;
};

std::istream& operator>>(std::istream& is, Point& point) {
  is >> point.x >> point.y;
  return is;
}

std::ostream& operator<<(std::ostream& os, const Point& point) {
  os << point.x << ' ' << point.y;
  return os;
}

void BuildConvexHullGr(std::vector<Point>& points, std::vector<Point>& hull) {
  Point p0 = points[0];
  for (auto& point : points) {
    if (Point::compareX(point, p0)) {
      p0 = point;
    }
  }

  std::sort(points.begin(), points.end(),
            [&](const Point& point1, const Point& point2) {
              int64_t res = (point1 - p0).crossProduction(point2 - p0);
              if (res == 0) {
                return (point1 - p0).len2() < (point2 - p0).len2();
              }
              return res > 0;
            });

  for (size_t i = 0; i < points.size(); ++i) {
    while (hull.size() >= 2 &&
           (hull.back() - hull[hull.size() - 2])
                   .crossProduction(points[i] - hull.back()) < 0) {
      hull.pop_back();
    }
    hull.push_back(points[i]);
  }
} /* End of 'buildConvexHull' function */

// void BuildConvexHullDj(std::vector<Point>& points, std::vector<Point>& hull)
// {
//   Point p0 = points[0];
//   for (auto point : points) {
//     if (Point::compareX(point, p0)) {
//       p0 = point;
//     }
//   }
//   hull.push_back(p0);
//   while (true) {
//     Point t = p0;
//     for (auto p : points) {
//       if ((p - p0).c)
//     }
//   }
//
//   for (size_t i = 0; i < points.size(); ++i) {
//     while (hull.size() >= 2 &&
//         (hull.back() - hull[hull.size() - 2]).crossProduction(points[i] -
//         hull.back()) < constants::kThreshold) {
//       hull.pop_back();
//     }
//     hull.push_back(points[i]);
//   }
////  return hull;
//} /* End of 'buildConvexHull' function */

int main() {
  int number_polygon;
  std::cin >> number_polygon;
  std::vector<Point> points(number_polygon), hull;
  for (int i = 0; i < number_polygon; ++i) {
    std::cin >> points[i];
  }

  BuildConvexHullGr(points, hull);
  std::cout << hull.size() << '\n';
  for (auto& point : hull) {
    std::cout << point << '\n';
  }
}