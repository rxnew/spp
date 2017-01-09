#include "gtest/gtest.h"

#include "io.hpp"

using Hyperrectangle3i = mathutils::Hyperrectangle<3, int>;

class SppOutputTest : public ::testing::Test {
 protected:
  SppOutputTest()
    : output_data_(R"({"hyperrectangles":[{"size":[1,1,1],"position":[0,0,0]},{"size":[2,1,1],"position":[0,0,0]}]})"),
      hyperrectangles_{Hyperrectangle3i(1, 1, 1), Hyperrectangle3i(2, 1, 1)} {}

  std::string output_data_;
  std::vector<Hyperrectangle3i> hyperrectangles_;
};

TEST_F(SppOutputTest, Outputs) {
  auto output_data = std::string();
  spp::io::outputs(hyperrectangles_, output_data);
  auto err = std::string();
  EXPECT_EQ(json11::Json::parse(output_data, err),
            json11::Json::parse(output_data_, err));
}

TEST_F(SppOutputTest, OutputsPointer) {
  auto hyperrectangles = std::vector<std::shared_ptr<Hyperrectangle3i>>();
  for(auto const& e : hyperrectangles_) {
    hyperrectangles.push_back(std::make_shared<Hyperrectangle3i>(e));
  }
  auto output_data = std::string();
  spp::io::outputs(hyperrectangles, output_data);
  auto err = std::string();
  EXPECT_EQ(json11::Json::parse(output_data, err),
            json11::Json::parse(output_data_, err));
}
