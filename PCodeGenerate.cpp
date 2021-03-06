//
// Created by WML on 2018/11/24.
//
#pragma warning(disable:4996)

#include "PCodeGenerate.h"
#include "lib.h"
#include "MipsGenerate.h"
#include "Exception.h"
#include <iostream>
#include <unordered_map>
#include <iterator>
#include <map>
#include <string>
#include <fstream>
#include <malloc.h>
#include <cstring>
#include <algorithm>

using namespace std;

PCode pcode[4096];
unordered_map<int, RuntimeCodeInfo> code_info;
map<int, int> Pool;
Block block[4096];
int pcode_num, store_num = 0;

void OpExchange(int op, ofstream &file);

void PCodeOptimize();

void PCodePreProcess();

void AddressAssign(int code, int *space, int *mid_code_stack);

void CodeInfoInit(int code);

void GlobalOptimize();

void RegAssign();

void BasicBlock();

void BlockFill();

void PCodeInsert(int num, int x, int y, int op, int z) {
    pcode[num].x = x;
    pcode[num].y = y;
    pcode[num].z = z;
    pcode[num].op = op;
    pcode[num].address = line;
}

void PCodePrint() {
    if (error_num > 0) {
        cout << error_num << " errors have been found, do you want to continue to generate PCode & Mips?" << endl;
        getchar();
        getchar();
    }
    RuntimeCodeInfo info = {0, 0, 1, 0, 0};
    code_info.insert(pair<int, RuntimeCodeInfo>{0, info});
    PCodeOptimize();
    PCodePreProcess();
    GlobalOptimize();
    RegAssign();
    BasicBlock();
    BlockFill();
    /*for (int i = 0; i < store_num; i++) {
        auto iter = block[i].used_reg.begin();
        cout << block[i].func << " " << block[i].addr<<endl;
        while (iter != block[i].used_reg.end()) {
            cout << iter->second << endl;
            iter++;
        }
        cout << endl;
    }*/
    const char MIPSFILE[64] = "PCode.txt\0";
    ofstream file;
    file.open(MIPSFILE, ios::out);
    for (int i = 0; i < pcode_num; i++) {
        if (pcode[i].op == NOP)
            continue;
        file << "PCode#" << i << ": ";
        if (pcode[i].x < MID_CODE_BASE && pcode[i].x >= GLOBAL_CODE_BASE)
            ZExchange(pcode[i].x, file);
        else {
            file << pcode[i].x;
        }
        file << " ";
        if (pcode[i].y < MID_CODE_BASE && pcode[i].y >= GLOBAL_CODE_BASE)
            ZExchange(pcode[i].y, file);
        else {
            if (pcode[i].y >= MID_CODE_BASE && code_info.find(pcode[i].y)->second.isValue)
                file << code_info.find(pcode[i].y)->second.value << "(" << pcode[i].y << ")";
            else
                file << pcode[i].y;
        }
        OpExchange(pcode[i].op, file);
        if (pcode[i].z < MID_CODE_BASE && pcode[i].z >= GLOBAL_CODE_BASE) {
            ZExchange(pcode[i].z, file);
        } else {
            if (pcode[i].z >= MID_CODE_BASE && code_info.find(pcode[i].z)->second.isValue)
                file << code_info.find(pcode[i].z)->second.value << "(" << pcode[i].z << ")";
            else
                file << pcode[i].z;
        }
        file << "\n";
    }
    file.close();
}

