//
// Created by Eddie on 12-Sep-16.
//
#include "gtest/gtest.h"
#include "../../headers/functions.h"

using Ramp::RGB565;

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

  // TODO
  // incorrect values checks
  // edge values

}

//void set_corner_values(int argc, char *argv[], RGB565 &tl, RGB565 &tr, RGB565 &bl, RGB565 &br);
TEST(function_checks, set_corner_values)
{
  int argc = 6;
  char *argv[] = {(char *) "ramp.exe", (char *) "display", (char *) "0", (char *) "2", (char *) "3", (char *) "4",
                  NULL};
  RGB565 tl, tr, bl, br;
  Ramp::set_corner_values(argc, argv, tl, tr, bl, br);
  EXPECT_EQ(tl.b, 0);
  EXPECT_EQ(tr.b, 2);
  EXPECT_EQ(bl.b, 3);
  EXPECT_EQ(br.b, 4);

  // TODO edge values
}

namespace
{
  void check_row(const std::vector<std::vector<RGB565>> result, unsigned int row,
                 std::vector<std::vector<unsigned short>> expectations, std::string error_msg)
  {
    if (result[row].size() != expectations.size())
    {
      ASSERT_TRUE(false) << "Test has not been structured correctly: mismatched sizes of result[row].size() "
                    "!= expectations.size(): " << result[row].size() << " != " << expectations.size() << "."
                         << error_msg;
    }
    int i = 0;
    for (std::vector<std::vector<unsigned short>>::iterator it = expectations.begin(); it != expectations.end(); ++it)
    {
      if (it->size() == 1)
      {
        EXPECT_EQ(it->at(0), result[row][i].to_ushort()) << error_msg << " At position [" << row << "][" << i << "].";
      }
      else
      {
        bool b = false;
        std::string possible_results = "{";
        for (std::vector<unsigned short>::iterator possible_results_it = it->begin(); possible_results_it != it->end();
             ++possible_results_it)
        {
          possible_results += *possible_results_it + ", ";
          if (result[row][i] == RGB565(*possible_results_it))
          {
            b = true;
            break;
          }
        }
        EXPECT_TRUE(b) << result[row][i].to_ushort() << " not in "
                       << possible_results.substr(possible_results.length() - 1) << "} "
                       << error_msg << " At position [" << row << "][" << i << "].";
      }
      ++i;
    }
  }

  void check_row(const std::vector<std::vector<RGB565>> result, unsigned int row,
                 std::vector<unsigned short> expectations, std::string error_msg)
  {
    if (result[row].size() != expectations.size())
    {
      ASSERT_TRUE(false) << "Test has not been structured correctly: mismatched sizes of result[row].size() "
                    "!= expectations.size(): " << result[row].size() << " != " << expectations.size() << "."
                         << error_msg;
    }
    int i = 0;
    for (std::vector<unsigned short>::iterator it = expectations.begin(); it != expectations.end(); ++it)
    {
      EXPECT_EQ(*it, result[row][i].to_ushort()) << error_msg << " At position [" << row << "][" << i << "].";
      ++i;
    }
  }

  void check_column(const std::vector<std::vector<RGB565>> result, unsigned int column,
                    std::vector<unsigned short> expectations, std::string error_msg)
  {
    if (result.size() != expectations.size())
    {
      ASSERT_TRUE(false) << "Test has not been structured correctly: mismatched sizes of result.size() "
                    "!= expectations.size(): " << result.size() << " != " << expectations.size() << "."
                         << error_msg;
    }
    int i = 0;
    for (std::vector<unsigned short>::iterator it = expectations.begin(); it != expectations.end(); ++it)
    {
      EXPECT_EQ(*it, result[i][column].to_ushort()) << error_msg << " At position [" << i << "][" << column << "].";
      ++i;
    }
  }

