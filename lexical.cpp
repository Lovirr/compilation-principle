#include "lexical.h"
#include <Windows.h>

void color1(WORD c);//控制输出字体属性(字体颜色)
void color1(WORD c) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);//设置控制台输出字体颜色值为c的值
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
    //字符串常量表中没有单词p,就把p存储到字符串常量表和单词表中
    //type=1,表示已经定义的标识符
    if (i == signTableSize && type) {
        symbolTable[symbolTableSize].sign = p;
        symbolTable[symbolTableSize++].code = 1;
        signTable[signTableSize++].name = p;
    }
    //type=0,表示未定义的标识符
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
    /* 查找p是否已经在符号表中
     1.已定义
     2.能在符号表中找到
     3.是字母开头(表示变量)
     4.只有一个字符(区分标识符和字符串常量)*/
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
                //如果符合就是字符串常量
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
            // 判断单词是否为字符串
            word.clear();
            word += *p;
            p++;
            // 判断p读头是否为字符串或数字
            while (isalnum(*p) || *p == '_') {
                word += *p;
                p++;
            }
            if (word == "int" || word == "float" || word == "char")
                // 为1代表int float char 类型
                type = true;
            addSymbol(word, type);
        } else if (*p >= '0' && *p <= '9') {
            //判断单词是否为整数
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
