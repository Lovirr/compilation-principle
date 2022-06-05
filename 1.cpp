//�ʷ���������
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;

const int NUMBER = 300;
const int STRING_LENGTH = 4000;
const int LENGTH = 40;

//���浥�ʱ�
struct
{
    char sign[10];
    int code;
} symbol[NUMBER];

// ����ؼ��ֵı�
struct
{
    char symbol[30];
    char code[5];
} propertytable[NUMBER];

//�����ַ��������ı�
struct
{
    char name[10];
    char cat[10];
    char type[10];
    int value;
} signtable[1150];

int propertytable_count = 0, signtable_count = 0, symbol_count = 0, type = 1;

//�������ַ���ת��Ϊ����
int changestring(char *p) {
    int i, num = 0;
    for (i = 0; p[i] != '\0'; i++) {
        num = num * 10 + p[i] - '0';
    }
    return num;
}

int findcreate(char *p) {
    int i;
    for (i = 0; i < signtable_count; i++) {
        if (strcmp(signtable[i].name, p) == 0) {
            strcpy(symbol[symbol_count].sign, p);
            symbol[symbol_count++].code = 1;
            return 0;
        }
    }
    if (i == signtable_count && type)  // ��ʾ�ַ�����������û�е���p,�Ͱ�p�洢���ַ���������͵��ʱ���
    {
        strcpy(symbol[symbol_count].sign, p);
        symbol[symbol_count++].code = 1;
        strcpy(signtable[signtable_count++].name, p);
    }
    if (type == 0) {
        printf("%snot defined\n", p);
    }
    return 0;
}

void find(char *p) {
    int i, num = 0;
    if (*p >= '0' && *p <= '9')  //����
    {
        for (i = 0; p[i] != '\0'; i++) {
            num = num * 10 + p[i] - '0';
            symbol[symbol_count].sign[i] = p[i];
        }
        symbol[symbol_count].sign[i] = '\0';
        symbol[symbol_count++].code = 2;
    } else {
        for (i = 0; i < propertytable_count; i++) {
            if (strcmp(propertytable[i].symbol, p) == 0) {
                strcpy(symbol[symbol_count].sign, p);
                symbol[symbol_count++].code = changestring(propertytable[i].code);
                break;
            }
        }
        if (i == propertytable_count) {
            if (*p >= 'A' && *p <= 'Z' || *p >= 'a' && *p <= 'z')  //������Ͼ����ַ�������
            {
                findcreate(p);
            } else if (*p >= 32) {
                strcpy(symbol[symbol_count].sign, p);
                symbol[symbol_count++].code = 0;
            }
        }
    }
}

void Test(char *p) {
    int k;
    char word[30];
    while (*p != '\0') {
        if (*p >= 'A' && *p <= 'Z' || *p >= 'a' && *p <= 'z')  // �жϵ����Ƿ�Ϊ�ַ���
        {
            k = 0;
            word[k++] = *p;
            p++;
            while (*p >= 'A' && *p <= 'Z' || *p >= 'a' && *p <= 'z' || *p >= '0' && *p <= '9' || *p == '_') {
                word[k++] = *p;
                p++;
            }
            word[k] = '\0';
            if (strcmp(word, "int") == 0 || strcmp(word, "float") == 0 || strcmp(word, "char") == 0) {
                type = 1;  // Ϊ1����int float char ���͵��ַ�������
            }
            find(word);
        } else if (*p >= '0' && *p <= '9')  //�жϵ����Ƿ�Ϊ����
        {
            k = 0;
            word[k++] = *p;
            p++;
            while (*p >= '0' && *p <= '9') {
                word[k++] = *p;
                p++;
            }
            word[k] = '\0';
            find(word);
        } else if (*p == '<' || *p == '>' || *p == '=' || *p == '!' || *p == '&' || *p == '|') {
            k = 0;
            word[k++] = *p;
            p++;
            if (*(p - 1) == '&') {
                if (*p == '&') {
                    word[k++] = *p;
                    p++;
                }
            } else if (*(p - 1) == '|') {
                if (*p == '|') {
                    word[k++] = *p;
                    p++;
                }
            } else {
                if (*p == '=') {
                    word[k++] = *p;
                    p++;
                }
            }
            word[k] = '\0';
            find(word);
        } else if (*p == ' ') {
            p++;
        } else {
            k = 0;
            word[k++] = *p;
            word[k] = '\0';
            if (strcmp(word, ";") == 0) {
                type = 0;
            }
            p++;
            find(word);
        }
    }
}

// �ѹؼ��ֱ��е�symbol �� code���뵽propertytable�ṹ����
void Create() {
    int i = 0;
    FILE *fp;
    if ((fp = fopen("D:\\Code\\C++\\CompilationPrinciple\\keyword.txt", "r")) == NULL) {
        printf("keyword.txt not found");
        return;
    }
    while (!feof(fp)) {
        fscanf(fp, "%s %s", propertytable[i++].symbol, propertytable[i].code);
        propertytable_count++;
    }
    fclose(fp);  // �ر��ļ�
}

void Finput() {
    int i = 0;
    char ch;
    char string[STRING_LENGTH];  // C���Գ����ı��ַ���
    char file[LENGTH];           // �ļ������ַ���
    FILE *fp;
    printf("input filename:");
    scanf("%s", file);
    if ((fp = fopen(file, "rb")) == NULL) {
        printf("file not found");
        return;
    }
    ch = fgetc(fp);
    while (ch != EOF)  // �жϳ����Ƿ����
    {
        string[i++] = ch;
        ch = fgetc(fp);
    }
    string[i] = '\0';  // ��Ϊ�����ַ�����β��ʶ
    printf("c program is :\n");
    printf("%s\n", string);
    Test(string);  // �Գ�����дʷ�����
}

int main() {
    Create();
    Finput();
    system("pause");
    return 0;
}