/**Дан отсортированный по возрастанию массив попарно различных целых чисел A[0..n-1].
 * На вход также подается некоторое целое число k. Необходимо вернуть индекс элемента k в массиве A,
 * если он там присутствует, либо вернуть позицию, куда его следовало бы вставить,
 * чтобы массив остался отсортированным.**/

#include <iostream>

int looking_number(const int *arr, int size, int number) {
    for( int i = 0; i < size; i++ ) {
        if( arr[i] >= number )
            return i;
    }

    return size;
}

int main() {
    int n = 0;
    std::cin >> n;
    int *arr = new int[n];

    for( int i = 0; i < n; i++ )
        std::cin >> arr[i];

    int k = 0;
    std::cin >> k;

    std::cout << looking_number(arr, n, k);

    delete [] arr;

    return 0;
}
