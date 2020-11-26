/**Даны неотрицательные целые числа n,k и массив целых чисел из [0..10^9] размера n.
 * Требуется найти k-ю порядковую статистику. т.е. напечатать число,
 * которое бы стояло на позиции с индексом k (0..n-1) в отсортированном массиве.
 *
 * Требования: к дополнительной памяти: O(n). Среднее время работы: O(n).
 * Должна быть отдельно выделенная функция partition. Рекурсия запрещена.
 * Решение должно поддерживать передачу функции сравнения снаружи.
 *
 * Функцию Partition следует реализовывать методом прохода двумя итераторами в одном направлении.
 * Описание для случая прохода от начала массива к концу:
 *   Выбирается опорный элемент. Опорный элемент меняется с последним элементом массива.
 *   Во время работы Partition в начале массива содержатся элементы, не бОльшие опорного.
 *   Затем располагаются элементы, строго бОльшие опорного. В конце массива лежат нерассмотренные элементы. Последним элементом лежит опорный.
 *   Итератор (индекс) i указывает на начало группы элементов, строго бОльших опорного.
 *   Итератор j больше i, итератор j указывает на первый нерассмотренный элемент.
 *   Шаг алгоритма. Рассматривается элемент, на который указывает j. Если он больше опорного, то сдвигаем j.
 *   Если он не больше опорного, то меняем a[i] и a[j] местами, сдвигаем i и сдвигаем j.
 *   В конце работы алгоритма меняем опорный и элемент, на который указывает итератор i.
 *
 * 6_1. Реализуйте стратегию выбора опорного элемента “медиана трёх”.
 * Функцию Partition реализуйте методом прохода двумя итераторами от начала массива к концу.**/

#include <iostream>

template<class T>
class CmpDefault {
public:
    bool operator()(const T& l, const T& r) { return l < r; }
};

template <class T, class Compare = CmpDefault<T>>
int looking_pivot( T* a, int n, Compare less = CmpDefault<T> () ) {
    T a1 = a[0];
    T a2 = a[n / 2];
    T a3 = a[n - 1];

    if( ( less( a1, a2 ) && less( a3, a1 ) ) ||
        ( less( a2, a1 ) && less( a1, a3 ) ) )
        return 0;
    else if( ( less( a2, a1 ) && less( a3, a2 ) ) ||
             ( less( a1, a2 ) && less( a2, a3 ) ) )
        return n / 2;
    else
        return n - 1;
}

template <class T, class Compare = CmpDefault<T>>
int Partition( T* a, int n, Compare less = CmpDefault<T> () ) {
    if ( n <= 1 ) {
        return 0;
    }
    std::swap( a[looking_pivot( a, n, less )], a[n - 1] );
    const T& pivot = a[n - 1];
    int i = 0, j = 0;
    while( j < n - 1 ) {
        for( ; less( pivot, a[j] ); ++j ) {}
        if( j < n - 1 ) {
            std::swap( a[i++], a[j++] );
        }
    }
    std::swap( a[i], a[n - 1] );
    return i;
}

template <class T, class Compare = CmpDefault<T>>
int FindKStat( T* a, int n, int k, Compare less = CmpDefault<T> () ) {
    int part = Partition( a, n, less );
    while( part != k ) {
        if( k < part )
            n = part;
        else {
            a += part + 1;
            n -= (part + 1);
            k -= (part + 1);
        }
        part = Partition( a, n, less );
    }
    return a[part];
}

int main() {
    int n = 0, k = 0;
    std::cin >> n >> k;

    int *arr = new int[n];
    for( int i = 0; i < n; ++i ) {
        std::cin >> arr[i];
    }

    std::cout << FindKStat(arr, n, k);

    delete [] arr;

    return 0;
}
