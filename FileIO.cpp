//
// Created by WML on 2018/11/20.
//
#pragma warning(disable:4996)

#include "FileIO.h"
#include "LexicalAnalysis.h"
#include "lib.h"
#include <iostream>
#include <string.h>

using namespace std;

int ReadFromFile() {
    FILE *fp;
    char str[100000];
    char mid[512];
    char path[64];
    int i = 0;
    cout << "Input file path: ";
    cin >> path;
    fp = fopen(path, "r");
    while (fgets(mid, 511, fp)) {
        strcpy(str + i * sizeof(char), mid);
        i += strlen(mid);
    }
    iden_point = str;
    line = 1;
    Program(str);
    return 0;
}