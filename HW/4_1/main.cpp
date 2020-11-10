/**Вовочка ест фрукты из бабушкиной корзины.
 * В корзине лежат фрукты разной массы. Вовочка может поднять не более K грамм.
 * Каждый фрукт весит не более K грамм. За раз он выбирает несколько самых тяжелых фруктов,
 * которые может поднять одновременно, откусывает от каждого половину и кладет огрызки обратно в корзину.
 * Если фрукт весит нечетное число грамм, он откусывает большую половину. Фрукт массы 1гр он съедает полностью.
 *
 * Определить за сколько подходов Вовочка съест все фрукты в корзине.**/


#include <iostream>
#include <cstring>
#include <cassert>

#define START_SIZE 4

template<class T>
class Array {
public:
    Array();
    Array(const Array<T>& _arr);
    ~Array();


    int get_size() const;
    T& get(int index) const;
    void push(T value);
    T last();
    void delete_last();

    T& operator [] (int index) const{
        return get(index);
    }

    Array& operator= (const Array<T>& _arr);

    bool IsEmpty() { return size == 0; }
private:
    T* arr;
    int size;
    int capacity;
};

template<class T>
Array<T>::Array(const Array<T>& _arr) {
    capacity = _arr.capacity;
    size = _arr.get_size();
    arr = new T[capacity];

    for(int i = 0; i < size; i++) {
        arr[i] = _arr[i];
    }
}

template<class T>
Array<T>& Array<T>::operator=(const Array<T>& _arr) {

    if (this != &_arr) {
        this->~Array();
        new (this) Array<T>(_arr);
    }

    return *this;
}

template<class T>
Array<T>::Array() {
    capacity = START_SIZE;
    arr = new T[capacity];
    size = 0;
}

template<class T>
Array<T>::~Array() {
    delete [] arr;
}

template<class T>
int Array<T>::get_size() const {
    return size;
}

template<class T>
T& Array<T>::get(int index) const {
    return arr[index];
}

template<class T>
void Array<T>::push(T value) {
    if(size >= capacity) {
        capacity *= 2;
        T* new_arr = new T[capacity];
        memcpy(new_arr, arr, sizeof(int) * size);
        delete [] arr;
        arr = new_arr;
    }

    arr[size] = value;
    size++;
}

template<class T>
T Array<T>::last() {
    return arr[size - 1];
}

template<class T>
void Array<T>::delete_last() {
    size--;
}



template<class T>
class Heap {
public:
    Heap(Heap& h) = delete;
    explicit Heap(const Array<T>& _array);
    ~Heap() = default;
// Добавить элемент в кучу за
    void Insert(const T& element);
// Извлечь максимум из кучи за
    T ExtractMax();
// Посмотреть значение максимума в куче за
    const T& PeekMax();

    bool IsEmpty() { return array.IsEmpty(); }
private:
    Array<T> array;
    void add(T val);
    void buildHeap();
    void siftDown(int i);
    void siftUp( int i );
    T last();
    void delete_last();
};

template<class T>
Heap<T>::Heap(const Array<T>& _array) {
    array = _array;
    buildHeap();
};

template<class T>
void Heap<T>::add(T val) {
    array.push(val);
    siftUp(array.get_size() - 1);
}

template<class T>
T Heap<T>::last() {
    return array.last();
}

template<class T>
void Heap<T>::delete_last() {
    array.delete_last();
}

template<class T>
const T& Heap<T>::PeekMax() {
    assert(!array.IsEmpty());
    return array[0];
}

template<class T>
void Heap<T>::siftDown( int i )
{
    int left = 2 * i + 1;
    int right = 2 * i + 2;
// Ищем большего сына, если такой есть.
    int largest = i;
    if(left < array.get_size() && array[left] > array[i] )
        largest = left;
    if(right < array.get_size() && array[right] > array[largest] )
        largest = right;
// Если больший сын есть, то проталкиваем корень в него.
    if( largest != i ) {
        std::swap(array[i], array[largest]);
        siftDown(largest);
    }
}

template<class T>
void Heap<T>::buildHeap()
{
    for(int i = array.get_size() / 2 - 1; i >= 0; i--) {
        siftDown( i );
    }
}

template<class T>
void Heap<T>::siftUp( int index )
{
    while(index > 0) {
        int parent = (index - 1) / 2;
        if(array[index] <= array[parent])
            return;
        std::swap(array[index], array[parent]);
        index = parent;
    }
}

template<class T>
void Heap<T>::Insert( const T& element )
{
    add(element);
    siftUp(array.get_size() - 1);
}

template<class T>
T Heap<T>::ExtractMax()
{
    assert(!array.IsEmpty());
// Запоминаем значение корня.
    int result = array[0];
// Переносим последний элемент в корень.
    array[0] = last();
    delete_last();
// Вызываем SiftDown для корня.
    if(array.get_size() != 0) {
        siftDown(0);
    }
    return result;
}


int number_approaches(Array<int> array) {
    Heap<int> heap(array);

    int k = 0;
    std::cin >> k;

    int number = 0;
    while(!heap.IsEmpty()) {
        number++;
        int sum = 0;
        Array<int> fruct;
        while(!heap.IsEmpty() && (sum + heap.PeekMax() <= k)) {
            fruct.push(heap.PeekMax());
            sum += heap.ExtractMax();
        }
        while(!fruct.IsEmpty()) {
            if (fruct.last() / 2 != 0)
                heap.Insert(fruct.last() / 2);

            fruct.delete_last();
        }
    }

    return number;
}

int main() {
    int number = 0;
    std::cin >> number;
    Array<int> array;

    for(int i = 0; i < number; i++) {
        int val = 0;
        std::cin >> val;
        array.push(val);
    }

    std::cout << number_approaches(array);

    return 0;
}