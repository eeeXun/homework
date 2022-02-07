#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;

#define LABEL_START 0
#define LABEL_LEN 8
#define OPCODE_START 9
#define OPCODE_LEN 6
#define OPERAND_START 17
#define BYTE1 1
#define BYTE3 3
struct SYB {
    string name;
    int loc;
    int loc_end;
};
vector<SYB> syb_list;

string get_label(string s);
string get_opcode(string s);
string get_operand(string s);

int main()
{
    int loc;
    string input;
    string label, opcode, operand;
    SYB syb;
    FILE* fp;
    fp = fopen("INTFILE", "w");
    getline(cin, input);
    loc = stoi(get_operand(input), 0, 16);
    fprintf(fp, "%.6X %s\n", loc, input.c_str());
    // START
    label = get_label(input);
    syb.name = label;
    syb.loc = loc;
    syb_list.push_back(syb);
    while (getline(cin, input)) {
        fprintf(fp, "%.6X %s\n", loc, input.c_str());
        label = get_label(input);
        opcode = get_opcode(input);
        if (opcode.compare("RSUB") == 0) {
            loc += BYTE3;
        } else {
            // SYMTAB
            if (!label.empty()) {
                syb.name = label;
                syb.loc = loc;
                syb_list.push_back(syb);
            }
            // calculate loc
            operand = get_operand(input);
            if (opcode.compare("RESB") == 0)
                loc += BYTE1 * stoi(operand);
            else if (opcode.compare("RESW") == 0)
                loc += BYTE3 * stoi(operand);
            else if (opcode.compare("BYTE") == 0 && operand.at(0) == 'C')
                loc += BYTE1 * operand.length() - 3;
            else if (opcode.compare("BYTE") == 0 && operand.at(0) == 'X')
                loc += BYTE1 * (operand.length() - 3) / 2;
            else if (opcode == "END")
                syb_list.at(0).loc_end = (loc - syb_list.at(0).loc);
            else
                loc += BYTE3;
        }
    }
    fclose(fp);
    // write SYMTAB
    fp = fopen("SYMTAB", "w");
    for (int i = 0; i < syb_list.size(); i++) {
        if (i == 0)
            fprintf(fp, "%-6s %.6X %.6X\n", syb_list.at(0).name.c_str(),
                syb_list.at(0).loc, syb_list.at(0).loc_end);
        else
            fprintf(fp, "%-6s %.6X\n", syb_list.at(i).name.c_str(),
                syb_list.at(i).loc);
    }
    fclose(fp);
}

string get_label(string s)
{
    s = s.substr(LABEL_START, LABEL_LEN);
    s = s.substr(0, s.find(' '));

    return s;
}

string get_opcode(string s)
{
    s = s.substr(OPCODE_START, OPCODE_LEN);
    s = s.substr(0, s.find(' '));

    return s;
}

string get_operand(string s)
{
    s = s.substr(OPERAND_START, s.length() - OPERAND_START);

    return s;
}
