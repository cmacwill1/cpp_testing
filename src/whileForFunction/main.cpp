#include <iostream>

using namespace std;

double square(double x) {
    return x*x;
}


int main()
{
    double userchoice = 0;
    int while_i = 0;
    cout << "Please enter a number to start squaring at:\n";
    cin >> userchoice;
    double tmp_userchoice = userchoice;

    cout << "\nWhile loop\n";

    while (while_i < 10) {
        tmp_userchoice++;
        double out_userchoice = square(tmp_userchoice);
        while_i++;
        cout << tmp_userchoice << " squared == " << out_userchoice << '\n';
    }

    cout << "\nFor loop\n";

    tmp_userchoice = userchoice;
    for (int i=0; i<10; i++){
        tmp_userchoice++;
        double out_userchoice = square(tmp_userchoice);
        cout << tmp_userchoice << " squared == " << out_userchoice << '\n';
    }
}
