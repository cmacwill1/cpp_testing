#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<double> values(5);
    double sum = 0;
    cout << "put 5 doubles in the vector\n";
    for (int i = 0; i<values.size(); i++) {
        cin >> values[i];
    }

    cout << '\n';

    for (double i:values) {
        //cout << i << '\n';
        sum += i;
    }
    cout << "the average of the elements is: " << sum / values.size() << '\n';

    ranges::sort(values);
    cout << "The sorted vector is:\n";
    for (double i:values) {
        cout << i << '\n';
    }
}
