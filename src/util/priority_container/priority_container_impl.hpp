#pragma once

namespace spp {
template <class T, class Compare>
template <class... Args>
PriorityContainer<T, Compare>::PriorityContainer(Args&&... args)
  : Super(std::forward<Args>(args)...) {}

template <class T, class Compare>
auto PriorityContainer<T, Compare>::operator[](std::size_t n) const
  -> T const& {
  assert(n < size());
  auto pos = begin();
  std::advance(pos, n);
  return *pos;
}
}
