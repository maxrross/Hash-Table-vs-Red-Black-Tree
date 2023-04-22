#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>
#include <fstream>

using namespace std;

enum Color {RED, BLACK};

struct Person {
    std::string fName;
    std::string lName;
    std::string address;
    std::string city;
    std::string state;
    std::string zip;
    std::string phoneNum;
};

struct Node {
    Person person;
    Node *parent;
    Node *left;
    Node *right;
    Color color;
};

class RedBlack {
public:
    RedBlack();
    void Insert(std::string fName, std::string lName, std::string address, std::string city, std::string state,
                std::string zip, std::string phoneNum);
    void Search(std::string first, std::string last);
    void Print();
    void LeftRotate(Node *x);
    void RightRotate(Node *x);
    Node *TreeMinimum(Node *x);
    Node *TreeMaximum(Node *x);
    Node *TreeSuccessor(Node *x);
    Node *TreePredecessor(Node *x);
    Node *Search(std::string first, std::string last, Node *x);
    Node *root;
    Node *nodington;
};

RedBlack::RedBlack() {
    nodington = new Node;
    nodington->color = BLACK;
    nodington->left = nullptr;
    nodington->right = nullptr;
    nodington->parent = nullptr;
    root = nodington;
}

void RedBlack::LeftRotate(Node *x) {
    Node *y = x->right;
    x->right = y->left;

    if (y->left != nodington)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == nodington)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

void RedBlack::RightRotate(Node *x) {
    Node *y = x->left;
    x->left = y->right;

    if (y->right != nodington)
        y->right->parent = x;

    y->parent = x->parent;

    if (x->parent == nodington)
        root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;

    y->right = x;
    x->parent = y;
}

Node *RedBlack::TreeMinimum(Node *x) {
    while (x->left != nodington)
        x = x->left;
    return x;
}

Node *RedBlack::TreeMaximum(Node *x) {
    while (x->right != nodington)
        x = x->right;
    return x;
}

Node *RedBlack::TreeSuccessor(Node *x) {
    if (x->right != nodington)
        return TreeMinimum(x->right);
    Node *y = x->parent;
    while (y != nodington && x == y->right) {
        x = y;
        y = y->parent;
    }
    return y;
}

Node *RedBlack::TreePredecessor(Node *x) {
    if (x->left != nodington)
        return TreeMaximum(x->left);
    Node *y = x->parent;
    while (y != nodington && x == y->left) {
        x = y;
        y = y->parent;
    }
    return y;
}

Node *RedBlack::Search(std::string first, std::string last, Node *x) {
    if (x == nodington || (first == x->person.fName && last == x->person.lName))
        return x;
    if (first < x->person.fName)
        return Search(first, last, x->left);
    else
        return Search(first, last, x->right);
}

void RedBlack::Insert(std::string fName, std::string lName, std::string address, std::string city, std::string state,
                      std::string zip, std::string phoneNum) {
    Node *y = nodington;
    Node *x = root;
    Node *z = new Node;
    z->person.fName = fName;
    z->person.lName = lName;
    z->person.address = address;
    z->person.city = city;
    z->person.state = state;
    z->person.zip = zip;
    z->person.phoneNum = phoneNum;
    z->left = nodington;
    z->right = nodington;
    z->color = RED;
    while (x != nodington) {
        y = x;
        if (z->person.fName < x->person.fName)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if (y == nodington)
        root = z;
    else if (z->person.fName < y->person.fName)
        y->left = z;
    else
        y->right = z;
    if (z->parent == nodington) {
        z->color = BLACK;
        return;
    }
    if (z->parent->parent == nodington)
        return;
    Node *uncle;
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            uncle = z->parent->parent->right;
            if (uncle->color == RED) {
                z->parent->color = BLACK;
                uncle->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    LeftRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                RightRotate(z->parent->parent);
            }
        } else {
            uncle = z->parent->parent->left;
            if (uncle->color == RED) {
                z->parent->color = BLACK;
                uncle->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    RightRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                LeftRotate(z->parent->parent);
            }
        }
        if (z == root)
            break;
    }
    root->color = BLACK;
}

void RedBlack::Search(std::string first, std::string last) {
    Node *x = root;
    while (x != nodington) {
        if (x->person.fName == first && x->person.lName == last) {
            std::cout << "First Name: " << x->person.fName << std::endl;
            std::cout << "Last Name: " << x->person.lName << std::endl;
            std::cout << "Address: " << x->person.address << std::endl;
            std::cout << "City: " << x->person.city << std::endl;
            std::cout << "State: " << x->person.state << std::endl;
            std::cout << "Zip: " << x->person.zip << std::endl;
            std::cout << "Phone Number: " << x->person.phoneNum << std::endl;
            return;
        } else if (x->person.fName > first)
            x = x->left;
        else
            x = x->right;
    }
    std::cout << "Person not found." << std::endl;
}

void ParseFile(std::string fileName, RedBlack& tree) {
    std::ifstream inFile(fileName);
    std::string line;
    std::string word;
    std::vector<std::string> row;
    std::vector<Person> people;
    int num = 0;

    auto start = std::chrono::high_resolution_clock::now();

    if (inFile.is_open()) {
        while (std::getline(inFile, line)) {
            row.clear();
            std::stringstream s(line);

            while (std::getline(s, word, ',')) {
                row.push_back(word);
            }

            // insert into black red tree
            tree.Insert(row[0], row[1], row[2], row[3], row[4], row[5], row[6]);
            num++;
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Inserted " << num << " elements in " << duration.count() << " microseconds" << std::endl;
}
