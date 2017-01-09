#pragma once

#include <cassert>
#include <fstream>
#include <memory>

#include "mathutils/vector.hpp"

namespace spp {
namespace io {
// prototype declarations
template <class T>
auto _get_hyperrectangles(json11::Json const& json_obj)
  -> std::vector<std::shared_ptr<T>>;
template <class T>
auto _get_base(json11::Json const& json_obj) -> std::shared_ptr<T>;
template <int dim, class Real>
auto _get_vector(json11::Json const& json_obj, std::string const& key)
  -> mathutils::Vector<dim, Real>;
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
template <class T>
auto open(std::string const& filename)
  -> std::tuple<std::vector<std::shared_ptr<T>>, std::shared_ptr<T>> {
  auto hyperrectangles = std::vector<std::shared_ptr<T>>();
  auto base = std::shared_ptr<T>();
  input(hyperrectangles, base, filename);
  return std::make_tuple(hyperrectangles, base);
}

template <class T>
auto input(std::vector<std::shared_ptr<T>>& hyperrectangles,
           std::shared_ptr<T>& base,
           std::string const& filename) -> void {
  auto ifs = std::ifstream(filename);

  assert(!ifs.fail());

  auto buf = std::string();
  auto tmp = std::string();
  while(std::getline(ifs, tmp)) buf += tmp;

  ifs.close();

  auto err = std::string();
  auto json_obj = json11::Json::parse(buf, err);

  input(hyperrectangles, base, json_obj);
}

template <class T>
auto input(std::vector<std::shared_ptr<T>>& hyperrectangles,
           std::shared_ptr<T>& base,
           json11::Json const& json_obj) -> void {
  hyperrectangles = _get_hyperrectangles<T>(json_obj);
  base = _get_base<T>(json_obj);
}

template <class T, template <class...> class U>
auto output(std::string const& key, U<T> const& array,
            std::ostream& os) -> void {
  auto json_obj = to_json(key, array);
  os << json_obj.dump() << std::endl;
}

template <class T, template <class...> class U>
auto output(U<T> const& array, std::ostream& os) -> void {
  output("hyperrectangles", array, os);
}

template <class... Args>
auto to_json(Args&&... args) -> json11::Json {
  return _to_json(std::forward<Args>(args)...);
}

template <class T>
auto _get_hyperrectangles(json11::Json const& json_obj)
  -> std::vector<std::shared_ptr<T>> {
  constexpr auto const dim = T::Dimension::value;
  using Real = typename T::Real;

  auto hyperrectangles = std::vector<std::shared_ptr<T>>();
  assert(json_obj.is_object());
  auto const& hyperrectangles_json_array = json_obj["hyperrectangles"];
  assert(hyperrectangles_json_array.is_array());
  for(auto const& json_obj : hyperrectangles_json_array.array_items()) {
    auto ptr = std::make_shared<T>(_get_vector<dim, Real>(json_obj, "size"));
    hyperrectangles.push_back(std::move(ptr));
  }

  return hyperrectangles;
}

template <class T>
auto _get_base(json11::Json const& json_obj) -> std::shared_ptr<T> {
  constexpr auto const dim = T::Dimension::value;
  using Real = typename T::Real;

  assert(json_obj.is_object());
  auto const& base_json_obj = json_obj["base"];
  assert(base_json_obj.is_object());

  return std::make_shared<T>(_get_vector<dim, Real>(base_json_obj, "size"),
                             _get_vector<dim, Real>(base_json_obj, "position"));
}

template <int dim, class Real>
auto _get_vector(json11::Json const& json_obj, std::string const& key)
  -> mathutils::Vector<dim, Real> {
  assert(json_obj.is_object());
  auto const& vector_json_array = json_obj[key];
  assert(vector_json_array.is_array());
  auto vector = mathutils::Vector<dim, Real>();
  {
    auto i = 0;
    for(auto const& json_number : vector_json_array.array_items()) {
      assert(json_number.is_number());
      vector[i++] = static_cast<Real>(json_number.number_value());
    }
  }
  return vector;
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
