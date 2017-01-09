#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include "json11.hpp"
#include "mathutils/vector.hpp"

namespace spp {
namespace io {
template <int dim, class Real, template <class...> class U = std::vector>
auto open(std::string const& filename)
  -> std::tuple<U<std::shared_ptr<mathutils::Hyperrectangle<dim, Real>>>,
     std::shared_ptr<mathutils::Hyperrectangle<dim, Real>>>;
template <class... Args>
auto input(Args&&... args) -> void;
template <class... Args>
auto inputs(Args&&... args) -> void;
template <class T, template <class...> class U>
auto output(std::string const& key, U<T> const& array,
            std::ostream& os = std::cout) -> void;
template <class T, template <class...> class U>
auto output(U<T> const& array, std::ostream& os = std::cout) -> void;
template <class T, template <class...> class U>
auto outputs(std::string const& key, U<T> const& array, std::string& s)
  -> void;
template <class T, template <class...> class U>
auto outputs(U<T> const& array, std::string& s) -> void;
template <class... Args>
auto from_json(Args&&... args) -> void;
template <class... Args>
auto to_json(Args&&... args) -> json11::Json;
}
}

#include "io/io_impl.hpp"
