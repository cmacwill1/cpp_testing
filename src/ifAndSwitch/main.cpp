#include <iostream>

using namespace std;

int main()
{
    bool user_signal = true;
    while (user_signal) {
        int user_choice = 0;
        double distance = 0;
        cout << "Enter imperial distance, and a case:\nCase 1: feet to miles\nCase 2: feet to inches\nCase 3: feet to yards\nCase 4: quit\n";
        cin >> distance >> user_choice;
        switch (user_choice) {
            case 1: {
                double out_distance = distance / 5480;
                cout << distance << " feet is " << out_distance << " miles\n";
                break;
            }
            case 2: {
                double out_distance = distance * 12;
                cout << distance << " feet is " << out_distance << " inches\n";
                break;
            }
            case 3: {
                double out_distance = distance / 3;
                cout << distance << " feet is " << out_distance << " yards\n";
                break;
            }
            case 4: {
                user_signal = false;
            }
        }
    }
}
