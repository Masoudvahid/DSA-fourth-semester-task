// https://contest.yandex.ru/contest/38500/run-report/69186585/
#include <iostream>
#include<cmath>

using std::cin;
using std::cout;
using std::max;
using std::endl;
using std::min;
using std::to_string;
using std::make_pair;
using std::swap;
using std::pair;
using std::abs;

struct node {
    node *left;
    node *right;
    int value;
    int height;
};

typedef struct node *Node;

class AVLBinaryTree {
public:
    void Insert(int x, Node &p);

    bool find(int, Node &);

    void preorder(Node);

    void inorder(Node);

    void postorder(Node);

    static int Height(Node);

    static Node srl(Node &);

    static Node drl(Node &);

    static Node srr(Node &);

    static Node drr(Node &);

    static int max(int, int);

    int nonodes(Node);

    static int MinForInputHelper(int, Node);

    static int MinForInput(int, Node);

};

// Inserting a node
void AVLBinaryTree::Insert(int x, Node &p) {
    if (p == nullptr) {
        p = new node;
        p->value = x;
        p->left = nullptr;
        p->right = nullptr;
        p->height = 0;
        if (p == nullptr) {
            return;
        }
    } else {
        if (x < p->value) {
            Insert(x, p->left);
            if ((Height(p->left) - Height(p->right)) == 2) {
                if (x < p->left->value) {
                    p = srl(p);
                } else {
                    p = drl(p);
                }
            }
        } else if (x > p->value) {
            Insert(x, p->right);
            if ((Height(p->right) - Height(p->left)) == 2) {
                if (x > p->right->value) {
                    p = srr(p);
                } else {
                    p = drr(p);
                }
            }
        } else {
            return;
        }
    }
    int m, n, d;
    m = Height(p->left);
    n = Height(p->right);
    d = max(m, n);
    p->height = d + 1;
}

// Finding a value
bool AVLBinaryTree::find(int x, Node &p) {
    if (p == nullptr) {
        return false;
    } else {
        if (x < p->value) {
            find(x, p->left);
        } else {
            if (x > p->value) {
                find(x, p->right);
            } else {
                return true;
            }
        }
    }
    return false;
}

void AVLBinaryTree::preorder(Node p) {
    if (p != nullptr) {
        cout << p->value << "\t";
        preorder(p->left);
        preorder(p->right);
    }
}

// Inorder Printing
void AVLBinaryTree::inorder(Node p) {
    if (p != nullptr) {
        inorder(p->left);
        cout << p->value << "\t";
        inorder(p->right);
    }
}

// PostOrder Printing
void AVLBinaryTree::postorder(Node p) {
    if (p != nullptr) {
        postorder(p->left);
        postorder(p->right);
        cout << p->value << "\t";
    }
}

int AVLBinaryTree::max(int value1, int value2) {
    return ((value1 > value2) ? value1 : value2);
}

int AVLBinaryTree::Height(Node p) {
    int t;
    if (p == nullptr) {
        return -1;
    } else {
        t = p->height;
        return t;
    }
}

Node AVLBinaryTree::srl(Node &p1) {
    Node p2;
    p2 = p1->left;
    p1->left = p2->right;
    p2->right = p1;
    p1->height = max(Height(p1->left), Height(p1->right)) + 1;
    p2->height = max(Height(p2->left), p1->height) + 1;
    return p2;
}

Node AVLBinaryTree::srr(Node &p1) {
    Node p2;
    p2 = p1->right;
    p1->right = p2->left;
    p2->left = p1;
    p1->height = max(Height(p1->left), Height(p1->right)) + 1;
    p2->height = max(p1->height, Height(p2->right)) + 1;
    return p2;
}

Node AVLBinaryTree::drl(Node &p1) {
    p1->left = srr(p1->left);
    return srl(p1);
}

Node AVLBinaryTree::drr(Node &p1) {
    p1->right = srl(p1->right);
    return srr(p1);
}

int AVLBinaryTree::nonodes(Node p) {
    int count = 0;
    if (p != nullptr) {
        nonodes(p->left);
        nonodes(p->right);
        count++;
    }
    return count;
}

int AVLBinaryTree::MinForInputHelper(int value, Node p) {
    Node curr = p;
    Node ans = nullptr;
    while (curr) {
        if (curr->value > value) {
            ans = curr;
            curr = curr->left;
        } else if (curr->value == value) {
            ans = curr;
            break;
        } else
            curr = curr->right;
    }
    if (ans != nullptr)
        return ans->value;
    return -1;
}

int AVLBinaryTree::MinForInput(int value, Node p) {
    return MinForInputHelper(value, p);

}

int main() {
    Node root;
    AVLBinaryTree bst;

    root = nullptr;

    int number_of_commands;
    std::string command;
    std::cin >> number_of_commands;
    int query_result;
    std::string last_provided_command;
    while (number_of_commands != 0) {
        number_of_commands--;
        std::cin >> command;
        if (command == "+") {
            int input_value;
            std::cin >> input_value;
            if (last_provided_command == "?") {
                if (bst.find((input_value + query_result) % (int) pow(10, 9), root)) {
                    continue;
                } else {
                    bst.Insert((input_value + query_result) % (int) pow(10, 9), root);
                }
            } else {
                bst.Insert(input_value, root);
            }
            last_provided_command = command;
            continue;
        }
        if (command == "?") {
            int input_value;
            std::cin >> input_value;
            query_result = bst.MinForInput(input_value, root);
            std::cout << query_result << "\n";
            last_provided_command = command;
            continue;
        }
    }
}