void PCodeOptimize() {
    int mid = 0;
    for (int i = 0; i < pcode_num; i++) {
        CodeInfoInit(pcode[i].x);
        CodeInfoInit(pcode[i].y);
        CodeInfoInit(pcode[i].z);
        if (pcode[i].x >= MID_CODE_BASE && pcode[i].y == 0 && pcode[i].op == PLUS && pcode[i].z >= LOCAL_CODE_BASE) {
            pcode[i].op = NOP;
            for (int j = i + 1; j < pcode_num; j++) {
                if (pcode[j].y == pcode[i].x) {
                    pcode[j].y = pcode[i].z;
                }
                if (pcode[j].z == pcode[i].x) {
                    pcode[j].z = pcode[i].z;
                }
                if (pcode[j].op == SW && pcode[j].x == pcode[i].x) {
                    pcode[j].x = pcode[i].z;
                }
                if (pcode[j].x == pcode[i].x) {
                    break;
                }
            }
        } else if (pcode[i].x >= MID_CODE_BASE && pcode[i].z == 0 && pcode[i].op == PLUS &&
                   pcode[i].y >= LOCAL_CODE_BASE) {
            pcode[i].op = NOP;
            for (int j = i + 1; j < pcode_num; j++) {
                if (pcode[j].y == pcode[i].x) {
                    pcode[j].y = pcode[i].y;
                }
                if (pcode[j].z == pcode[i].x) {
                    pcode[j].z = pcode[i].y;
                }
                if (pcode[j].op == SW && pcode[j].x == pcode[i].x) {
                    pcode[j].x = pcode[i].x;
                }
                if (pcode[j].x == pcode[i].x) {
                    break;
                }
            }
        } else if ((pcode[i].op == ADI || pcode[i].op == LCH) && pcode[i].y == 0 && pcode[i].x >= MID_CODE_BASE) {
            code_info.find(pcode[i].x)->second.value = pcode[i].z;
            code_info.find(pcode[i].x)->second.isValue = 1;
        }
        if (pcode[i].x >= MID_CODE_BASE &&
            (pcode[i].op == PLUS || pcode[i].op == SUB || pcode[i].op == MUL || pcode[i].op == DIV) &&
            code_info.find(pcode[i].y)->second.isValue &&
            code_info.find(pcode[i].z)->second.isValue) {
            int y_value = code_info.find(pcode[i].y)->second.value;
            int z_value = code_info.find(pcode[i].z)->second.value;
            if (pcode[i].op == PLUS)
                mid = y_value + z_value;
            else if (pcode[i].op == SUB)
                mid = y_value - z_value;
            else if (pcode[i].op == MUL)
                mid = y_value * z_value;
            else if (pcode[i].op == DIV) {
                if (z_value == 0) {
                    NaN(i);
                    return;
                }
                mid = y_value / z_value;
            }
            code_info.find(pcode[i].x)->second.value = mid;
            code_info.find(pcode[i].x)->second.isValue = 1;
        }
    }
}

void CodeInfoInit(int code) {
    if (code_info.find(code) != code_info.end() || code < GLOBAL_CODE_BASE)
        return;
    RuntimeCodeInfo info = {code, 0, 0, 0, 0};
    if (code >= GLOBAL_CODE_BASE && code < MID_CODE_BASE)
        info = {code, CodeFind(code)->second.type, (CodeFind(code)->second.kind == 0 ? 1 : 0),
                (CodeFind(code)->second.kind == 0 ? CodeFind(code)->second.value : 0), 0};
    code_info.insert(pair<int, RuntimeCodeInfo>{code, info});
}

void AddressAssign(int code, int *space, int *mid_code_stack) {
    if (code < LOCAL_CODE_BASE)
        return;
    *space += 1;
    code_info.find(code)->second.address = *mid_code_stack;
    *mid_code_stack += 1;
}

