#pragma once

#include <iostream>
#include <vector>

#include "json11.hpp"

namespace spp {
namespace io {
template <class T, template <class...> class U>
auto output(std::string const& key, U<T> const& array,
            std::ostream& os = std::cout) -> void;
template <class... Args>
auto to_json(Args&&... args) -> json11::Json;
}
}

#include "io/io_impl.hpp"
