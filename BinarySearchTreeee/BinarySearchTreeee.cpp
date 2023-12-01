#include <iostream>
#include <string>

class Date {
public:
    int day;
    int month;
    int year;

    Date(int d, int m, int y) : day(d), month(m), year(y) {}

    bool operator<(const Date& other) const {
        if (year != other.year) {
            return year < other.year;
        }
        if (month != other.month) {
            return month < other.month;
        }
        return day < other.day;
    }

    bool operator==(const Date& other) const {
        return day == other.day && month == other.month && year == other.year;
    }

    bool operator>(const Date& other) const {
        return !(*this < other) && !(*this == other);
    }
};

class MultiSetTreeNode {
public:
    Date key;
    int count;
    MultiSetTreeNode* left;
    MultiSetTreeNode* right;

    MultiSetTreeNode(const Date& value) : key(value), count(1), left(nullptr), right(nullptr) {}
};

class MultiSet {
private:
    MultiSetTreeNode* root;

public:
    MultiSet() : root(nullptr) {}

    MultiSet(const MultiSet& other) {
        root = copyTree(other.root);
    }

    MultiSet& operator=(const MultiSet& other) {
        if (this != &other) {
            clear(root);
            root = copyTree(other.root);
        }
        return *this;
    }

    void insert(const Date& value) {
        root = insertTree(root, value);
    }

    void print() {
        printTree(root, 0);
        std::cout << "\n";
    }

    void prefixPrint() {
        prefixPrintTree(root);
        std::cout << "\n";
    }

    ~MultiSet() {
        clear(root);
    }

private:

    MultiSetTreeNode* insertTree(MultiSetTreeNode* node, const Date& value) {
        if (node == nullptr) {
            return new MultiSetTreeNode(value);
        }

        if (value == node->key) {
            // Вставка дубликата
            node->count++;
            node->left = insertTree(node->left, value);
        }
        else if (value < node->key) {
            node->left = insertTree(node->left, value);
        }
        else {
            node->right = insertTree(node->right, value);
        }

        return node;
    }

    void printTree(MultiSetTreeNode* node, int level) {
        if (node != nullptr) {
            printTree(node->right, level + 1);
            for (int i = 0; i < level; i++) {
                std::cout << "\t";
            }
            std::cout << node->key.day << "." << node->key.month << "." << node->key.year << "\n";
            printTree(node->left, level + 1);
        }
    }

    void prefixPrintTree(MultiSetTreeNode* node) {
        if (node != nullptr) {
            std::cout << node->key.day << "." << node->key.month << "." << node->key.year << "\n";
            prefixPrintTree(node->left);
            prefixPrintTree(node->right);
        }
    }

    void clear(MultiSetTreeNode* node) {
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    MultiSetTreeNode* copyTree(const MultiSetTreeNode* node) {
        if (node == nullptr) {
            return nullptr;
        }

        MultiSetTreeNode* newNode = new MultiSetTreeNode(node->key);
        newNode->count = node->count;
        newNode->left = copyTree(node->left);
        newNode->right = copyTree(node->right);

        return newNode;
    }
};

int main() {
    MultiSet multiSet;

    multiSet.insert(Date(10, 12, 2022));
    multiSet.insert(Date(4, 5, 2022));
    multiSet.insert(Date(2, 1, 2022));
    multiSet.insert(Date(8, 9, 2022));
    multiSet.insert(Date(6, 7, 2022));
    multiSet.insert(Date(4, 5, 2022));

    std::cout << "MultiSet Tree:\n";
    multiSet.print();

    std::cout << "Prefix Print of MultiSet Tree:\n";
    multiSet.prefixPrint();

    MultiSet copyMultiSet = multiSet;

    std::cout << "Copied MultiSet Tree:\n";
    copyMultiSet.print();

    std::cout << "Prefix Print of Copied MultiSet Tree:\n";
    copyMultiSet.prefixPrint();

    return 0;
}
