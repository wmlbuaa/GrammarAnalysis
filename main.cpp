#pragma warning(disable:4996)

#include <iostream>
#include <windows.h>
#include <unordered_map>
#include "FileIO.h"
#include "lib.h"
#include "PCodeGenerate.h"
#include "MipsGenerate.h"
#include "Exception.h"

using namespace std;


int main() {
    ExpInit();
    pcode_num = 0;
    ReadFromFile();
    SymPrint();
    PCodePrint();
    WriteMipsFile();
    getchar();
    getchar();
    return 0;
}