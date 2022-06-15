#ifndef CODER_H
#define CODER_H

#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;
#include "my_structs.h"

//���������
class Coder {
private:
    vector<quad> *quadtable;

    //������
    struct Com {
        string lable;
        string op;
        string arg1;
        string arg2;
        Com(){};
        Com(string l, string o, string a1, string a2) : lable(l), op(o), arg1(a1), arg2(a2){};
    };
    //�������
    vector<Com> comTable;

public:
    Coder(){};

    Coder(vector<quad> *t) : quadtable(t){};

    //����Ԫʽת�ɻ�����
    void quadtocode();

    //��ӡ������
    void printCode();
};

#endif