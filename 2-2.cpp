//�ݹ��½���������
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
char a[80];
char sym;
int i = 0;

void E();
void E1();
void T();
void T1();
void F();
void input();
void Scaner();
void Error();

void input() {
    puts("������Ҫ�������ַ�������#����β��:");
    cin >> a;
}

void Scaner() {
    sym = a[i];
    i++;
}

void Error() {
    cout << "Error" << endl;
    exit(0);
}

main() {
    while (1) {
        input();
        Scaner();
        E();
        if (sym == '#')
            printf("���ַ����Ǹ��ķ����ַ���!\n");
        else
            printf("Error!\n");
        i = 0;
    }
}

void E() {
    T();
    E1();
}

void E1() {
    if (sym == '+') {
        Scaner();
        T();
        E1();
    } else if ((sym != ')') && (sym != '#'))
        Error();
}

void T() {
    F();
    T1();
}

void T1() {
    if (sym == '*') {
        Scaner();
        F();
        T1();
    } else if ((sym != '+' && sym != ')') && sym != '#')
        Error();
}

void F() {
    if (sym == '(') {
        Scaner();
        E();
        if (sym == ')')
            Scaner();
        else
            Error();
    } else if (sym == 'i')
        Scaner();
    else
        Error();
}
