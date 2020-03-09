#include <iostream>
#include <string>

using namespace std;

int main () {
    string str = "";
    char c = *str.begin();

    if (c == ' ') {
        cout << 1 << endl;
    }
    if (c == '\0') {
        cout << 2 << endl;
    }

    //cout << c;
}