#ifndef PARSER_H
#define PARSER_H

#include "my_structs.h"
using namespace std;

//��Ԫʽ������
class Parser {
public:
    /**
     * @brief ���ҵ����ڵ��ʱ��е��±�
     *
     * @param x ����
     * @return int �����ڵ��ʱ��е��±�
     */
    int findstring(int x);

    /**
     * @brief ������ķ��ű���ڵ�ַ
     *
     * @param p ����ı���
     * @return int �����ķ��ű���ڵ�ַ\n
     *         >=1000��ʾ����ʱ����\n
     *         >=10000��ʾ�ǳ���
     */
    int entry(string &p);

    /**
     * @brief ����һ���µ���ʱ����
     *
     * @param op �����
     * @param E1_place ��һ���������ķ��ű���ڵ�ַ
     * @param E2_place �ڶ����������ķ��ű���ڵ�ַ
     * @return int �µ���ʱ�����ķ��ű���ڵ�ַ
     */
    int newtemp(char op, int E1_place, int E2_place);

    /**
     * @brief ������Ԫʽ��������Ԫʽ��
     *
     * @param op �����
     * @param arg1 ��һ���������ķ��ű���ڵ�ַ
     * @param arg2 �ڶ����������ķ��ű���ڵ�ַ
     * @param result ����ķ��ű���ڵ�ַ
     */
    void gen(string op, int arg1, int arg2, string result);

    /**
     * @brief �������
     *
     * @param p ��ʼ���������
     * @param t �������Ԫʽ�±�
     */
    void Backpatch(int p, int t);

    /**
     * @brief ����
     *
     * @param p1 ��һ������
     * @param p2 �ڶ�������
     * @return int �ϲ���ɺ������
     */
    int Merg(int p1, int p2);
};

#endif