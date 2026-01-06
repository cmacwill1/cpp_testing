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

class Token_stream {
public:
    Token get();
    void putback(Token t);
private:
    bool is_full = false;
    Token buffer = 0;
};

double expression();
double primary();
double term();
