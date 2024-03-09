#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <bitset>
#include "helperFunctions.cpp"
#include "instructionTypeProcesses.cpp"

using namespace std;

vector<string> R, I, S, SB, U, UJ;                             // Sets to differentiate between different formats of commands
unordered_map<string, unordered_map<string, string>> instructionData; // Stores Pre-defined data of of all commands
unordered_map<string, int> labelAddresses;

// Function prototypes
void initializeInstructionData();
string instructionToMachineCode(const string& instruction, unordered_map<string, int>& labelAddresses, int& currentAddress);
int handleDirective(const string& line, ofstream& mcFile, unordered_map<string, int>& labelAddresses, int& currentAddress);

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input.asm> <output.mc>" << endl;
        return 1;
    }

    ifstream asmFile(argv[1]);
    ofstream mcFile(argv[2]);

    if (!asmFile.is_open() || !mcFile.is_open()) {
        cerr << "Error opening files." << endl;
        return 1;
    }

    string line;
    int currentAddress = 0;
    while(getline(asmFile, line)) {
        line = removeWhitespaces(line);

        if(line.empty() || line[0] == '#') continue; // Skip empty lines and comments
        else if (line[0] == '.') {
            currentAddress += handleDirective(line, mcFile, currentAddress);
        }else if(line.back() == ':') {
            labelAddresses[line.substr(0, line.size() - 1)] = currentAddress;
        }else{
            string machineCode = instructionToMachineCode(line, currentAddress);
            mcFile << machineCode << endl;
            currentAddress += 4; // Assuming each instruction is 4 bytes
        }
    }

    asmFile.close();
    mcFile.close();

    cout << "Assembly completed." << endl;
    return 0;
}

void initializeInstructionData() {
    instructionData["add"]["opcode"] = "0110011";
    instructionData["add"]["func3"] = "000";
    instructionData["add"]["func7"] = "0000000";
    instructionData["add"]["type"] = "R";

    instructionData["and"]["opcode"] = "0110011";
    instructionData["and"]["func3"] = "111";
    instructionData["and"]["func7"] = "0000000";
    instructionData["and"]["type"] = "R";

    instructionData["or"]["opcode"] = "0110011";
    instructionData["or"]["func3"] = "110";
    instructionData["or"]["func7"] = "0000000";
    instructionData["or"]["type"] = "R";

    instructionData["sll"]["opcode"] = "0110011";
    instructionData["sll"]["func3"] = "001";
    instructionData["sll"]["func7"] = "0000000";
    instructionData["sll"]["type"] = "R";

    instructionData["slt"]["opcode"] = "0110011";
    instructionData["slt"]["func3"] = "010";
    instructionData["slt"]["func7"] = "0000000";
    instructionData["slt"]["type"] = "R";

    instructionData["sra"]["opcode"] = "0110011";
    instructionData["sra"]["func3"] = "101";
    instructionData["sra"]["func7"] = "0100000";
    instructionData["sra"]["type"] = "R";

    instructionData["srl"]["opcode"] = "0110011";
    instructionData["srl"]["func3"] = "101";
    instructionData["srl"]["func7"] = "0000000";
    instructionData["srl"]["type"] = "R";

    instructionData["sub"]["opcode"] = "0110011";
    instructionData["sub"]["func3"] = "000";
    instructionData["sub"]["func7"] = "0100000";
    instructionData["sub"]["type"] = "R";

    instructionData["xor"]["opcode"] = "0110011";
    instructionData["xor"]["func3"] = "100";
    instructionData["xor"]["func7"] = "0000000";
    instructionData["xor"]["type"] = "R";

    instructionData["mul"]["opcode"] = "0110011";
    instructionData["mul"]["func3"] = "000";
    instructionData["mul"]["func7"] = "0000001";
    instructionData["mul"]["type"] = "R";

    instructionData["div"]["opcode"] = "0110011";
    instructionData["div"]["func3"] = "100";
    instructionData["div"]["func7"] = "0000001";
    instructionData["div"]["type"] = "R";

    instructionData["rem"]["opcode"] = "0110011";
    instructionData["rem"]["func3"] = "110";
    instructionData["rem"]["func7"] = "0000001";
    instructionData["rem"]["type"] = "R";

    instructionData["addi"]["opcode"] = "0010011";
    instructionData["addi"]["func3"] = "000";
    instructionData["addi"]["type"] = "I";

    instructionData["andi"]["opcode"] = "0010011";
    instructionData["andi"]["func3"] = "111";
    instructionData["andi"]["type"] = "I";

    instructionData["ori"]["opcode"] = "0010011";
    instructionData["ori"]["func3"] = "110";
    instructionData["ori"]["type"] = "I";

    instructionData["lb"]["opcode"] = "0000011";
    instructionData["lb"]["func3"] = "000";
    instructionData["lb"]["type"] = "I";

    instructionData["lh"]["opcode"] = "0000011";
    instructionData["lh"]["func3"] = "001";
    instructionData["lh"]["type"] = "I";

    instructionData["lw"]["opcode"] = "0000011";
    instructionData["lw"]["func3"] = "010";
    instructionData["lw"]["type"] = "I";

    instructionData["ld"]["opcode"] = "0000011";
    instructionData["ld"]["func3"] = "011";
    instructionData["ld"]["type"] = "I";

    instructionData["jalr"]["opcode"] = "1100111";
    instructionData["jalr"]["func3"] = "000";
    instructionData["jalr"]["type"] = "I";

    instructionData["sb"]["opcode"] = "0100011";
    instructionData["sb"]["func3"] = "000";
    instructionData["sb"]["type"] = "S";

    instructionData["sh"]["opcode"] = "0100011";
    instructionData["sh"]["func3"] = "001";
    instructionData["sh"]["type"] = "S";

    instructionData["sw"]["opcode"] = "0100011";
    instructionData["sw"]["func3"] = "010";
    instructionData["sw"]["type"] = "S";

    instructionData["sd"]["opcode"] = "0100011";
    instructionData["sd"]["func3"] = "011";
    instructionData["sd"]["type"] = "S";

    instructionData["beq"]["opcode"] = "1100011";
    instructionData["beq"]["func3"] = "000";
    instructionData["beq"]["type"] = "SB";

    instructionData["bne"]["opcode"] = "1100011";
    instructionData["bne"]["func3"] = "001";
    instructionData["bne"]["type"] = "SB";

    instructionData["blt"]["opcode"] = "1100011";
    instructionData["blt"]["func3"] = "100";
    instructionData["blt"]["type"] = "SB";

    instructionData["bge"]["opcode"] = "1100011";
    instructionData["bge"]["func3"] = "101";
    instructionData["bge"]["type"] = "SB";

    instructionData["auipc"]["opcode"] = "0010111";
    instructionData["auipc"]["type"] = "U";

    instructionData["lui"]["opcode"] = "0110111";
    instructionData["lui"]["type"] = "U";

    instructionData["jal"]["opcode"] = "1101111";
    instructionData["jal"]["type"] = "UJ";

}

