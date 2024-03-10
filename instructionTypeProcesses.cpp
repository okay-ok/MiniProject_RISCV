#include <iostream>
#include <string>
#include <sstream>
#include <bits/stdc++.h>
#include "helperFunctions.h"

using namespace std;

string processRType(string instruction, unordered_map<string,unordered_map<string,  string>& opcodeData,unordered_map<string,  string>& func3Data,unordered_map<string,  string>& func7Data, unordered_map<string, int>& labelAddresses){
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

string processIType(string instruction, unordered_map<string,  string>& opcodeData,unordered_map<string,  string>& func3Data,unordered_map<string,  string>& func7Data, unordered_map<string, int>& labelAddresses){

    stringstream ss(instruction);
    string inst;
    ss >> inst;

    string opcode, rd, funct3, rs1, imm;

    ss >> rd >> rs1 >> imm;
    opcode = opcodeData[inst];
    funct3 = func3Data[inst];
    imm=immediateToBinary(imm);
    string machineCode = imm + registerToBinary(rs1) + funct3 + registerToBinary(rd) + opcode;
    return binaryToHexadecimal(machineCode);

}

string processSType(string instruction, unordered_map<string,  string>& opcodeData,unordered_map<string,  string>& func3Data,unordered_map<string,  string>& func7Data, unordered_map<string, int>& labelAddresses){
    
        stringstream ss(instruction);
        string inst;
        ss >> inst;
    
        string opcode, funct3, rs1, rs2, imm;
    
        ss >> rs1 >> rs2 >> imm;
        opcode = opcodeData[inst];
        funct3 = func3Data[inst];
        imm=immediateToBinary(imm);
        string imm1 = imm.substr(0, 7);
        string imm2 = imm.substr(7, 5);
        string machineCode = imm1 + registerToBinary(rs2) + registerToBinary(rs1) + funct3 + imm2 + opcode;
        return binaryToHexadecimal(machineCode);
}

string processSBType(string instruction, unordered_map<string,  string>& opcodeData,unordered_map<string,  string>& func3Data,unordered_map<string,  string>& func7Data, unordered_map<string, int>& labelAddresses){
    stringstream ss(instruction);
    string inst;
    ss >> inst;

    string opcode, funct3, rs1, rs2, imm;

    ss >> rs1 >> rs2 >> imm;
    opcode = opcodeData[inst];
    funct3 = func3Data[inst];
    imm=immediateToBinary(imm);
    string imm1 = imm.substr(0, 1);
    string imm2 = imm.substr(1, 4);
    string imm3 = imm.substr(5, 6);
    string imm4 = imm.substr(11, 1);
    string machineCode = imm1 + imm3 + registerToBinary(rs2) + registerToBinary(rs1) + funct3 + imm2 + imm4 + opcode;
    return binaryToHexadecimal(machineCode);
}

string processUType(string instruction, unordered_map<string,  string>& opcodeData,unordered_map<string,  string>& func3Data,unordered_map<string,  string>& func7Data, unordered_map<string, int>& labelAddresses){
    
        stringstream ss(instruction);
        string inst;
        ss >> inst;
    
        string opcode, rd, imm;
    
        ss >> rd >> imm;
        opcode = opcodeData[inst];
        imm=immediateToBinary(imm, 20);
        string machineCode = imm + registerToBinary(rd) + opcode;
        return binaryToHexadecimal(machineCode);
}

string processUJType(string instruction,unordered_map<string,  string>& opcodeData,unordered_map<string,  string>& func3Data,unordered_map<string,  string>& func7Data, unordered_map<string, int>& labelAddresses){
    stringstream ss(instruction);
    string inst;
    ss >> inst;

    string opcode, rd, imm;

    ss >> rd >> imm;
    opcode = opcodeData[inst];
    imm = immediateToBinary(labelAddresses[imm] - 4, 20);
    string imm1 = imm.substr(0, 1);
    string imm2 = imm.substr(1, 8);
    string imm3 = imm.substr(9, 1);
    string imm4 = imm.substr(10, 10);
    string machineCode = imm1 + imm4 + imm3 + imm2 + registerToBinary(rd) + opcode;
    return binaryToHexadecimal(machineCode);
}

string instructionToMachineCode(string instruction, int currentAddress, unordered_map<string,  string>& opcodeData,unordered_map<string,  string>& func3Data,unordered_map<string,  string>& func7Data, unordered_map<string, int>& labelAddresses) {
    stringstream ss(instruction);
    string inst;
    ss >> inst;

    string instructionCode = "";
//god!
    if(opcodeData[inst] == "0110011") instructionCode = processRType(instruction, instructionData);
    else if(opcodeData[inst]== "0000011") instructionCode = processIType(instruction, instructionData);
    else if(opcodeData[inst] == "0100011") instructionCode = processSType(instruction, instructionData);
    else if(opcodeData[inst] == "1100011") instructionCode = processSBType(instruction, instructionData);
    else if(opcodeData[inst] == "0110111") instructionCode = processUType(instruction, instructionData);
    else if(opcodeData[inst] == "1101111") instructionCode = processUJType(instruction, instructionData);
    else {
        cerr << "ERROR: Unknown instruction '" << inst << "'" << endl;
        return "";
    }
    
    return "0x" + decimalToHexadecimal(currentAddress) + " " + instructionCode;
}
