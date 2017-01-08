#pragma once

#include "point.hpp"
#include "size.hpp"

namespace spp {
struct Rectangle : Point2, Size2 {
  Rectangle() : Point2(), Size2() {}
  Rectangle(int x, int y, int w, int h)
    : Point2(x, y), Size2(w, h) {}
  Rectangle(Point2 const& point, int w, int h)
    : Point2(point), Size2(w, h) {}
  Rectangle(int x, int y, Size2 const& size)
    : Point2(x, y), Size2(size) {}
  Rectangle(Point2 const& point, Size2 const& size)
    : Point2(point), Size2(size) {}
  Rectangle(Rectangle const& other)
    : Point2(other), Size2(other) {}
  virtual ~Rectangle() = default;

  auto operator=(Rectangle const& other) -> Rectangle& {
    Point2::operator=(other);
    Size2::operator=(other);
    return *this;
  }
  auto operator==(Rectangle const& other) const -> bool {
    return Point2::operator==(other) && Size2::operator==(other);
  }
  auto operator!=(Rectangle const& other) const -> bool {
    return !(*this == other);
  }

  auto get_point() const -> Point2 {
    return Point2(x, y);
  }
  auto get_antigoglin_point() const -> Point2 {
    return Point2(x + w, y + h);
  }
  auto set_point(Point2 const& point) -> Rectangle {
    Point2::operator=(point);
    return *this;
  }
  auto is_intersected(Point2 const& point) const -> bool {
    return is_intersected(Rectangle(point, 0, 0));
  }
  auto is_intersected(Rectangle const& other) const -> bool {
    return
      x < other.x + other.w &&
      y < other.y + other.h &&
      x + w > other.x &&
      y + h > other.y;
  }
  auto print(std::ostream& os = std::cout) const -> void {
    os << "Point(" << x << ',' << y << "), "
       << "Size("  << w << ',' << h << ")" << std::endl;
  }
};
}
