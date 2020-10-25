#include <iostream>
/*
int Partition( int* a, int n ) {
    if ( n <= 1 ) {
        return 0;
    }
    const int& pivot = a[n-1];
    int i = 0, j = n- 2;
    while( i <= j ) {
        for( ; a[i] < pivot; ++i ) {}
        for( ; j >= 0 && !(a[j] < pivot); --j ) {}
        if( i < j ) {
            std::swap( a[i++], a[j--] );
        }
    }
    std::swap( a[i], a[n - 1] );
    return i;
}

int FindKStat( int* a, int n, int k ) {
    int part = Partition( a, n );
    if( part == k ) {
        return a[part];
    }
    if( k < part ) {
        return FindKStat( a, part, k);
    }
    return FindKStat( a + part + 1, n - part - 1, k - part - 1 );
}

int main() {
    int arr[6] = { 0, 1, 2, 3, 4 ,5 };
    std::cout << FindKStat( arr, 6, 3 );
    return 0;
}
*/

void CountionSort1( int* a, int n ) {
    int k = a[0]; // k >> n - лучше сравнением за n log n
                    // k ~ n - лучше подсчетом
    for( int i = 0; i < n; ++i )
        k = std::max( k, a[i] );
    ++k;
    int* c = new int[k + 1];
    for( int i = 0; i < k; ++i )
        c[i] = 0;
    for( int i = 0; i < n; ++i )
        ++c[a[i]];
    int pos = 0;
    for( int i = 0; i < k; ++i ) {
        for( int j = 0; j < c[i]; ++j )
            a[pos++] = i;
    }
    delete [] c;
}

int main() {
    int arr[6] = { 100, 4, 7, 2, 5, 0 };
    CountionSort1( arr, 6 );
    for(int i : arr) {
        std::cout << i << ", ";
    }
}