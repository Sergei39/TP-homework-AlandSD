#include <iostream>
#include <cassert>

int looking_number(const int *arr, int size, int number) {
    bool flag = false;
    int l = 0;
    int r = size - 1;
    int mid = 0;

    while ((l <= r) && !flag) {
        mid = (l + r) / 2;

        if (arr[mid] == number) flag = true;
        if (arr[mid] > number) r = mid - 1;
        else l = mid + 1;
    }

    if (!flag)
        return -1;

    return mid;
}

template <class T>
class My_Vector {
public:
    My_Vector(int size);
    ~My_Vector();

    T get(int index);
    void push(T value);
    void pop();

    int looking_num(T value);

private:
    int head;
    int size;
    int capacity;
    T *arr;
};

template <class T>
My_Vector<T>::My_Vector(int size) :
        size(0),
        head(0),
        capacity(size)
{
    arr = new T[capacity];
}

template <class T>
My_Vector<T>::~My_Vector(){
    delete [] arr;
}

template <class T>
T My_Vector<T>::get(int index) {
    assert(index < size);
    return arr[index];
}

template <class T>
void My_Vector<T>::push(T value) {
    assert(size < capacity);

    arr[size] = value;
    size++;
}

template<class T>
void My_Vector<T>::pop() {
    size--;
}

template <class T>
int My_Vector<T>::looking_num(T value) {
    bool flag = false;
    int l = 0;
    int r = size - 1;
    int mid = 0;

    while ((l <= r) && !flag) {
        mid = (l + r) / 2;

        if (arr[mid] == number) flag = true;
        if (arr[mid] > number) r = mid - 1;
        else l = mid + 1;
    }

    if (!flag)
        return -1;

    return mid;
}

int main() {
    int n_size = 0;
    int m_size = 0;
    int res_size = -1;
    std::cin >> n_size >> m_size;

    My_Vector<int> n_arr(n_size);
    My_Vector<int> m_arr(m_size);
    My_Vector<int> res(m_size);


    for (int i = 0; i < n_size; i++) {
        int num;
        std::cin >> num;
        n_arr.push(num);
    }

    for (int i = 0; i < m_size; i++){
        int num;
        std::cin >> num;

        if (num > n_arr.get(n_size - 1)) {
            m_size = i + 1;
            break;
        }
        m_arr.push(num);
    }

    while (n_arr.get(n_size - 1) > m_arr.get(m_size - 1)) {
        n_size--;
        n_arr.pop();
    }



    int min_index = 0;
    for (int i = 0; i < n_size; i++) {
        int index = looking_number(n_arr + min_index, n_size - min_index, m_arr[i]);

        if (index > -1) {
            res[++res_size] = m_arr[i];
            min_index += index;
        }
    }

    for (int i = 0; i <= res_size; i++)
        std::cout << res.get(i) << std::endl;

    return 0;
}