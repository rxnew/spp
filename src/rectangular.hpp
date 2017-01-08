#pragma once

#include <iostream>

#include "mathutils/vector.hpp"

namespace spp {
class Rectangular : public mathutils::Polyhedron<3, int> {
 private:
  using Super = mathutils::Polyhedron<3, int>;

 public:
  template <class... Args>
  Rectangular(Args&&... args);

  auto operator<(Rectangular const& other) const -> bool;
  auto operator>(Rectangular const& other) const -> bool;

  auto front_surface() const -> Rectangular;
  auto back_surface() const -> Rectangular;

  int& x;
  int& y;
  int& z;
  int& w;
  int& h;
  int& d;
};
}

/*
struct Rectangular : Point3, Size3 {
  Rectangular() : Point3(), Size3() {}
  Rectangular(int x, int y, int z, int w, int h, int d)
    : Point3(x, y, z), Size3(w, h, d) {}
  Rectangular(Point3 const& point, int w, int h, int d)
    : Point3(point), Size3(w, h, d) {}
  Rectangular(int x, int y, int z, Size3 const& size)
    : Point3(x, y, z), Size3(size) {}
  Rectangular(Point3 const& point, Size3 const& size)
    : Point3(point), Size3(size) {}
  Rectangular(Size3 const& size) : Point3(), Size3(size) {}
  Rectangular(Rectangular const& other)
    : Point3(other), Size3(other) {}
  virtual ~Rectangular() = default;

  auto operator=(Rectangular const& other) -> Rectangular& {
    Point3::operator=(other);
    Size3::operator=(other);
    return *this;
  }
  auto operator==(Rectangular const& other) const -> bool {
    return Point3::operator==(other) && Size3::operator==(other);
  }
  auto operator!=(Rectangular const& other) const -> bool {
    return !(*this == other);
  }
  auto operator<(Rectangular const& other) const -> bool {
    return Point3::operator<(other);
  }
  auto operator>(Rectangular const& other) const -> bool {
    return Point3::operator>(other);
  }

  auto get_point() const -> Point3 {
    return Point3(x, y, z);
  }
  auto get_antigoglin_point() const -> Point3 {
    return Point3(x + w, y + h, z + d);
  }
  auto set_point(Point3 const& point) -> Rectangular {
    Point3::operator=(point);
    return *this;
  }
  auto front_surface() const -> Rectangular {
    return Rectangular(x, y, z + d, w, h, 0);
  }
  auto back_surface() const -> Rectangular {
    return Rectangular(x, y, z, w, h, 0);
  }
  auto to_rectangle() const -> Rectangle {
    return Rectangle(x, y, w, h);
  }
  auto is_intersected(Point3 const& point) const -> bool {
    return is_intersected(Rectangular(point, 0, 0, 0));
  }
  auto is_intersected(Rectangular const& other) const -> bool {
    return
      x < other.x + other.w &&
      y < other.y + other.h &&
      z < other.z + other.d &&
      x + w > other.x &&
      y + h > other.y &&
      z + d > other.z;
  }
  auto print(std::ostream& os = std::cout) const -> void {
    os << "Point(" << x << ',' << y << ',' << z << "), "
       << "Size("  << w << ',' << h << ',' << d << ")" << std::endl;
  }
};
}
*/

namespace std {
template <>
struct hash<spp::Rectangular> {
  auto operator()(spp::Rectangular const& obj) const noexcept -> size_t;
};
}
