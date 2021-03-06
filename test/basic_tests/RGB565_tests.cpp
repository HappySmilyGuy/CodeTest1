#include "gtest/gtest.h"
#include "../../headers/RGB565.h"
#include "../../headers/constants.h"

using Ramp::RGB565;
using Ramp::Constants::MAX_COLOUR_VAL;

TEST(RGB565, default_constructor)
{
  RGB565 colour;
  EXPECT_EQ(0, colour.get_r()) << "RGB565::RGB565() does not set the red value to 0.";
  EXPECT_EQ(0, colour.get_g()) << "RGB565::RGB565() does not set the green value to 0.";
  EXPECT_EQ(0, colour.get_b()) << "RGB565::RGB565() does not set the blue value to 0.";
}

TEST(RGB565, integer_constructor)
{
  unsigned short us = (3 << 11) + (5 << 5) + 8;
  RGB565 colour(us);
  EXPECT_EQ(3, colour.get_r()) << "RGB565::RGB565(ushort) does not correctly set the red value: Normal.";
  EXPECT_EQ(5, colour.get_g()) << "RGB565::RGB565(ushort) does not correctly set the green value: Normal.";
  EXPECT_EQ(8, colour.get_b()) << "RGB565::RGB565(ushort) does not correctly set the blue value: Normal.";

  colour = RGB565(0);
  EXPECT_EQ(0, colour.get_r()) << "RGB565::RGB565(ushort) does not correctly set the red value: Min.";
  EXPECT_EQ(0, colour.get_g()) << "RGB565::RGB565(ushort) does not correctly set the green value: Min.";
  EXPECT_EQ(0, colour.get_b()) << "RGB565::RGB565(ushort) does not correctly set the blue value: Min.";

  colour = RGB565(MAX_COLOUR_VAL);
  EXPECT_EQ(0b11111, colour.get_r()) << "RGB565::RGB565(ushort) does not correctly set the red value: Max.";
  EXPECT_EQ(0b111111, colour.get_g()) << "RGB565::RGB565(ushort) does not correctly set the green value: Max.";
  EXPECT_EQ(0b11111, colour.get_b()) << "RGB565::RGB565(ushort) does not correctly set the blue value: Max.";
}

TEST(RGB565, triple_integer_constructor)
{
  RGB565 colour(3, 5, 8);
  EXPECT_EQ(3, colour.get_r()) << "RGB565::RGB565(ushort) does not correctly set the red value: Normal.";
  EXPECT_EQ(5, colour.get_g()) << "RGB565::RGB565(ushort) does not correctly set the green value: Normal.";
  EXPECT_EQ(8, colour.get_b()) << "RGB565::RGB565(ushort) does not correctly set the blue value: Normal.";

  colour = RGB565(0, 0, 0);
  EXPECT_EQ(0, colour.get_r()) << "RGB565::RGB565(ushort) does not correctly set the red value: Min.";
  EXPECT_EQ(0, colour.get_g()) << "RGB565::RGB565(ushort) does not correctly set the green value: Min.";
  EXPECT_EQ(0, colour.get_b()) << "RGB565::RGB565(ushort) does not correctly set the blue value: Min.";

  colour = RGB565(0b11111, 0b111111, 0b11111);
  EXPECT_EQ(0b11111, colour.get_r()) << "RGB565::RGB565(ushort) does not correctly set the red value: Max.";
  EXPECT_EQ(0b111111, colour.get_g()) << "RGB565::RGB565(ushort) does not correctly set the green value: Max.";
  EXPECT_EQ(0b11111, colour.get_b()) << "RGB565::RGB565(ushort) does not correctly set the blue value: Max.";
}

TEST(RGB565, to_ushort)
{
  unsigned short i = 0b0011100011100011;
  RGB565 colour(i);
  EXPECT_EQ(i, colour.to_ushort()) << "RGB565.to_short() returns an incorrect value: Normal.";

  colour = RGB565(0);
  EXPECT_EQ((unsigned short) 0, colour.to_ushort()) << "RGB565.to_short() returns an incorrect value: Min.";

  colour = RGB565(MAX_COLOUR_VAL);
  EXPECT_EQ(MAX_COLOUR_VAL, colour.to_ushort()) << "RGB565.to_short() returns an incorrect value: Max.";
}

TEST(RGB565, equality)
{
  RGB565 a, b;
  EXPECT_EQ(a, b) << "RGB565::operator== fails to notice equality: Min.";

  unsigned short i = 0b0011100011100011;
  a = RGB565(i);
  b = RGB565(0b00111, 0b000111, 0b00011);
  EXPECT_EQ(a, b) << "RGB565::operator== fails to notice equality: Normal.";
  EXPECT_EQ(b, a) << "RGB565::operator== fails to notice equality: symmetric.";

  a = RGB565(MAX_COLOUR_VAL);
  b = RGB565(0b11111, 0b111111, 0b11111);
  EXPECT_EQ(a, b) << "RGB565::operator== fails to notice equality: Max.";

  a = RGB565();
  b = RGB565(1, 0, 0);
  EXPECT_NE(a, b) << "RGB565::operator== fails to notice inequality: Blue.";
  EXPECT_NE(b, a) << "RGB565::operator== fails to notice inequality: Blue.";
  b = RGB565(0, 1, 0);
  EXPECT_NE(a, b) << "RGB565::operator== fails to notice inequality: Red.";
  EXPECT_NE(b, a) << "RGB565::operator== fails to notice inequality: Red.";
  b = RGB565(0, 0, 1);
  EXPECT_NE(a, b) << "RGB565::operator== fails to notice inequality: Green.";
  EXPECT_NE(b, a) << "RGB565::operator== fails to notice inequality: Green.";

  a = RGB565(0b0011100011100010);
  b = RGB565(0b00111, 0b000111, 0b00011);
  EXPECT_NE(a, b) << "RGB565::operator== fails to notice inequality: Normal.";
  EXPECT_NE(b, a) << "RGB565::operator== fails to notice inequality: symmetric.";

  a = RGB565(MAX_COLOUR_VAL);
  b = RGB565();
  EXPECT_NE(a, b) << "RGB565::operator== fails to notice inequality: Max&Min.";
}