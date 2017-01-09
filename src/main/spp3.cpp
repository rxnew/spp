#include "spp3.hpp"
#include "io.hpp"

auto main(int argc, char* argv[]) -> int {
  auto filename = argc >= 2 ? argv[1] : "test_data/example_spp3.json";
  auto input_data = spp::io::open<3, int>(filename);
  auto& boxes = std::get<0>(input_data);
  auto& base = std::get<1>(input_data);
  spp::Spp3<int>().solve(boxes, base);
  spp::io::output(boxes);
  return 0;
}
