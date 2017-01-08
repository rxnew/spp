#include "../rectangular.hpp"

namespace spp {
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
