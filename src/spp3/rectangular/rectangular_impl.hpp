#pragma once

namespace spp {
template <class... Args>
Rectangular::Rectangular(Args&&... args)
  : Super(std::forward<Args>(args)...) {
}
}
