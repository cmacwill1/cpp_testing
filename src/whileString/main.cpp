#include <iostream>
#include <string>

using namespace std;

int main()
{
    int word_counter = 0;
    string current = "new";
    string previous = "old";
    while (cin >> current) {
        word_counter++;
        if (current == previous) {
            cout << "Same word: " << current << "\nword count: " << word_counter << '\n';
        }
        previous = current;
    }
}
