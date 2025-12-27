#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

void error(string s) {
    throw runtime_error(s);
}

double get_input() {
    double user_input = 0;
    cin >> user_input;
    if (cin.fail()) {
        error("Not a double!");
        return 1;
    } else {
        return user_input;
    }
}

int main()
{
    cout << "Enter days to convert to hours:\n";
    try {
        string s(5,'x');
        double func_output = get_input();
        cout << func_output << " days is " << func_output * 24 << " hour\n";
        cout << s << '\n';
        return 0;
    } catch(runtime_error& e) {
        cerr << "error: " << e.what() << "\n";
    }
}
