#ifndef LEXICAL_H
#define LEXICAL_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "my_structs.h"
using namespace std;

/**
 * @brief �ʷ���������
 *
 */
class LexicalAnalysis {
private:
    //�ؼ��ֱ�
    vector<property> propertytable;
    //���ʱ�
    vector<word>* symbol;
    //�ַ���������
    vector<sign>* signtable;

    /**
     * @brief ���ַ���p�����ַ���������͵��ʱ���
     *
     * @param p Ҫ������ַ���
     * @param type �ַ���ǰ�Ƿ������������
     * @return bool �Ƿ�ɹ�
     */
    bool findcreate(string& p, bool type);
    /**
     * @brief �򵥴ʱ�����ӳ���������ĵ���
     *
     * @param p Ҫ�������ַ���
     * @param type �ַ���ǰ�Ƿ������������
     */
    void find(string& p, bool type);

public:
    LexicalAnalysis(){};
    LexicalAnalysis(vector<word>* sy, vector<sign>* si);
    LexicalAnalysis(string local, vector<word>* sy, vector<sign>* si);

    /**
     * @brief �ѹؼ��ֱ��е�symbol��code���뵽propertytable�ṹ����
     *
     * @param local  �ļ�����λ��
     */
    void loadProperty(string local);

    /**
     * @brief �Դ�����дʷ�����
     *
     * @param code �����ַ���
     */
    void test(string& code);
};

#endif