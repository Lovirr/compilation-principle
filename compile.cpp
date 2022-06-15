#include "compile.h"

Complier::Complier() {
    lexical = new LexicalAnalysis(prefix + "keyword.txt", &symbol, &signtable);
    grammar = new GrammarAnalysis(&symbol, &signtable, &quadtable);
    coder = new Coder(&quadtable);
}

Complier::~Complier() {
    delete lexical;
    delete grammar;
    delete coder;
}

bool Complier::loadCode() {
    string file;
    ifstream fin;
    cout << "�������ļ����ƣ�";
    cin >> file;
    fin.open(prefix + file);
    if (!fin.is_open()) {
        cout << "�޷����ļ�" << endl;
        system("pause");
        return false;
    }
    // C���Գ����ı��ַ���
    string c((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());
    code = c;
    fin.close();
    return true;
}

void Complier::printSymbol() {
    for (int i = 0; i < (int)symbol.size(); i++)
        cout << symbol[i].sign << " " << symbol[i].code << endl;
}

void Complier::printQuadTable() {
    for (int i = 0; i < (int)quadtable.size(); i++)
        cout << '(' << quadtable[i].op << "," << quadtable[i].arg1 << "," << quadtable[i].arg2 << "," << quadtable[i].result << ')' << endl;
}

bool Complier::complie() {
    if (!loadCode()) {
        cout << "�ļ���ʧ�ܣ�" << endl;
        return false;
    }
    cout << "C���Դ�������: " << endl;
    cout << code << endl;
    cout << "�ʷ�����������£�" << endl;
    lexical->test(code);
    printSymbol();
    cout << "��Ԫʽ���£�" << endl;
    grammar->analysis();
    printQuadTable();
    cout << "���������£�" << endl;
    coder->quadtocode();
    coder->printCode();
    return true;
}

int main(int argc, char *argv[]) {
    Complier c;
    c.complie();
    system("pause");
    return 0;
}