void PCodePreProcess() {
    int mid_code_stack = 0, space = 0, func_code = 0;
    unordered_map<int, FuncRuntime>::iterator it;
    unordered_map<int, Sym>::iterator it_code;
    for (int i = 0; i < pcode_num; i++) {
        if (pcode[i].op == NOP)
            continue;
        if (pcode[i].op == LABEL && pcode[i].z >= LOCAL_CODE_BASE && pcode[i].z < MID_CODE_BASE) {
            mid_code_stack = 0;
            if (func_code != 0) {
                it_code = CodeFind(func_code);
                FuncRuntime funcRuntime = {it_code->second.name, func_code, space};
                RuntimeStack.insert(pair<int, FuncRuntime>(func_code, funcRuntime));
            }
            func_code = pcode[i].z;
            space = 0;
            continue;
        }
        AddressAssign(pcode[i].x, &space, &mid_code_stack);
        AddressAssign(pcode[i].y, &space, &mid_code_stack);
        AddressAssign(pcode[i].z, &space, &mid_code_stack);
        if (pcode[i].op == LDA && CodeFind(pcode[i].y)->second.type == 1 && pcode[i].x >= MID_CODE_BASE)
            code_info.find(pcode[i].x)->second.type = 1;
        else if (pcode[i].op == PLUS && pcode[i].x >= MID_CODE_BASE && pcode[i].y == 0 &&
                 ((pcode[i].z >= MID_CODE_BASE && code_info.find(pcode[i].z)->second.type == 1) ||
                  (pcode[i].z < MID_CODE_BASE && pcode[i].z >= GLOBAL_CODE_BASE &&
                   CodeFind(pcode[i].z)->second.type == 1)))
            code_info.find(pcode[i].x)->second.type = 1;
        else if (pcode[i].op == CALL && pcode[i].x != 0)
            code_info.find(pcode[i].x)->second.type = CodeFind(pcode[i].z)->second.type;
        else if (pcode[i].op == LCH && pcode[i].x >= MID_CODE_BASE)
            code_info.find(pcode[i].x)->second.type = 1;
        if ((pcode[i].op == LDA || pcode[i].op == SW) && code_info.find(pcode[i].z)->second.isValue &&
            (code_info.find(pcode[i].z)->second.value >= CodeFind(pcode[i].y)->second.dimension ||
             code_info.find(pcode[i].z)->second.value < 0))
            ArrayOverflowExp(i, pcode[i].y, pcode[i].z);
        else if (pcode[i].op == PLUS && pcode[i].y == 0 &&
                 code_info.find(pcode[i].x)->second.type != code_info.find(pcode[i].z)->second.type)
            ValuePassExp(i, pcode[i].x, pcode[i].z);
        else if (pcode[i].op == CALL) {
            int call_start = i, begin_num = 0, call = 0, func_define = 0, isPara = 1;
            while (begin_num != 1) {
                if (pcode[call_start].op == OVER)
                    begin_num--;
                else if (pcode[call_start].op == BEGIN)
                    begin_num++;
                call_start--;
            }
            while (!(pcode[func_define].op == LABEL && pcode[func_define].z == pcode[i].z)) {
                func_define++;
            }
            for (call = call_start + 1, begin_num = 0; call < i; call++) {
                if (pcode[call].op == BEGIN)
                    begin_num++;
                else if (pcode[call].op == OVER)
                    begin_num--;
                if (begin_num == 1 && pcode[call].op == PUSH) {
                    func_define++;
                    if (pcode[func_define].op == PARA) {
                        if (code_info.find(pcode[func_define].z)->second.type !=
                            code_info.find(pcode[call].z)->second.type) {
                            ValueParaListWarn(i, pcode[i].z, pcode[call].z);
                        }
                    } else {
                        ValueParaListError(i, pcode[i].z, pcode[call].z);
                    }
                }
            }
        } else if ((pcode[i].op == BLEZ || pcode[i].op == BLTZ || pcode[i].op == BGEZ || pcode[i].op == BGTZ ||
                    pcode[i].op == BNE || pcode[i].op == BEQ) &&
                   (code_info.find(pcode[i].y)->second.type == 1 || code_info.find(pcode[i].z)->second.type == 1))
            ValueCompareExp(i, pcode[i].y, pcode[i].z);
        if (pcode[i].x >= GLOBAL_CODE_BASE && pcode[i].x < MID_CODE_BASE &&
            CodeFind(pcode[i].x)->second.kind == 0 &&
            (pcode[i].op == PLUS || pcode[i].op == SUB || pcode[i].op == MUL ||
             pcode[i].op == DIV || pcode[i].op == ADI ||
             pcode[i].op == LCH))
            ConstChange(i);
    }
    it_code = CodeFind(func_code);
    FuncRuntime funcRuntime = {it_code->second.name, func_code, space};
    RuntimeStack.insert(pair<int, FuncRuntime>(func_code, funcRuntime));

}

