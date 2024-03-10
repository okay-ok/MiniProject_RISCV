#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include <string>

using namespace std;

string registerToBinary(std::string reg);
string immediateToBinary(std::string imm, int bits);
string decimalToHexadecimal(int decimal);
string binaryToHexadecimal(std::string binary);
string longDecimalToHexadecimal(long long decimal);
string removeCommasAndInLineConsecutiveWhitespace(std::string input);
string removeWhitespaces(std::string input);
string cleanInputLine(std::string input);

#endif // HELPER_FUNCTIONS_H