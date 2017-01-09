#pragma once

namespace std {
template <>
struct hash<spp::Rectangular> {
  auto operator()(spp::Rectangular const& obj) const noexcept -> size_t;
};
}

#include "hash/hash_impl.hpp"
