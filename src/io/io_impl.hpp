#pragma once

#include <cassert>
#include <fstream>

namespace spp {
namespace io {
// prototype declarations
template <int dim, class Real, template <class...> class U>
auto _input(U<mathutils::Hyperrectangle<dim, Real>>& hyperrectangles,
            mathutils::Hyperrectangle<dim, Real>& base,
            std::string const& filename) -> void;
template <int dim, class Real, template <class...> class U>
auto _input(U<std::shared_ptr<mathutils::Hyperrectangle<dim, Real>>>&
            hyperrectangles,
            std::shared_ptr<mathutils::Hyperrectangle<dim, Real>>& base,
            std::string const& filename) -> void;
template <int dim, class Real, template <class...> class U>
auto _inputs(U<mathutils::Hyperrectangle<dim, Real>>& hyperrectangles,
             mathutils::Hyperrectangle<dim, Real>& base,
             std::string const& s) -> void;
template <int dim, class Real, template <class...> class U>
auto _inputs(U<std::shared_ptr<mathutils::Hyperrectangle<dim, Real>>>&
             hyperrectangles,
             std::shared_ptr<mathutils::Hyperrectangle<dim, Real>>& base,
             std::string const& s) -> void;
template <int dim, class Real, template <class...> class U>
auto _from_json(U<mathutils::Hyperrectangle<dim, Real>>& hyperrectangles,
                mathutils::Hyperrectangle<dim, Real>& base,
                json11::Json const& json_obj) -> void;
template <int dim, class Real, template <class...> class U>
auto _from_json(U<mathutils::Hyperrectangle<dim, Real>>& hyperrectangles,
                json11::Json const& json_array) -> void;
template <int dim, class Real>
auto _from_json(mathutils::Hyperrectangle<dim, Real>& hyperrectangle,
                json11::Json const& json_obj) -> void;
template <int dim, class Real>
auto _from_json(mathutils::Vector<dim, Real>& vector,
                json11::Json const& json_array) -> void;
template <class T>
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
template <int dim, class Real, template <class...> class U>
auto open(std::string const& filename)
  -> std::tuple<U<std::shared_ptr<mathutils::Hyperrectangle<dim, Real>>>,
     std::shared_ptr<mathutils::Hyperrectangle<dim, Real>>> {
  using Hyperrectangle = mathutils::Hyperrectangle<dim, Real>;

  auto hyperrectangles = U<std::shared_ptr<Hyperrectangle>>();
  auto base = std::shared_ptr<Hyperrectangle>();
  _input(hyperrectangles, base, filename);
  return std::make_tuple(hyperrectangles, base);
}

template <class... Args>
auto input(Args&&... args) -> void {
  _input(std::forward<Args>(args)...);
}

template <class... Args>
auto inputs(Args&&... args) -> void {
  _inputs(std::forward<Args>(args)...);
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
auto from_json(Args&&... args) -> void {
  return _from_json(std::forward<Args>(args)...);
}

template <class... Args>
auto to_json(Args&&... args) -> json11::Json {
  return _to_json(std::forward<Args>(args)...);
}

template <int dim, class Real, template <class...> class U>
auto _input(U<mathutils::Hyperrectangle<dim, Real>>& hyperrectangles,
            mathutils::Hyperrectangle<dim, Real>& base,
            std::string const& filename) -> void {
  auto ifs = std::ifstream(filename);

  assert(!ifs.fail());

  auto buf = std::string();
  auto tmp = std::string();
  while(std::getline(ifs, tmp)) buf += tmp;

  ifs.close();

  auto err = std::string();
  auto json_obj = json11::Json::parse(buf, err);

  from_json(hyperrectangles, base, json_obj);
}

template <int dim, class Real, template <class...> class U>
auto _input(U<std::shared_ptr<mathutils::Hyperrectangle<dim, Real>>>&
            hyperrectangles,
            std::shared_ptr<mathutils::Hyperrectangle<dim, Real>>& base,
            std::string const& filename) -> void {
  using Hyperrectangle = mathutils::Hyperrectangle<dim, Real>;

  auto hyperrectangles_t = U<Hyperrectangle>();
  auto base_t = Hyperrectangle();
  _input(hyperrectangles_t, base_t, filename);
  for(auto& e : hyperrectangles_t) {
    hyperrectangles.push_back(std::make_shared<Hyperrectangle>(std::move(e)));
  }
  base = std::make_shared<Hyperrectangle>(std::move(base_t));
}

template <int dim, class Real, template <class...> class U>
auto _inputs(U<mathutils::Hyperrectangle<dim, Real>>& hyperrectangles,
             mathutils::Hyperrectangle<dim, Real>& base,
             std::string const& s) -> void {
  auto err = std::string();
  auto json_obj = json11::Json::parse(s, err);
  from_json(hyperrectangles, base, json_obj);
}

template <int dim, class Real, template <class...> class U>
auto _inputs(U<std::shared_ptr<mathutils::Hyperrectangle<dim, Real>>>&
             hyperrectangles,
             std::shared_ptr<mathutils::Hyperrectangle<dim, Real>>& base,
             std::string const& s) -> void {
  using Hyperrectangle = mathutils::Hyperrectangle<dim, Real>;

  auto hyperrectangles_t = U<Hyperrectangle>();
  auto base_t = Hyperrectangle();
  _inputs(hyperrectangles_t, base_t, s);
  for(auto& e : hyperrectangles_t) {
    hyperrectangles.push_back(std::make_shared<Hyperrectangle>(std::move(e)));
  }
  base = std::make_shared<Hyperrectangle>(std::move(base_t));
}

template <int dim, class Real, template <class...> class U>
auto _from_json(U<mathutils::Hyperrectangle<dim, Real>>& hyperrectangles,
                mathutils::Hyperrectangle<dim, Real>& base,
                json11::Json const& json_obj) -> void {
  auto const& hyperrectangles_json_array = json_obj["hyperrectangles"];
  auto const& base_json_obj              = json_obj["base"];
  _from_json(hyperrectangles, hyperrectangles_json_array);
  _from_json(base, base_json_obj);
}

template <int dim, class Real, template <class...> class U>
auto _from_json(U<mathutils::Hyperrectangle<dim, Real>>& hyperrectangles,
                json11::Json const& json_array) -> void {
  if(!json_array.is_array()) return;
  for(auto const& json_obj : json_array.array_items()) {
    auto hyperrectangle = mathutils::Hyperrectangle<dim, Real>();
    _from_json(hyperrectangle, json_obj);
    hyperrectangles.push_back(std::move(hyperrectangle));
  }
}

template <int dim, class Real>
auto _from_json(mathutils::Hyperrectangle<dim, Real>& hyperrectangle,
                json11::Json const& json_obj) -> void {
  using Vector = typename mathutils::Hyperrectangle<dim, Real>::Vector;

  if(!json_obj.is_object()) return;
  auto const& size_json_array     = json_obj["size"];
  auto const& position_json_array = json_obj["position"];
  auto size     = Vector();
  auto position = Vector();
  _from_json(size    , size_json_array);
  _from_json(position, position_json_array);
  hyperrectangle.set_size(size);
  hyperrectangle.set_position(position);
}

template <int dim, class Real>
auto _from_json(mathutils::Vector<dim, Real>& vector,
                json11::Json const& json_array) -> void {
  if(!json_array.is_array()) return;
  auto const& array = json_array.array_items();
  auto const n = std::min(dim, static_cast<int>(array.size()));
  for(auto i = 0; i < n; ++i) {
    if(!array[i].is_number()) continue;
    vector[i] = static_cast<Real>(array[i].number_value());
  }
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
