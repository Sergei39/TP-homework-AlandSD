#include "intersection.h"

int looking_number(int *arr, int size, int number) {
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

int intersection() {
    int n_size = 0;
    int m_size = 0;
    int res_size = 0;
    std::cout << "Input size array1 and array2" << std::endl;
    std::cin >> n_size >> m_size;

    int *n_arr, *m_arr, *res;
    n_arr = new int[n_size];
    m_arr = new int[m_size];
    res = new int[n_size];

    std::cout << "Input element array1" << std::endl;
    for (int i = 0; i < n_size; i++)
        std::cin >> n_arr[i];

    std::cout << "Input element array2" << std::endl;
    for (int i = 0; i < m_size; i++)
        std::cin >> m_arr[i];

    int min_index_n_arr = 0;

    int max_index_n_arr = n_size - 1;

    for (int i = 0; i < m_size; i++) {
        int index = looking_number(n_arr + min_index_n_arr, max_index_n_arr + 1 - min_index_n_arr, m_arr[i]);

        if (index > -1) {
            res[res_size] = m_arr[i];
            min_index_n_arr += index + 1;
            res_size++;
        }
    }

    std::cout << "Result: " << std::endl;
    for (int i = 0; i < res_size; i++)
        std::cout << res[i] << std::endl;

    delete [] n_arr;
    delete [] m_arr;
    delete [] res;

    return 0;
}