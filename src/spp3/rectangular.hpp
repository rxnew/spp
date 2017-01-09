#pragma once

#include <iostream>

#include "mathutils/vector.hpp"

namespace spp {
class Rectangular : public mathutils::Hyperrectangle<3, int> {
 private:
  using Super = mathutils::Hyperrectangle<3, int>;

 public:
  using Dimension = std::integral_constant<int, 3>;
  using Real = int;
  using Vector = typename Super::Vector;

  template <class... Args>
  Rectangular(Args&&... args);
  Rectangular(Rectangular const& other);
  Rectangular(Rectangular&& other);

  auto operator=(Rectangular const& other) -> Rectangular&;
  auto operator=(Rectangular&& other) -> Rectangular&;
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

 private:
  auto _set_references() -> void;
};
}

#include "rectangular/rectangular_impl.hpp"
#include "rectangular/hash.hpp"
