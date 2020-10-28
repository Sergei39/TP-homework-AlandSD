/**На склад привезли много пустых ящиков. Все ящики пронумерованы по порядку поступления от 0.
 * Известно, что их все можно сложить один в один (то есть так, что каждый следующий помещается в предыдущий).
 * Один ящик можно вложить в другой, если его можно перевернуть так,
 * что размеры одного ящика по всем осям станут строго меньше размеров другого ящика по соответствующим осям.
 *
 * Требуется определить, в какой последовательности они будут вложены друг в друга. Вывести номера ящиков.
 *
 * Максимальное кол-во 10000.**/

#include <iostream>
#include <cstring>

struct Map{
    int key;
    int val;
    Map() : key(0), val(0) {}
    Map(int _key, int _val) : key(_key), val(_val) {}
};

class CmpByPoint {
public:
    explicit CmpByPoint(const Map& _pt) : pt( _pt ) {}

    bool operator()(const Map& l, const Map& r) { return l.val < r.val; }

private:
    Map pt;
};


template<class T>
class CmpDefault {
public:
    bool operator()(const T& l, const T& r) { return l < r; }
};


template<class T, class Compare = CmpDefault<T>>
void Merge(const T* firstArr, int firstLen,
           const T* secondArr, int secondLen,
           T* res, Compare less = CmpDefault<T> ()) {

    int i = 0, j = 0;
    while(i < firstLen && j < secondLen) {
        if(less(firstArr[i], secondArr[j])) {
            res[i + j] = firstArr[i];
            i++;
        } else {
            res[i + j] = secondArr[j];
            j++;
        }
    }
    while(i < firstLen) {
        res[i + j] = firstArr[i];
        i++;
    }
    while(j < secondLen) {
        res[i + j] = secondArr[j];
        j++;
    }
}

template<class T, class Compare = CmpDefault<T>>
void MergeSort(T* a, int aLen, Compare less = CmpDefault<T> ()) {
    if(aLen <= 1) {
        return;
    }
    int firstLen = aLen / 2;
    int secondLen = aLen - firstLen;
    MergeSort(a, firstLen, less);
    MergeSort(a + firstLen, secondLen, less);
    T* res = new T[aLen];
    Merge(a, firstLen, a + firstLen, secondLen, res, less);
    memcpy(a, res, sizeof(T) * aLen);
    delete[] res;
}

int main() {
    int n = 0;
    std::cin >> n;

    Map *arr = new Map[n];

    for( int i = 0; i < n; i++ ) {
        arr[i].key = i;
        for (int j = 0; j < 3; j++) {
            int val = 0;
            std::cin >> val;
            arr[i].val += val;
        }
    }

    MergeSort(arr, n, CmpByPoint(arr[0]));

    for( int i = 0; i < n; i++ ) {
        std::cout << arr[i].key << " ";
    }


    delete [] arr;

    return 0;
}
