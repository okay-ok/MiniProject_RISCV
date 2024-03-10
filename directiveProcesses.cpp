#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <sstream>
#include "helperFunctions.h"

using namespace std;

void handleDirectives(string instruction, vector<string>& staticMemory){
    stringstream ss(instruction);
    string directive;
    ss >> directive;

    int num;
    string hex;
    if(directive == ".asciiz"){
        instruction = instruction.substr(instruction.find_first_of('"') + 1, instruction.find_last_of('"') - instruction.find_first_of('"') - 1);
        // cout<<instruction<<endl;
        for(int i = 0; i < instruction.length(); i++){
            num = instruction[i];
            hex = decimalToHexadecimal(num);
            staticMemory.push_back(hex.substr(6, 2));
        }
        staticMemory.push_back("00");
    }else if(directive == ".word"){
        while (ss >> num) {
            hex = decimalToHexadecimal(num);
            for(int j = 3; j >= 0; j--){
                staticMemory.push_back(hex.substr(j * 2, 2));
            }
        }
    }else if(directive == ".half"){
        while (ss >> num) {
            hex = decimalToHexadecimal(num);
            for(int j = 3; j >= 2; j--){
                staticMemory.push_back(hex.substr(j * 2, 2));
            }
        }
    }else if(directive == ".byte"){
        while (ss >> num) {
            hex = decimalToHexadecimal(num);
            staticMemory.push_back(hex);
        }
    }else if(directive == ".dword"){
        long long num;
        while (ss >> num) {
            hex = longDecimalToHexadecimal(num);
            for(int j = 7; j >= 0; j--){
                staticMemory.push_back(hex.substr(j * 2, 2));
            }
        }
    }
}
