#include "lexical.h"
#include <Windows.h>

void color1(WORD c);//���������������(������ɫ)
void color1(WORD c) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);//���ÿ���̨���������ɫֵΪc��ֵ
}


bool LexicalAnalysis::findcreate(string &p, bool type) {
    int i;
    for (i = 0; i < signTableSize; i++) {
        if (signTable[i].name == p) {
            symbolTable[symbolTableSize].sign = p;
            symbolTable[symbolTableSize++].code = 1;
            return false;
        }
    }
    //�ַ�����������û�е���p,�Ͱ�p�洢���ַ���������͵��ʱ���
    //type=1,��ʾ�Ѿ�����ı�ʶ��
    if (i == signTableSize && type) {
        symbolTable[symbolTableSize].sign = p;
        symbolTable[symbolTableSize++].code = 1;
        signTable[signTableSize++].name = p;
    }
    //type=0,��ʾδ����ı�ʶ��
    if (!type) {
        color1(0x0c);
        cout << "ERROR:  The variable '" << p << "' was undefined!" << endl;
        color1(0x07);
        lexicalFlag = false;
        exit(0);
    }
    return true;
}

void LexicalAnalysis::addSymbol(string &p, bool type) {
    int i;
    /* ����p�Ƿ��Ѿ��ڷ��ű���
     1.�Ѷ���
     2.���ڷ��ű����ҵ�
     3.����ĸ��ͷ(��ʾ����)
     4.ֻ��һ���ַ�(���ֱ�ʶ�����ַ�������)*/
//    if (type && findcreate(p, type) == 0 && isalpha(p[0]) &&p[1]=='\0' ) {
//        color1(0x0c);
//        cout << "ERROR:  The variable '" << p << "' was already defined!" << endl;
//        color1(0x07);
//        lexicalFlag = false;
//    }
    if (isdigit(p[0])) {
        symbolTable[symbolTableSize].sign = p;
        symbolTable[symbolTableSize++].code = 2;
    } else {
        for (i = 0; i < propertyTableSize; i++) {
            if (propertyTable[i].symbol == p) {
                symbolTable[symbolTableSize].sign = p;
                symbolTable[symbolTableSize++].code = atoi(propertyTable[i].code.c_str());
                break;
            }
        }
        if (i == propertyTableSize) {
            if (isalpha(p[0])) {
                //������Ͼ����ַ�������
                findcreate(p, type);
            } else if (p[0] >= 32) {
                symbolTable[symbolTableSize].sign = p;
                symbolTable[symbolTableSize++].code = 0;
            }
        }
    }
}

void LexicalAnalysis::loadProperty(string fileName) {
    int i = 0;
    ifstream fin(fileName);
    if (!fin.is_open()) {
        color1(0x0c);
        cout << "ERROR: failed to find propertyTable!" << endl;
        color1(0x07);
        return;
    }
    while (!fin.eof()) {
        fin >> propertyTable[i].symbol >> propertyTable[i].code;
        i++;
        propertyTableSize++;
    }
    fin.close();
}

void LexicalAnalysis::analyse(string &code) {
    bool type = true;
    int k;
    string word;
    string::iterator p = code.begin();
    while (p < code.end()) {
        if (isalpha(*p)) {
            // �жϵ����Ƿ�Ϊ�ַ���
            word.clear();
            word += *p;
            p++;
            // �ж�p��ͷ�Ƿ�Ϊ�ַ���������
            while (isalnum(*p) || *p == '_') {
                word += *p;
                p++;
            }
            if (word == "int" || word == "float" || word == "char")
                // Ϊ1����int float char ����
                type = true;
            addSymbol(word, type);
        } else if (*p >= '0' && *p <= '9') {
            //�жϵ����Ƿ�Ϊ����
            word.clear();
            word += *p;
            p++;
            while (*p >= '0' && *p <= '9') {
                word += *p;
                p++;
            }
            addSymbol(word, type);
        } else if (*p == '<' || *p == '>' || *p == '=' || *p == '!' || *p == '&' || *p == '|') {
            word.clear();
            word += *p;
            p++;
            if (*(p - 1) == '&' && *p == '&') {
                word += *p;
                p++;
            } else if (*(p - 1) == '|' && *p == '|') {
                word += *p;
                p++;
            } else if (*p == '=') {
                word += *p;
                p++;
            }
            addSymbol(word, type);
        } else if (*p == ' ') {
            p++;
        } else {
            word.clear();
            word += *p;
            if (word == ";") {
                type = false;
            }
            p++;
            addSymbol(word, type);
        }
    }
    if (lexicalFlag) {
        color1(0x02);
        cout << "LEXICAL ANALYSIS SUCCESS!" << endl;
        color1(0x07);
    } else {
        color1(0x0c);
        cout << "LEXICAL ANALYSIS FAILED!" << endl;
        exit(0);
    }
}
