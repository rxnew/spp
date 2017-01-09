#pragma once

#include <set>

namespace spp {
template <class T, class Compare = std::less<T>>
class PriorityContainer : private std::set<T, Compare> {
 private:
  using Super = std::set<T, Compare>;

 public:
  using Super::key_type;
  using Super::value_type;
  using Super::reference;
  using Super::const_reference;
  using Super::size_type;

  template <class... Args>
  PriorityContainer(Args&&... args);

  ~PriorityContainer() = default;

  using Super::begin;
  using Super::end;
  using Super::cbegin;
  using Super::cend;
  using Super::empty;
  using Super::size;
  using Super::insert;
  using Super::erase;
  using Super::swap;
  using Super::clear;
  using Super::emplace;

  auto operator[](std::size_t n) const -> T const&;
};
}

#include "priority_container/priority_container_impl.hpp"
