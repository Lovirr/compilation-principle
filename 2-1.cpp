//Ԥ���������
#include <cstdio>
#include <cstring>
#include <iostream>

char inputString[13];                   /*�����洢�û�������ַ������Ϊ20���ַ�*/
char stack[13];                         /*���������﷨������ջ�ṹ*/
int base = 0;                           /*ջ��ָ��*/
int top = 1;                            /*ջ��ָ��*/
char VT[5] = {'i', '+', '*', '(', ')'}; /*�������5���ս��*/
char chanShengShi[13];                  /*�������Ԥ�������M[A,a]�е�һ������ʽ*/
int firstCharIntex = 0;                 /*���aƥ�����ʽ����ÿ��firstCharIntex ���� 1 */
                                        /*firstCharIntex��������û����봮�ĵ�һ��Ԫ�ص��±�*/
char pop();                             /*����ջ��Ԫ��*/

int push(char ch); /*��ջ�����һ��Ԫ�أ��ɹ�����1����ջ�����򷵻�0*/

int search(char temp); /*���ҷ��ս������VT���Ƿ���ڱ���temp�����ڷ���1�������ڷ���0*/

int M(char A, char a); /* ��Ԥ�������M[A,a]�д��ڲ���ʽ��
                          �򽫸ò���ʽ�����ַ�����chanShengShi[10]�������� 1��
                          ��M[A,a]���޶������ʽ�򷵻� 0
                        */

void init(); /*��ʼ������inputString[10] ��ջ stack[10] �� chanShengShi[10]*/

int yuCeFenXi();         /* �������봮��Ԥ������������ܺ�����
                            �����봮�����ķ��򷵻� 1���������򷵻�0
                          */
void printStack();       /*��ӡջ��Ԫ��    */
void printinputString(); /*��ӡ�û����봮  */

/*����������*/
main() {
    //  clrscr();
    yuCeFenXi(); /*�����﷨Ԥ���������*/
                 // getch();
}

/*�����Ķ���*/

int yuCeFenXi() {
    char X; /*X�����洢ÿ�ε�����ջ��Ԫ��*/
    char a; /*a�����洢�û����봮�ĵ�һ��Ԫ��*/
    int i;
    int counter = 1; /*�ñ�����¼�﷨�����Ĳ�����*/

    init();                       /*��ʼ������*/
    printf("wen fa  :     \n\n"); /*����ķ���Ϊ��ʾ*/
    printf("E->Te        \n");
    printf("e->+Te | $    \n");
    printf("T->Ft    \n");
    printf("t->*Ft|$\n");
    printf("F ->(E)|i   \n");

    printf("input string ,'#' is a end sign  !!( i1+i2 ) \n "); /*��ʾ�û����뽫Ҫ���Ե��ַ���*/
    scanf("%s", inputString);

    push('#');
    push('E');

    printf(" Counter-----Stack---------------Input string "); /*��������ʾ���*/

    while (1) /*whileѭ��Ϊ�﷨��������������*/
    {
        printf(" ");
        printf("\n");
        printf("  %d", counter); /*�������������*/
        printf("         ");     /*�����ʽ�������*/
        printStack();            /*�����ǰջ������Ԫ��*/
        X = pop();               /*����ջ��Ԫ�ظ�������X*/
        printinputString();      /*�����ǰ�û�������ַ���*/
        if (search(X) == 0)      /*���ս������VT�в��ұ���X��ֵ�����ڷ��� 1�����򷵻� 0*/
        {
            if (X == '#') /*ջ�Ѿ����գ��﷨���������ȷ������ 1*/
            {
                printf("success ... "); /*�﷨���������������ַ��������ķ�����*/
                return 1;
            } else {
                a = inputString[firstCharIntex];
                if (M(X, a) == 1) /*�鿴Ԥ�������M[A,a]�Ƿ���ڲ���ʽ�����ڷ���1�������ڷ���0*/
                {
                    for (i = 0; i < 13; i++) /* '$'Ϊ����ʽ�Ľ�����,forѭ���ҳ��ò���ʽ�����һ��Ԫ�ص��±�*/
                    {
                        if (chanShengShi[i] == '$')
                            break;
                    }
                    i--; /*��Ϊ '$' ���ǲ���ʽ��ֻ��һ������ʽ�Ľ�����־������i�Լ�1*/

                    while (i >= 0) {
                        push(chanShengShi[i]); /*����ǰ����ʽ����ѹ��ջ��*/
                        i--;
                    }
                } else {
                    printf(" error(1) !!"); /*��Ԥ�������M[A,a]�����ڲ���ʽ��˵���﷨����*/
                    return 0;
                }
            }
        } else /*˵��XΪ�ս��*/
        {
            if (X == inputString[firstCharIntex]) /*���X����a,˵��aƥ��*/
            {
                firstCharIntex++; /*���봮�ĵ�һ��Ԫ�ر�Լȥ����һ��Ԫ�س�Ϊ�µ�ͷԪ��*/
            } else {
                printf(" error(2) !! ");
                return 0;
            }
        }
        counter++;
    }
}

