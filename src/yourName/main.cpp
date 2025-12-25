#include <iostream>
#include <string>

using namespace std;

int main()
{
    cout << "Enter Name (first & last) and age (years):\n";
    string first_name;
    string last_name;
    double age;
    cin >> first_name >> last_name >> age;
    cout << "Hello " << first_name << " " << last_name << "\n";
    int months = age * 12;
    cout << "You are " << age << " years old, (" << months << " months)\n";

    // do note that this string comparison hits the first character and compares it; case matters; it seems lowercase > uppercase
    if (first_name == last_name) {
        cout << "First and last names are the same\n";
    } else if (first_name > last_name) {
        cout << "First name > last name (alphabetically)\n";
    } else {
        cout << "First name < last name (alphabetically)\n";
    }
}
