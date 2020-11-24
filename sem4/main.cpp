#include <iostream>
#include <vector>
#include <assert.h>
#include <string>

using std::vector;
using std::string;
using std::cin;
using std::cout;

template<class T, class H>
class HashTable {
public:
    explicit HashTable( H& hasher );
    HashTable( const HashTable& ) = delete;
    HashTable& operator=( const HashTable& ) = delete;
    ~HashTable();

    bool Add( const T& data );
    bool Has( const T& data ) const;
    bool Delete( const T& data );

private:
    struct HashTableNode {
        T Data;
        HashTableNode* Next;

        HashTableNode() : Next( nullptr ) {}
        HashTableNode( const T& data, HashTableNode* next ) : Data( data ), Next( next ) {}
    };
    H hasher;
    vector<HashTableNode*> table;
    int keysCount;

    void growTable();
};

template<class T, class H>
HashTable<T, H>::HashTable( H& _hasher ) :
    hasher( _hasher ),
    table( 8, nullptr ),
    keysCount( 0 ) {};

template<class T, class H>
HashTable<T, H>::~HashTable() {
    for( size_t i = 0; i < table.size(); ++i ) {
        HashTableNode* node = table[i];
        while( node != nullptr ) {
            HashTableNode* nextNode = node->Next;
            delete node;
            node = nextNode;
        }
    }
};

template<class T, class H>
bool HashTable<T, H>::Add( const T& data ) {
    if (keysCount > 3 * table.size())
        growTable();

    unsigned int hash = hasher(data) % table.size();
    HashTableNode* node = table[hash];
    while (node != nullptr && node->Data != data)
        node = node->Next;

    if( node != nullptr )
        return false;

    table[hash] = new HashTableNode( data, table[hash] );
    ++keysCount;
    return true;
}

template<class T, class H>
void HashTable<T, H>::growTable() {
    vector<HashTableNode*> newTable( table.size() * 2, nullptr );
    for( size_t i = 0; i < table.size(); ++i ) {
        HashTableNode* node = table[i];
        while( node != nullptr ) {
            HashTableNode* nextNode = node->Next;
            unsigned int newHash = hasher( node->Data ) % newTable.size();
            node->Next = newTable[newHash];
            newTable[newHash] = node;
            node = nextNode;
        }
    }
    table = std::move( newTable );
}

template<class T, class H>
bool HashTable<T, H>::Has( const T& data ) const {
    unsigned int hash = hasher(data) % table.size();
    HashTableNode* node = table[hash];
    while (node != nullptr && node->Data != data)
        node = node->Next;

    return node != nullptr;
}

template<class T, class H>
bool HashTable<T, H>::Delete( const T& data ) {
    unsigned int hash = hasher( data ) % table.size();
    HashTableNode* prevNode = nullptr;
    HashTableNode* node = table[hash];
    while (node != nullptr && node->Data != data) {
        prevNode = node;
        node = node->Next;
    }

    if( node == nullptr ) // ключа нет, удалять нечего
        return false;

    if( prevNode == nullptr ) // удаление из начала списка
        table[hash] = node->Next;
    else
        prevNode->Next = node->Next;

    delete node;

    --keysCount;
    return true;
}

struct Hasher {
    unsigned int operator()( const string& data ) const {
        int hash = 0;
        for( size_t i = 0; i < data.size(); ++i )
            hash = hash * 7 + data[i];
        return hash;
    }
};

int main() {
    Hasher hasher;
    HashTable<string, Hasher> table( hasher );
    char operation;
    string word;
    while( cin >> operation >> word ) {
        if( operation == '+' )
            cout << ( table.Add( word ) ? "OK" : "FAIL" ) << std::endl;
        if( operation == '-' )
            cout << ( table.Delete( word ) ? "OK" : "FAIL" ) << std::endl;
        if( operation == '?' )
            cout << ( table.Has( word ) ? "OK" : "FAIL" ) << std::endl;
    }


    return 0;
}
