/**
 * Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией.
 * Хранимые строки непустые и состоят из строчных латинских букв.
 * Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
 * Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте при добавлении элементов в случае,
 * когда коэффициент заполнения таблицы достигает 3/4.
 * Структура данных должна поддерживать операции добавления строки в множество,
 * удаления строки из множества и проверки принадлежности данной строки множеству.
 *
 * 1_2. Для разрешения коллизий используйте двойное хеширование.
 * **/

#include <iostream>
#include <vector>
#include <assert.h>
#include <string>

using std::vector;
using std::string;
using std::cin;
using std::cout;

template<class T, class H, class H2>
class HashTable {
public:
    HashTable( H& _hasher, H2 _hasher_coll, T _empty, T _del );
    HashTable( const HashTable& ) = delete;
    HashTable& operator=( const HashTable& ) = delete;
    ~HashTable();

    bool Add( const T& data );
    bool Has( const T& data ) const;
    bool Delete( const T& data );

private:
    struct HashTableNode {
        enum TCellType {
            Key,
            Del,
            Empty,
        };

        T Data;
        TCellType Type;

        HashTableNode() : Type( TCellType::Empty ) {};
        explicit HashTableNode( const T& data) : Data( data ), Type( TCellType::Key ) {}
    };
    H hasher;
    H2 hasher_coll;
    T empty;
    T del;
    vector<HashTableNode> table;
    int keys_count;
    int del_count;

    void growTable(size_t size);
};

template<class T, class H, class H2>
HashTable<T, H, H2>::HashTable( H& _hasher, H2 _hasher_coll, T _empty, T _del ) :
        hasher( _hasher ),
        hasher_coll( _hasher_coll ),
        table( 8 ),
        keys_count( 0 ),
        del_count( 0 ),
        empty(_empty),
        del(_del) {};

template<class T, class H, class H2>
HashTable<T, H, H2>::~HashTable() {

};

template<class T, class H, class H2>
bool HashTable<T, H, H2>::Add( const T& data ) {
    if (keys_count * 3 > 2 * table.size())
        growTable(table.size() * 2);
    if (del_count * 2 > table.size())
        growTable(table.size());

    unsigned int hash = hasher( data ) % table.size();
    unsigned int firstDelPos = -1;
    int i = 0;

    while( i < table.size() ) {
        if( table[hash].Type == HashTableNode::TCellType::Del && firstDelPos == -1 )
            firstDelPos = hash;

        if( table[hash].Data == data ) {
            return false;
        }

        if( table[hash].Type == HashTableNode::TCellType::Empty ) {
            if(firstDelPos == -1 ) {
                firstDelPos = hash;
            }
            else --del_count;

            table[firstDelPos].Type = HashTableNode::TCellType::Key;
            table[firstDelPos].Data = data;
            ++keys_count;

            return true;
        }

        hash = ( hasher( data ) + i * hasher_coll( data ) ) % table.size();
        ++i;
    }

    assert(firstDelPos != -1);
    table[firstDelPos].Type = HashTableNode::TCellType::Key;
    table[firstDelPos].Data = data;
    ++keys_count;
    --del_count;

    return true;
}

template<class T, class H, class H2>
void HashTable<T, H, H2>::growTable(size_t size) {
    vector<HashTableNode> newTable( size );
    for( size_t i = 0; i < table.size(); ++i ) {
        if( table[i].Type == HashTableNode::TCellType::Key ) {
            unsigned int newHash = hasher( table[i].Data ) % newTable.size();
            int j = 0;
            while ( newTable[newHash].Type == HashTableNode::TCellType::Key ) {
                newHash = (hasher(table[i].Data) + j * hasher_coll(table[i].Data)) % newTable.size();
                ++j;
            }

            newTable[newHash] = table[i];
        }
    }
    table = std::move( newTable );
}

template<class T, class H, class H2>
bool HashTable<T, H, H2>::Has( const T& data ) const {
    unsigned int hash = hasher( data ) % table.size();
    int i = 0;

    while( i < table.size() && table[hash].Type != HashTableNode::TCellType::Empty ) {
        if( table[hash].Data == data ) {
            return true;
        }
        hash = ( hasher( data ) + i * hasher_coll( data ) ) % table.size();
        ++i;
    }

    return false;
}

template<class T, class H, class H2>
bool HashTable<T, H, H2>::Delete( const T& data ) {
    unsigned int hash = hasher( data ) % table.size();
    int i = 0;

    while( i < table.size() && table[hash].Type != HashTableNode::TCellType::Empty ) {
        if( table[hash].Data == data ) {
            table[hash].Type = HashTableNode::TCellType::Del;
            table[hash].Data = del;

            --keys_count;
            ++del_count;
            return true;
        }
        hash = ( hasher( data ) + i * hasher_coll( data ) ) % table.size();
        ++i;
    }

    return false;
}

struct Hasher {
    unsigned int operator()( const string& data ) const {
        int hash = 0;
        for( size_t i = 0; i < data.size(); ++i )
            hash = hash * 7 + data[i];
        return hash;
    }
};

struct Hasher_Coll {
    unsigned int operator()( const string& data ) const {
        int hash = 0;
        for( size_t i = 0; i < data.size(); ++i )
            hash = hash * 7 + data[i];
        hash *= 2;
        ++hash;
        return hash;
    }
};

int main() {
    Hasher hasher;
    Hasher_Coll hasherColl;
    HashTable<string, Hasher, Hasher_Coll> table( hasher, hasherColl, "EMPTY", "DEL" );
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
