#pragma once

#include <memory>

#include "mathutils/vector.hpp"

namespace spp {
template <int dim, class Real, template <class...> class U>
auto is_intersected(U<mathutils::Hyperrectangle<dim, Real>> const&
                    hyperrectangles) -> bool;
template <int dim, class Real, template <class...> class U>
auto is_intersected(U<std::shared_ptr<mathutils::Hyperrectangle<dim, Real>>>
                    const& hyperrectangles) -> bool;
template <int dim, class Real, template <class...> class U>
auto is_inside(U<mathutils::Hyperrectangle<dim, Real>> const& hyperrectangles,
               mathutils::Hyperrectangle<dim, Real> const& base) -> bool;
template <int dim, class Real, template <class...> class U>
auto is_inside(U<std::shared_ptr<mathutils::Hyperrectangle<dim, Real>>> const&
               hyperrectangles,
               std::shared_ptr<mathutils::Hyperrectangle<dim, Real>> const&
               base) -> bool;
template <int dim, class Real, template <class...> class U>
auto is_strip_packed(U<mathutils::Hyperrectangle<dim, Real>> const&
                     hyperrectangles,
                     mathutils::Hyperrectangle<dim, Real> const& base) -> bool;
template <int dim, class Real, template <class...> class U>
auto is_strip_packed(U<std::shared_ptr<mathutils::Hyperrectangle<dim, Real>>>
                     const& hyperrectangles,
                     std::shared_ptr<mathutils::Hyperrectangle<dim, Real>>
                     const& base) -> bool;
}

#include "debug/debug_impl.hpp"
