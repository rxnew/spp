#pragma once

namespace spp {
struct Size2 {
  int w;
  int h;

  Size2() : w(0), h(0) {}
  Size2(int w, int h) : w(w), h(h) {}
  Size2(Size2 const& other) : w(other.w), h(other.h) {}
  virtual ~Size2() noexcept = default;

  auto operator=(Size2 const& other) -> Size2& {
    w = other.w;
    h = other.h;
    return *this;
  }
  auto operator==(Size2 const& other) const -> bool {
    return w == other.w && h == other.h;
  }
  auto operator!=(Size2 const& other) const -> bool {
    return !(*this == other);
  }
};

struct Size3 : Size2 {
  int d;

  Size3() : Size2(), d(0) {}
  Size3(int w, int h, int d) : Size2(w, h), d(d) {}
  Size3(Size3 const& other) : Size2(other), d(other.d) {}
  virtual ~Size3() noexcept = default;

  auto operator=(Size3 const& other) -> Size3& {
    Size2::operator=(other);
    d = other.d;
    return *this;
  }
  auto operator==(Size3 const& other) const -> bool {
    return Size2::operator==(other) && d == other.d;
  }
  auto operator!=(Size3 const& other) const -> bool {
    return !(*this == other);
  }
};
}