void GlobalOptimize() {
    for (int i = 0; i < pcode_num; i++) {
        if ((pcode[i].op == PLUS || pcode[i].op == SUB || pcode[i].op == MUL || pcode[i].op == DIV) &&
            pcode[i].x >= MID_CODE_BASE &&
            code_info.find(pcode[i].y)->second.isValue &&
            code_info.find(pcode[i].z)->second.isValue) {
            pcode[i].op = NOP;
        }
        if ((pcode[i].op == ADI || pcode[i].op == LCH) && code_info.find(pcode[i].y)->second.isValue) {
            pcode[i].op = NOP;
        }
        if (pcode[i].x >= GLOBAL_CODE_BASE && pcode[i].x < MID_CODE_BASE && pcode[i].op == PLUS &&
            pcode[i].z >= MID_CODE_BASE && !code_info.find(pcode[i].z)->second.isValue) {
            pcode[i].op = NOP;
            int find = i - 1;
            while (find > 1) {
                if (pcode[find].x == pcode[i].z) {
                    pcode[find].x = pcode[i].x;
                    break;
                }
                find--;
            }
        }
        if (pcode[i].op == PLUS && (pcode[i].y == 0 || (code_info.find(pcode[i].y)->second.isValue &&
                                                        code_info.find(pcode[i].y)->second.value == 0)) &&
            pcode[i].z >= MID_CODE_BASE && !code_info.find(pcode[i].z)->second.isValue) {
            for (int j = i - 1; j > 0; j--) {
                if (pcode[j].op == LABEL)
                    break;
                if ((pcode[j].op == PLUS || pcode[j].op == SUB || pcode[j].op == DIV || pcode[j].op == MUL ||
                     pcode[j].op == ADI || pcode[j].op == LCH) &&
                    pcode[j].x == pcode[i].z) {
                    pcode[i].op = NOP;
                    pcode[j].x = pcode[i].x;
                    break;
                }
            }
        }
    }

}

void PoolInsert(int code, int weight) {
    if (code < LOCAL_CODE_BASE || (code >= LOCAL_CODE_BASE && code < MID_CODE_BASE &&
                                   (CodeFind(code)->second.kind == 2 || CodeFind(code)->second.type == 2 ||
                                    CodeFind(code)->second.type == 3)) ||
        code_info.find(code)->second.isValue)
        return;
    if (Pool.find(code) == Pool.end())
        Pool.insert(pair<int, int>{code, weight});
    else
        Pool.find(code)->second += weight;

}

void RegAssign() {
    int used[1000][2], size = 0, j = 0, weight = 1;
    map<int, int>::iterator iter;
    map<int, int> tmp;
    for (int i = 0; i < pcode_num; i++) {
        if (LoopMark.find(i) != LoopMark.end()) {
            if (LoopMark.find(i)->second)
                weight *= 5;
            else
                weight /= 5;
        }
        if (pcode[i].op == NOP)
            continue;
        if (pcode[i].op == LABEL && pcode[i].z >= LOCAL_CODE_BASE) {
            iter = Pool.begin();
            while (iter != Pool.end()) {
                tmp.insert(pair<int, int>{iter->second * 10000 +
                                          (iter->first >= MID_CODE_BASE ? (iter->first - MID_CODE_BASE) : (iter->first -
                                                                                                           LOCAL_CODE_BASE)),
                                          iter->first});
                iter++;
            }
            iter = tmp.begin();
            while (iter != tmp.end()) {
                used[j][0] = iter->second;
                used[j++][1] = iter->first;
                iter++;
            }
            size = tmp.size();
            for (j = 0; j < 15 && j < size; j++)
                RegPool.insert(pair<int, int>{used[size - j - 1][0], j + 11});
            memset(used, 0, sizeof(int) * 1000);
            j = 0;
            Pool.clear();
            tmp.clear();
        } else if (pcode[i].op == ADI || pcode[i].op == LCH) {
            PoolInsert(pcode[i].x, weight);
            PoolInsert(pcode[i].y, weight);
        } else {
            PoolInsert(pcode[i].x, weight);
            PoolInsert(pcode[i].y, weight);
            PoolInsert(pcode[i].z, weight);
        }
    }
    iter = Pool.begin();
    while (iter != Pool.end()) {
        tmp.insert(pair<int, int>{iter->second * 10000 +
                                  (iter->first >= MID_CODE_BASE ? (iter->first - MID_CODE_BASE) : (iter->first -
                                                                                                   LOCAL_CODE_BASE)),
                                  iter->first});
        iter++;
    }
    iter = tmp.begin();
    while (iter != tmp.end()) {
        used[j][0] = iter->second;
        used[j++][1] = iter->first;
        iter++;
    }
    size = tmp.size();
    for (j = 0; j < 15 && j < size; j++)
        RegPool.insert(pair<int, int>{used[size - j - 1][0], j + 11});
}

