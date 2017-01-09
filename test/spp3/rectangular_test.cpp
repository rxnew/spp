#include "gtest/gtest.h"

#include "spp3/rectangular.hpp"

using spp::Rectangular;

class RectangularTest : public ::testing::Test {
 protected:
  RectangularTest() : rectangular_(1, 2, 3, 4, 5, 6) {}

  Rectangular rectangular_;
};

TEST_F(RectangularTest, Constructor) {
  EXPECT_EQ(rectangular_.w, 1);
  EXPECT_EQ(rectangular_.h, 2);
  EXPECT_EQ(rectangular_.d, 3);
  EXPECT_EQ(rectangular_.x, 4);
  EXPECT_EQ(rectangular_.y, 5);
  EXPECT_EQ(rectangular_.z, 6);

  Rectangular surface(1, 2, 0);
  EXPECT_EQ(surface.w, 1);
  EXPECT_EQ(surface.h, 2);
  EXPECT_EQ(surface.d, 0);
  EXPECT_EQ(surface.x, 0);
  EXPECT_EQ(surface.y, 0);
  EXPECT_EQ(surface.z, 0);
}

TEST_F(RectangularTest, DefaultConstructor) {
  auto rectangular = Rectangular();
  EXPECT_EQ(rectangular.w, 0);
  EXPECT_EQ(rectangular.h, 0);
  EXPECT_EQ(rectangular.d, 0);
  EXPECT_EQ(rectangular.x, 0);
  EXPECT_EQ(rectangular.y, 0);
  EXPECT_EQ(rectangular.z, 0);
}

TEST_F(RectangularTest, CopyConstructor) {
  auto rectangular = rectangular_;
  EXPECT_EQ(rectangular.w, 1);
  EXPECT_EQ(rectangular.h, 2);
  EXPECT_EQ(rectangular.d, 3);
  EXPECT_EQ(rectangular.x, 4);
  EXPECT_EQ(rectangular.y, 5);
  EXPECT_EQ(rectangular.z, 6);

  rectangular.w = 0;
  EXPECT_EQ(rectangular_.w, 1);
  EXPECT_EQ(rectangular.w, 0);
}

TEST_F(RectangularTest, MoveConstructor) {
  auto rectangular_t = rectangular_;
  auto rectangular = std::move(rectangular_);
  EXPECT_EQ(rectangular.w, 1);
  EXPECT_EQ(rectangular.h, 2);
  EXPECT_EQ(rectangular.d, 3);
  EXPECT_EQ(rectangular.x, 4);
  EXPECT_EQ(rectangular.y, 5);
  EXPECT_EQ(rectangular.z, 6);
}

TEST_F(RectangularTest, CopyAssignment) {
  auto rectangular = Rectangular();
  rectangular = rectangular_;
  EXPECT_EQ(rectangular.w, 1);
  EXPECT_EQ(rectangular.h, 2);
  EXPECT_EQ(rectangular.d, 3);
  EXPECT_EQ(rectangular.x, 4);
  EXPECT_EQ(rectangular.y, 5);
  EXPECT_EQ(rectangular.z, 6);

  rectangular.w = 0;
  EXPECT_EQ(rectangular_.w, 1);
  EXPECT_EQ(rectangular.w, 0);
}

TEST_F(RectangularTest, MoveAssignment) {
  auto rectangular_t = rectangular_;
  auto rectangular = Rectangular();
  rectangular = std::move(rectangular_t);
  EXPECT_EQ(rectangular.w, 1);
  EXPECT_EQ(rectangular.h, 2);
  EXPECT_EQ(rectangular.d, 3);
  EXPECT_EQ(rectangular.x, 4);
  EXPECT_EQ(rectangular.y, 5);
  EXPECT_EQ(rectangular.z, 6);
}
