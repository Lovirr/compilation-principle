#include "compile.h"

Complier::Complier() {
    lexical = new LexicalAnalysis(prefix + "keyword.txt", &symbol, &signtable);
}

Complier::~Complier() {
    delete lexical;
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

bool Complier::complie() {
    if (!loadCode())
        return false;
    lexical->test(code);
    printSymbol();
    return true;
}

int main(int argc, char *argv[]) {
    Complier c;
    c.complie();
    return 0;
}