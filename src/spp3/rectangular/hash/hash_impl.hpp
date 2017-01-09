#pragma once

namespace std {
inline auto hash<spp::Rectangular>::
operator()(spp::Rectangular const& obj) const noexcept -> size_t {
  return hash<mathutils::Hyperrectangle<3, int>>()(obj);
}
}
