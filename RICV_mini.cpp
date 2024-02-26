#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <bitset>

using namespace std;

// Function prototypes
string instructionToMachineCode(const string& instruction, unordered_map<string, int>& labelAddresses, int& currentAddress);
string registerToBinary(const string& reg);
string immediateToBinary(const string& imm, int bits);
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
    unordered_map<string, int> labelAddresses;
    int currentAddress = 0;
    while (getline(asmFile, line)) {
        if (line.empty() || line[0] == '#') continue; // Skip empty lines and comments

        if (line[0] == '.') {
            currentAddress += handleDirective(line, mcFile, labelAddresses, currentAddress);
        } else if (line.back() == ':') {
            labelAddresses[line.substr(0, line.size() - 1)] = currentAddress;
        } else {
            string machineCode = instructionToMachineCode(line, labelAddresses, currentAddress);
            mcFile << machineCode << endl;
            currentAddress += 4; // Assuming each instruction is 4 bytes
        }
    }

    asmFile.close();
    mcFile.close();

    cout << "Assembly completed." << endl;
    return 0;
}

string instructionToMachineCode(const string& instruction, unordered_map<string, int>& labelAddresses, int& currentAddress) {
    stringstream ss(instruction);
    string opcode, rd, rs1, rs2, imm;
    ss >> opcode;

    // Implementing the instructions as per the requirement
    unordered_map<string, string> opcodeMap = {
        {"add", "0110011"}, {"and", "0110011"}, {"or", "0110011"}, {"sll", "0110011"},
        {"slt", "0110011"}, {"sra", "0110011"}, {"sub", "0110011"}, {"xor", "0110011"},
        {"mul", "0110011"}, {"div", "0110011"}, {"rem", "0110011"}, {"addi", "0010011"},
        {"andi", "0010011"}, {"ori", "0010011"}, {"lb", "0000011"}, {"ld", "0000011"},
        {"lh", "0000011"}, {"lw", "0000011"}, {"jalr", "1100111"}, {"sb", "0100011"},
        {"sw", "0100011"}, {"sd", "0100011"}, {"sh", "0100011"}, {"beq", "1100011"},
        {"bne", "1100011"}, {"bge", "1100011"}, {"blt", "1100011"}, {"auipc", "0010111"},
        {"lui", "0110111"}, {"jal", "1101111"}
    };

    // Implementing the function type mapping
    unordered_map<string, string> funct3Map = {
        {"add", "000"}, {"and", "111"}, {"or", "110"}, {"sll", "001"},
        {"slt", "010"}, {"sra", "101"}, {"sub", "000"}, {"xor", "100"},
        {"mul", "000"}, {"div", "100"}, {"rem", "110"}, {"addi", "000"},
        {"andi", "111"}, {"ori", "110"}, {"lb", "000"}, {"ld", "011"},
        {"lh", "001"}, {"lw", "010"}, {"jalr", "000"}, {"sb", "000"},
        {"sw", "010"}, {"sd", "011"}, {"sh", "001"}, {"beq", "000"},
        {"bne", "001"}, {"bge", "101"}, {"blt", "100"}, {"auipc", ""},
        {"lui", ""}, {"jal", ""}
    };

    // Implementing the funct7 mapping
    unordered_map<string, string> funct7Map = {
        {"add", "0000000"}, {"sub", "0100000"}, {"sra", "0100000"},
        {"mul", "0000001"}, {"div", "0000001"}, {"rem", "0000001"}
    };

    // Implementing the instruction encoding
    if (opcodeMap.find(opcode) != opcodeMap.end()) {
        ss >> rd >> rs1 >> rs2;
        string funct7 = funct7Map[opcode];
        string funct3 = funct3Map[opcode];
        string opcodeBin = opcodeMap[opcode];
        return funct7 + registerToBinary(rs2) + registerToBinary(rs1) + funct3 + registerToBinary(rd) + opcodeBin;
    }

    return "ERROR: Unknown instruction";
}

string registerToBinary(const string& reg) {
    // Assuming registers are named x0 to x31
    int regNum = stoi(reg.substr(1)); // Remove the 'x' and convert to int
    return bitset<5>(regNum).to_string();
}

string immediateToBinary(const string& imm, int bits) {
    int value = stoi(imm);
    return bitset<32>(value).to_string().substr(32 - bits, bits); // Convert to binary and take the last 'bits' bits
}

int handleDirective(const string& line, ofstream& mcFile, unordered_map<string, int>& labelAddresses, int& currentAddress) {
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
