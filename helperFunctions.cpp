#include <iostream>
#include <string>
#include <bits/stdc++.h>

using namespace std;

string registerToBinary(string reg) {
    int regNum = stoi(reg.substr(1)); // Remove the 'x' and convert to int
    return bitset<5>(regNum).to_string();
}

string immediateToBinary(string imm, int bits) {
    int value = stoi(imm);
    return bitset<32>(value).to_string().substr(32 - bits, bits); // Convert to binary and take the last 'bits' bits
}

string decimalToHexadecimal(int decimal) {
    string hex;
    while (decimal > 0) {
        int remainder = decimal % 16;
        if (remainder < 10)
            hex.push_back('0' + remainder);
        else
            hex.push_back('A' + remainder - 10);
        decimal /= 16;
    }
    reverse(hex.begin(), hex.end());
    return hex;
}

string cleanInputLine(string input){
    string output = removeWhitespaces(input);
    return removeCommasAndInLineConsecutiveWhitespace(output);
}

string removeCommasAndInLineConsecutiveWhitespace(string input) {
    string output;
    for (int i = 0; i < input.length(); i++) {
        if (input[i] == ',') {
            output.push_back(' ');
        } else if (input[i] == ' ' && input[i + 1] == ' ') {
            continue;
        } else {
            output.push_back(input[i]);
        }
    }
    return output;
}

string removeWhitespaces(string input) { 
    int i = 0;
    while (input[i] == ' ') { 
        i++; 
    } 
  
    int j = input.length() - 1;
    while (j >= 0 && input[j] == ' ') {
        j--;
    }

    return input.substr(i, j + 1); 
}

