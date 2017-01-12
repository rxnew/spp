#include "gtest/gtest.h"

#include "spp3.hpp"

using Spp3 = spp::Spp3<int>;
using Vector = typename spp::Spp3<int>::Vector;
using Box = typename spp::Spp3<int>::Box;
using BoxPtr = std::shared_ptr<Box>;
using Boxes = std::vector<BoxPtr>;

TEST(Spp3Test, SolveCase1) {
  auto boxes = Boxes{
    std::make_shared<Box>(1, 1, 1),
    std::make_shared<Box>(2, 1, 1)
  };
  auto base = Box(3, 1, 0, 0, 0, 0);
  Spp3().solve(boxes, base);
  EXPECT_EQ(boxes[0]->get_position(), Vector(0, 0, 0));
  EXPECT_EQ(boxes[1]->get_position(), Vector(1, 0, 0));
}

TEST(Spp3Test, SolveCase2) {
  auto boxes = Boxes{
    std::make_shared<Box>(2, 1, 1),
    std::make_shared<Box>(2, 1, 1)
  };
  auto base = Box(2, 1, 0, 0, 0, 0);
  Spp3().solve(boxes, base);
  EXPECT_EQ(boxes[0]->get_position(), Vector(0, 0, 0));
  EXPECT_EQ(boxes[1]->get_position(), Vector(0, 0, 1));
}

TEST(Spp3Test, SolveCase3) {
  auto boxes = Boxes{
    std::make_shared<Box>(3, 1, 1),
    std::make_shared<Box>(2, 1, 1),
    std::make_shared<Box>(1, 1, 1)
  };
  auto base = Box(3, 1, 0, 0, 0, 0);
  Spp3().solve(boxes, base);
  EXPECT_EQ(boxes[0]->get_position(), Vector(0, 0, 0));
  EXPECT_EQ(boxes[1]->get_position(), Vector(0, 0, 1));
  EXPECT_EQ(boxes[2]->get_position(), Vector(2, 0, 1));
}

TEST(Spp3Test, SolveCase4) {
  auto boxes = Boxes{
    std::make_shared<Box>(1, 1, 1),
    std::make_shared<Box>(2, 1, 1)
  };
  auto base = Box(3, 1, 0, 1, 1, 1);
  Spp3().solve(boxes, base);
  EXPECT_EQ(boxes[0]->get_position(), Vector(1, 1, 1));
  EXPECT_EQ(boxes[1]->get_position(), Vector(2, 1, 1));
}

TEST(Spp3Test, SolveCase5) {
  auto boxes = Boxes{
    std::make_shared<Box>(1, 1, 1),
    std::make_shared<Box>(2, 1, 1)
  };
  auto base = std::make_shared<Box>(3, 1, 0, 0, 0, 0);
  Spp3().solve(boxes, base);
  EXPECT_EQ(boxes[0]->get_position(), Vector(0, 0, 0));
  EXPECT_EQ(boxes[1]->get_position(), Vector(1, 0, 0));
}

TEST(Spp3Test, SolveCase6) {
  auto boxes = Boxes{
    std::make_shared<Box>(1, 1, 1),
    std::make_shared<Box>(2, 1, 1)
  };
  auto base = Vector(3, 1, 0);
  Spp3().solve(boxes, base);
  EXPECT_EQ(boxes[0]->get_position(), Vector(0, 0, 0));
  EXPECT_EQ(boxes[1]->get_position(), Vector(1, 0, 0));
}

// X軸方向のストリップパッキング
TEST(Spp3Test, SolveCase7) {
  auto boxes = Boxes{
    std::make_shared<Box>(1, 1, 3),
    std::make_shared<Box>(1, 1, 2),
    std::make_shared<Box>(1, 1, 1)
  };
  auto base = Box(0, 1, 3, 0, 0, 0);
  Spp3().solve(boxes, base);
  EXPECT_EQ(boxes[0]->get_position(), Vector(0, 0, 0));
  EXPECT_EQ(boxes[1]->get_position(), Vector(1, 0, 0));
  EXPECT_EQ(boxes[2]->get_position(), Vector(1, 0, 2));
}

// Y軸方向のストリップパッキング
TEST(Spp3Test, SolveCase8) {
  auto boxes = Boxes{
    std::make_shared<Box>(3, 1, 1),
    std::make_shared<Box>(2, 1, 1),
    std::make_shared<Box>(1, 1, 1)
  };
  auto base = Box(3, 0, 1, 0, 0, 0);
  Spp3().solve(boxes, base);
  EXPECT_EQ(boxes[0]->get_position(), Vector(0, 0, 0));
  EXPECT_EQ(boxes[1]->get_position(), Vector(0, 1, 0));
  EXPECT_EQ(boxes[2]->get_position(), Vector(2, 1, 0));
}
