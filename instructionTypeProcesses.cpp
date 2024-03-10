#include <iostream>
#include <string>
#include <sstream>
#include <bits/stdc++.h>

using namespace std;

string instructionToMachineCode(string instruction, int currentAddress, unordered_map<string, unordered_map<string, string>>& instructionData, unordered_map<string, int>& labelAddresses) {
    stringstream ss(instruction);
    string inst;
    ss >> inst;

    string instructionCode = "";

    if(instructionData[inst]["type"] == "R") instructionCode = processRType(instruction, instructionData);
    else if(instructionData[inst]["type"] == "I") instructionCode = processIType(instruction, instructionData);
    else if(instructionData[inst]["type"] == "S") instructionCode = processSType(instruction, instructionData);
    else if(instructionData[inst]["type"] == "SB") instructionCode = processSBType(instruction, instructionData);
    else if(instructionData[inst]["type"] == "U") instructionCode = processUType(instruction, instructionData);
    else if(instructionData[inst]["type"] == "UJ") instructionCode = processUJType(instruction, instructionData);
    else {
        cerr << "ERROR: Unknown instruction '" << inst << "'" << endl;
        return "";
    }
    
    return "0x" + decimalToHexadecimal(currentAddress) + " " + instructionCode;
}

string processRType(string instruction, unordered_map<string, unordered_map<string, string>>& instructionData){
    stringstream ss(instruction);
    string inst;
    ss >> inst;

    string opcode, rd, funct3, rs1, rs2, funct7;

    ss >> rd >> rs1 >> rs2;
    opcode = instructionData[inst]["opcode"];
    funct3 = instructionData[inst]["funct3"];
    funct7 = instructionData[inst]["funct7"];

    string machineCode = funct7 + registerToBinary(rs2) + registerToBinary(rs1) + funct3 + registerToBinary(rd) + opcode;
    return binaryToHexadecimal(machineCode);
}

string processIType(string instruction, unordered_map<string, unordered_map<string, string>>& instructionData){
    
}

string processSType(string instruction, unordered_map<string, unordered_map<string, string>>& instructionData){

}

string processSBType(string instruction, unordered_map<string, unordered_map<string, string>>& instructionData){

}

string processUType(string instruction, unordered_map<string, unordered_map<string, string>>& instructionData){

}

string processUJType(string instruction, unordered_map<string, unordered_map<string, string>>& instructionData){
    
}
