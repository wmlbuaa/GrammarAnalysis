//
// Created by WML on 2018/11/20.
//
#pragma warning(disable:4996)

#include "Exception.h"
#include "lib.h"
#include "PCodeGenerate.h"
#include <iostream>
#include <windows.h>

using namespace std;

char *excep;
int error_num = 0;
int warn_num = 0;

int Exception(char *str) {
    int process_len = JumpExp(str);
    char errormsg[255];
    for (int i = 0; i < process_len; i++) {
        errormsg[i] = *(str + i);
    }
    errormsg[process_len] = '\0';
    cout << endl << "ERROR: illegal character found: " << errormsg << "in line " << line << endl;
    return process_len;
}

void ExpInit() {
    Sym sym = {MidCode++, "error", 0, 0, 0, 0, ""};
    SymTable[0].insert(pair<string, Sym>("error", sym));
    CodeIndex[0].insert(pair<int, Sym>(sym.code, sym));
}

int JumpExp(char *str) {
    char *p = str;
    while (*p != '\n')
        p++;
    return (int) ((p - str) / sizeof(char));
}

void ConstructionLoss(char colon) {
    error_num++;
    cout << "ERROR: \"" << colon << "\"loss in line:" << line << endl;
}

void RepeatDefine(char *name) {
    error_num++;
    cout << "ERROR: repeat define for \"" << name << "\" in line " << *excep << endl;
}

void IllegalArraySpace(int space) {
    error_num++;
    cout << "ERROR: illegal array space define \"" << space << "\" in line" << *excep << endl;
}

void ValuePassExp(int num, int x, int y) {
    warn_num++;
    cout << "WARNING: illegal value pass in line " << pcode[num].address << ": From " << y << " to " << x << endl;
}

void ArrayOverflowExp(int num, int x, int y) {
    warn_num++;
    cout << "WARNING: array overflow in line " << pcode[num].address << ": #array:" << x << " loc:" << y << endl;
}

void ValueParaListError(int num, int x, int y) {
    warn_num++;
    cout << "WARNING: ValueParaList's para miss or overflow in line " << pcode[num].address << ": #Func Call:" << x
         << " Para:" << y
         << endl;
}

void ValueParaListWarn(int num, int x, int y) {
    warn_num++;
    cout << "WARNING: Type is not match in ValueParaList in line " << pcode[num].address << ": #Func Call:" << x
         << " Para:" << y
         << endl;
}

void ValueCompareExp(int num, int x, int y) {
    warn_num++;
    cout << "WARNING: illegal value type compare in line " << pcode[num].address << ": From " << y << " to " << x
         << endl;
}

void ConstChange(int num) {
    warn_num++;
    cout << "WARNING: const can't be changed in line " << pcode[num].address << endl;
}

void NaN(int num) {
    warn_num++;
    cout << "WARNING: 0 is Divisor in line " << pcode[num].address << endl;
}