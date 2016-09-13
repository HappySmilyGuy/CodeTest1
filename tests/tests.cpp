#include "RGB565_tests.h"
#include "functions_tests.h"

int main()
{
  Ramp::Test::FunctionsTests::test_all();
  Ramp::Test::RGB565Tests::test_all();
  return 0;
}