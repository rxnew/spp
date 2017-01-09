#pragma once

namespace spp {
template <class RecPtrsT>
auto Spp3::solve(RecPtrsT&& rectangulars,
                 RecPtr const& container_back_surface)
  -> std::unordered_set<RecPtr> const& {
  sigma_ = std::forward<RecPtrsT>(rectangulars);
  container_back_surface_ = container_back_surface;
  container_front_surface_ = _make_ptr(*container_back_surface);
  container_front_surface_->z = INF;
  _solve();
  return placed_;
}

template <class RecPtrsT>
auto Spp3::solve(RecPtrsT&& rectangulars,
                 Rectangular const& container_back_surface)
  -> std::unordered_set<RecPtr> const& {
  return solve(rectangulars, _make_ptr(container_back_surface));
}

template <class RecPtrsT>
auto Spp3::solve(RecPtrsT&& rectangulars,
                 Rectangular&& container_back_surface)
  -> std::unordered_set<RecPtr> const& {
  return solve(rectangulars, _make_ptr(std::move(container_back_surface)));
}

template <class RecPtrsT>
auto Spp3::solve(RecPtrsT&& rectangulars,
                 Vector const& container_back_surface)
  -> std::unordered_set<RecPtr> const& {
  return solve(rectangulars, _make_ptr(container_back_surface, Vector()));
}

inline auto Spp3::_front_surface(RecPtr const& rectangular) const -> RecPtr {
  return _make_ptr(rectangular->front_surface());
}

inline auto Spp3::_back_surface(RecPtr const& rectangular) const -> RecPtr {
  return _make_ptr(rectangular->back_surface());
}

template <class... Args>
inline auto Spp3::_make_ptr(Args&&... args) const -> RecPtr {
  return std::make_shared<Rectangular>(std::forward<Args>(args)...);
}
}