  void check_column(const std::vector<std::vector<RGB565>> result, unsigned int column,
                    std::vector<std::vector<unsigned short>> expectations, std::string error_msg)
  {
    if (result.size() != expectations.size())
    {
      ASSERT_TRUE(false) << "Test has not been structured correctly: mismatched sizes of result.size() "
                    "!= expectations.size(): " << result.size() << " != " << expectations.size() << "."
                         << error_msg;
    }
    int i = 0;
    for (std::vector<std::vector<unsigned short>>::iterator it = expectations.begin(); it != expectations.end(); ++it)
    {
      if (it->size() == 1)
      {
        EXPECT_EQ(it->at(0), result[i][column].to_ushort())
                      << error_msg << " At position [" << i << "][" << column << "].";
      }
      else
      {
        bool b = false;
        std::string possible_results = "{";
        for (std::vector<unsigned short>::iterator possible_results_it = it->begin(); possible_results_it != it->end();
             ++possible_results_it)
        {
          possible_results += *possible_results_it + ", ";
          if (result[i][column] == RGB565(*possible_results_it))
          {
            b = true;
            break;
          }
        }
        EXPECT_TRUE(b) << result[i][column].to_ushort() << " not in "
                       << possible_results.substr(possible_results.length() - 1) << "} "
                       << error_msg << " At position [" << i << "][" << column << "].";
      }
      ++i;
    }
  }

}

//std::vector<std::vector<RGB565>> calculate_ramped_rows(const RGB565 &tl, const RGB565 &tr, const RGB565 &bl,
//                                                       const RGB565 &br, const int width, const int height);
TEST(function_checks, calculate_ramped_rows_too_small_grids)
{
  { // check a 16x0 grid
    unsigned short tl = 0;
    unsigned short tr = 2;
    std::vector<std::vector<RGB565>> result = Ramp::calculate_ramped_rows(RGB565(tl), RGB565(tr),
                                                                          RGB565(tl), RGB565(tr), 16, 0);
    EXPECT_EQ(result.size(), 0) << " Failed to create a 16x0 grid.";
  }
  { // check a 0x16 grid
    unsigned short tl = 0;
    unsigned short tr = 2;
    std::vector<std::vector<RGB565>> result = Ramp::calculate_ramped_rows(RGB565(tl), RGB565(tr),
                                                                          RGB565(tl), RGB565(tr), 0, 16);
    EXPECT_EQ(result.size(), 0) << " Failed to create a 0x16 grid.";
  }
  { // check a 0x0 grid
    unsigned short tl = 0;
    unsigned short tr = 2;
    std::vector<std::vector<RGB565>> result = Ramp::calculate_ramped_rows(RGB565(tl), RGB565(tr),
                                                                          RGB565(tl), RGB565(tr), 0, 0);
    EXPECT_EQ(result.size(), 0) << " Failed to create a 0x0 grid.";
  }
}

TEST(function_checks, calculate_ramped_rows)
{
  { // check a 2x2 grid, small values
    std::vector<std::vector<RGB565>> result = Ramp::calculate_ramped_rows(RGB565(0), RGB565(1),
                                                                          RGB565(2), RGB565(3), 2, 2);
    std::vector<std::vector<RGB565>> comparator;
    std::vector<RGB565> row = {0, 1};
    comparator.push_back(row);
    row = {2, 3};
    comparator.push_back(row);
    EXPECT_EQ(result, comparator) << " Failed to create a 2x2 grid with the corner values.";
  }
  { // check a 2x2 grid, large values
    unsigned short tl = 0b1111111111111111;
    unsigned short tr = 0b111111111111111;
    unsigned short bl = 0b11111111111111;
    unsigned short br = 0b1111111111111;
    std::vector<std::vector<RGB565>> result = Ramp::calculate_ramped_rows(RGB565(tl), RGB565(tr),
                                                                          RGB565(bl), RGB565(br), 2, 2);
    std::vector<std::vector<RGB565>> comparator = {{tl, tr},
                                                   {bl, br}};
    EXPECT_EQ(result, comparator) << " Failed to create a 2x2 grid with the corner values.";
  }
  { // check a 3x3 grid
    unsigned short tl = 0b1110011110011100;
    unsigned short tr = 0b1100011100011000;
    unsigned short bl = 0b1000011000010000;
    unsigned short br = 0b0000010000000000;
    std::vector<std::vector<RGB565>> result = Ramp::calculate_ramped_rows(RGB565(tl), RGB565(tr),
                                                                          RGB565(bl), RGB565(br), 3, 3);
    std::vector<std::vector<RGB565>> comparator = {{tl,                 0b1101011101011010, tr},
                                                   {0b1011011011010110, 0b1000111000110001, 0b0110010110001100},
                                                   {bl,                 0b0100010100001000, br}};
    EXPECT_EQ(result, comparator) << " Failed to create a 3x3 grid with the corner values.";
  }
}

TEST(function_checks, calculate_ramped_rows_R)
{
  // TODO
}

TEST(function_checks, calculate_ramped_rows_G)
{
  // TODO
}

