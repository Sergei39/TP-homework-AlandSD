/**Реализовать дек с динамическим зацикленным буфером.
 *
 * Обрабатывать команды push * и pop *.
 *
 * Формат ввода
 * В первой строке количество команд n. n ≤ 1000000.
 *
 * Каждая команда задаётся как 2 целых числа: a b.
 *
 * a = 1 - push front
 * a = 2 - pop front
 * a = 3 - push back
 * a = 4 - pop back
 * Если дана команда pop *, то число b - ожидаемое значение.
 * Если команда pop * вызвана для пустой структуры данных, то ожидается “-1”.**/

#include <iostream>
#include <cassert>

#define START_SIZE 10


template <class T>
class Dec{
public:
    Dec();
    Dec(Dec& dec) = delete;
    ~Dec();

    void push_back(const T &value);
    void push_front(const T &value);
    T pop_back();
    T pop_front();

    bool IsEmpty() const;
private:

    T *get_next(T *tmp);
    T *get_prev(T *tmp);
    void alloc_memory();

    T *head;
    T *last;
    T *arr;

    long size;
    long capacity;
};


template <class T>
Dec<T>::Dec() :
        head(nullptr),
        last(nullptr),
        capacity(START_SIZE),
        size(0)
{
    arr = new T [capacity];
}

template <class T>
Dec<T>::~Dec() {
    delete [] arr;
}

template<class T>
T* Dec<T>::get_next(T *tmp) {
    if(tmp == arr + capacity - 1)
        return arr;
    else
        return ++tmp;
}

template<class T>
T* Dec<T>::get_prev(T *tmp) {
    if(tmp == arr)
        return (arr + capacity - 1);
    else
        return --tmp;
}

template<class T>
void Dec<T>::alloc_memory() {
    T *new_arr = new T[capacity * 2];

    T *tmp = head;
    int i = -1;
    while (tmp != last) {
        new_arr[++i] = *tmp;
        tmp = get_next(tmp);
    }
    new_arr[++i] = *tmp;
    head = new_arr;
    last = new_arr + i;

    delete [] arr;
    arr = new_arr;
    capacity *= 2;
}

template <class T>
void Dec<T>::push_back(const T &value) {
    if (size >= capacity)
        alloc_memory();

    if(size == 0) {
        head = arr;
        last = arr;
    } else {
        last = get_next(last);
    }

    *last = value;
    size++;
}

template <class T>
void Dec<T>::push_front(const T &value) {
    if (size >= capacity)
        alloc_memory();

    if (size == 0) {
        head = arr;
        last = arr;
    } else {
        head = get_prev(head);
    }

    *head = value;
    size++;
}

template <class T>
T Dec<T>::pop_back() {
    assert(!IsEmpty());

    size--;
    T tmpValue = *last;
    last = get_prev(last);

    return tmpValue;
}

template <class T>
T Dec<T>::pop_front() {
    assert(!IsEmpty());

    size--;
    T tmpValue = *head;
    head = get_next(head);

    return tmpValue;
}

template <class T>
bool Dec<T>::IsEmpty() const {
    return size == 0;
}


int main() {
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