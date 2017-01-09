#pragma once

#include <memory>

#include "mathutils/vector.hpp"

namespace spp {
namespace io {
// prototype declarations
template <class T, std::enable_if_t<std::is_convertible<T, json11::Json>::value,
                                    std::nullptr_t> = nullptr>
auto _to_json(T const& t) -> json11::Json;
template <int dim, class Real, class T =
          std::conditional_t<std::is_integral<Real>::value, int, double>>
auto _to_json(mathutils::Vector<dim, Real> const& vector) -> json11::Json;
template <int dim, class Real>
auto _to_json(mathutils::Hyperrectangle<dim, Real> const& hyperrectangle)
  -> json11::Json;
template <class T>
auto _to_json(std::shared_ptr<T> const& ptr) -> json11::Json;
template <class T, template <class...> class U>
auto _to_json(U<T> const& array) -> json11::Json;
template <class T, template <class...> class U>
auto _to_json(std::string const& key, U<T> const& array)
  -> json11::Json;

// implementations
template <class T, template <class...> class U>
auto output(std::string const& key, U<T> const& array,
            std::ostream& os) -> void {
  auto json_obj = to_json(key, array);
  os << json_obj.dump() << std::endl;
}

template <class... Args>
auto to_json(Args&&... args) -> json11::Json {
  return _to_json(std::forward<Args>(args)...);
}

template <class T, std::enable_if_t<std::is_convertible<T, json11::Json>::value,
                                    std::nullptr_t>>
auto _to_json(T const& t) -> json11::Json {
  return t;
}

template <int dim, class Real, class T>
auto _to_json(mathutils::Vector<dim, Real> const& vector) -> json11::Json {
  auto json_array = json11::Json::array();
  for(auto const& e : vector) {
    json_array.push_back(static_cast<T>(e));
  }
  return json_array;
}

template <int dim, class Real>
auto _to_json(mathutils::Hyperrectangle<dim, Real> const& hyperrectangle)
  -> json11::Json {
  return json11::Json::object{
    {"size"    , _to_json(hyperrectangle.get_size())},
    {"position", _to_json(hyperrectangle.get_position())}
  };
}

template <class T>
auto _to_json(std::shared_ptr<T> const& ptr) -> json11::Json {
  return _to_json(*ptr);
}

template <class T, template <class...> class U>
auto _to_json(U<T> const& array) -> json11::Json {
  auto json_array = json11::Json::array();
  for(auto const& e : array) {
    json_array.push_back(_to_json(e));
  }
  return json_array;
}

template <class T, template <class...> class U>
auto _to_json(std::string const& key, U<T> const& array)
  -> json11::Json {
  return json11::Json::object{{key, to_json(array)}};
}
}
}
