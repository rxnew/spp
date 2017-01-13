#pragma once

#include "mathutils/vector.hpp"

namespace spp {
template <int dim, class Real, template <class...> class U>
auto make_convex_hull(U<mathutils::Hyperrectangle<dim, Real>> const&
                      hyperrectangles) -> mathutils::Hyperrectangle<dim, Real>;
template <int dim, class Real, template <class...> class U>
auto make_convex_hull(U<std::shared_ptr<mathutils::Hyperrectangle<dim, Real>>>
                      const& hyperrectangles)
  -> std::shared_ptr<mathutils::Hyperrectangle<dim, Real>>;
template <int dim, class Real, template <class...> class U>
auto calculate_filling_rate(U<mathutils::Hyperrectangle<dim, Real>> const&
                            hyperrectangles,
                            mathutils::Hyperrectangle<dim, Real> const&
                            base) -> long double;
template <int dim, class Real, template <class...> class U>
auto calculate_filling_rate(U<std::shared_ptr
                            <mathutils::Hyperrectangle<dim, Real>>> const&
                            hyperrectangles,
                            std::shared_ptr
                            <mathutils::Hyperrectangle<dim, Real>> const&
                            base) -> long double;
template <int dim, class Real>
auto to_object(std::shared_ptr<mathutils::Hyperrectangle<dim, Real>> const&
               hyperrectangle) -> mathutils::Hyperrectangle<dim, Real>;
template <int dim, class Real, template <class...> class U>
auto to_object(U<std::shared_ptr<mathutils::Hyperrectangle<dim, Real>>> const&
               hyperrectangles) -> U<mathutils::Hyperrectangle<dim, Real>>;
template <int dim, class Real>
auto to_pointer(mathutils::Hyperrectangle<dim, Real> const& hyperrectangle)
  -> std::shared_ptr<mathutils::Hyperrectangle<dim, Real>>;
template <int dim, class Real, template <class...> class U>
auto to_pointer(U<mathutils::Hyperrectangle<dim, Real>> const& hyperrectangles)
  -> U<std::shared_ptr<mathutils::Hyperrectangle<dim, Real>>>;
}

#include "util/util_impl.hpp"
