#ifndef MY_STRUCTS_H
#define MY_STRUCTS_H

#include <string>
using namespace std;

//����
struct word {
    string sign;
    int code;

    word() : sign(""), code(0){};
    word(string s, int c) : sign(s), code(c){};
};

//�ַ�������
struct sign {
    string name;
    string cat;
    string type;
    int value;

    sign() : name(""), cat(""), type(""), value(0){};
    sign(string n) : name(n), cat(""), type(""), value(0){};
    sign(string n, string c, string t, int v) : name(n), cat(c), type(t), value(v){};
};

//�ؼ���
struct property {
    string symbol;
    string code;
};

#endif