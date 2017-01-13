#pragma once

namespace spp {
template <int dim, class Real, template <class...> class U>
auto make_convex_hull(U<mathutils::Hyperrectangle<dim, Real>> const&
                      hyperrectangles) -> mathutils::Hyperrectangle<dim, Real> {
  static auto const INF = std::numeric_limits<Real>::max();

  auto min_position = mathutils::Vector<dim, Real>(INF, INF, INF);
  auto max_position = mathutils::Vector<dim, Real>(0, 0, 0);
  for(auto const& hyperrectangle : hyperrectangles) {
    auto const& position = hyperrectangle.get_position();
    auto const& antigoglin_position = hyperrectangle.antigoglin_position();
    for(auto i = 0; i < dim; ++i) {
      min_position[i] = std::min(min_position[i], position[i]);
      max_position[i] = std::max(max_position[i], antigoglin_position[i]);
    }
  }
  auto size = max_position - min_position;
  return mathutils::Hyperrectangle<dim, Real>(size, min_position);
}

template <int dim, class Real, template <class...> class U>
auto make_convex_hull(U<std::shared_ptr<mathutils::Hyperrectangle<dim, Real>>>
                      const& hyperrectangles)
  -> std::shared_ptr<mathutils::Hyperrectangle<dim, Real>> {
  auto hyperrectangles_t = to_object(hyperrectangles);
  return to_pointer(make_convex_hull(hyperrectangles_t));
}

template <int dim, class Real, template <class...> class U>
auto calculate_filling_rate(U<mathutils::Hyperrectangle<dim, Real>> const&
                            hyperrectangles,
                            mathutils::Hyperrectangle<dim, Real> const&
                            base) -> long double {
  auto const convex_hull = make_convex_hull(hyperrectangles);
  auto axis = -1;
  for(auto i = 0; i < dim; ++i) {
    if(base.get_size()[i] == 0) axis = i;
  }
  assert(axis != -1);
  auto sum_of_volume = 0.0l;
  for(auto const& hyperrectangle : hyperrectangles) {
    sum_of_volume += static_cast<long double>(hyperrectangle.volume());
  }
  return sum_of_volume / convex_hull.volume();
}

template <int dim, class Real, template <class...> class U>
auto calculate_filling_rate(U<std::shared_ptr
                            <mathutils::Hyperrectangle<dim, Real>>> const&
                            hyperrectangles,
                            std::shared_ptr
                            <mathutils::Hyperrectangle<dim, Real>> const&
                            base) -> long double {
  auto hyperrectangles_t = to_object(hyperrectangles);
  auto base_t = to_object(base);
  return calculate_filling_rate(hyperrectangles_t, base_t);
}

template <int dim, class Real>
auto to_object(std::shared_ptr<mathutils::Hyperrectangle<dim, Real>> const&
               hyperrectangle) -> mathutils::Hyperrectangle<dim, Real> {
  return *hyperrectangle;
}

template <int dim, class Real, template <class...> class U>
auto to_object(U<std::shared_ptr<mathutils::Hyperrectangle<dim, Real>>> const&
               hyperrectangles) -> U<mathutils::Hyperrectangle<dim, Real>> {
  auto hyperrectangles_t = U<mathutils::Hyperrectangle<dim, Real>>();
  for(auto const& e : hyperrectangles) {
    hyperrectangles_t.push_back(*e);
  }
  return hyperrectangles_t;
}

template <int dim, class Real>
auto to_pointer(mathutils::Hyperrectangle<dim, Real> const& hyperrectangle)
  -> std::shared_ptr<mathutils::Hyperrectangle<dim, Real>> {
  return std::make_shared<mathutils::Hyperrectangle<dim, Real>>(hyperrectangle);
}

template <int dim, class Real, template <class...> class U>
auto to_pointer(U<mathutils::Hyperrectangle<dim, Real>> const& hyperrectangles)
  -> U<std::shared_ptr<mathutils::Hyperrectangle<dim, Real>>> {
  using Hyperrectangle = mathutils::Hyperrectangle<dim, Real>();

  auto hyperrectangles_t = U<std::shared_ptr<Hyperrectangle>>();
  for(auto const& e : hyperrectangles) {
    hyperrectangles_t.push_back(std::make_shared<Hyperrectangle>(e));
  }
  return hyperrectangles_t;
}
}
