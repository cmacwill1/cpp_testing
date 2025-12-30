#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

// A class for storing the tokens of the expression
class Token {
public:
    char kind;
    double value;
    Token(char k):kind{k},value{0.0}{}
    Token(char k, double v):kind{k},value{v}{}
};

// from a string, return a vector of valid tokens
vector<Token> get_token_vector(string str) {
    // construct vectors of booleans to represent string character's Token type.
    vector<bool> is_number; //is index i a number? '.' included, as these will be floats
    vector<bool> is_operator; // is index i an operator?
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
    // add padding to trigger getting final number
    is_number.push_back(0);
    is_operator.push_back(0);

    //construct token vector
    vector<Token> token_vector;
    // init with "null"
    token_vector.push_back(Token('n',0));
    // extract sequences of numbers, converted to doubles
    int double_length = 0;
    for (int i=0; i<is_number.size(); i++) {
        if (is_number[i]) {
            ++double_length;
        } else {
            if (double_length != 0) {
                double double_val = stod(str.substr(i - double_length, double_length)); //slice string from current index - length of the float, till end of the float.
                token_vector.push_back(Token('#', double_val));
            }
            double_length = 0;
            if (is_operator[i]) {
                token_vector.push_back(Token(str[i])); //pushes valid operators ONLY to the vector of tokens; needs a case to check for bad syntax.
            }
        }
    }
    return token_vector;
}

// really just to handle negative numbers, in absense of special negative value
vector<Token> preprocessor(vector<Token> token_vector) {
    if (token_vector[1].kind == '-') {
        token_vector[0].kind = '#';
        token_vector[0].value = 0;
    }

    for (int i=2; i<token_vector.size(); i++) {
        if (token_vector[i].kind == '#' && token_vector[i-1].kind == '-' && token_vector[i-2].kind != '#') {
            token_vector[i].value *= -1;
            token_vector[i-1].kind = 'n';
            token_vector[i-1].value = 0;
        }
    }

    return token_vector;

}

// Find a "root expression" IE the first instance of the most nested parenthesis
// Returns a vector of ints with {start index, end index, is there still an operator?}
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

// The following function solves at an operator.
// Pass in the index of the operator to solve for within the token vector, and the token vector.
vector<Token> operation_evaluator(vector<Token> token_vector, int solve_index) {
    int first_number = 1;
    int second_number = 1;
    bool is_valid = 1;
    // by default, checks left and right of the operator for numbers (.kind == '#'); if there are no numbers, increment and check.
    while(is_valid) {
        if (token_vector[solve_index - first_number].kind != '#') {
            first_number++;
        } else if (token_vector[solve_index + second_number].kind != '#') {
            second_number++;
        } else {
            is_valid = 0;
        }
    }

    //solve the operation given the operator, numbers, and their location.
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

    //replace all indices with "nulls"
    for (int i=solve_index - first_number; i <= solve_index + second_number; i++) {
        token_vector[i].kind = 'n';
        token_vector[i].value = 0;
    }
    // drop in solved number in the solved index's place
    token_vector[solve_index].kind = '#';
    token_vector[solve_index].value = new_value;
    //return new token_vector
    return token_vector;
}

// given a root expression (IE start and end index of something to evaluate down to a single float), evaluate it via order of operations.
// NOTE: / and - are NOT COMMUTATIVE!!! So it is imperitave that they are calculated first, apart from PEMDAS.
// This is sort of scuffed, but works plenty fine.
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

// Given a token vector, return the output
double calculator(vector<Token> token_vector) {
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
