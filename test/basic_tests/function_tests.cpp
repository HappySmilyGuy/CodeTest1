//
// Created by Eddie on 12-Sep-16.
//
#include "gtest/gtest.h"
#include "../../headers/functions.h"

//  bool checks_args(int argc, char *argv[], Display &d, bool &show_help, std::string &errors);
TEST(function_checks, check_args)
{
  std::string errors;
  bool show_help = false;
  int argc = 6;
  char *argv[] = {(char *) "ramp.exe", (char *) "display", (char *) "0", (char *) "0", (char *) "0", (char *) "0",
                  NULL};
  Display d;
  EXPECT_EQ(true, Ramp::checks_args(argc, argv, d, show_help, errors));
  EXPECT_EQ(false, show_help);
  EXPECT_EQ("", errors);
}

//void set_corner_values(int argc, char *argv[], RGB565 &tl, RGB565 &tr, RGB565 &bl, RGB565 &br);
TEST(function_checks, set_corner_values)
{
  Ramp::RGB565 tl, tr, bl, br;
  int argc = 6;
  char *argv[] = {(char *) "ramp.exe", (char *) "display", (char *) "0", (char *) "2", (char *) "3", (char *) "4",
                  NULL};
  Ramp::set_corner_values(argc, argv, tl, tr, bl, br);
  EXPECT_EQ(tl.b, 0);
  EXPECT_EQ(tr.b, 2);
  EXPECT_EQ(bl.b, 3);
  EXPECT_EQ(br.b, 4);
}

//std::vector<std::vector<RGB565>> calculate_ramped_rows(const RGB565 &tl, const RGB565 &tr, const RGB565 &bl,
//                                                       const RGB565 &br, const int width, const int height);
TEST(function_checks, calculate_ramped_rows)
{
  Ramp::RGB565 tl(0), tr(1), bl(2), br(3);
  std::vector<std::vector<Ramp::RGB565>> result = Ramp::calculate_ramped_rows(tl, tr, bl, br, 2, 2);
  std::vector<std::vector<Ramp::RGB565>> compariter;
  std::vector<Ramp::RGB565> row = {0, 1};
  compariter.push_back(row);
  row = {2, 3};
  compariter.push_back(row);
  EXPECT_EQ(result, compariter);
}