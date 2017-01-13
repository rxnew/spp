#pragma once

#include "../util.hpp"

namespace spp {
template <int dim, class Real, template <class...> class U>
auto is_intersected(U<std::shared_ptr<mathutils::Hyperrectangle<dim, Real>>>
                    const& hyperrectangles) -> bool {
  auto hyperrectangles_t = to_object(hyperrectangles);
  return mathutils::is_intersected(hyperrectangles_t);
}

template <int dim, class Real, template <class...> class U>
auto is_inside(U<std::shared_ptr<mathutils::Hyperrectangle<dim, Real>>> const&
               hyperrectangles,
               std::shared_ptr<mathutils::Hyperrectangle<dim, Real>> const&
               base) -> bool {
  auto axis = -1;
  for(auto i = 0; i < dim; ++i) {
    if(base->get_size()[i]) continue;
    axis = i;
    break;
  }
  assert(axis != -1);
  auto const& base_size = base->get_size();
  auto const& base_position = base->get_position();
  for(auto const& hyperrectangle : hyperrectangles) {
    auto const& size = hyperrectangle->get_size();
    auto const& position = hyperrectangle->get_position();
    for(auto i = 0; i < dim; ++i) {
      if(i == axis) continue;
      if(position[i] < base_position[i] ||
         position[i] + size[i] > base_position[i] + base_size[i]) return false;
    }
  }
  return true;
}

template <int dim, class Real, template <class...> class U>
auto is_strip_packed(U<std::shared_ptr<mathutils::Hyperrectangle<dim, Real>>>
                     const& hyperrectangles,
                     std::shared_ptr<mathutils::Hyperrectangle<dim, Real>>
                     const& base) -> bool {
  return !is_intersected(hyperrectangles) && is_inside(hyperrectangles, base);
}
}
