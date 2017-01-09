#include "gtest/gtest.h"

#include "io.hpp"
#include "spp3/rectangular.hpp"

using spp::Rectangular;
using RecPtr = std::shared_ptr<Rectangular>;
using Rectangulars = std::vector<RecPtr>;

TEST(InputTest, Input) {
  auto const data_string = R"({"hyperrectangles":[{"size":[1,1,1]},{"size":[2,1,1]}],"base":{"size":[3,1,0],"position":[0,0,0]}})";
  auto err = std::string();
  auto json_obj = json11::Json::parse(data_string, err);
  auto rectangulars_a = Rectangulars();
  auto base_a = RecPtr();

  spp::io::input(rectangulars_a, base_a, json_obj);

  auto const rectangulars_b = Rectangulars{
    std::make_shared<Rectangular>(1, 1, 1),
    std::make_shared<Rectangular>(2, 1, 1)
  };
  auto const base_b = std::make_shared<Rectangular>(3, 1, 0, 0, 0, 0);

  EXPECT_EQ(*rectangulars_a[0], *rectangulars_b[0]);
  EXPECT_EQ(*rectangulars_a[1], *rectangulars_b[1]);
  EXPECT_EQ(*base_a, *base_b);
}
