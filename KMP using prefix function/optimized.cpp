// KMP using optimized version
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
    for (int i = 1; i < input.size(); i++) {
        int j = pi_function[i - 1];
        while (j > 0 && input[i] != input[j]) {
            j = pi_function[j - 1];
        }
        if (input[i] == input[j]) {
            j++;
        }
        pi_function[i] = j;
    }

    // Print output
    for (const auto &item: pi_function) {
        cout << item;
    }
}