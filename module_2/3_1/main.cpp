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
    int Deep();

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

int BinTree::Deep() {
    struct Wrapper {
        Node* Nd;
        int Deep;
        Wrapper(Node* nd, int deep) : Nd(nd), Deep(deep) {}
    };

    Node* node = root;
    if(node == nullptr)
        return 0;

    int max_deep = 0;
    stack<Wrapper*> stack;
    stack.push(new Wrapper(node, 1));

    while(!stack.empty()) {
        Wrapper* current = stack.top();
        stack.pop();

        if(current->Deep > max_deep)
            max_deep = current->Deep;

        if(current->Nd->Left != nullptr)
            stack.push(new Wrapper(current->Nd->Left, current->Deep + 1));

        if(current->Nd->Right != nullptr)
            stack.push(new Wrapper(current->Nd->Right, current->Deep + 1));

        delete current;
    }

    return max_deep;
}



class DecTree {
public:
    DecTree();
    DecTree(const DecTree&) = delete;
    DecTree& operator=(const DecTree&) = delete;
    ~DecTree();

    void Add(int key, int prior);
    void Delete(int key);

    int Deep();

private:
    struct Node {
        Node* Left;
        Node* Right;
        int Key;
        int Prior;
        Node(int key, int prior) : Left(nullptr), Right(nullptr), Key(key), Prior(prior) {}
    };
    Node* root;

private:
    void Split(Node* currentNode, int key, Node*& left, Node*& right);
    void Merge( Node* left, Node* right, Node* result );
};

int DecTree::Deep() {
    struct Wrapper {
        Node* Nd;
        int Deep;
        Wrapper(Node* nd, int deep) : Nd(nd), Deep(deep) {}
    };

    Node* node = root;
    if(node == nullptr)
        return 0;

    int max_deep = 0;
    stack<Wrapper*> stack;
    stack.push(new Wrapper(node, 1));

    while(!stack.empty()) {
        Wrapper* current = stack.top();
        stack.pop();

        if(current->Deep > max_deep)
            max_deep = current->Deep;

        if(current->Nd->Left != nullptr)
            stack.push(new Wrapper(current->Nd->Left, current->Deep + 1));

        if(current->Nd->Right != nullptr)
            stack.push(new Wrapper(current->Nd->Right, current->Deep + 1));

        delete current;
    }

    return max_deep;
}

void DecTree::Split( Node* currentNode, int key, Node*& left,
            Node*& right )
{
    if( currentNode == nullptr ) {
        left = nullptr;
        right = nullptr;
    } else if( currentNode->Key <= key ) {
        Split( currentNode->Right, key, currentNode->Right, right );
        left = currentNode;
    } else {
        Split( currentNode->Left, key, left, currentNode->Left );
        right = currentNode;
    }
}

void DecTree::Merge( Node* left, Node* right, Node* result )
{
    if( left == nullptr || right == nullptr ) {
        result =  left == nullptr ? right : left;
        return;
    }
    if( left->Prior > right->Prior ) {
        Merge( left->Right, right, left->Right );
        result = left;
        return;
    } else {
        Merge( left, right->Left, right->Left );
        result = right;
        return;
    }
}

DecTree::DecTree() : root(nullptr) {}

DecTree::~DecTree() {
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

void DecTree::Add( int key, int prior ) {
    Node* current = new Node(key, prior);

    if(root == nullptr) {
        root = current;
        return;
    }

    Node* node = root;
    Node* parent = nullptr;

    while(node != nullptr && node->Prior > prior) {
        parent = node;
        if (node->Key <= key)
            node = node->Right;
        else
            node = node->Left;
    }

    if(node != nullptr)
        Split(node, key, current->Left, current->Right);

    if(parent == nullptr)
        root = current;
    else if(parent->Key <= key)
        parent->Right = current;
    else
        parent->Left = current;
}

void DecTree::Delete(int key) {
    Node* node = root;
    Node* parent = root;

    while(node != nullptr && node->Key != key) {
        parent = node;
        if (node->Key < key)
            node = node->Right;
        else
            node = node->Left;
    }

    if(node == nullptr) {
        return;
    }

    Node *current = nullptr;
    Merge(node->Left, node->Right, current);

    if(parent->Key <= key)
        parent->Right = current;
    else
        parent->Left = current;
}

int main() {
    DecTree decTree;
    BinTree binTree;
    int number = 0;
    std::cin >> number;
    for(int i = 0; i < number; i++) {
        int key = 0, prior = 0;
        std::cin >> key >> prior;
        decTree.Add(key, prior);
        binTree.Add(key);
    }

    std::cout << binTree.Deep() - decTree.Deep();

    return 0;
}