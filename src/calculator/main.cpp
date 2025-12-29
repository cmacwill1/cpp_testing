#include <iostream>
#include <stdexcept>
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

vector<Token> get_token_vector(string str) {
    vector<bool> is_number;
    vector<bool> is_operator;

    for (int i=0; i<str.length(); i++) {
        if ((0x30 <= str[i] && str[i] <=0x39) || str[i] == 0x2E) {
            is_number.push_back(1);
        } else {
            is_number.push_back(0);
        }

        if (str[i] == '(' || str[i] == ')' || str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') {
            is_operator.push_back(1);
        } else {
            is_operator.push_back(0);
        }
    }
    is_number.push_back(0); // add padding to trigger getting final number
    is_operator.push_back(0); // add padding to trigger getting final number

    vector<Token> token_str;
    int double_length = 0;
    for (int i=0; i<is_number.size(); i++) {
        if (is_number[i]) {
            ++double_length;
        } else {
            if (double_length != 0) {
                double double_val = stod(str.substr(i - double_length, double_length));
                token_str.push_back(Token('#', double_val));
            }
            double_length = 0;
            if (is_operator[i]) {
                token_str.push_back(Token(str[i]));
            }
        }
    }
    return token_str;
}

double evaluate_token_map(vector<Token> token_vector, int solve_index) {
    int first_number = 1;
    int second_number = 1;
    bool is_valid = 1;
    while(is_valid) {
        if (token_vector[solve_index - first_number].kind != '#') {
            first_number++;
        } else if (token_vector[solve_index + second_number].kind != '#') {
            second_number++;
        } else {
            is_valid = 0;
        }
    }

    switch (token_vector[solve_index].kind) {
        case '+': {
            return token_vector[solve_index - first_number].value + token_vector[solve_index + second_number].value;
        }
        case '-': {
            return token_vector[solve_index - first_number].value - token_vector[solve_index + second_number].value;
        }
        case '*': {
            return token_vector[solve_index - first_number].value * token_vector[solve_index + second_number].value;
        }
        case '/': {
            return token_vector[solve_index - first_number].value / token_vector[solve_index + second_number].value;
        }
        default: {
            throw runtime_error("Invalid operator");
        }
    }
}


int main() {
    cout << "enter expression:\n";
    string user_input;
    getline(cin, user_input);
    vector<Token> token_vector = get_token_vector(user_input);



    for (Token t:token_vector) {
        cout << t.kind << ' ' << t.value << '\n';
    }
    cout << '\n';

    double value = evaluate_token_map(token_vector, 1);
    cout << value << '\n';
}
