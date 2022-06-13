#include <fstream>
#include <iostream>
#include <string>
#include <vector>
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

/**
 * @brief �ʷ���������
 *
 */
class LexicalAnalysis {
private:
    //�ؼ���
    struct property {
        string symbol;
        string code;
    };
    //�ؼ��ֱ�
    vector<property> propertytable;

    /**
     * @brief ���ַ���p�����ַ���������͵��ʱ���
     *
     * @param p Ҫ������ַ���
     * @param type �ַ���ǰ�Ƿ������������
     * @return bool �Ƿ�ɹ�
     */
    bool findcreate(string& p, bool type) {
        int i;
        for (i = 0; i < (int)signtable.size(); i++) {
            if (signtable[i].name == p) {
                symbol.emplace_back(word(p, 1));
                return true;
            }
        }
        // �ַ�����������û�е���p,�Ͱ�p�洢���ַ���������͵��ʱ���
        if (i == (int)signtable.size() && type) {
            symbol.emplace_back(word(p, 1));
            signtable.emplace_back(sign(p));
        }
        if (!type) {
            cout << p << "δ����!" << endl;
            return false;
        }
        return true;
    }
    /**
     * @brief �򵥴ʱ�����ӳ���������ĵ���
     *
     * @param p Ҫ�������ַ���
     * @param type �ַ���ǰ�Ƿ������������
     */
    void find(string& p, bool type) {
        int i;
        //����
        if (p[0] >= '0' && p[0] <= '9') {
            symbol.emplace_back(word(p, 2));
        } else {
            for (i = 0; i < (int)propertytable.size(); i++) {
                if (propertytable[i].symbol == p) {
                    symbol.emplace_back(word(p, atoi(propertytable[i].code.c_str())));
                    break;
                }
            }
            if (i == (int)propertytable.size()) {
                //������Ͼ����ַ�������
                if (isalpha(p[0]))
                    findcreate(p, type);
                else if (p[0] >= 32)
                    symbol.emplace_back(word(p, p[0]));
            }
        }
    }

public:
    //���ʱ�
    vector<word> symbol;
    //�ַ���������
    vector<sign> signtable;
    /**
     * @brief �ѹؼ��ֱ��е�symbol��code���뵽propertytable�ṹ����
     *
     * @param prefix  �ļ�����λ��,������,Ĭ��Ϊ��
     */
    void loadProperty(string prefix = "") {
        ifstream fin(prefix + "keyword.txt");
        if (!fin.is_open()) {
            cout << "�޷��ҵ��ؼ��ֱ�" << endl;
            return;
        }
        property p;
        while (!fin.eof()) {
            fin >> p.symbol >> p.code;
            propertytable.emplace_back(p);
        }
        // �ر��ļ�
        fin.close();
    }

    /**
     * @brief �Դ�����дʷ�����
     *
     * @param code �����ַ���
     */
    void test(string& code) {
        bool type = true;
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
                find(word, type);
            } else if (*p >= '0' && *p <= '9') {
                //�жϵ����Ƿ�Ϊ����
                word.clear();
                word += *p;
                p++;
                while (*p >= '0' && *p <= '9') {
                    word += *p;
                    p++;
                }
                find(word, type);
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
                find(word, type);
            } else if (*p == ' ') {
                p++;
            } else {
                word.clear();
                word += *p;
                if (word == ";") {
                    type = false;
                }
                p++;
                find(word, type);
            }
        }
    }

    //��ӡ���ʱ�
    void printSymbol() {
        for (int i = 0; i < (int)symbol.size(); i++)
            cout << symbol[i].sign << " " << symbol[i].code << endl;
    }
};

int main(int argc, char* argv[]) {
    string prefix;
    if (argc >= 2)
        prefix = argv[1];
    LexicalAnalysis la;
    la.loadProperty(prefix);
    // �ļ������ַ���
    string file;
    ifstream fin;
    cout << "�������ļ����ƣ�";
    cin >> file;
    fin.open(prefix + file);
    if (!fin.is_open()) {
        cout << "�޷����ļ�" << endl;
        system("pause");
        return 1;
    }
    // C���Գ����ı��ַ���
    string code((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());
    fin.close();
    cout << "C���Գ����ı�Ϊ:" << endl;
    cout << code << endl;
    // �Գ�����дʷ�����
    la.test(code);
    cout << "�ʷ��������Ϊ��" << endl;
    la.printSymbol();
    system("pause");
    return 0;
}