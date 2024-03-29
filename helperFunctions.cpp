#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include "helperFunctions.h"

using namespace std;

string registerToBinary(string reg) {
    int regNum = stoi(reg.substr(1)); // Remove the 'x' and convert to int
    return bitset<5>(regNum).to_string();
}

string immediateToBinary(string imm, int bits) {
    int immNum = stoi(imm);
    if(bits == 12) return bitset<12>(immNum).to_string();
    else if(bits == 13) return bitset<13>(immNum).to_string();
    else if(bits == 20) return bitset<20>(immNum).to_string();
    else return bitset<21>(immNum).to_string();
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
    while (hex.size() < 8) {
        hex.insert(hex.begin(), '0');
    }
    return hex;
}

string longDecimalToHexadecimal(long long decimal) {
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
    while (hex.size() < 16) {
        hex.insert(hex.begin(), '0');
    }
    return hex;
}

string binaryToHexadecimal(string binary){
    string hex;
    for(int i = 0; i < binary.length(); i += 4){
        int decimal = 0;
        for(int j = 0; j < 4; j++){
            decimal *= 2;
            decimal += binary[i + j] - '0';
        }
        if(decimal < 10){
            hex.push_back('0' + decimal);
        }else{
            hex.push_back('A' + decimal - 10);
        }
    }
    return hex;
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

string cleanInputLine(string input){
    string output = removeWhitespaces(input);
    return removeCommasAndInLineConsecutiveWhitespace(output);
}

