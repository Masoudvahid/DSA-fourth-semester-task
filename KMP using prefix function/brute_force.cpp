// KMP using brute force
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::string;

int main() {
    string input;
    cin >> input;

    vector<int> pi_function(input.size());
    // The first value always has prefix equal to 0
    pi_function[0] = 0;
    // Find the prefix function for the rest of the array
    for (int i = 1; i < input.size(); i++) {
        for (int j = 0; j < i; j++) {
            if (input.substr(0, j) == input.substr(i - j + 1, j)) {
                pi_function[i] = j;
            }
        }
    }

    // Print output
    for (const auto &item: pi_function) {
        cout << item;
    }

}