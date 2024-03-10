#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <bitset>
#include "directiveProcesses.cpp"
#include "helperFunctions.cpp"
#include "instructionTypeProcesses.cpp"

using namespace std;

#define MEMORY_START_LOCATION 268435456

unordered_map<string, unordered_map<string, string>> instructionData; // Stores Pre-defined data of of all commands
unordered_map<string, int> labelAddresses;                     // Stores the address of all labels
vector<string> staticMemory;                               // Stores the static memory data

// Function prototypes
void initializeInstructionData();

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

    initializeInstructionData();

    string line;
    int currentAddress = 0;
    bool isText = true;
    while(getline(asmFile, line)) {
        line = cleanInputLine(line);

        if(line.empty() || line[0] == '#') continue; // Skip empty lines and comments
        else if (line == ".text") {
            isText = true;
            continue;
        }else if (line == ".data") {
            isText = false;
            continue;
        }

        if(isText){
            int colonIndex = line.find(':');
            if(colonIndex != string::npos){
                labelAddresses[line.substr(0, colonIndex)] = currentAddress;
                line = line.substr(colonIndex + 1);
            }

            line = removeWhitespaces(line);
            if(line.empty()) continue;
            
            string machineCode = instructionToMachineCode(line, currentAddress, instructionData, labelAddresses);
            mcFile << machineCode << endl;

            currentAddress += 4;
        }else{
            // TODO: Handle label --------------------------------------------------------------------------------------------------------
            handleDirectives(line, staticMemory);
        }
    }

    mcFile << "0x" << decimalToHexadecimal(currentAddress) << " 00" << endl; // Halt instruction at the end
    
    currentAddress = MEMORY_START_LOCATION;
    for (auto& data : staticMemory) {
        mcFile << "0x" << decimalToHexadecimal(currentAddress) << " 0x" << data << endl;
        currentAddress += 4;
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

