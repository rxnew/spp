#include "gtest/gtest.h"

#include "io.hpp"

using Hyperrectangle3i = mathutils::Hyperrectangle<3, int>;

class SppInputTest : public ::testing::Test {
 protected:
  SppInputTest()
    : input_data_(R"({"hyperrectangles":[{"size":[1,1,1]},{"size":[2,1,1]}],"base":{"size":[3,1,0],"position":[0,0,0]}})"),
      hyperrectangles_{Hyperrectangle3i(1, 1, 1), Hyperrectangle3i(2, 1, 1)},
      base_(3, 1, 0) {}

  std::string input_data_;
  std::vector<Hyperrectangle3i> hyperrectangles_;
  Hyperrectangle3i base_;
};

TEST_F(SppInputTest, Inputs) {
  auto hyperrectangles = std::vector<Hyperrectangle3i>();
  auto base = Hyperrectangle3i();
  spp::io::inputs(hyperrectangles, base, input_data_);
  EXPECT_EQ(hyperrectangles, hyperrectangles_);
  EXPECT_EQ(base, base_);
}

TEST_F(SppInputTest, InputsPointer) {
  auto hyperrectangles = std::vector<std::shared_ptr<Hyperrectangle3i>>();
  auto base = std::shared_ptr<Hyperrectangle3i>();
  spp::io::inputs(hyperrectangles, base, input_data_);
  EXPECT_EQ(*hyperrectangles[0], hyperrectangles_[0]);
  EXPECT_EQ(*hyperrectangles[1], hyperrectangles_[1]);
  EXPECT_EQ(*base, base_);
}