void init() {
    int i;
    for (i = 0; i < 13; i++) {
        inputString[i] = NULL;  /*��ʼ������inputString[10] */
        stack[i] = NULL;        /*��ʼ��ջstack[10]         */
        chanShengShi[i] = NULL; /*��ʼ������chanShengShi[10]*/
    }
}

int M(char A, char a) /*�ķ�������ʵ��������������ķ�Ϊ�α�������ķ�*/
{                     /*�ú���ģ��Ԥ��������еĶ�ά����              */
    if (A == 'E' && a == 'i') {
        strcpy(&chanShengShi[0], "Te$");
        return 1;
    }
    if (A == 'E' && a == '(') {
        strcpy(&chanShengShi[0], "Te$");
        return 1;
    }
    if (A == 'e' && a == '+') {
        strcpy(&chanShengShi[0], "+Te$");
        return 1;
    }
    if (A == 'e' && a == ')') {
        strcpy(&chanShengShi[0], "$");
        return 1;
    }
    if (A == 'e' && a == '#') {
        strcpy(&chanShengShi[0], "$");
        return 1;
    }
    if (A == 'T' && a == 'i') {
        strcpy(&chanShengShi[0], "Ft$");
        return 1;
    }
    if (A == 'T' && a == '(') {
        strcpy(&chanShengShi[0], "Ft$");
        return 1;
    }
    if (A == 't' && a == '+') {
        strcpy(&chanShengShi[0], "$");
        return 1;
    }
    if (A == 't' && a == '*') {
        strcpy(&chanShengShi[0], "*Ft$");
        return 1;
    }
    if (A == 't' && a == ')') {
        strcpy(&chanShengShi[0], "$");
        return 1;
    }
    if (A == 't' && a == '#') {
        strcpy(&chanShengShi[0], "$");
        return 1;
    }
    if (A == 'F' && a == 'i') {
        strcpy(&chanShengShi[0], "i$");
        return 1;
    }
    if (A == 'F' && a == '(') {
        strcpy(&chanShengShi[0], "(E)$");
        return 1;
    } else
        return 0; /*û�ж������ʽ�򷵻�0*/
}

char pop() /*����ջ��Ԫ�أ���topChar����*/
{
    char topChar;
    topChar = stack[--top];
    return topChar;
}

int push(char ch) {
    if (top > 12) {
        printf(" error : stack overflow "); /*ջ�ռ����*/
        return 0;
    } else {
        stack[top] = ch; /*��ջ���ռ丳ֵ*/
        top++;
        return 1;
    }
}

int search(char temp) {
    int i, flag = 0; /*flag������Ϊ��־�����ҵ�temp��1������0*/
    for (i = 0; i < 5; i++) {
        if (temp == VT[i]) /*�ս�������д���temp*/
        {
            flag = 1;
            break;
        }
    }

    if (flag == 1)
        return 1; /*flag==1˵�����ҵ�����temp��Ԫ��*/
    else
        return 0;
}

void printStack() /*���ջ������*/
{
    int temp;
    for (temp = 1; temp < top; temp++) {
        printf("%c", stack[temp]);
    }
}

void printinputString() /*����û�������ַ���*/
{
    int temp = firstCharIntex;
    printf("                     "); /*�þ���������ʽ*/
    do {
        printf("%c", inputString[temp]);
        temp++;
    } while (inputString[temp - 1] != '#');
    printf(" ");
}
