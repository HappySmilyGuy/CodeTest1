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
  char *argv[] = {(char *)"ramp.exe", (char *)"display", (char *)"0", (char *)"0", (char *)"0", (char *)"0", NULL};
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
  char *argv[] = {(char *)"ramp.exe", (char *)"display", (char *)"0", (char *)"2", (char *)"3", (char *)"4", NULL};
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
    RGB565 tl(0), tr(2);
    std::vector<std::vector<RGB565>> result = Ramp::calculate_ramped_rows(tl, tr, tl, tr, 16, 0);
    EXPECT_EQ(result.size(), 0) << " Failed to create a 16x0 grid.";
  }
  { // check a 0x16 grid
    RGB565 tl(0), tr(2);
    std::vector<std::vector<RGB565>> result = Ramp::calculate_ramped_rows(tl, tr, tl, tr, 0, 16);
    EXPECT_EQ(result.size(), 0) << " Failed to create a 0x16 grid.";
  }
  { // check a 0x0 grid
    RGB565 tl(0), tr(2);
    std::vector<std::vector<RGB565>> result = Ramp::calculate_ramped_rows(tl, tr, tl, tr, 0, 0);
    EXPECT_EQ(result.size(), 0) << " Failed to create a 0x0 grid.";
  }
}

TEST(function_checks, calculate_ramped_rows)
{
  { // check a 2x2 grid, small values
    unsigned short tl = 0, tr = 1, bl = 2, br = 3;
    std::vector<std::vector<RGB565>> result = Ramp::calculate_ramped_rows(RGB565(tl), RGB565(tr),
                                                                          RGB565(bl), RGB565(br), 2, 2);
    std::vector<std::vector<RGB565>> comparator = {{tl, tr},
                                                   {bl, br}};
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

namespace
{ // Red pixel checks
  const unsigned short R0 = RGB565(0, 0, 0).to_ushort(),
          R1 = RGB565(1, 0, 0).to_ushort(),
          R2 = RGB565(2, 0, 0).to_ushort(),
          R3 = RGB565(3, 0, 0).to_ushort();
  // check a 16x1 grid
  TEST(function_checks, calculate_ramped_rows_RED_0)
  {
    RGB565 tl(0, 0, 0), tr(2, 0, 0);
    std::vector<std::vector<RGB565>> result = Ramp::calculate_ramped_rows(tl, tr, tl, tr, 16, 1);
    check_row(result, 0, /*@formatter:off*/{{R0}, {R0}, {R0}, {R0}, {R0}, {R0, R1},
                                            {R1}, {R1}, {R1}, {R1}, {R1, R2},
                                            {R2}, {R2}, {R2}, {R2}, {R2}},/*@formatter:on*/
              " Failed to create a 16x1 grit with correct values.");
  }

  // check a 1x9 grid
  TEST(function_checks, calculate_ramped_rows_RED_1)
  {
    RGB565 tl(0, 0, 0), bl(3, 0, 0);
    std::vector<std::vector<RGB565>> result = Ramp::calculate_ramped_rows(tl, tl, bl, bl, 1, 9);
    check_column(result, 0, /*@formatter:off*/{{R0}, {R0}, {R0, R1},
                                               {R1}, {R1, R2},
                                               {R2}, {R2, R3},
                                               {R3}, {R3}},/*@formatter:on*/
                 " Failed to create a 1x9 grit with correct values.");
    EXPECT_TRUE(result[4][0] == R1 || (result[4][0] == R2 && result[2][0] == R1))
                  << " Failed to create a 1x9 grid with the correct [4][0] value.";
    EXPECT_TRUE(result[6][0] == R2 || (result[6][0] == R3 && result[4][0] == R2))
                  << " Failed to create a 1x9 grid with the correct [6][0] value.";
  }
}

namespace
{ // Green pixel checks
  const unsigned short G0 = RGB565(0, 0, 0).to_ushort(),
          G1 = RGB565(0, 1, 0).to_ushort(),
          G2 = RGB565(0, 2, 0).to_ushort(),
          G3 = RGB565(0, 3, 0).to_ushort();
  // check a 16x1 grid
  TEST(function_checks, calculate_ramped_rows_GREEN_0)
  {
    RGB565 tl(0, 0, 0), tr(0, 2, 0);
    std::vector<std::vector<RGB565>> result = Ramp::calculate_ramped_rows(tl, tr, tl, tr, 16, 1);
    check_row(result, 0, /*@formatter:off*/{{G0}, {G0}, {G0}, {G0}, {G0}, {G0, G1},
                                            {G1}, {G1}, {G1}, {G1}, {G1, G2},
                                            {G2}, {G2}, {G2}, {G2}, {G2}},/*@formatter:on*/
              " Failed to create a 16x1 grit with correct values.");
  }

  // check a 1x9 grid
  TEST(function_checks, calculate_ramped_rows_GREEN_1)
  {
    RGB565 tl(0, 0, 0), bl(0, 3, 0);
    std::vector<std::vector<RGB565>> result = Ramp::calculate_ramped_rows(tl, tl, bl, bl, 1, 9);
    check_column(result, 0, /*@formatter:off*/{{G0}, {G0}, {G0, G1},
                                                 {G1}, {G1, G2},
                                                 {G2}, {G2, G3},
                                                 {G3}, {G3}},/*@formatter:on*/
                 " Failed to create a 1x9 grit with correct values.");
    EXPECT_TRUE(result[4][0] == G1 || (result[4][0] == G2 && result[2][0] == G1))
                  << " Failed to create a 1x9 grid with the correct [4][0] value.";
    EXPECT_TRUE(result[6][0] == G2 || (result[6][0] == G3 && result[4][0] == G2))
                  << " Failed to create a 1x9 grid with the correct [6][0] value.";
  }
}

namespace
{ // Blue pixel checks
  // check a 16x1 grid
  TEST(function_checks, calculate_ramped_rows_BLUE_0)
  {
    RGB565 tl(0), tr(2);
    std::vector<std::vector<RGB565>> result = Ramp::calculate_ramped_rows(tl, tr, tl, tr, 16, 1);
    check_row(result, 0, /*@formatter:off*/{{0},{0},{0},{0},{0},{0,1},{1},{1},{1},{1},{1,2},{2},{2},{2},{2},{2}},
              /*@formatter:on*/ " Failed to create a 16x1 grit with correct values.");
  }

  // check a 1x9 grid
  TEST(function_checks, calculate_ramped_rows_BLUE_1)
  {
    RGB565 tl(0), bl(3);
    std::vector<std::vector<RGB565>> result = Ramp::calculate_ramped_rows(tl, tl, bl, bl, 1, 9);
    check_column(result, 0, /*@formatter:off*/{{0},{0},{0,1},{1},{1,2},{2},{2,3},{3},{3}},/*@formatter:on*/
                 " Failed to create a 1x9 grit with correct values.");
    EXPECT_TRUE(result[4][0] == 1 || (result[4][0] == 2 && result[2][0] == 1))
                  << " Failed to create a 1x9 grid with the correct [4][0] value.";
    EXPECT_TRUE(result[6][0] == 2 || (result[6][0] == 3 && result[4][0] == 2))
                  << " Failed to create a 1x9 grid with the correct [6][0] value.";
  }
}

namespace
{ // combined Red Green and Blue checks
  const unsigned short C0 = RGB565(0, 0, 0).to_ushort(),
          C1 = RGB565(1, 1, 1).to_ushort(),
          C2 = RGB565(2, 2, 2).to_ushort(),
          C3 = RGB565(3, 3, 3).to_ushort(),
          C4 = RGB565(4, 4, 4).to_ushort(),
          C5 = RGB565(5, 5, 5).to_ushort(),
          C6 = RGB565(6, 6, 6).to_ushort(),
          C7 = RGB565(7, 7, 7).to_ushort(),
          C8 = RGB565(8, 8, 8).to_ushort(),
          C9 = RGB565(9, 9, 9).to_ushort(),
          C10 = RGB565(10, 10, 10).to_ushort(),
          C11 = RGB565(11, 11, 11).to_ushort(),
          C12 = RGB565(12, 12, 12).to_ushort(),
          C13 = RGB565(13, 13, 13).to_ushort(),
          C14 = RGB565(14, 14, 14).to_ushort(),
          C15 = RGB565(15, 15, 15).to_ushort(),
          C16 = RGB565(16, 16, 16).to_ushort();

  //check all 4 sides and a random row and column of a 16x9
  TEST(function_checks, calculate_ramped_rows_RGB_2)
  {
    RGB565 tl(0, 0, 0), tr(2, 2, 2), bl(3, 3, 3), br(4, 4, 4);
    std::vector<std::vector<RGB565>> result = Ramp::calculate_ramped_rows(tl, tr, bl, br, 16, 9);
    // far left column
    check_column(result, 0, /*@formatter:off*/{{C0},{C0},{C0,C1},{C1},{C1,C2},{C2},{C2,C3},{C3},{C3}},/*@formatter:on*/
                 " Failed to create a 16x9 grit with correct values.");
    EXPECT_TRUE(result[4][0] == C1 || (result[4][0] == C2 && result[2][0] == C1))
                  << " Failed to create a 16x9 grid with the correct [4][0] value.";
    EXPECT_TRUE(result[6][0] == C2 || (result[6][0] == C3 && result[4][0] == C2))
                  << " Failed to create a 16x9 grid with the correct [6][0] value.";
    check_row(result, 0, /*@formatter:off*/{{C0}, {C0}, {C0}, {C0}, {C0},
                                              {C0, C1}, {C1}, {C1}, {C1}, {C1}, {C1, C2},
                                              {C2}, {C2}, {C2}, {C2},{C2}}, /*@formatter:on*/
              " Failed to create a 16x9 grit with correct values."); // top row
    check_column(result, 15, {C2, C2, C2, C3, C3, C3, C4, C4, C4},
                 " Failed to create a correct 16x9 grid: far right column.");
    check_row(result, 8, {C3, C3, C3, C3, C3, C3, C3, C3, C4, C4, C4, C4, C4, C4, C4, C4},
              " Failed to create a correct 16x9 grid: bottom row.");
    check_column(result, 6, {C1, C1, C1, C2, C2, C2, C3, C3, C3}, " Failed to create a correct 16x9 grid: 7th column.");
    check_row(result, 5, {C2, C2, C2, C2, C2, C2, C2, C2, C3, C3, C3, C3, C3, C3, C3, C3},
              " Failed to create a correct 16x1 grid: 6th row.");
  }

  // check a perfect ramp 17x9
  TEST(function_checks, calculate_ramped_rows_RGB_3)
  { // check a perfect ramp 17x9
    RGB565 tl(0, 0, 0), tr(16, 16, 16), bl(16, 16, 16), br(0, 0, 0);
    std::vector<std::vector<RGB565>> result = Ramp::calculate_ramped_rows(tl, tr, bl, br, 17, 9);
    check_column(result, 0, {C0, C2, C4, C6, C8, C10, C12, C14, C16}, " Failed to create a perfect 17x9 ramped grid.");
    check_column(result, 16, {C16, C14, C12, C10, C8, C6, C4, C2, C0}, " Failed to create a perfect 17x9 ramped grid.");
    check_row(result, 0, {C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14, C15, C16},
              " Failed to create a perfect 17x9 ramped grid.");
    check_row(result, 8, {C16, C15, C14, C13, C12, C11, C10, C9, C8, C7, C6, C5, C4, C3, C2, C1, C0},
              " Failed to create a perfect 17x9 ramped grid.");
  }
}