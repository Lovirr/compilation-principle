#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define ERROR 0
#define OK 1
//********************************************ջģ��
typedef struct SqStack1  //������ջ
{
    int *base;
    int *top;
    int stacksize;
} SqStack1;
typedef struct SqStack2  //�����ջ
{
    char *base;
    char *top;
    int stacksize;
} SqStack2;
void IntInitStack(SqStack1 *S) {
    S->base = (int *)malloc(STACK_INIT_SIZE * sizeof(int));
    if (!S->base)
        exit(ERROR);
    S->top = S->base;
    S->stacksize = STACK_INIT_SIZE;
}
void CharInitStack(SqStack2 *S) {
    S->base = (char *)malloc(STACK_INIT_SIZE * sizeof(char));
    if (!S->base)
        exit(ERROR);
    S->top = S->base;
    S->stacksize = STACK_INIT_SIZE;
}
int IntGetTop(SqStack1 *S)  //ȡջ��Ԫ��
{
    int e;
    if ((*S).top == (*S).base)
        return 0;
    e = *((*S).top - 1);
    return e;
}
char CharGetTop(SqStack2 *S)  //ȡջ��Ԫ��
{
    char e;
    if ((*S).top == (*S).base)
        return 0;
    e = *((*S).top - 1);
    return e;
}
int IntPush(SqStack1 *S, int e) {
    *(*S).top++ = e;
    return OK;
}
int CharPush(SqStack2 *S, char e) {
    *(*S).top++ = e;
    return OK;
}

int IntPop(SqStack1 *S) {
    int e;
    if ((*S).top == (*S).base)
        return 0;
    e = *--(*S).top;
    return e;
}
int CharPop(SqStack2 *S) {
    char e;
    if ((*S).top == (*S).base)
        return 0;
    e = *--(*S).top;
    return e;
}
//������������������������������������*******************����ģ��
char Precede(char a, char b)  //�������ȼ��ж�
{
    int i, j;
    char Table[8][8] = {
        ' ',
        '+',
        '-',
        '*',
        '/',
        '(',
        ')',
        '#',
        '+',
        '>',
        '>',
        '<',
        '<',
        '<',
        '>',
        '>',
        '-',
        '>',
        '>',
        '<',
        '<',
        '<',
        '>',
        '>',
        '*',
        '>',
        '>',
        '>',
        '>',
        '<',
        '>',
        '>',
        '/',
        '>',
        '>',
        '>',
        '>',
        '<',
        '>',
        '>',
        '(',
        '<',
        '<',
        '<',
        '<',
        '<',
        '=',
        ' ',
        ')',
        '>',
        '>',
        '>',
        '>',
        ' ',
        '>',
        '>',
        '#',
        '<',
        '<',
        '<',
        '<',
        '<',
        ' ',
        '=',
    };  //���ȼ����
    for (i = 0; i < 8; i++)
        if (Table[0][i] == a)  //������Ѱ��
            break;
    for (j = 0; j < 8; j++)  //������Ѱ��
        if (Table[j][0] == b)
            break;
    return Table[j][i];
}
int Operate(int a, char theta, int b)  //������ʽֵ����Ҫ�ǽ���ı��ʽת����С�ı��ʽ��������ֵ
{
    int c;
    if (theta == '+')
        c = a + b;
    else if (theta == '-')
        c = a - b;
    else if (theta == '*')
        c = a * b;
    else
        c = a / b;
    return c;
}  // Operate
int In(char c)  //�ж�c�Ƿ�Ϊ������
{
    if (c == '(' || c == '+' || c == '-' || c == '*' || c == '/' || c == ')' || c == '#' || c == '^')
        return 1;  //����ǲ���������1
    else
        return 0;  //���ǣ�����0
}
int result(SqStack1 *OPND, SqStack2 *OPTR)  //��ֵ
{
    char a = 0;
    char theta;
    int b, c, number = 0;
    IntInitStack(OPND);
    CharInitStack(OPTR);
    CharPush(OPTR, '#');
    a = getchar();
    while (a != '#' || CharGetTop(OPTR) != '#') {
        printf("�����ַ���%c    ", a);
        if (!In(a))  //������������ջ
        {
            number = 0;
            while (!In(a)) {
                number = number * 10 + (a - 48);  //�����λ����	z=10*x+y
                a = getchar();
            }
            IntPush(OPND, number);
            printf("��Ҫ������Push(OPND,%d)       ", number);
        } else
            switch (Precede(a, CharGetTop(OPTR))) {
            case '<':
                CharPush(OPTR, a);
                a = getchar();
                printf("��Ҫ������Push(OPTR,%c)       ", a);
                break;
            case '=':
                CharPop(OPTR);
                a = getchar();
                printf("��Ҫ������Pop(OPTR,%c)        ", a);
                break;
            case '>':
                theta = CharPop(OPTR);
                c = IntPop(OPND);
                b = IntPop(OPND);
                IntPush(OPND, Operate(b, theta, c));
                printf("��Ҫ������Operate(%d,%c,%d)     ", b, theta, c);
                break;
            }
        printf("OPNDջ��%d  OPTRջ��%c\n", IntGetTop(OPND), CharGetTop(OPTR));
    }
    printf("\n���:%d.\n", IntGetTop(OPND));  //��ӡ������ʽֵ
    return OK;
}
//������������������������������������������������������ģ��
main()  //��������ʹ���Զ��庯����ɹ���
{
    SqStack1 s1, *OPND;
    SqStack2 s2, *OPTR;
    OPND = &s1;
    OPTR = &s2;
    printf("�������������ʽ����'#'��β.\n");
    printf("�������ʽ:");
    result(OPND, OPTR);
    system("pause");
}
