#include "operation.h"
#include <Windows.h>

void color4(WORD c);//控制输出字体属性(字体颜色)
void color4(WORD c) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);//设置控制台输出字体颜色值为c的值
}


//求表达式的值，类似于计算器

int OperationAnalysis::getLRIndex(int a) {
    int i;
    int PAT[] = {'i', 3, 4, 5, 6, 17, 18, '#', 'E'};
    i = 0;
    while (PAT[i] != a && i <= 8) {
        i++;
    }
    if (i == 9) {
        i = 7;
    }
    return i;
}

bool OperationAnalysis::analyse() {
    int sym, acc, t, j, E1_place, E2_place, x, l;
    stack<int> s1, s2, s3;
    s1.emplace(0);
    //压入#
    s2.emplace(24);
    s3.emplace('@');
    Flag = 0;
    sym1 = symbolTable[symbolIndex++].code;
    if (sym1 == 1 || sym1 == 2) {
        sym = 'i';
    } else {
        sym = sym1;
    }
    acc = false;
    while (!acc) {
        l = s1.top();
        j = getLRIndex(sym);
        t = LRTable[l][j];
        if (t == -1) {
            color4(0x0c);
            cout << "ERROR:  Arithmetic Syntax error!" << endl;
            color4(0x07);
            exit(0);
        } else if (t == -2) {
            acc = true;
        } else if (t >= 0 && t < 100) {
            s1.emplace(t);
            s2.emplace(sym);
            if (sym == 'i') {
                s3.emplace(parser->entry(symbolTable[symbolIndex - 1].sign));
            } else {
                s3.emplace('@');
            }
            sym1 = symbolTable[symbolIndex++].code;
            if (sym1 == 1 || sym1 == 2) {
                sym = 'i';
            } else {
                sym = sym1;
            }
        } else if (t >= 100 && t <= 200) {
            char op = 0;
            switch (t) {
            case 101:
                op = '+';
                break;

            case 102:
                op = '-';
                break;

            case 103:
                op = '*';
                break;

            case 104:
                op = '/';
                break;

            case 105:
                s1.pop();
                s1.pop();
                s1.pop();
                s2.pop();
                s2.pop();
                s2.pop();
                s3.pop();
                Temp = s3.top();
                s3.pop();
                s3.pop();
                t = s1.top();
                s2.emplace('E');
                j = getLRIndex('E');
                x = LRTable[t][j];
                s1.emplace(x);
                s3.emplace(Temp);
                break;

            case 106:
                s1.pop();
                s2.pop();
                s2.emplace('E');
                Temp = s3.top();
                t = s1.top();
                j = getLRIndex('E');
                x = LRTable[t][j];
                s1.emplace(x);
                Flag++;
            }
            if (op) {
                s1.pop();
                s1.pop();
                s1.pop();
                s2.pop();
                s2.pop();
                s2.pop();
                E2_place = s3.top();
                s3.pop();
                s3.pop();
                E1_place = s3.top();
                Temp = parser->newtemp(op, E1_place, E2_place);
                s3.pop();
                t = s1.top();
                s2.emplace('E');
                j = getLRIndex('E');
                x = LRTable[t][j];
                s1.emplace(x);
                string op1(1, op);
                parser->gen(op1, E1_place, E2_place, "T");
                tempIndex++;
                s3.emplace(Temp);
            }
        }
    }
    return true;
}