#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Token {
public:
    char kind;
    double value;
    Token(char k):kind{k},value{0.0}{}
    Token(char k, double v):kind{k},value{v}{}
};



vector<Token> get_token_vector(){
    vector<Token> tokens;
    char kind = 'n';
    double value = 0;
    while(cin >> kind >> value) {
        if (kind == '+' || kind == '-' || kind == '*' || kind == '/') {
            tokens.push_back(Token(kind));
            cout << "hello\n";
        } else {
            tokens.push_back(Token(kind,value));
        }
    }
    return tokens;
}

Token get_token(){
    char kind;
    cin >> kind;
    switch(kind) {
        case '+': case '-': case '*': case '/': case '(': case ')': {
            return Token(kind);
        }
        case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': case '.': {
            cin.putback(kind);
            double value;
            cin >> value;
            return Token('n',value);
        }
    }
}


string test;


int main() {
    //vector<Token> tokens = get_token_vector();
    //Token t1 = get_token();
    cout << "enter expression:\n";
    getline(cin, test);
    vector<bool> is_number;
    vector<bool> is_operator;

    for (int i=0; i<test.length(); i++) {
        if ((0x30 <= test[i] && test[i] <=0x39) || test[i] == 0x2E) {
            is_number.push_back(1);
        } else {
            is_number.push_back(0);
        }

        if (test[i] == '(' || test[i] == ')' || test[i] == '+' || test[i] == '-' || test[i] == '*' || test[i] == '/') {
            is_operator.push_back(1);
        } else {
            is_operator.push_back(0);
        }
    }
    is_number.push_back(0); // add padding
    is_operator.push_back(0); // add padding

    vector<Token> token_test;
    int double_length = 0;
    for (int i=0; i<is_number.size(); i++) {
        if (is_number[i]) {
            ++double_length;
        } else {
            if (double_length != 0) {
                cout << "cutting at " << i - double_length << " with snip length: " << double_length << '\n';
                double double_val = stod(test.substr(i - double_length, double_length));
                token_test.push_back(Token('n', double_val));
            }
            double_length = 0;
            if (is_operator[i]) {
                token_test.push_back(Token(test[i]));
            }
        }
    }


    for (Token t:token_test) {
        cout << t.kind << ' ' << t.value << '\n';
    }
    cout << '\n';
    /*
    char test;
    cin >> test;
    cin.putback(test);
    double test2;
    cin >> test2;
    cout << test2 << '\n';
    cout << "output\n";
    for (Token x:tokens) {
        cout << x.kind << ' ' << x.value << '\n';
    }

    cout << tokens.size() << '\n';
    */
}