TEST(function_checks, calculate_ramped_rows_B)
{
  { // check a 16x1 grid
    unsigned short tl = 0;
    unsigned short tr = 2;
    std::vector<std::vector<RGB565>> result = Ramp::calculate_ramped_rows(RGB565(tl), RGB565(tr),
                                                                          RGB565(tl), RGB565(tr), 16, 1);
    check_row(result, 0, {{0},
                          {0},
                          {0},
                          {0},
                          {0},
                          {0, 1},
                          {1},
                          {1},
                          {1},
                          {1},
                          {1, 2},
                          {2},
                          {2},
                          {2},
                          {2},
                          {2}},
              " Failed to create a 16x1 grit with correct values.");
  }
  { // check a 1x9 grid
    unsigned short tl = 0;
    unsigned short bl = 3;
    std::vector<std::vector<RGB565>> result = Ramp::calculate_ramped_rows(RGB565(tl), RGB565(tl),
                                                                          RGB565(bl), RGB565(bl), 1, 9);
    check_column(result, 0, {{0},
                             {0},
                             {0, 1},
                             {1},
                             {1, 2},
                             {2},
                             {2, 3},
                             {3},
                             {3}},
                 " Failed to create a 1x9 grit with correct values.");
    EXPECT_TRUE(result[4][0] == 1 || (result[4][0] == 2 && result[2][0] == 1))
                  << " Failed to create a 1x9 grid with the correct [4][0] value.";
    EXPECT_TRUE(result[6][0] == 2 || (result[6][0] == 3 && result[4][0] == 2))
                  << " Failed to create a 1x9 grid with the correct [6][0] value.";
  }
  { //check all 4 sides and a random row and column of a 16x9
    unsigned short tl = 0;
    unsigned short tr = 2;
    unsigned short bl = 3;
    unsigned short br = 4;
    std::vector<std::vector<RGB565>> result = Ramp::calculate_ramped_rows(RGB565(tl), RGB565(tr),
                                                                          RGB565(bl), RGB565(br), 16, 9);
    // far left column
    check_column(result, 0, {{0},
                             {0},
                             {0, 1},
                             {1},
                             {1, 2},
                             {2},
                             {2, 3},
                             {3},
                             {3}},
                 " Failed to create a 16x9 grit with correct values.");
    EXPECT_TRUE(result[4][0] == 1 || (result[4][0] == 2 && result[2][0] == 1))
                  << " Failed to create a 16x9 grid with the correct [4][0] value.";
    EXPECT_TRUE(result[6][0] == 2 || (result[6][0] == 3 && result[4][0] == 2))
                  << " Failed to create a 16x9 grid with the correct [6][0] value.";

    check_row(result, 0, {{0},
                          {0},
                          {0},
                          {0},
                          {0},
                          {0, 1},
                          {1},
                          {1},
                          {1},
                          {1},
                          {1, 2},
                          {2},
                          {2},
                          {2},
                          {2},
                          {2}},
              " Failed to create a 16x9 grit with correct values."); // top row
    check_column(result, 15, {2, 2, 2, 3, 3, 3, 4, 4, 4}, " Failed to create a correct 16x9 grid: far right column.");
    check_row(result, 8, {3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4},
              " Failed to create a correct 16x9 grid: bottom row.");
    check_column(result, 6, {1, 1, 1, 2, 2, 2, 3, 3, 3}, " Failed to create a correct 16x9 grid: 7th column.");
    check_row(result, 5, {2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3},
              " Failed to create a correct 16x1 grid: 6th row.");
  }

  { // check a perfect ramp 17x9
    unsigned short tl = 0;
    unsigned short tr = 16;
    unsigned short bl = 16;
    unsigned short br = 0;
    std::vector<std::vector<RGB565>> result = Ramp::calculate_ramped_rows(RGB565(tl), RGB565(tr),
                                                                          RGB565(bl), RGB565(br), 17, 9);
    check_column(result, 0, {0, 2, 4, 6, 8, 10, 12, 14, 16}, " Failed to create a perfect 17x9 ramped grid.");
    check_column(result, 16, {16, 14, 12, 10, 8, 6, 4, 2, 0}, " Failed to create a perfect 17x9 ramped grid.");
    check_row(result, 0, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16},
              " Failed to create a perfect 17x9 ramped grid.");
    check_row(result, 8, {16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0},
              " Failed to create a perfect 17x9 ramped grid.");
  }
}