#include <iostream>
#include <cassert>
#include "dek.h"

template <class T>
class Dec{
public:
    Dec();
    ~Dec();

    void push_back(const T &value);
    void push_front(const T &value);
    T pop_back();
    T pop_front();

    bool IsEmpty() const;
private:
    struct Node{
        T Value;
        Node *Next;
        Node *Prev;

        Node() : Next(nullptr), Prev(nullptr) {}
    };

    Node *head;
    Node *last;
    long size;
    long capacity;
};


template <class T>
Dec<T>::Dec() :
        head(nullptr),
        last(nullptr),
        size(0),
        capacity(0)
{}

template <class T>
Dec<T>::~Dec() {
    while (capacity > 0) {
        Node *tmpNode = head;
        head = head->Next;

        delete tmpNode;
        capacity --;
    }
}

template <class T>
void Dec<T>::push_back(const T &value) {
    if (capacity > size) {
        last = last->Next;
        last->Value = value;
        size++;
    } else {
        Node *tmpNode = new Node;
        tmpNode->Value = value;

        if (size == 0) {
            head = tmpNode;
            last = tmpNode;
        } else {
            last->Next = tmpNode;
            tmpNode->Prev = last;
            last = tmpNode;
        }
        last->Next = head;
        head->Prev = last;
        capacity++;
        size++;
    }
}

template <class T>
void Dec<T>::push_front(const T &value) {
    if (capacity > size) {
        head = head->Prev;
        head->Value = value;
        size++;
    } else {
        Node *tmpNode = new Node;
        tmpNode->Value = value;

        if (size == 0) {
            head = tmpNode;
            last = tmpNode;
        } else {
            head->Prev = tmpNode;
            tmpNode->Next = head;
            head = tmpNode;
        }
        last->Next = head;
        head->Prev = last;
        capacity++;
        size++;
    }
}

template <class T>
T Dec<T>::pop_back() {
    assert(!IsEmpty());

    size--;
    T tmpValue = last->Value;
    last = last->Prev;

    return tmpValue;
}

template <class T>
T Dec<T>::pop_front() {
    assert(!IsEmpty());

    size--;
    T tmpValue = head->Value;
    head = head->Next;

    return tmpValue;
}

template <class T>
bool Dec<T>::IsEmpty() const {
    return size == 0;
}


int main_3_2_list() {
    long number_command = 0;
    Dec<short> dec;
    std::cin >> number_command;
    bool result = true;

    for (long i = 0; i < number_command; i++){
        int command;
        short value;
        std::cin >> command >> value;

        switch (command) {
            case 1:
                dec.push_front(value);
                break;
            case 2:
                if (dec.IsEmpty())
                    result = result && value == -1;
                else
                    result = result && value == dec.pop_front();
                break;
            case 3:
                dec.push_back(value);
                break;
            case 4:
                if (dec.IsEmpty())
                    result = result && value == -1;
                else
                    result = result && value == dec.pop_back();
                break;
            default:
                assert(false);
        }
    }

    std::cout << (result ? "YES" : "NO");

    return 0;
}