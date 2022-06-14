#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

#include "my_structs.h"
using namespace std;

class Parser {
private:
    //��ǰ��ʱ�������±�
    int index = 0;
    //��ʱ������
    vector<int> signTableTemp;
    vector<word> *symbol;
    vector<sign> *signtable;
    vector<quad> *quadtable;

public:
    Parser();

    Parser(vector<word> *symbol, vector<sign> *signtable, vector<quad> *quadtable);

    int findstring(int x);

    // ������ķ��ű���ڵ�ַ
    int entry(string &p);

    int newtemp(char op, int E1_place, int E2_place);

    // ������Ԫʽ
    void gen(string op, int arg1, int arg2, string result);

    void gen(char op, int arg1, int arg2, string result);
};

#endif