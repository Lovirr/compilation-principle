//Ԥ���������
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

//�����洢�û�������ַ������Ϊ20���ַ�
string inputString;
//ʹ��vectorģ��ջ
vector<char> stack;
//�������5���ս��
const unordered_set<char> VT = {'i', '+', '*', '(', ')'};
//�������Ԥ�������M[A,a]�е�һ������ʽ
string chanShengShi;
//��������û����봮�ĵ�һ��Ԫ�ص��±꣬���aƥ�����ʽ����ÿ��firstCharIntex ���� 1
int firstCharIndex = 0;

/*
    ��Ԥ�������M[A,a]�д��ڲ���ʽ��
    �򽫸ò���ʽ�����ַ�����chanShengShi�������� 1��
    ��M[A,a]���޶������ʽ�򷵻� 0
*/
bool M(char A, char a) {
    if (A == 'E' && a == 'i') {
        chanShengShi = "Te$";
        return true;
    }
    if (A == 'E' && a == '(') {
        chanShengShi = "Te$";
        return true;
    }
    if (A == 'e' && a == '+') {
        chanShengShi = "+Te$";
        return true;
    }
    if (A == 'e' && a == ')') {
        chanShengShi = "$";
        return true;
    }
    if (A == 'e' && a == '#') {
        chanShengShi = "$";
        return true;
    }
    if (A == 'T' && a == 'i') {
        chanShengShi = "Ft$";
        return true;
    }
    if (A == 'T' && a == '(') {
        chanShengShi = "Ft$";
        return true;
    }
    if (A == 't' && a == '+') {
        chanShengShi = "$";
        return true;
    }
    if (A == 't' && a == '*') {
        chanShengShi = "*Ft$";
        return true;
    }
    if (A == 't' && a == ')') {
        chanShengShi = "$";
        return true;
    }
    if (A == 't' && a == '#') {
        chanShengShi = "$";
        return true;
    }
    if (A == 'F' && a == 'i') {
        chanShengShi = "i$";
        return true;
    }
    if (A == 'F' && a == '(') {
        chanShengShi = "(E)$";
        return true;
    } else
        return false;
}

//��ӡջ��Ԫ��
void printStack() {
    for (int i = 1; i < (int)stack.size(); i++)
        cout << stack[i];
    cout << "\t\t";
}

//��ӡ�û����봮
void printinputString() {
    for (int i = firstCharIndex; i < (int)inputString.size() && inputString[i] != '#'; i++)
        cout << inputString[i];
    cout << "\t\t";
}

/*
    �������봮��Ԥ������������ܺ�����
    �����봮�����ķ��򷵻� 1���������򷵻�0
*/
bool yuCeFenXi() {
    // X�����洢ÿ�ε�����ջ��Ԫ��
    char X;
    // a�����洢�û����봮�ĵ�һ��Ԫ��
    char a;
    //�ñ�����¼�﷨�����Ĳ�����
    int counter = 1;

    cout << "������֧�ֵ��ķ�Ϊ��" << endl;
    cout << "E->Te" << endl;
    cout << "e->+Te | $" << endl;
    cout << "T->Ft" << endl;
    cout << "t->*Ft | $" << endl;
    cout << "F->(E) | i" << endl;
    cout << "������һ���ַ�������#������" << endl;
    cin >> inputString;

    stack.emplace_back('#');
    stack.emplace_back('E');

    cout << "����\t\tջ��\t\t���봮\t\t����" << endl;
    while (1) {
        cout << counter << "\t\t";
        printStack();
        X = stack.back();
        stack.pop_back();
        printinputString();
        //���ս������VT�в��ұ���X��ֵ
        if (!VT.count(X)) {
            if (X == '#') {
                //ջ�Ѿ����գ��﷨���������ȷ
                cout << endl;
                cout << "ʶ��ɹ�" << endl;
                return true;
            } else {
                a = inputString[firstCharIndex];
                //�鿴Ԥ�������M[A,a]�Ƿ���ڲ���ʽ�����ڷ���1�������ڷ���0
                if (M(X, a) == 1) {
                    //'$'Ϊ����ʽ�Ľ�����,�ҳ��ò���ʽ�����һ��Ԫ�ص��±�
                    for (int i = chanShengShi.find('$') - 1; i >= 0; i--)
                        stack.emplace_back(chanShengShi[i]);
                    cout << "�Ƶ�";
                } else {
                    cout << "Ԥ�������M[A,a]�����ڲ���ʽ��ʶ��ʧ��" << endl;
                    return false;
                }
            }
        } else {
            //�ս��
            if (X == inputString[firstCharIndex]) {
                //ƥ��
                firstCharIndex++;
                cout << "ƥ��";
            } else {
                cout << "ƥ�����ʶ��ʧ��" << endl;
                return false;
            }
        }
        counter++;
        cout << endl;
    }
}

int main() {
    yuCeFenXi();
    system("pause");
    return 0;
}