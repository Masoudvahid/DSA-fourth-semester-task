// https://contest.yandex.ru/contest/38500/run-report/68936767/

#include<iostream>
#include<vector>
#include<set>

using std::cin;
using std::cout;
using std::vector;
using std::set;
using std::string;
using std::endl;

vector<int> array;

struct Node {
    int value;
    Node *right;
    Node *left;

};

Node *NewNode(int data) {
    Node *new_node = new Node;
    new_node->value = data;
    new_node->right = nullptr;
    new_node->left = nullptr;
    return new_node;
}

Node *InsertNode(Node *node, int value) {
    if (node == nullptr) {
        node = NewNode(value);
    }
    if (value > node->value) {
        node->right = InsertNode(node->right, value);
    }
    if (value < node->value) {
        node->left = InsertNode(node->left, value);
    }

    return node;
}

void PrintLeafs(Node *tree) {
    if (tree->left != nullptr) {
        PrintLeafs(tree->left);
    }
    if (tree->right != nullptr) {
        PrintLeafs(tree->right);
    }
    if (tree->left == nullptr && tree->right == nullptr) {
        cout << tree->value << " ";
    }
}

int main() {
    int input;
    while (cin >> input && input != 0) {
        array.push_back(input);
    }

    // Create tree form the given array
    Node *tree = nullptr;
    for (const auto &item: array) {
        tree = InsertNode(tree, item);
    }

    PrintLeafs(tree);
}
