/**Дан массив строк. Количество строк не больше 100000.
 * Отсортировать массив методом поразрядной сортировки MSD по символам.
 * Размер алфавита - 256 символов. Последний символ строки = ‘\0’.**/


#include <iostream>
#include <string>

void count_sort(std::string* a, int digit, int n ) {
    int k = 256;

    int* c = new int[k];
    for( int i = 0; i < k; ++i )
        c[i] = 0;
    for( int i = 0; i < n; ++i ) {
        if (a[i].size() > digit)
            ++c[a[i][digit]];
        else // если в слове меньше букв, чем тот разряд по которому сортируем
            ++c[0];
    }

    if( c[0] == n ) {
        delete [] c;
        return;
    }

    for( int i = 1; i < k; ++i ) {
        c[i] += c[i - 1];
    }
    std::string* b = new std::string [n];
    for( int i = n - 1; i >= 0; --i ) {
        if( a[i].size() > digit )
            b[--c[a[i][digit]]] = a[i];
        else
            b[--c[0]] = a[i];
    }

    for( int i = 0; i < n; i++ )
        a[i] = b[i];

    delete [] b;

    // рекурсивно вызваем сортировку следующих символов в слове
    for( int i = 1; i < k; ++i ) {
        if( c[i] - c[i - 1] > 1 )
            count_sort(a + c[i - 1], digit + 1, c[i] - c[i - 1]);
    }

    delete [] c;
}

void sort( std::string* string, int n ) {
    count_sort(string, 0, n);
}

int main() {
    std::string val;
    int n = 0, capacity = 2;
    std::string* string = new std::string [capacity];

    while( std::cin >> val ) {
        if( n >= capacity ) {
            std::string* new_string = new std::string [capacity * 2];
            for( int i = 0; i < capacity; ++i )
                new_string[i] = string[i];

            capacity *= 2;
            delete [] string;
            string = new_string;
        }

        string[n] = val;
        n++;
    }

    sort(string, n);

    for( int i = 0; i < n; i++ )
        std::cout << string[i] << std::endl;

    delete [] string;
}