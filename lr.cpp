#include <fstream>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

//��ʱ���
//����
struct word {
    string sign;
    int code;

    word() : sign(""), code(0){};
    word(string s, int c) : sign(s), code(c){};
};
//���ʱ�
vector<word> symbol;

//�ַ�������
struct sign {
    string name;
    string cat;
    string type;
    int value;

    sign() : name(""), cat(""), type(""), value(0){};
    sign(string n) : name(n), cat(""), type(""), value(0){};
    sign(string n, int v) : name(n), cat(""), type(""), value(v){};
    sign(string n, string c, string t, int v) : name(n), cat(c), type(t), value(v){};
};
//�ַ���������
vector<sign> signtable;

//��Ԫʽ
struct quad {
    string op;
    string arg1;
    string arg2;
    string result;
};
vector<quad> quadtable;

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
// END

class Parser {
private:
    //��ǰ��ʱ�������±�
    int index = 0;
    //��ʱ������
    vector<int> signTableTemp;

public:
    int findstring(int x) {
        int i;
        for (i = 0; i < (int)symbol.size(); i++)
            if (atoi(symbol[i].sign.c_str()) == x)
                break;
        return i;
    }

    // ������ķ��ű���ڵ�ַ
    int entry(string& p) {
        int i;
        for (i = 0; i < (int)signtable.size(); i++) {
            if (signtable[i].name == p) {
                return i;
            }
        }
        if (p == "T") {
            i = 1000 + index;
            index++;
        } else {
            i = stoi(p.c_str()) + 10000;
        }
        return i;
    }

    int newtemp(char op, int E1_place, int E2_place) {
        int temp, temp1, temp2;
        string T = 'T' + to_string(index);
        if (E1_place >= 10000)
            temp1 = E1_place - 10000;
        else if (E1_place >= 1000)
            temp1 = signTableTemp[E1_place - 1000];
        else
            temp1 = signtable[E1_place].value;
        if (E2_place >= 10000)
            temp2 = E2_place - 10000;
        else if (E2_place >= 1000)
            temp2 = signTableTemp[E2_place - 1000];
        else
            temp2 = signtable[E2_place].value;
        if (op == '+')
            temp = temp1 + temp2;
        else if (op == '*')
            temp = temp1 * temp2;
        else if (op == '-')
            temp = temp1 - temp2;
        else if (op == '/') {
            if (temp2 != 0)
                temp = temp1 / temp2;
        }
        signTableTemp.emplace_back(temp);
        return 1000 + index;
    }

    // ������Ԫʽ
    void gen(string op, int arg1, int arg2, string result) {
        quad q;
        q.op = op;
        if (arg1 >= 10000)
            q.arg1 = symbol[findstring(arg1 - 10000)].sign;
        else if (arg1 == -1)
            q.arg1 = "-";
        else if (arg1 >= 1000)
            q.arg1 = "T" + to_string(arg1 - 1000);
        else
            q.arg1 = signtable[arg1].name;
        if (arg2 >= 10000)
            q.arg2 = symbol[findstring(arg2 - 10000)].sign;
        else if (arg2 == -1)
            q.arg2 = "-";
        else if (arg2 >= 1000)
            q.arg2 = "T" + to_string(arg2 - 1000);
        else
            q.arg2 = signtable[arg2].name;
        if (result == "T") {
            q.result = "T" + to_string(index);
        } else {
            q.result = result;
        }
        quadtable.emplace_back(q);
        index++;
        // NXQ = quad_i;
    }

    void gen(char op, int arg1, int arg2, string result) {
        string op1(1, op);
        gen(op1, arg1, arg2, result);
    }
};

// LR�﷨��������
class LRAnalysis {
private:
    // LR������
    const int LRTable[14][9] = {
        {3, -1, -1, -1, -1, 2, -1, -1, 1},
        {-1, 4, 5, 6, 7, -1, -1, -2, -1},
        {3, -1, -1, -1, -1, 2, -1, -1, 8},
        {-1, 106, 106, 106, 106, -1, 106, 106, -1},
        {3, -1, -1, -1, -1, 2, -1, -1, 9},
        {3, -1, -1, -1, -1, 2, -1, -1, 10},
        {3, -1, -1, -1, -1, 2, -1, -1, 11},
        {3, -1, -1, -1, -1, 2, -1, -1, 12},
        {-1, 4, 5, 6, 7, -1, 13, -1, -1},
        {-1, 101, 101, 6, 7, -1, 101, 101, -1},
        {-1, 102, 102, 6, 7, -1, 102, 102, -1},
        {-1, 103, 103, 103, 103, -1, 103, 103, -1},
        {-1, 104, 104, 104, 104, -1, 104, 104, -1},
        {-1, 105, 105, 105, 105, -1, 105, 105, -1}};
    Parser* parser;

