#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

struct Student {
    char name[10];
    unsigned char height;
    unsigned char weight;
};

int main()
{
    ifstream ifile;
    ofstream ofile;
    string filename;
    cout << "Filename?";
    cin >> filename;
    string iname;
    int iheight, iweight;
    Student astudent;
    ifile.open(filename.c_str());
    ofile.open("student.dat");
    while (ifile >> iname >> iheight >> iweight) {
        strcpy(astudent.name, iname.c_str());
        astudent.height = (char)iheight;
        astudent.weight = (char)iweight;
        ofile.write((char*)&astudent, sizeof(astudent));
    }
    ifile.close();
    ofile.close();

    return 0;
}