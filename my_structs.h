#ifndef MY_STRUCTS_H
#define MY_STRUCTS_H

#include <string>
using namespace std;

//�ؼ���
struct property {
    string symbol;
    string code;
};
//�ؼ��ֱ�
extern property propertyTable[300];

//�ַ�������
struct sign {
    string name;
    string cat;
    string type;
    int value;
};
//�ַ���������
extern sign signTable[1150];

//����
struct sym {
    string sign;
    int code;
};
//���ʱ�
extern sym symbolTable[300];

//��Ԫʽ
struct quad {
    string op;
    string arg1;
    string arg2;
    string result;
};
//��Ԫʽ��
extern quad quadTable[300];

//������
struct com {
    string lable;
    string op;
    string arg1;
    string arg2;
};
//�������
extern com comTable[300];

extern int propertyTableSize, signTableSize, symbolTableSize;
extern int Flag, tempIndex, quadIndex, NXQ, sym1, symbolIndex, Temp, bracket, E_TC, E_FC, Schain;
extern bool ifFlag, whileFlag, doFlag;
extern int comIndex;

#endif