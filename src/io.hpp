#pragma once

#include <iostream>
#include <vector>

#include "json11.hpp"

namespace spp {
namespace io {
template <class T>
auto open(std::string const& filename)
  -> std::tuple<std::vector<std::shared_ptr<T>>, std::shared_ptr<T>>;
template <class T>
auto input(std::vector<std::shared_ptr<T>>& hyperrectangles,
           std::shared_ptr<T>& base,
           std::string const& filename) -> void;
template <class T>
auto input(std::vector<std::shared_ptr<T>>& hyperrectangles,
           std::shared_ptr<T>& base,
           json11::Json const& json_obj) -> void;
template <class T, template <class...> class U>
auto output(std::string const& key, U<T> const& array,
            std::ostream& os = std::cout) -> void;
template <class T, template <class...> class U>
auto output(U<T> const& array, std::ostream& os = std::cout) -> void;
template <class... Args>
auto to_json(Args&&... args) -> json11::Json;
}
}

#include "io/io_impl.hpp"
