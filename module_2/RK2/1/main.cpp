#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}

struct Hasher_Coll {
    unsigned int operator()( const Person& data ) const {
        int hash = 0;
        for( size_t i = 0; i < data.size(); ++i )
            hash = hash * 7 + data[i];
        hash *= 2;
        ++hash;
        return hash;
    }
};

template<class T>
class CmpDefault {
public:
    bool operator()(const Person& l, const Person& r) {
        if (l.ChildCount > r.ChildCount)
            return true;
        else if (l.ChildCount < r.ChildCount)
            return false;

        if (l.LastName > r.LastName)
            return true;
        else if (l.LastName < r.LastName)
            return false;

        if (l.FirstName > r.FirstName)
            return true;
        else return false;
    }
};

template<class Node>
int minG(Node* node) {
    if (node == nullptr)
        return 0;
    if (node->Left == nullptr && node->Right == nullptr)
        return 1;
    if (minG<Node>(node->Left) < minG<Node>(node->Right))
        return minG<Node>(node->Left) + 1;
    else
        return minG<Node>(node->Right) + 1;
}