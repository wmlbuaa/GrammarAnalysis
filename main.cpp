#pragma warning(disable:4996)

#include <iostream>
#include <windows.h>
#include <unordered_map>
#include "FileIO.h"
#include "lib.h"
#include "PCodeGenerate.h"

using namespace std;


int main() {//C:\\Users\\wml\\CLionProjects\\GrammarAnalysis\\helloworld.txt
    pcode_num = 0;
    ReadFromFile();
    SymPrint();
    cout << "-------------------------------" << endl;
    PCodePrint();
    system("pause");
    return 0;
}