    /**
     * @brief ���LR�������ͷ���±�
     *
     * @param a �������
     * @return int LR�������ͷ���±�
     */
    int getLRIndex(int a) {
        int PAT[9] = {'i', 3, 4, 5, 6, 17, 18, '#', 'E'};
        for (int i = 0; i < 9; i++) {
            if (a == PAT[i])
                return i;
        }
        return 7;
    }

public:
    LRAnalysis() {
        parser = new Parser();
    }

    ~LRAnalysis() {
        delete parser;
    }

    /**
     * @brief �Դ������LR�﷨������������Ԫʽ
     *
     * @return �Ƿ�����ɹ�
     */
    bool sentenceAnalysis() {
        //��ǰ�����ʷ��±�
        int index = 0;
        int E1_place, E2_place;
        stack<int> s1, s2;
        stack<int> s3;
        s1.emplace(0);
        //ѹ��#
        s2.emplace(24);
        s3.emplace('@');
        //����ĵ������
        int sym = symbol[index++].code;
        if (sym == 1 || sym == 2)
            sym = 'i';
        //�Ƿ�����ɹ�
        bool acc = false;
        while (!acc) {
            int action = LRTable[s1.top()][getLRIndex(sym)];
            if (action == -1) {
                cout << "�����﷨����ʧ��" << endl;
                return false;
            } else if (action == -2)
                acc = true;
            else if (action >= 0 && action < 100) {
                //�ƽ�����
                s1.emplace(action);
                s2.emplace(sym);
                if (sym == 'i')
                    s3.emplace(parser->entry(symbol[index - 1].sign));
                else
                    s3.emplace('@');
                sym = symbol[index++].code;
                if (sym == 1 || sym == 2)
                    sym = 'i';
            } else if (action >= 100 && action < 200) {
                char op = 0;
                //��Լ����
                switch (action) {
                //��Լ:E -> E + E
                case 101:
                    op = '+';
                    break;
                //��Լ:E -> E - E
                case 102:
                    op = '-';
                    break;
                //��Լ:E -> E * E
                case 103:
                    op = '*';
                    break;
                //��Լ:E -> E / E
                case 104:
                    op = '/';
                    break;
                //��Լ:E -> (E)
                case 105: {
                    s1.pop();
                    s1.pop();
                    s1.pop();
                    s2.pop();
                    s2.pop();
                    s2.pop();
                    s2.emplace('E');
                    s3.pop();
                    int temp = s3.top();
                    s3.pop();
                    s3.pop();
                    action = s1.top();
                    s1.emplace(LRTable[action][getLRIndex('E')]);
                    s3.emplace(temp);
                    break;
                }
                //��Լ:E -> i
                case 106:
                    s1.pop();
                    s2.pop();
                    s2.emplace('E');
                    action = s1.top();
                    s1.emplace(LRTable[action][getLRIndex('E')]);
                    break;
                }
                if (op) {
                    s1.pop();
                    s1.pop();
                    s1.pop();
                    s2.pop();
                    s2.pop();
                    s2.pop();
                    s2.emplace('E');
                    E2_place = s3.top();
                    s3.pop();
                    s3.pop();
                    E1_place = s3.top();
                    s3.pop();
                    s3.emplace(parser->newtemp(op, E1_place, E2_place));
                    parser->gen(op, E1_place, E2_place, "T");
                    action = s1.top();
                    s1.emplace(LRTable[action][getLRIndex('E')]);
                }
            }
        }
        return true;
    }
};

void printQuad() {
    for (int i = 0; i < (int)quadtable.size(); i++)
        cout << '(' << quadtable[i].op << "," << quadtable[i].arg1 << "," << quadtable[i].arg2 << "," << quadtable[i].result << ')' << endl;
}

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
    LRAnalysis lr;
    // �Գ�������﷨����
    if (lr.sentenceAnalysis()) {
        cout << "�﷨�����ɹ�" << endl;
        printQuad();
    }
    system("pause");
    return 0;
}