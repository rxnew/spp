#pragma once

namespace spp {
struct Point2 {
  int x;
  int y;

  Point2() : x(0), y(0) {}
  Point2(int x, int y) : x(x), y(y) {}
  Point2(Point2 const& other) : x(other.x), y(other.y) {}
  virtual ~Point2() = default;

  auto operator=(Point2 const& other) -> Point2& {
    x = other.x;
    y = other.y;
    return *this;
  }

  auto operator==(Point2 const& other) const -> bool {
    return x == other.x && y == other.y;
  }
  auto operator!=(Point2 const& other) const -> bool {
    return !(*this == other);
  }
  auto operator<(Point2 const& other) const -> bool {
    return y < other.y || (y == other.y && x < other.x);
  }
  auto operator>(Point2 const& other) const -> bool {
    return !(*this == other || *this < other);
  }
  auto print(std::ostream& os = std::cout) const -> void {
    os << "Point(" << x << ',' << y << ")" << std::endl;
  }
};

struct Point3 : Point2 {
  int z;

  Point3() : Point2(), z(0) {}
  Point3(int x, int y, int z) : Point2(x, y), z(z) {}
  Point3(Point3 const& other) : Point2(other), z(other.z) {}
  virtual ~Point3() noexcept = default;

  auto operator=(Point3 const& other) -> Point3& {
    Point2::operator=(other);
    z = other.z;
    return *this;
  }

  auto operator==(Point3 const& other) const -> bool {
    return Point2::operator==(other) && z == other.z;
  }
  auto operator!=(Point3 const& other) const -> bool {
    return !(*this == other);
  }
  auto operator<(Point3 const& other) const -> bool {
    return z < other.z || (z == other.z && Point2::operator<(other));
  }
  auto operator>(Point3 const& other) const -> bool {
    return !(*this == other || *this < other);
  }
  auto print(std::ostream& os = std::cout) const -> void {
    os << "Point(" << x << ',' << y << ',' << z << ")" << std::endl;
  }
};
}
