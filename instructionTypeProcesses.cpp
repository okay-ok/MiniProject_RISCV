#include <iostream>
#include <string>
#include <sstream>
#include <bits/stdc++.h>
#include "helperFunctions.h"

using namespace std;

string processRType(string instruction, unordered_map<string, string>& opcodeData, unordered_map<string, string>& func3Data, unordered_map<string, string>& func7Data, unordered_map<string, int>& labelAddresses){
    stringstream ss(instruction);
    string inst;
    ss >> inst;

    string opcode, rd, funct3, rs1, rs2, funct7;

    ss >> rd >> rs1 >> rs2;
    opcode = opcodeData[inst];
    funct3 = func3Data[inst];
    funct7 = func7Data[inst];

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
    imm=immediateToBinary(imm, 12);
    string machineCode = imm + registerToBinary(rs1) + funct3 + registerToBinary(rd) + opcode;
    return binaryToHexadecimal(machineCode);

}

string processSType(string instruction, unordered_map<string,  string>& opcodeData,unordered_map<string,  string>& func3Data,unordered_map<string,  string>& func7Data, unordered_map<string, int>& labelAddresses){
    
        stringstream ss(instruction);
        string inst;
        ss >> inst;

        string opcode, funct3, rs1, rs2, imm;

        ss >> rs1 >> rs2;

        // Check if rs2 contains parenthesis offset
        if (rs2.find('(') != string::npos) {
            // Extract the offset and register from rs2
            string offset = rs2.substr(0, rs2.find('('));
            string registerName = rs2.substr(rs2.find('(') + 1, rs2.find(')') - rs2.find('(') - 1);

            // Remove the parenthesis offset from rs2
            rs2 = registerName;
            imm = immediateToBinary(offset, 12);
        } else {
            ss >> imm;
            imm = immediateToBinary(imm, 12);
        }

        opcode = opcodeData[inst];
        funct3 = func3Data[inst];

        string imm1 = imm.substr(0, 7);
        string imm2 = imm.substr(7, 5);
        string machineCode = imm1 + registerToBinary(rs1) + registerToBinary(rs2) + funct3 + imm2 + opcode;
        return binaryToHexadecimal(machineCode);
}

string processSBType(string instruction, unordered_map<string,  string>& opcodeData,unordered_map<string,  string>& func3Data,unordered_map<string,  string>& func7Data, unordered_map<string, int>& labelAddresses, int currentAddress){
    stringstream ss(instruction);
    string inst;
    ss >> inst;

    string opcode, funct3, rs1, rs2, imm;

    ss >> rs1 >> rs2 >> imm;
    opcode = opcodeData[inst];
    funct3 = func3Data[inst];

    imm=immediateToBinary(to_string(labelAddresses[imm] - currentAddress), 13);
    string imm1 = imm.substr(0, 1);
    string imm2 = imm.substr(8, 4);
    string imm3 = imm.substr(2, 6);
    string imm4 = imm.substr(1, 1);
    string machineCode = imm1 + imm3 + registerToBinary(rs1) + registerToBinary(rs2) + funct3 + imm2 + imm4 + opcode;
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

string processUJType(string instruction, unordered_map<string,  string>& opcodeData,unordered_map<string,  string>& func3Data,unordered_map<string,  string>& func7Data, unordered_map<string, int>& labelAddresses, int currentAddress){
    stringstream ss(instruction);
    string inst;
    ss >> inst;

    string opcode, rd, imm;

    ss >> rd >> imm;
    opcode = opcodeData[inst];
    imm = immediateToBinary(to_string(labelAddresses[imm] - currentAddress), 21);
    string imm1 = imm.substr(0, 1);
    string imm2 = imm.substr(1, 8);
    string imm3 = imm.substr(9, 1);
    string imm4 = imm.substr(10, 10);
    string machineCode = imm1 + imm4 + imm3 + imm2 + registerToBinary(rd) + opcode;
    return binaryToHexadecimal(machineCode);
}

string instructionToMachineCode(string instruction, int currentAddress, unordered_map<string,  string>& opcodeData, unordered_map<string,  string>& func3Data, unordered_map<string,  string>& func7Data, unordered_map<string, int>& labelAddresses, unordered_map<string,string>instructionTypeData) {
    stringstream ss(instruction);
    string inst;
    ss >> inst;

    string instructionCode = "";

    if(instructionTypeData[inst] == "R") instructionCode = processRType(instruction, opcodeData, func3Data, func7Data, labelAddresses);
    else if(instructionTypeData[inst]== "I") instructionCode = processIType(instruction, opcodeData, func3Data, func7Data, labelAddresses);  
    else if(instructionTypeData[inst] == "S") instructionCode = processSType(instruction, opcodeData, func3Data, func7Data, labelAddresses);
    else if(instructionTypeData[inst] == "SB") instructionCode = processSBType(instruction, opcodeData, func3Data, func7Data, labelAddresses, currentAddress);
    else if(instructionTypeData[inst] == "U") instructionCode = processUType(instruction, opcodeData, func3Data, func7Data, labelAddresses);
    else if(instructionTypeData[inst] == "UJ") instructionCode = processUJType(instruction, opcodeData, func3Data, func7Data, labelAddresses, currentAddress);
    else {
        cerr << "ERROR: Unknown instruction '" << inst << "'" << endl;
        return "";
    }

    return "0x" + decimalToHexadecimal(currentAddress) + " 0x" + instructionCode;
}
