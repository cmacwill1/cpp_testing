#include <cmath>
#include <exception>
#include <iostream>
#include <random>
#include <string>
#include <stdexcept>

using namespace std;

[[noreturn]] void error(string s) {
    throw runtime_error(s);
}

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


class Dice_engine {
public:
    int roll(int nrolls, int dice);
private:
    default_random_engine generator;
};

int Dice_engine::roll(int nrolls, int dice)
{
    uniform_int_distribution distribution(1,dice);
    int total = 0;
    for (int i = 0; i<nrolls; i++) {
        total += distribution(generator);
    }
    return total;
}


void Token_stream::putback(Token t)
{
    buffer = t;
    is_full = true;
}

Token Token_stream::get()
{
    if(is_full) {
        is_full = false;
        return buffer;
    }
    char ch = 0;
    if (!(cin >> ch)) {
        error("No input");
    }
    switch(ch) {
        case';':
        case'q':
        case'(':
        case')':
        case'+':
        case'-':
        case'*':
        case'/':
        case'd':
        {
            return Token{ch};
        }
        case'.':
        case'0':
        case'1':
        case'2':
        case'3':
        case'4':
        case'5':
        case'6':
        case'7':
        case'8':
        case'9':
        {
            cin.putback(ch);
            double val = 0;
            cin >> val;
            return Token{'#',val};
        }
        default:
            error("bad token");
    }
}










Token_stream ts;
Dice_engine de;

double expression();

double primary()
{
    Token t = ts.get();
    switch (t.kind) {
        case '(':
        {
            double d = expression();
            t = ts.get();
            if (t.kind != ')') {
                error("')' expected");
            }
            return d;
        }
        case '#':
        {
            return t.value;
        }
        case '-':
        {
            return -primary();
        }
        case '+':
        {
            return primary();
        }
        default:
            error("primary expected");
    }
}

double term()
{
    double left = primary();
    Token t = ts.get();
    while (true) {
        switch (t.kind) {
            case 'd':
            {
                int d_num1 = static_cast<int>(round(left));
                int d_num2 = static_cast<int>(round(primary()));
                left = static_cast<double>(de.roll(d_num1,d_num2));
                t = ts.get();
                break;
            }
            case '*':
            {
                left *= primary();
                t = ts.get();
                break;
            }
            case '/':
            {
                double d = primary();
                if (d == 0) {
                    error("divide by 0");
                }
                left /= d;
                t = ts.get();
                break;
            }
            default:
                ts.putback(t);
                return left;
        }
    }
}

double expression()
{
    double left = term();
    Token t = ts.get();
    while (true) {
        switch (t.kind) {
            case '+':
            {
                left += term();
                t = ts.get();
                break;
            }
            case '-':
            {
                left -= term();
                t = ts.get();
                break;
            }
            default:
                ts.putback(t);
                return left;
        }
    }
}

int main()
{
    double val = 0;
    while (cin) {
        try {
            Token t = ts.get();
            if (t.kind == 'q') //quit
                break;
            if (t.kind == ';') {
                cout << val << '\n';
            }
            else {
                ts.putback(t);
            }
            val = expression();
        }
        catch (exception& e) {
            cerr << "Exception: " << e.what() << '\n';
            return 1;
        }
        catch (...) {
            cerr << "Unknown Exception: " << '\n';
            return 2;
        }
    }
}
