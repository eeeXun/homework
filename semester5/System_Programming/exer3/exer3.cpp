#include <ctype.h>
#include <iostream>
#include <stdio.h>
using namespace std;

#define labelSTART 0
#define labelLen 8
#define opcodeSTART 9
#define opcodeLen 6
#define operandSTART 17
#define operandLen 18

int main()
{
    string input, label, opcode, operand;
    string label_out, opcode_out, operand_out;
    int inputLen;
    int is_operand, firstQuote, isChar;
    while (getline(cin, input)) {
        label_out.clear();
        opcode_out.clear();
        operand_out.clear();
        // label
        label = input.substr(labelSTART, labelLen);
        if (label.at(0) == '.')
            continue;
        else {
            for (int i = 0; i < labelLen; i++) {
                if (label.at(i) != ' ')
                    label_out += (char)toupper(label.at(i));
            }
            printf("%-8s ", label_out.c_str());
        }
        // opcode
        opcode = input.substr(opcodeSTART, opcodeLen);
        inputLen = input.length() - opcodeSTART;
        for (int i = 0; i < opcodeLen && i < inputLen; i++) {
            if (opcode.at(i) != ' ')
                opcode_out += (char)toupper(opcode.at(i));
        }
        if (opcode_out.length() >= 4
            && (opcode_out.at(0) == 'r' || opcode_out.at(0) == 'R')
            && (opcode_out.at(1) == 's' || opcode_out.at(1) == 'S')
            && (opcode_out.at(2) == 'u' || opcode_out.at(2) == 'U')
            && (opcode_out.at(3) == 'b' || opcode_out.at(3) == 'B')) {
            printf("RSUB\n");
            continue;
        } else {
            printf("%-6s  ", opcode_out.c_str());
        }
        // operand
        operand = input.substr(operandSTART, operandLen);
        inputLen = input.length() - operandSTART;
        is_operand = 0;
        firstQuote = 1;
        isChar = 0;
        for (int i = 0; i < operandLen && i < inputLen; i++) {
            if (operand.at(i) != ' ') {
                is_operand = 1;
                if (operand.at(i) == '\'' && firstQuote
                    && (operand.at(i - 1) == 'C' || operand.at(i - 1) == 'c')) {
                    firstQuote = 0;
                    isChar = 1;
                    operand_out += '\'';
                } else if (isChar) {
                    operand_out += operand.at(i);
                } else {
                    operand_out += (char)toupper(operand.at(i));
                }
            } else if (is_operand && operand.at(i) == ' ')
                break;
        }
        printf("%s\n", operand_out.c_str());
    }
}