string instructionToMachineCode(const string& instruction, int& currentAddress) {
    stringstream ss(instruction);
    string inst;
    ss >> inst;

    string instructionCode = "";

    if(instructionData[inst]["type"] == "R") instructionCode = processRType(instruction);
    else if(instructionData[inst]["type"] == "I") instructionCode = processIType(instruction);
    else if(instructionData[inst]["type"] == "S") instructionCode = processSType(instruction);
    else if(instructionData[inst]["type"] == "SB") instructionCode = processSBType(instruction);
    else if(instructionData[inst]["type"] == "U") instructionCode = processUType(instruction);
    else if(instructionData[inst]["type"] == "UJ") instructionCode = processUJType(instruction);
    else {
        cerr << "ERROR: Unknown instruction '" << inst << "'" << endl;
        return "";
    }
    
    return "0x" + decimalToHexadecimal(currentAddress) + " " + instructionCode;
}

int handleDirective(const string& line, ofstream& mcFile, int& currentAddress) {
    stringstream ss(line);
    string directive;
    ss >> directive; // Extract the directive from the line

    if (directive == ".word") {
        // Handle the .word directive which defines a word of data
        int value;
        while (ss >> value) { // Read all values defined by this directive
            mcFile.write(reinterpret_cast<const char*>(&value), sizeof(value)); // Write the value as binary data
            currentAddress += 4; // Increase the address by the size of a word
        }
    } else if (directive == ".byte") {
        // Handle the .byte directive which defines a byte of data
        int value;
        while (ss >> value) {
            char byteValue = static_cast<char>(value);
            mcFile.write(&byteValue, sizeof(byteValue)); // Write the byte value
            currentAddress += 1; // Increase the address by the size of a byte
        }
    } else if (directive == ".half") {
        // Handle the .half directive which defines a halfword (2 bytes) of data
        int value;
        while (ss >> value) {
            short halfValue = static_cast<short>(value);
            mcFile.write(reinterpret_cast<const char*>(&halfValue), sizeof(halfValue)); // Write the halfword value
            currentAddress += 2; // Increase the address by the size of a halfword
        }
    } else if (directive == ".text") {
        // This directive might be used to indicate the start of the text (code) section
        // For simplicity, we do not handle it here but acknowledge its presence
    } else if (directive == ".data") {
        // This directive indicates the start of the data section
        // Set the current address to the start of the data segment
        currentAddress = 0x10000000;
    } else {
        cerr << "ERROR: Unknown directive '" << directive << "'" << endl;
        return -1; // Return an error code for unknown directive
    }

    return 0; // Return success code
}
