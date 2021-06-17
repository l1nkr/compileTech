
#include <iostream>
#include <cstring>
#include <fstream>
#include <cctype>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct symbol{
    string str;
    int coding;
    symbol():str(""), coding(0){};
}symbol;

vector<string> keywordList = {"void", "char", "int", "float", "double", "short", "long", "signed", "unsigned", "struct",
                              "union", "enum", "typedef", "sizeof", "auto", "static", "register", "extern", "const", "volatile",
                              "return", "continue", "break", "goto", "if", "else", "switch", "case", "default", "for", "do",
                              "while", "scanf", "printf"};
vector<string> operatorList = {"{", "}", "[", "]", "(", ")", ".", "->", "~", "++", "--", "!", "&", "*", "/", "%", "+", "-", "<<",
                               ">>", ">", ">=", "<", "<=", "==", "!=", "^", "|", "&&", "||", "?", "=", "/=", "*=", "%=", "+=", "-=",
                               "&=", "^=", "|=", ",", "#", ";", ":"};
char ch;
string strToken = "";
int row = 1;

vector<symbol> keywords(34), identifiers(44);

ifstream file;

//给单词符号设定编码
void initiallization(){
    int num = 1;
    for (int i = 0; i < 34; i++) {
        keywords[i].str = keywordList[i];
        keywords[i].coding = num;
        num++;
    }
    for (int i = 0; i < 44; i++) {
        identifiers[i].str = operatorList[i];
        identifiers[i].coding = num;
        num++;
    }
}

//把下一个字符读入 ch 中
void getNextChar(){
    file.get(ch);
    if (ch == '\n') row++;
}

//检查ch的字符是否为空白符、回车或者制表符，若是，则反复调用getNextChar()，直至ch中读入一非上述符号
void getbc(){
    while (ch == ' ' || ch == '\n' || ch == '\t') getNextChar();
}

//将输入的字符ch连接到strToken
void concat(){
    strToken += ch;
}

//放回去
void retract(){
    file.putback(ch);
}

//对于strToken中的字符串判断它是否为保留字，若为保留字则给出编码，否则返回0
int reserveString(string str){
    for (int i = 0; i < keywords.size(); i++) {
        if (keywords[i].str == str) return keywords[i].coding;
    }
    return 0;
}

//返回strToken中所识别的算符和界符编码
int reserveOperator(string str){
    for (int i = 0; i < identifiers.size(); i++) {
        if (identifiers[i].str == str) return identifiers[i].coding;
    }
    return 0;
}

//出错处理
void error(){
    cout << "error" << endl;
    cout << "row" << row << "Invalid symbol" << endl;
    exit(0);

}

//词法分析
void LexiscalAnalyzer(){
    int code;
    strToken = "";
    getNextChar();
    getbc();

    switch (ch){
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
        case 'g':
        case 'h':
        case 'i':
        case 'j':
        case 'k':
        case 'l':
        case 'm':
        case 'n':
        case 'o':
        case 'p':
        case 'q':
        case 'r':
        case 's':
        case 't':
        case 'u':
        case 'v':
        case 'w':
        case 'x':
        case 'y':
        case 'z':
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
        case 'G':
        case 'H':
        case 'I':
        case 'J':
        case 'K':
        case 'L':
        case 'M':
        case 'N':
        case 'O':
        case 'P':
        case 'Q':
        case 'R':
        case 'S':
        case 'T':
        case 'U':
        case 'V':
        case 'W':
        case 'X':
        case 'Y':
        case 'Z':
        case '_':
            while (isalpha(ch) || isdigit(ch) || ch == '_') {//含有 alpha digit underLine的标识符
                concat();//合并
                getNextChar();//继续拿下一个字符
            }
            retract();
            code = reserveString(strToken);
            if (code == 0) cout << 79 << "    ,  " << strToken << endl;
            else cout << code << "    ,  " << strToken << endl;
            break;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            while (isdigit(ch)) {//常数
                concat();
                getNextChar();
            }
            retract();
            cout << 80 << "    ,  " << strToken << endl;
            break;
        case '{':
        case '}':
        case '[':
        case ']':
        case '(':
        case ')':
        case '.':
        case '~':
        case '?':
        case ',':
        case '#':
        case ';':
        case ':':
        case '"':
        case '\'':
            concat();
            code = reserveOperator(strToken);
            cout << code << "    ,  " << strToken << endl;
            break;
        case '-':
            concat();
            getNextChar();
            if (ch == '>' || ch == '-' || ch == '=') concat();
            else retract();
            code = reserveOperator(strToken);
            cout << code << "    ,  " << strToken << endl;
            break;
        case '+':
            concat();
            getNextChar();
            if (ch == '+' || ch == '=') concat();
            else retract();
            code = reserveOperator(strToken);
            cout << code << "    ,  " << strToken << endl;
            break;
        case '*':
            concat();
            getNextChar();
            if (ch == '=') concat();
            else retract();
            code = reserveOperator(strToken);
            cout << code << "    ,  " << strToken << endl;
            break;
        case '&':
            concat();
            getNextChar();
            if (ch == '&' || ch == '=') concat();
            else retract();
            code = reserveOperator(strToken);
            cout << code << "    ,  " << strToken << endl;
            break;
        case '!':
            concat();
            getNextChar();
            if(ch == '=') concat();
            else retract();
            code = reserveOperator(strToken);
            cout << code << "    ,  " << strToken << endl;
            break;
        case '%':
            concat();
            getNextChar();
            if(ch == '=') concat();
            else retract();
            code = reserveOperator(strToken);
            cout << code << "    ,  " << strToken << endl;
            break;
        case '<':
            concat();
            getNextChar();
            if(ch == '=' || ch == '<') concat();
            else retract();
            code = reserveOperator(strToken);
            cout << code << "    ,  " << strToken << endl;
            break;
        case '>':
            concat();
            getNextChar();
            if(ch == '=' || ch == '>') concat();
            else retract();
            code = reserveOperator(strToken);
            cout << code << "    ,  " << strToken << endl;
            break;
        case '=':
            concat();
            getNextChar();
            if(ch == '=') concat();
            else retract();
            code = reserveOperator(strToken);
            cout << code << "    ,  " << strToken << endl;
            break;
        case '^':
            concat();
            getNextChar();
            if(ch == '=') concat();
            else retract();
            code = reserveOperator(strToken);
            cout << code << "    ,  " << strToken << endl;
            break;
        case '|':
            concat();
            getNextChar();
            if(ch == '=' || ch == '|') concat();
            else retract();
            code = reserveOperator(strToken);
            cout << code << "    ,  " << strToken << endl;
            break;
        case '/':
            concat();
            getNextChar();
            if(ch == '=') {
                concat();
                code = reserveOperator(strToken);
                cout << code << "    ,  " << strToken << endl;
            } else if (ch == '/') {
                getNextChar();
                while (ch != '\n') {
                    getNextChar();
                }
                break;
            } else if (ch == '*') {
                getNextChar();
                while (ch != '*') {
                    getNextChar();
                }
                getNextChar();
                if (ch == '/') break;
            } else {
                retract();
                code = reserveOperator(strToken);
                cout << code << "    ,  " << strToken << endl;
            }
            break;
        default:
            if (ch == EOF) {
                break;
            }
            error();
    }
}

int main(){
    initiallization();
    string fileName;
    cout << "please input file name" << endl;
    cin >> fileName;
    file.open(fileName);
    while(file.peek() != EOF) {
        LexiscalAnalyzer();
    }
    file.close();
    return 0;
}
