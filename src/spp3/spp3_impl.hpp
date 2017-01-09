#pragma once

namespace spp {
template <class RecPtrsT>
auto Spp3::solve(RecPtrsT&& rectangulars,
                 RecPtr const& base)
  -> std::unordered_set<RecPtr> const& {
  sigma_ = std::forward<RecPtrsT>(rectangulars);
  container_back_surface_ = base;
  auto size = base->get_size();
  auto position = base->get_position();
  position[2] = INF;
  container_front_surface_ = _make_ptr(size, position);
  _solve();
  return placed_;
}

template <class RecPtrsT>
auto Spp3::solve(RecPtrsT&& rectangulars,
                 Rectangular const& base)
  -> std::unordered_set<RecPtr> const& {
  return solve(rectangulars, _make_ptr(base));
}

template <class RecPtrsT>
auto Spp3::solve(RecPtrsT&& rectangulars,
                 Rectangular&& base)
  -> std::unordered_set<RecPtr> const& {
  return solve(rectangulars, _make_ptr(std::move(base)));
}

template <class RecPtrsT>
auto Spp3::solve(RecPtrsT&& rectangulars,
                 Vector const& base)
  -> std::unordered_set<RecPtr> const& {
  return solve(rectangulars, _make_ptr(base));
}

template <class... Args>
inline auto Spp3::_make_ptr(Args&&... args) -> RecPtr {
  return std::make_shared<Rectangular>(std::forward<Args>(args)...);
}
}
