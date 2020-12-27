#include <iostream>

using std::cin;

template<class T, class Cmp>
class AvlTree {
public:
    AvlTree();
    AvlTree( const AvlTree& ) = delete;
    AvlTree& operator=( const AvlTree& ) = delete;
    ~AvlTree();

    void Add(T key);
    void Remove(T key);

    void InOrderDFS(void visit(T));
    T NumberStatistic(int number);

private:
    struct Node {
        T Key;
        unsigned char Height;
        unsigned char CountNode;
        Node* Left;
        Node* Right;
        explicit Node(T key) { Key = key; Left = Right = nullptr; Height = 1; CountNode = 1;}
    };

    Node* root;

private:
    unsigned char height(Node* p);
    unsigned char countNode(Node* p);
    int bFactor(Node* p);
    void  fixHeight(Node* p);
    void  fixCountNode(Node* p);
    Node* rotateRight(Node* p);
    Node* rotateLeft(Node* q);
    Node* balance(Node* p);

    Node* add(Node* p, T key, Cmp less = Cmp());

    Node* findRemoveMin(Node*& p, Node* parent);
    Node* findRemoveMax(Node*& p, Node* parent);
    Node* remove(Node* p, T k, Cmp less = Cmp());

    void postOrderDFS(Node *node, void visit(Node*));
    void inOrderDFS(Node* node, void visit(T));

    T numberStatistic(Node* node, int number);
};

template<class T, class Cmp>
unsigned char AvlTree<T, Cmp>::height(Node* p) {
    return p != nullptr? p->Height: 0;
}

template<class T, class Cmp>
int AvlTree<T, Cmp>::bFactor(Node* p) {
    return height(p->Right) - height(p->Left);
}

template<class T, class Cmp>
void  AvlTree<T, Cmp>::fixHeight(Node* p) {
    unsigned char hl = height(p->Left);
    unsigned char hr = height(p->Right);
    p->Height = (hl>hr? hl: hr) + 1;
}

template<class T, class Cmp>
void  AvlTree<T, Cmp>::fixCountNode(Node* p) {
    unsigned char hl = countNode(p->Left);
    unsigned char hr = countNode(p->Right);
    p->CountNode = hl + hr +1;
}

template<class T, class Cmp>
unsigned char AvlTree<T, Cmp>::countNode(Node* p) {
    return p != nullptr? p->CountNode: 0;
}

template<class T, class Cmp>
typename AvlTree<T, Cmp>::Node *AvlTree<T, Cmp>::rotateRight(AvlTree::Node *p) {
    Node* q = p->Left;
    p->Left = q->Right;
    q->Right = p;
    fixHeight(p);
    fixHeight(q);
    fixCountNode(p);
    fixCountNode(q);
    return q;
}

template<class T, class Cmp>
typename AvlTree<T, Cmp>::Node *AvlTree<T, Cmp>::rotateLeft(AvlTree::Node *q) {
    Node* p = q->Right;
    q->Right = p->Left;
    p->Left = q;
    fixHeight(q);
    fixHeight(p);
    fixCountNode(q);
    fixCountNode(p);
    return p;
}

template<class T, class Cmp>
typename AvlTree<T, Cmp>::Node* AvlTree<T, Cmp>::balance(Node* p) // балансировка узла p
{
    fixHeight(p);
    fixCountNode(p);
    if(bFactor(p) == 2 )
    {
        if(bFactor(p->Right) < 0 )
            p->Right = rotateRight(p->Right);
        return rotateLeft(p);
    }
    if(bFactor(p) == -2 )
    {
        if(bFactor(p->Left) > 0  )
            p->Left = rotateLeft(p->Left);
        return rotateRight(p);
    }
    return p; // балансировка не нужна
}

template<class T, class Cmp>
void AvlTree<T, Cmp>::Add(T key) {
    root = add(root, key);
}

template<class T, class Cmp>
typename AvlTree<T, Cmp>::Node* AvlTree<T, Cmp>::add(Node* p, T key, Cmp less) // вставка ключа key в дерево с корнем p
{
    if( !p ) return new Node(key);
    if(less(key, p->Key))
        p->Left = add(p->Left, key);
    else
        p->Right = add(p->Right, key);
    return balance(p);
}

