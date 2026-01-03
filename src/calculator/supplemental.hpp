#include <vector>
#include <string>

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
vector<Token> get_token_vector(string str);
// really just to handle negative numbers, in absense of special negative value
vector<Token> preprocessor(vector<Token> token_vector);
// Find a "root expression" IE the first instance of the most nested parenthesis
// Returns a vector of ints with {start index, end index, is there still an operator?}
vector<int> root_expression_finder(vector<Token> token_vector);

// The following function solves at an operator.
// Pass in the index of the operator to solve for within the token vector, and the token vector.
vector<Token> operation_evaluator(vector<Token> token_vector, int solve_index);

// given a root expression (IE start and end index of something to evaluate down to a single float), evaluate it via order of operations.
// NOTE: / and - are NOT COMMUTATIVE!!! So it is imperitave that they are calculated first, apart from PEMDAS.
// This is sort of scuffed, but works plenty fine.
vector<Token> evaluate_expression(vector<Token> token_vector, int start_index, int end_index);
