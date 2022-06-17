#ifndef CONDITIONAL_H
#define CONDITIONAL_H

#include <iostream>
#include <stack>

#include "my_structs.h"
#include "operation.h"
#include "parser.h"
using namespace std;

//��������﷨������
class ConditionalAnalyzer {
private:
    // LR������
    const int LRTable[16][11] =
        {{1, -1, 4, -1, 5, -1, -1, -1, 13, 7, 8},
         {-1, 2, -1, 101, -1, 101, 101, 101, -1, -1, -1},
         {3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
         {-1, -1, -1, 102, -1, 102, 102, 102, -1, -1, -1},
         {1, -1, 4, -1, 5, -1, -1, -1, 11, 7, 8},
         {1, -1, 4, -1, 5, -1, -1, -1, 6, 7, 8},
         {-1, -1, -1, 104, -1, 104, 104, 104, -1, -1, -1},
         {1, -1, 4, -1, 5, -1, -1, -1, 14, 7, 8},
         {1, -1, 4, -1, 5, -1, -1, -1, 15, 7, 8},
         {105, -1, 105, -1, 105, -1, -1, -1, -1, -1, -1},
         {107, -1, 107, -1, 107, -1, -1, -1, -1, -1, -1},
         {-1, -1, -1, 12, -1, 9, 10, -1, -1, -1, -1},
         {-1, -1, -1, 103, -1, 103, 103, 103, -1, -1, -1},
         {-1, -1, -1, -1, -1, 9, 10, -2, -1, -1, -1},
         {-1, -1, -1, 106, -1, 106, 106, 106, -1, -1, -1},
         {-1, -1, -1, 108, -1, 9, 108, 108, -1, -1, -1}};

    // ��Ԫʽ������
    class Parser *parser;
    //���������﷨������
    class OperationAnalysis *operation;

    /**
     * @brief ���LR�������ͷ���±�
     *
     * @param a �������
     * @return int LR�������ͷ���±�
     */
    int getLRIndex(int a);

public:
    ConditionalAnalyzer(Parser *p, OperationAnalysis *o) : parser(p), operation(o){};

    //�������������﷨����
    bool analyse();
};
#endif