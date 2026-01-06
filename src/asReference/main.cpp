#include <iostream>
#include <vector>

using namespace std;

vector<int> init() {
    vector<int> v(6);
    int val = 0;
    for (int& i:v) { // init i as an index of v; int i:v would initialize a copy! So we can mutate in place.
        i = ++val;
    }
    return v;
}

// print out vector by passing constant reference
void printVec(const vector<int>& v) {
    for (int i:v) {cout << i << '\n';}
    cout << '\n';
}

// functionally identical to printVec, but it copies the vector in memory
void printVecBad(vector<int> v) {
    for (int i:v) {
        cout << i << '\n';
    }
}

// increment vector in place
void vecInc(vector<int>& v) {
    for (int& i:v) {
        i++;
    }
}

vector<int> vecIncClear(vector<int> v) {
    for (int& i:v) {i++;}
    return v;
}


int main() {
    vector<int> v = init();
    printVec(v);
    vecInc(v);
    printVec(v);
    v = vecIncClear(v);
    printVec(v);
}