template<class T, class Cmp>
typename AvlTree<T, Cmp>::Node* AvlTree<T, Cmp>::findRemoveMin(Node*& p, Node* parent) // удаление узла с минимальным ключом из дерева p
{
    if( p->Left == nullptr ) {
        if(parent != nullptr) {
            parent->Left = p->Right;
        }
        else {
            Node* min = new Node(p->Key);
            delete p;
            p = nullptr;
            return min;
        }

        balance(parent);
        return p;
    }

    return findRemoveMin(p->Left, p);
}

template<class T, class Cmp>
typename AvlTree<T, Cmp>::Node* AvlTree<T, Cmp>::findRemoveMax(Node*& p, Node* parent) // удаление узла с минимальным ключом из дерева p
{
    if( p->Right == nullptr ) {
        if(parent != nullptr) {
            parent->Right = p->Left;
        }
        else {
            Node* min = new Node(p->Key);
            delete p;
            p = nullptr;
            return min;
        }

        balance(parent);
        return p;
    }

    return findRemoveMax(p->Left, p);
}

template<class T, class Cmp>
typename AvlTree<T, Cmp>::Node* AvlTree<T, Cmp>::remove(Node* p, T k, Cmp less) // удаление ключа k из дерева p
{
    if( !p ) return nullptr;
    if( less(k, p->Key) )
        p->Left = remove(p->Left, k);
    else if( less(p->Key, k) )
        p->Right = remove(p->Right, k);
    else //  k == p->key
    {
        Node* q = p->Left;
        Node* r = p->Right;
        delete p;

        if( !r ) return q;
        if( !q ) return r;

        Node* min = nullptr;
        if(r->Height > q->Height)
            min = findRemoveMin(r, nullptr);
        else
            min = findRemoveMax(q, nullptr);

        min->Left = q;
        min->Right = r;
        return balance(min);
    }
    return balance(p);
}

template<class T, class Cmp>
void AvlTree<T, Cmp>::Remove(T key) {
    root = remove(root, key);
}

template<class T, class Cmp>
AvlTree<T, Cmp>::AvlTree() {
    root = nullptr;
}

template<class T, class Cmp>
AvlTree<T, Cmp>::~AvlTree() {
    postOrderDFS(root, [](Node* node) {delete node;});
}

template<class T, class Cmp>
void AvlTree<T, Cmp>::postOrderDFS(Node *node, void visit(Node*)) {
    if(node == nullptr) {
        return;
    }

    postOrderDFS(node->Left, visit);
    postOrderDFS(node->Right, visit);
    visit(node);
}

template<class T, class Cmp>
void AvlTree<T, Cmp>::InOrderDFS(void visit(T)) {
    inOrderDFS(root, visit);
}

template<class T, class Cmp>
void AvlTree<T, Cmp>::inOrderDFS(Node *node, void visit(T)) {
    if(node == nullptr) {
        return;
    }

    inOrderDFS(node->Left, visit);
    visit(node->Key);
    inOrderDFS(node->Right, visit);
}

template<class T, class Cmp>
T AvlTree<T, Cmp>::NumberStatistic(int number) {
    numberStatistic(root, number);
}

template<class T, class Cmp>
T AvlTree<T, Cmp>::numberStatistic(AvlTree::Node *node, int number) {
    if(node == nullptr)
        return 0;
    if(countNode(node->Left) == number)
        return node->Key;
    if(countNode(node->Left) > number)
        return numberStatistic(node->Left, number);
    else
        return numberStatistic(node->Right, number - (countNode(node->Left) + 1));
}


class Comparator {
public:
    bool operator()(const int& l, const int& r) {
        return l < r;
    }
};

int main() {
    int number = 0;
    AvlTree<int, Comparator> tree;
    cin >> number;
    for(int i = 0; i < number; ++i) {
        int val = 0;
        cin >> val;
        if(val >= 0)
            tree.Add(val);
        else
            tree.Remove(abs(val));

        int st = 0;
        cin >> st;
        std::cout << tree.NumberStatistic(st) << std::endl;
    }

    return 0;
}
