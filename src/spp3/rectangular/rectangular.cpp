#include "../rectangular.hpp"

namespace spp {
Rectangular::Rectangular(Rectangular const& other)
  : Super(other),
    x(this->position_[0]), y(this->position_[1]), z(this->position_[2]),
    w(this->size_[0]), h(this->size_[1]), d(this->size_[2]) {
}

Rectangular::Rectangular(Rectangular&& other)
  : Super(std::move(other)),
    x(this->position_[0]), y(this->position_[1]), z(this->position_[2]),
    w(this->size_[0]), h(this->size_[1]), d(this->size_[2]) {
}

auto Rectangular::operator=(Rectangular const& other) -> Rectangular& {
  Super::operator=(other);
  _set_references();
  return *this;
}

auto Rectangular::operator=(Rectangular&& other) -> Rectangular& {
  Super::operator=(std::move(other));
  _set_references();
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

auto Rectangular::_set_references() -> void {
  x = position_[0];
  y = position_[1];
  z = position_[2];
  w = size_[0];
  h = size_[1];
  d = size_[2];
}
}
