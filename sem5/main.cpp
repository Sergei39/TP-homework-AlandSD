#include <iostream>
#include <vector>
#include <assert.h>

class BinTree {
public:
    BinTree();
    ~BinTree();

    void Add(int key);
    void InOrderDFS(void visit(int));

private:
    struct Node {
        Node* Left;
        Node* Right;
        int Key;
        Node(int key) : Left(nullptr), Right(nullptr), Key(key) {}
    };
    Node* root;

    void add(Node*& node, int key);
    void inOrderDFS(Node* node, void visit(int));
    void postOrderDFS(Node *node, void visit(Node*));
};

BinTree::BinTree() : root(nullptr) {}

BinTree::~BinTree() {
    postOrderDFS(root, [](Node* node) {delete node;});
}

void BinTree::postOrderDFS(Node *node, void visit(Node*)) {
    if(node == nullptr) {
        return;
    }

    postOrderDFS(node->Left, visit);
    postOrderDFS(node->Right, visit);
    visit(node);
}

void BinTree::Add( int key ) {
    add(root, key);
}

void BinTree::add(Node*& node, int key) {
    if(node == nullptr) {
        node = new Node(key);
        return;
    }
    if(key < node->Key) {
        add(node->Left, key);
    } else {
        add(node->Right, key);
    }
}

void BinTree::InOrderDFS(void visit(int)) {
    inOrderDFS(root, visit);
}

void BinTree::inOrderDFS(Node *node, void visit(int)) {
    if(node == nullptr) {
        return;
    }

    inOrderDFS(node->Left, visit);
    visit(node->Key);
    inOrderDFS(node->Right, visit);
}

int main() {
    BinTree tree;
    tree.Add(10);
    tree.Add(5);
    tree.Add(20);
    tree.Add(1);
    tree.Add(7);
    tree.Add(15);
    tree.Add(17);

    tree.InOrderDFS([](int key) {std::cout << key << " ";});

    return 0;
}
