//
// Created by WML on 2018/11/20.
//

#ifndef COMPILER_LIB_H
#define COMPILER_LIB_H

#include <unordered_map>

using namespace std;

#define LABEL_CODE_BASE 1000
#define GLOBAL_CODE_BASE 100000
#define LOCAL_CODE_BASE 10000000
#define MID_CODE_BASE 50000000

struct Sym {
    int code;
    string name;
    int type;//0.int 1.char 2.void 3.string
    int dimension;//0.0 other:space
    int kind;//0.const 1.var 2.func
    int value;
    string label;
};
extern char *iden_point;
extern int line;
extern int GlobalCode;
extern int LabelCode;
extern int LocalCode;
extern int MidCode;
extern int TableNum;
extern int StringNum;
extern unordered_map<string, Sym> SymTable[64];
extern unordered_map<int, Sym> CodeIndex[64];
extern unordered_map<int, int> LoopMark;

int JumpSpace(char *str);

int SymInsert(string name, int type, int dimension, int read, string label);

int SymInsert(string name, int type, int dimension, int read, int value);

int SymInsert(string name, int type, int dimension, int read);

int SymInsert(string name, int type);

void SymPrint();

unordered_map<string, Sym>::iterator SymFind(string name);

unordered_map<int, Sym>::iterator CodeFind(int code);

void Num2Char(int num, char *str);

#endif //COMPILER_LIB_H
