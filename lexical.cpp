#include "lexical.h"

bool LexicalAnalysis::findcreate(string &p, bool type) {
    int i;
    for (i = 0; i < signTableSize; i++) {
        if (signTable[i].name == p) {
            symbolTable[symbolTableSize].sign = p;
            symbolTable[symbolTableSize++].code = 1;
            return 0;
        }
    }
    //�ַ�����������û�е���p,�Ͱ�p�洢���ַ���������͵��ʱ���
    if (i == signTableSize && type) {
        symbolTable[symbolTableSize].sign = p;
        symbolTable[symbolTableSize++].code = 1;
        signTable[signTableSize++].name = p;
    }
    if (!type) {
        cout << p << "δ����!" << endl;
        return false;
    }
    return true;
}
void LexicalAnalysis::addSymbol(string &p, bool type) {
    int i;
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
        cout << "�޷��ҵ��ؼ��ֱ�" << endl;
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
            while (isalnum(*p) || *p == '_') {
                word += *p;
                p++;
            }
            if (word == "int" || word == "float" || word == "char")
                // Ϊ1����int float char ���͵��ַ�������
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
}
