#ifndef RAMP_CONSTANTS_H
#define RAMP_CONSTANTS_H

#include <string>
#include <sstream>

namespace Ramp
{
  namespace Constants
  {
    const std::string EXE_NAME = "ramp.exe";
    const std::string HELP_TEXT = "The program should be invoked by the following command line:\n\n"
                                          "C:>" + EXE_NAME + " Display tl tr [bl] [br]\n\n"
                                          "where \n"
                                          "  - Display is the name of the Display device\n"
                                          "  - tl is the top left colour value\n"
                                          "  - tr is the top right colour value\n"
                                          "  - bl is the bottom left colour value [optional, defaults to tl]\n"
                                          "  - br is the bottom right colour value [optional, defaults to tr]\n\n"
                                          "The colour values are specified as 16-bit RGB565 pixels in hex or decimal.\n"
                                          "The bits for each colour are assigned as follows:\n\n"
                                          "Bit    15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0\n"
                                          "Colour R4 R3 R2 R1 R0 G5 G4 G3 G2 G1 G0 B4 B3 B2 B1 B0\n\n"
                                          "For example, \n"
                                          "  - White is 0xffff\n"
                                          "  - Black is 0x0000\n"
                                          "  - Pure blue is 0x001f\n"
                                          "  - Pure green is 0x07e0\n"
                                          "  - Pure red is 0xf800\n\n"
                                          "The following inputs to the program are all valid:\n"
                                          "  - " + EXE_NAME + " Display 0x0 0x2\n"
                                          "  - " + EXE_NAME + " Display 65 255\n"
                                          "  - " + EXE_NAME + " Display 200 0 30\n"
                                                                                                       "  - " +
                                                             EXE_NAME + " Display 0 0 3200 1800\n";
    namespace
    {
      std::string toHexStr(const int i)
      {
        std::stringstream ss;
        ss << "0x" << std::hex << i;
        return ss.str();
      }
    }

    const unsigned short MAX_COLOUR_VAL = 0xffff;
    const unsigned int INT_FORMAT_ERROR_MSG_INPUT_POS = 16;
    const std::string INT_FORMAT_ERROR_MSG =
            "Input error at \"\":\nInput colour values must be integers between 0x0 and "
            + toHexStr(MAX_COLOUR_VAL) + " (" + std::to_string(MAX_COLOUR_VAL) + "),"
            + " in decimal (e.g. 42) or hexadecimal (e.g. 0x2A) format.\n";
    const unsigned int DEVICE_CONNECTION_FAILURE_MSG_INPUT_POS = 38;
    const std::string DEVICE_CONNECTION_FAILURE_MSG = "Unable to connect to Display device: .\n";
    const std::string TOO_FEW_CMD_ARGS_MSG = "Insufficient commandline arguments.\n";
    const std::string TOO_MANY_CMD_ARGS_MSG = "Too many commandline arguments.\n";
    const std::string HELP_SUGGESTION_MSG = "Run as \"" + Ramp::Constants::EXE_NAME + " help\" for help.\n";
  }
}

#endif //RAMP_CONSTANTS_H