void BlockInsert(int code, int block_num) {
    if (RegPool.find(code) != RegPool.end() &&
        block[block_num].used_reg.find(code) == block[block_num].used_reg.end()) {
        block[block_num].used_reg.insert(pair<int, int>{RegPool.find(code)->second, RegPool.find(code)->second});
    }
}

void BasicBlock() {
    int block_num = 0, func = 0;
    for (int i = 0; i < pcode_num; i++) {
        if (LoopMark.find(i) != LoopMark.end()) {
            if (LoopMark.find(i)->second) {
                block_num++;
                if (block_num == 1) {
                    store_num++;
                    block[store_num].func = func;
                    block[store_num].addr = i;
                }
            } else {
                block_num--;
                if (block_num == 0) {
                    store_num++;
                    block[store_num].func = func;
                    block[store_num].addr = i;
                }
            }
        }
        if (pcode[i].op == NOP)
            continue;
        if (pcode[i].op == LABEL && pcode[i].z >= LOCAL_CODE_BASE) {
            store_num++;
            func = pcode[i].z;
            block[store_num].func = pcode[i].z;
            block[store_num].addr = i;
        } else {
            BlockInsert(pcode[i].x, store_num);
            BlockInsert(pcode[i].y, store_num);
            BlockInsert(pcode[i].z, store_num);
        }
    }
}

void BlockFill() {
    int isStatic = 1, func = 0, near = 0;
    unordered_map<int, int> isCalled;
    while (true) {
        isStatic = 1;
        for (int i = 0; i < pcode_num; i++) {
            if (pcode[i].op == LABEL && pcode[i].z >= LOCAL_CODE_BASE)
                func = pcode[i].z;
            if (pcode[i].op == CALL) {
                isCalled.clear();
                for (int j = 0; j <= store_num; j++) {
                    if (block[j].addr <= i)
                        near = j;
                    if (block[j].func == pcode[i].z) {
                        auto iter = block[j].used_reg.begin();
                        while (iter != block[j].used_reg.end()) {
                            if (isCalled.find(iter->second) == isCalled.end())
                                isCalled.insert(pair<int, int>{iter->second, iter->second});
                            iter++;
                        }
                    }
                }
                auto iter = isCalled.begin();
                while (iter != isCalled.end()) {
                    if (block[near].used_reg.find(iter->second) == block[near].used_reg.end()) {
                        block[near].used_reg.insert(pair<int, int>{iter->second, iter->second});
                        isStatic = 0;
                    }
                    iter++;
                }
            }
        }
        if (isStatic)
            break;
    }
}


void OpExchange(int op, ofstream &file) {
    switch (op) {
        case PARA:
            file << " PARA ";
            break;
        case PUSH:
            file << " PUSH ";
            break;
        case CALL:
            file << " CALL ";
            break;
        case RET:
            file << " RET ";
            break;
        case GOTO:
            file << " GOTO ";
            break;
        case PLUS:
            file << " PLUS ";
            break;
        case SUB:
            file << " SUB ";
            break;
        case MUL:
            file << " MULTI ";
            break;
        case DIV:
            file << " DIV ";
            break;
        case LABEL:
            file << " --- LABEL --- ";
            break;
        case BEQ:
            file << " BEQ ";
            break;
        case BNE:
            file << " BNE ";
            break;
        case BLEZ:
            file << " BLEZ ";
            break;
        case BGTZ:
            file << " BGTZ ";
            break;
        case BLTZ:
            file << " BLTZ ";
            break;
        case BGEZ:
            file << " BGEZ ";
            break;
        case WRITE:
            file << " WRITE ";
            break;
        case READ:
            file << " READ ";
            break;
        case ADI:
            file << " ADI ";
            break;
        case LDA:
            file << " LDA ";
            break;
        case END:
            file << " END ";
            break;
        case SW:
            file << " SW ";
            break;
        case BEGIN:
            file << " BEGIN ";
            break;
        case OVER:
            file << " OVER ";
            break;
        case LCH:
            file << " LCH ";
            break;
        default:
            file << " " << op << " ";
    }
}


void ZExchange(int z, ofstream &file) {
    auto iter = CodeFind(z);
    file << iter->second.name;
}