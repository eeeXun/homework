#include <cstring>
#include <fstream>
#include <iomanip>
#include <map>
#include <stdio.h>
using namespace std;

#define LOC_START 0
#define LOC_LEN 6
#define LABEL_START 7
#define LABEL_LEN 8
#define OPCODE_START 16
#define OPCODE_LEN 6
#define OPERAND_START 24
#define TEXT_MAX 60
#define POW_2_15 (1 << 15)
map<string, string> op_table;
map<string, string> symtab;

string get_loc(string s);
string get_opcode(string s);
string get_operand(string s);
string process_byte(string operand);
string process_word(string operand);
string get_operand_obj(string operand);
void add_text_record(
    string& output, string obj_code, string& text_start, string loc);
void op_table_init();

int main()
{
    op_table_init();
    ifstream fp;
    // SYMTAB
    string label, loc_start, loc_end, loc;
    fp.open("SYMTAB");
    fp >> label >> loc_start >> loc_end;
    printf("H%-6s%s%s\n", label.c_str(), loc_start.c_str(), loc_end.c_str());
    while (fp >> label >> loc)
        symtab[label] = loc.substr(2, 4);
    fp.close();
    // INTFILE
    string line;
    string opcode, operand;
    string output;
    string text_start;
    output.clear();
    fp.open("INTFILE");
    // read START
    getline(fp, line);
    // read following
    while (getline(fp, line)) {
        loc = get_loc(line);
        if (output.empty()) {
            text_start = loc;
        }
        opcode = get_opcode(line);
        if (opcode.compare("END") == 0) {
            printf("T%s%.2X%s\nE%s\n", text_start.c_str(), output.length() / 2,
                output.c_str(), loc_start.c_str());
        } else if (opcode.compare("RSUB") == 0) {
            add_text_record(output, op_table[opcode] + "0000", text_start, loc);
        } else {
            operand = get_operand(line);
            if (opcode.compare("WORD") == 0) {
                operand = process_word(operand);
                add_text_record(output, operand, text_start, loc);
            } else if (opcode.compare("BYTE") == 0) {
                operand = process_byte(operand);
                add_text_record(output, operand, text_start, loc);
            } else if (opcode.compare("RESW") == 0
                || opcode.compare("RESB") == 0) {
                if (!output.empty())
                    printf("T%s%.2X%s\n", text_start.c_str(),
                        output.length() / 2, output.c_str());
                output.clear();
            } else {
                operand = get_operand_obj(operand);
                add_text_record(
                    output, op_table[opcode] + operand, text_start, loc);
            }
        }
    }

    return 0;
}

string get_loc(string s)
{
    s = s.substr(LOC_START, LOC_LEN);

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

string process_byte(string operand)
{
    string result;
    if (operand.at(0) == 'X')
        result = operand.substr(2, operand.length() - 3);
    else if (operand.at(0) == 'C') {
        char buf[5];
        for (int i = 2; i < operand.length() - 1; i++) {
            sprintf(buf, "%X", int(operand.at(i)));
            result.append(buf);
        }
    }

    return result;
}

// return a hex value with 6 char in string
string process_word(string operand)
{
    char buf[10];
    sprintf(buf, "%.6X", stoi(operand));

    return string(buf);
}

string get_operand_obj(string operand)
{
    if (operand.find(',') != string::npos) {
        // fix index mode
        int tmp;
        char buf[10];
        operand = operand.substr(0, operand.find(','));
        tmp = stoi(symtab[operand], 0, 16);
        sprintf(buf, "%X", tmp + POW_2_15);
        return string(buf);
    } else {
        return symtab[operand];
    }
}

void add_text_record(
    string& output, string obj_code, string& text_start, string loc)
{
    if ((output.length() + obj_code.length()) > TEXT_MAX) {
        printf("T%s%.2X%s\n", text_start.c_str(), output.length() / 2,
            output.c_str());
        output.clear();
        text_start = loc;
        output.append(obj_code);
    } else {
        output.append(obj_code);
    }
}

void op_table_init()
{
    op_table["ADD"] = "18";
    op_table["ADDF"] = "58";
    op_table["ADDR"] = "90";
    op_table["AND"] = "40";
    op_table["CLEAR"] = "B4";
    op_table["COMP"] = "28";
    op_table["COMPF"] = "88";
    op_table["COMPR"] = "A0";
    op_table["DIV"] = "24";
    op_table["DIVF"] = "64";
    op_table["DIVR"] = "9C";
    op_table["FIX"] = "C4";
    op_table["FLOAT"] = "C0";
    op_table["HIO"] = "F4";
    op_table["J"] = "3C";
    op_table["JEQ"] = "30";
    op_table["JGT"] = "34";
    op_table["JLT"] = "38";
    op_table["JSUB"] = "48";
    op_table["LDA"] = "00";
    op_table["LDB"] = "68";
    op_table["LDCH"] = "50";
    op_table["LDF"] = "70";
    op_table["LDL"] = "08";
    op_table["LDS"] = "6C";
    op_table["LDT"] = "74";
    op_table["LDX"] = "04";
    op_table["LPS"] = "D0";
    op_table["MUL"] = "20";
    op_table["MULF"] = "60";
    op_table["MULR"] = "98";
    op_table["NORM"] = "C8";
    op_table["OR"] = "44";
    op_table["RD"] = "D8";
    op_table["RMO"] = "AC";
    op_table["RSUB"] = "4C";
    op_table["SHIFTL"] = "A4";
    op_table["SHIFTR"] = "A8";
    op_table["SIO"] = "F0";
    op_table["SSK"] = "EC";
    op_table["STA"] = "0C";
    op_table["STB"] = "78";
    op_table["STCH"] = "54";
    op_table["STF"] = "80";
    op_table["STI"] = "D4";
    op_table["STL"] = "14";
    op_table["STS"] = "7C";
    op_table["STSW"] = "E8";
    op_table["STT"] = "84";
    op_table["STX"] = "10";
    op_table["SUB"] = "1C";
    op_table["SUBF"] = "5C";
    op_table["SUBR"] = "94";
    op_table["SVC"] = "B0";
    op_table["TD"] = "E0";
    op_table["TIO"] = "F8";
    op_table["TIX"] = "2C";
    op_table["TIXR"] = "B8";
    op_table["WD"] = "DC";
}
