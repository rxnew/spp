#include "../rectangular.hpp"

namespace spp {
Rectangular::Rectangular(Rectangular const& other)
  : Super(other) {
}

Rectangular::Rectangular(Rectangular&& other)
  : Super(std::move(other)) {
}

auto Rectangular::operator=(Rectangular const& other) -> Rectangular& {
  Super::operator=(other);
  return *this;
}

auto Rectangular::operator=(Rectangular&& other) -> Rectangular& {
  Super::operator=(std::move(other));
  return *this;
}
}
