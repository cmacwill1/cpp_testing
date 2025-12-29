#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <unistd.h>

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

vector<Token> operation_evaluator(vector<Token> token_vector, int solve_index) {
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

    double new_value = 0;
    switch (token_vector[solve_index].kind) {
        case '+': {
            new_value = token_vector[solve_index - first_number].value + token_vector[solve_index + second_number].value;
            break;
        }
        case '-': {
            new_value = token_vector[solve_index - first_number].value - token_vector[solve_index + second_number].value;
            break;
        }
        case '*': {
            new_value = token_vector[solve_index - first_number].value * token_vector[solve_index + second_number].value;
            break;
        }
        case '/': {
            new_value = token_vector[solve_index - first_number].value / token_vector[solve_index + second_number].value;
            break;
        }
        default: {
            throw runtime_error("Invalid operator");
        }
    }
    for (int i=solve_index - first_number; i <= solve_index + second_number; i++) {
        token_vector[i].kind = 'n';
        token_vector[i].value = 0;
    }
    token_vector[solve_index].kind = '#';
    token_vector[solve_index].value = new_value;
    return token_vector;
}

vector<Token> evaluate_expression(vector<Token> token_vector, int start_index, int end_index) {
    for (char ch:{'/','*','-','+'}) {
        for (int i=start_index; i <= end_index; i++) {
            if (token_vector[i].kind == ch) {
                token_vector = operation_evaluator(token_vector, i);
            }
        }
    }
    return token_vector;
}

vector<int> root_expression_finder(vector<Token> token_vector) {
    int parenthesis_counter = 0;
    int operation_counter = 0;
    for (int i = 0; i<token_vector.size(); i++) {
        if (token_vector[i].kind == '+' || token_vector[i].kind == '-' || token_vector[i].kind == '*' || token_vector[i].kind == '/') {
            operation_counter++;
        }
        if (token_vector[i].kind == '(') {
            parenthesis_counter = 0;
            operation_counter = 0;
        } else if (parenthesis_counter != ')') {
            parenthesis_counter++;
        }
        if (token_vector[i].kind == ')') {
            if (operation_counter == 0) {
                return vector<int> {i - parenthesis_counter, i, 1};
            } else {
                return vector<int> {i - parenthesis_counter, i, 0};
            }
        }
    }
    int wtf = token_vector.size(); // what the hell man
    return vector<int> {0,wtf,0};
}


int main() {
    cout << "enter expression:\nMATH REPL>> ";
    string user_input;
    getline(cin, user_input);
    vector<Token> token_vector = get_token_vector(user_input);


    int number_of_numbers = 0;
    while (number_of_numbers != 1) {
        number_of_numbers = 0;
        vector<int> checker = root_expression_finder(token_vector);

        token_vector = evaluate_expression(token_vector, checker[0], checker[1]);

        if (checker[2] == 1) {
            token_vector[checker[0]].kind = 'n';
            token_vector[checker[0]].value = 0;
            token_vector[checker[1]].kind = 'n';
            token_vector[checker[1]].value = 0;
        }

        for (Token t:token_vector) {
            if (t.kind == '#') {
                number_of_numbers++;
            }
        }

    }

    for (Token t:token_vector) {
        if (t.kind == '#') {
            cout << t.value << '\n';
        }
    }
    /*
    vector<int> solve_location = root_expression_finder(token_vector);
    if (solve_location[0] != 0) {
        for (int i=solve_location[1]; i < solve_location[1] + solve_location[0]; i++) {

        }
    }
    */
}
