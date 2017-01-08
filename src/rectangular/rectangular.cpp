#include "../rectangular.hpp"

namespace spp {
auto Rectangular::operator=(Rectangular const& other) -> Rectangular& {
  Super::operator=(other);
  x = position_[0];
  y = position_[1];
  z = position_[2];
  w = size_[0];
  h = size_[1];
  d = size_[2];
  return *this;
}

auto Rectangular::operator=(Rectangular&& other) -> Rectangular& {
  Super::operator=(std::move(other));
  x = position_[0];
  y = position_[1];
  z = position_[2];
  w = size_[0];
  h = size_[1];
  d = size_[2];
  return *this;
}

auto Rectangular::front_surface() const -> Rectangular {
  auto surface = *this;
  surface.size_[2] = 0;
  surface.position_[2] += size_[2];
  return surface;
}

auto Rectangular::back_surface() const -> Rectangular {
  auto surface = *this;
  surface.size_[2] = 0;
  return surface;
}
}
