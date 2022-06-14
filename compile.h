#ifndef COMPILE_H
#define COMPILE_H
#include <fstream>
#include <iostream>

#include "lexical.h"
using namespace std;

class Complier {
private:
    //���ʱ�
    vector<word> symbol;
    //�ַ���������
    vector<sign> signtable;
    class LexicalAnalysis *lexical;
    string code;
    const string prefix = "D:\\Code\\C++\\CompilationPrinciple\\";

public:
    Complier();
    ~Complier();
    bool loadCode();
    //��ӡ���ʱ�
    void printSymbol();
    bool complie();
};

#endif