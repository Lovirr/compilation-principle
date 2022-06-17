#ifndef GRAMMER_H
#define GRAMMER_H

#include "conditional.h"
#include "my_structs.h"
#include "operation.h"
#include "parser.h"
using namespace std;

//�﷨������
class GrammarAnalysis {
private:
    // ��Ԫʽ������
    class Parser *parser;
    //���������﷨������
    class OperationAnalysis *operation;
    //��������﷨������
    class ConditionalAnalyzer *conditional;

    //�ݹ��½��﷨����
    void program();

public:
    GrammarAnalysis();
    ~GrammarAnalysis();
    //�Դ�������﷨����
    void analyse();
};

#endif