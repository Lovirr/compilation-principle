#ifndef COMBUILDER_H
#define COMBUILDER_H

#include <iostream>
#include <set>
#include <unordered_map>

#include "my_structs.h"
using namespace std;

//������������
class ComBuilder {
private:
    /**
     * @brief ���ɱȽ�ָ��
     *
     * @param index ��Ԫʽ�±�
     */
    void buildCMP(int index);

    //��ӡ������
    void printVariables();

    //��ӡ��ջ��
    void printStacks();

    //��ӡ�����
    void printCode();

public:
    //����Ԫʽת���ɻ�����
    void build();

    //��ӡ������
    void printCom();
};

#endif