#include<iostream>
#include<vector>

using std::cin;
using std::cout;
using std::vector;
using std::string;
using std::endl;

vector<int> occurrence; // vector to store the start index from where the pattern matched

vector<int> FindPrefix(string text, size_t pattern_size) {
    int length = 0;
    vector<int> prefArray(pattern_size);

    for (int i = 1; i < pattern_size; i++) {
        if (text[i] == text[length]) {
            length++;
            prefArray[i] = length;
        } else {
            if (length != 0) {
                length = prefArray[length - 1];
                i--;     //decrease i to avoid effect of increasing after iteration
            } else
                prefArray[i] = 0;
        }
    }
    return prefArray;
}

void KMPSearch(string text, string pattern) {
    int i = 0, j = 0;
    vector<int> prefixArray = move(FindPrefix(pattern, pattern.size()));
    while (i < text.size()) {
        if (text[i] == pattern[j]) {
            i++;
            j++;
        }
        if (j == pattern.size()) {
            occurrence.push_back(i - j);      //item found at i-j position.
            j = prefixArray[j - 1];    //get the FindPrefix length from array
        } else if (i < text.size() && pattern[j] != text[i]) {
            if (j != 0)
                j = prefixArray[j - 1];
            else
                i++;
        }
    }
}

int main() {
    string text = "aaaabaaaaabbbaaaab";
    string pattern = "aaab";
    KMPSearch(text, pattern);

    for (const auto &item: occurrence) {
        cout << "Pattern found at index: " << item << endl;
    }
}
 