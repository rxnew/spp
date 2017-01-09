#include "gtest/gtest.h"

#include "spp3.hpp"

using spp::Rectangular;
using RecPtr = std::shared_ptr<Rectangular>;
using Rectangulars = std::vector<RecPtr>;
using Vector = mathutils::Vector<3, int>;

TEST(Spp3Test, SolveCase1) {
  auto rectangulars = Rectangulars{
    std::make_shared<Rectangular>(1, 1, 1),
    std::make_shared<Rectangular>(2, 1, 1)
  };
  auto surface = Rectangular(3, 1, 0, 0, 0, 0);
  spp::Spp3().solve(rectangulars, surface);
  EXPECT_EQ(rectangulars[0]->get_position(), Vector(0, 0, 0));
  EXPECT_EQ(rectangulars[1]->get_position(), Vector(1, 0, 0));
}

TEST(Spp3Test, SolveCase2) {
  auto rectangulars = Rectangulars{
    std::make_shared<Rectangular>(2, 1, 1),
    std::make_shared<Rectangular>(2, 1, 1)
  };
  auto surface = Rectangular(2, 1, 0, 0, 0, 0);
  spp::Spp3().solve(rectangulars, surface);
  EXPECT_EQ(rectangulars[0]->get_position(), Vector(0, 0, 0));
  EXPECT_EQ(rectangulars[1]->get_position(), Vector(0, 0, 1));
}

TEST(Spp3Test, SolveCase3) {
  auto rectangulars = Rectangulars{
    std::make_shared<Rectangular>(3, 1, 1),
    std::make_shared<Rectangular>(2, 1, 1),
    std::make_shared<Rectangular>(1, 1, 1)
  };
  auto surface = Rectangular(3, 1, 0, 0, 0, 0);
  spp::Spp3().solve(rectangulars, surface);
  EXPECT_EQ(rectangulars[0]->get_position(), Vector(0, 0, 0));
  EXPECT_EQ(rectangulars[1]->get_position(), Vector(0, 0, 1));
  EXPECT_EQ(rectangulars[2]->get_position(), Vector(2, 0, 1));
}

TEST(Spp3Test, SolveCase4) {
  auto rectangulars = Rectangulars{
    std::make_shared<Rectangular>(1, 1, 1),
    std::make_shared<Rectangular>(2, 1, 1)
  };
  auto surface = Rectangular(3, 1, 0, 1, 1, 1);
  spp::Spp3().solve(rectangulars, surface);
  EXPECT_EQ(rectangulars[0]->get_position(), Vector(1, 1, 1));
  EXPECT_EQ(rectangulars[1]->get_position(), Vector(2, 1, 1));
}

TEST(Spp3Test, SolveCase5) {
  auto rectangulars = Rectangulars{
    std::make_shared<Rectangular>(1, 1, 1),
    std::make_shared<Rectangular>(2, 1, 1)
  };
  auto surface = std::make_shared<Rectangular>(3, 1, 0, 0, 0, 0);
  spp::Spp3().solve(rectangulars, surface);
  EXPECT_EQ(rectangulars[0]->get_position(), Vector(0, 0, 0));
  EXPECT_EQ(rectangulars[1]->get_position(), Vector(1, 0, 0));
}

TEST(Spp3Test, SolveCase6) {
  auto rectangulars = Rectangulars{
    std::make_shared<Rectangular>(1, 1, 1),
    std::make_shared<Rectangular>(2, 1, 1)
  };
  auto surface = Vector(3, 1, 0);
  spp::Spp3().solve(rectangulars, surface);
  EXPECT_EQ(rectangulars[0]->get_position(), Vector(0, 0, 0));
  EXPECT_EQ(rectangulars[1]->get_position(), Vector(1, 0, 0));
}
