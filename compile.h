#ifndef COMPILE_H
#define COMPILE_H
#include <fstream>
#include <iostream>

#include "coder.h"
#include "grammar.h"
#include "lexical.h"
using namespace std;

//��������
class Complier {
private:
    //���ʱ�
    vector<word> symbol;
    //�ַ���������
    vector<sign> signtable;
    //��Ԫʽ��
    vector<quad> quadtable;
    class LexicalAnalysis *lexical;
    class GrammarAnalysis *grammar;
    class Coder *coder;
    string code;
    const string prefix = "D:\\Code\\C++\\CompilationPrinciple\\code\\";

public:
    Complier();
    ~Complier();
    //���ļ��ж������
    bool loadCode();
    //��ӡ���ʱ�
    void printSymbol();
    //��ӡ��Ԫʽ��
    void printQuadTable();
    //�Դ�����л��
    bool complie();
};

#endif