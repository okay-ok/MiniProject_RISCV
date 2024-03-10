#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <sstream>
#include <helperFunctions.cpp>

using namespace std;

void handleDirectives(string instruction, vector<string>& staticMemory){
    stringstream ss(instruction);
    string directive;
    ss >> directive;

    int num;
    string hex;
    if(directive == ".asciiz"){
        string data;
        ss >> data;

        for(int i = 1; i < data.length() - 1; i++){
            num = data[i];
            hex = decimalToHexadecimal(num);
            staticMemory.push_back(hex);
        }
        staticMemory.push_back("00");
    }else if(directive == ".word"){
        while (ss >> num) {
            num = num%(1 << 32);
            hex = decimalToHexadecimal(num);
            for(int j = 0; j < 4; j++){
                staticMemory.push_back(hex.substr(j * 2, 2));
            }
        }
    }else if(directive == ".half"){
        while (ss >> num) {
            num = num%(1 << 16);
            hex = decimalToHexadecimal(num);
            for(int j = 0; j < 2; j++){
                staticMemory.push_back(hex.substr(j * 2, 2));
            }
        }
    }else if(directive == ".byte"){
        while (ss >> num) {
            num = num%(1 << 8);
            hex = decimalToHexadecimal(num);
            staticMemory.push_back(hex);
        }
    }else if(directive == ".dword"){
        long long num;
        num = num%(1 << 64);
        while (ss >> num) {
            hex = decimalToHexadecimal(num);
            for(int j = 0; j < 8; j++){
                staticMemory.push_back(hex.substr(j * 2, 2));
            }
        }
    }
}
