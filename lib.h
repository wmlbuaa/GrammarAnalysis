//
// Created by WML on 2018/11/20.
//

#ifndef COMPILER_LIB_H
#define COMPILER_LIB_H

#include <unordered_map>

using namespace std;
struct Sym {
    int code;
    string name;
    int type;
    int dimension;//0.int 1.char 2.string
    int kind;//0.const 1.var 2.func
};
extern char *iden_point;
extern int line;
extern int LocalCode;
extern int MidCode;
extern unordered_map<string, Sym> SymTable;

int JumpSpace(char *str);

void WordExtract(char *str, char *word, int len);

int SymInsert(string name, int type, int dimension, int read);

#endif //COMPILER_LIB_H
