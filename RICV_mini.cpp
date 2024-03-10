#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <bitset>
#include "helperFunctions.h"
#include "directiveProcesses.cpp"
#include "instructionTypeProcesses.cpp"

using namespace std;

#define MEMORY_START_LOCATION 268435456

unordered_map<string, unordered_map<string, string>> instructionData; // Stores Pre-defined data of of all commands
unordered_map<string, int> labelAddresses;                     // Stores the address of all labels
vector<string> staticMemory;                               // Stores the static memory data

// Function prototypes
void initializeInstructionData();

int main(int argc, char* argv[]) 
{
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
            if(colonIndex != string::npos)
            {
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
        currentAddress++;
    }

    asmFile.close();
    mcFile.close();

    cout << "Assembly completed." << endl;
    return 0;
}
 unordered_map<string, string> opcodeData;
    unordered_map<string, string> func3Data;
    unordered_map<string, string> func7Data;
void initializeInstructionData() {
   

    opcodeData["add"] = "0110011";
    opcodeData["and"] = "0110011";
    opcodeData["or"] = "0110011";
    opcodeData["sll"] = "0110011";
    opcodeData["slt"] = "0110011";
    opcodeData["sra"] = "0110011";
    opcodeData["srl"] = "0110011";
    opcodeData["sub"] = "0110011";
    opcodeData["xor"] = "0110011";
    opcodeData["mul"] = "0110011";
    opcodeData["div"] = "0110011";
    opcodeData["rem"] = "0110011";
    opcodeData["addi"] = "0010011";
    opcodeData["andi"] = "0010011";
    opcodeData["ori"] = "0010011";
    opcodeData["lb"] = "0000011";
    opcodeData["lh"] = "0000011";
    opcodeData["lw"] = "0000011";
    opcodeData["ld"] = "0000011";
    opcodeData["jalr"] = "1100111";
    opcodeData["sb"] = "0100011";
    opcodeData["sh"] = "0100011";
    opcodeData["sw"] = "0100011";
    opcodeData["sd"] = "0100011";
    opcodeData["beq"] = "1100011";
    opcodeData["bne"] = "1100011";
    opcodeData["blt"] = "1100011";
    opcodeData["bge"] = "1100011";
    opcodeData["auipc"] = "0010111";
    opcodeData["lui"] = "0110111";
    opcodeData["jal"] = "1101111";

    func3Data["add"] = "000";
    func3Data["and"] = "111";
    func3Data["or"] = "110";
    func3Data["sll"] = "001";
    func3Data["slt"] = "010";
    func3Data["sra"] = "101";
    func3Data["srl"] = "101";
    func3Data["sub"] = "000";
    func3Data["xor"] = "100";
    func3Data["mul"] = "000";
    func3Data["div"] = "100";
    func3Data["rem"] = "110";
    func3Data["addi"] = "000";
    func3Data["andi"] = "111";
    func3Data["ori"] = "110";
    func3Data["lb"] = "000";
    func3Data["lh"] = "001";
    func3Data["lw"] = "010";
    func3Data["ld"] = "011";
    func3Data["jalr"] = "000";
    func3Data["sb"] = "000";
    func3Data["sh"] = "001";
    func3Data["sw"] = "010";
    func3Data["sd"] = "011";
    func3Data["beq"] = "000";
    func3Data["bne"] = "001";
    func3Data["blt"] = "100";
    func3Data["bge"] = "101";
    func3Data["auipc"] = "";
    func3Data["lui"] = "";
    func3Data["jal"] = "";

    func7Data["add"] = "0000000";
    func7Data["and"] = "0000000";
    func7Data["or"] = "0000000";
    func7Data["sll"] = "0000000";
    func7Data["slt"] = "0000000";
    func7Data["sra"] = "0100000";
    func7Data["srl"] = "0000000";
    func7Data["sub"] = "0100000";
    func7Data["xor"] = "0000000";
    func7Data["mul"] = "0000001";
    func7Data["div"] = "0000001";
    func7Data["rem"] = "0000001";
    func7Data["addi"] = "";
    func7Data["andi"] = "";
    func7Data["ori"] = "";
    func7Data["lb"] = "";
    func7Data["lh"] = "";
    func7Data["lw"] = "";
    func7Data["ld"] = "";
    func7Data["jalr"] = "";
    func7Data["sb"] = "";
    func7Data["sh"] = "";
    func7Data["sw"] = "";
    func7Data["sd"] = "";
    func7Data["beq"] = "";
    func7Data["bne"] = "";
    func7Data["blt"] = "";
    func7Data["bge"] = "";
    func7Data["auipc"] = "";
    func7Data["lui"] = "";
    func7Data["jal"] = "";



}

