#pragma once

namespace spp {
template <class... Args>
Rectangular::Rectangular(Args&&... args)
  : Super(std::forward<Args>(args)...),
    x(this->position_[0]), y(this->position_[1]), z(this->position_[2]),
    w(this->size_[0]), h(this->size_[1]), d(this->size_[2]) {
}

inline auto Rectangular::operator<(Rectangular const& other) const -> bool {
  return position_ < other.position_;
}

inline auto Rectangular::operator>(Rectangular const& other) const -> bool {
  return position_ > other.position_;
}
}

namespace std {
inline auto hash<spp::Rectangular>::
operator()(spp::Rectangular const& obj) const noexcept -> size_t {
  return hash<mathutils::Polyhedron<3, int>>()(obj);
}
}
