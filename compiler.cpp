#include "compiler.h"

void Compiler::init(string filename) {
    lexical.loadProperty(filename);
}

void Compiler::compile(string& code) {
    lexical.analyse(code);
    // printSymbol();
    grammar.analyse();
    printQuad();
    comBuilder.build();
    printCom();
}

void Compiler::printSymbol() {
    cout << "�ʷ������������: " << endl;
    for (int i = 0; i < symbolTableSize; i++)
        cout << symbolTable[i].sign << " " << symbolTable[i].code << endl;
}

void Compiler::printQuad() {
    int i;
    cout << "��Ԫʽ���£�" << endl;
    for (i = 1; i < quadIndex; i++) {
        cout << '(' << i << "): ";
        cout << '(' << quadTable[i].op << "," << quadTable[i].arg1 << "," << quadTable[i].arg2 << "," << quadTable[i].result << ')' << endl;
    }
}

void Compiler::printCom() {
    comBuilder.printCom();
}

int main(int argc, char* argv[]) {
    string prefix;
    prefix = "D:\\Code\\C++\\CompilationPrinciple\\code\\";
    class Compiler compiler;
    compiler.init(prefix + "keyword.txt");
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
    cout << "C���Դ�������: " << endl;
    cout << code << endl;
    compiler.compile(code);
    system("pause");
    return 0;
}