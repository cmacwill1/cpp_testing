#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include "supplemental.hpp"

using namespace std;


// Given a token vector, return the output
double calculator(vector<Token> token_vector)
{
    // once this hits 1 (only one number left), returns that number
    int number_of_numbers = 0;
    while (number_of_numbers != 1) {
        number_of_numbers = 0;
        // find next root expression
        vector<int> checker = root_expression_finder(token_vector);
        // evaluated that nested expression
        token_vector = evaluate_expression(token_vector, checker[0], checker[1]);
        // if there are no operators in the root expression, replace ( ) with null 'n'
        if (checker[2] == 1) {
            token_vector[checker[0]].kind = 'n';
            token_vector[checker[0]].value = 0;
            token_vector[checker[1]].kind = 'n';
            token_vector[checker[1]].value = 0;
        }
        // count numbers
        for (Token t:token_vector) {
            if (t.kind == '#') {
                number_of_numbers++;
            }
        }
    }

    // return final double
    for (Token t:token_vector) {
        if (t.kind == '#') {
            return t.value;
        }
    }
    throw runtime_error("Calculator failed, somehow");
}

int main() {
    cout << "Welcome to Calculator REPL version 1.0\nEnter expression with +,-,*,/ operators\nParenthesis (,) also supported\nEnter 'quit' to quit.\n" << '\n';
    bool running = 1;
    while(running) {
        cout << "Calculator REPL>> ";
        string user_input;
        getline(cin, user_input);
        if (user_input == "quit") {
            running = 0;
            break;
        }
        vector<Token> token_vector = get_token_vector(user_input);
        token_vector = preprocessor(token_vector);
        double returned_value = calculator(token_vector);
        cout << returned_value << '\n';
    }
}
