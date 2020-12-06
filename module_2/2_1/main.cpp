#include <iostream>
#include <vector>
#include <stack>

using std::stack;

class BinTree {
public:
    BinTree();
    BinTree( const BinTree& ) = delete;
    BinTree& operator=( const BinTree& ) = delete;
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
};

BinTree::BinTree() : root(nullptr) {}

BinTree::~BinTree() {
    stack<Node*> stack;
    if(root != nullptr) {
        stack.push(root);
    }

    while(stack.top()->Left != nullptr)
        stack.push(stack.top()->Left);
    while(!stack.empty()) {
        Node* tec = stack.top();
        stack.pop();

        if(tec->Right != nullptr) {
            stack.push(tec->Right);
            while (stack.top()->Left != nullptr)
                stack.push(stack.top()->Left);
        }

        delete tec;
    }
}

void BinTree::Add( int key ) {
    if(root == nullptr) {
        root = new Node(key);
        return;
    }

    Node* node = root;
    Node* parent = root;

    while(node != nullptr) {
        parent = node;

        if(key < node->Key) {
            node = node->Left;
        } else {
            node = node->Right;
        }
    }

    if(key < parent->Key) {
        parent->Left = new Node(key);
    } else {
        parent->Right = new Node(key);
    }
}

void BinTree::InOrderDFS(void visit(int)) {
    stack<Node*> stack;
    if(root != nullptr) {
        stack.push(root);
    }

    while(stack.top()->Left != nullptr)
        stack.push(stack.top()->Left);
    while(!stack.empty()) {
        visit(stack.top()->Key);
        Node* tec = stack.top();
        stack.pop();

        if(tec->Right != nullptr) {
            stack.push(tec->Right);
            while (stack.top()->Left != nullptr)
                stack.push(stack.top()->Left);
        }
    }
}

int main() {
    BinTree tree;
    int number = 0;
    std::cin >> number;
    for(int i = 0; i < number; i++) {
        int val = 0;
        std::cin >> val;
        tree.Add(val);
    }

    tree.InOrderDFS([](int key) {std::cout << key << " ";});

    return 0;
}