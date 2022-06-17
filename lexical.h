#ifndef LEXICAL_H
#define LEXICAL_H

#include <fstream>
#include <iostream>

#include "my_structs.h"
using namespace std;

class LexicalAnalysis {
private:
    /**
     * @brief ���ַ���p�����ַ���������͵��ʱ���
     *
     * @param p Ҫ������ַ���
     * @param type �ַ���ǰ�Ƿ������������
     * @return bool �Ƿ�ɹ�
     */
    bool findcreate(string &p, bool type);

    /**
     * @brief �򵥴ʱ�����ӳ���������ĵ���
     *
     * @param p Ҫ�������ַ���
     * @param type �ַ���ǰ�Ƿ������������
     */
    void addSymbol(string &p, bool type);

public:
    /**
     * @brief �ѹؼ��ֱ��е�symbol��code���뵽propertytable�ṹ����
     *
     * @param local  �ļ�����λ��
     */
    void loadProperty(string fileName);

    /**
     * @brief �Դ�����дʷ�����
     *
     * @param code �����ַ���
     */
    void analyse(string &code);
};

#endif