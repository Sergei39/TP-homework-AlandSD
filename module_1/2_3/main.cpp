/**Даны два массива неповторяющихся целых чисел, упорядоченные по возрастанию.
 * A[0..n-1] и B[0..m-1]. n » m. Найдите их пересечение. Требуемое время работы:
 * O(m * log k), где k - позиция элементта B[m-1] в массиве A..
 * В процессе поиска очередного элемента B[i] в массиве A пользуйтесь результатом поиска элемента
 * B[i-1]. n, k ≤ 10000.**/

#include <iostream>

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

// возвращает размер массива пересечения
int get_crossing(int* n_arr, int n_size, int* m_arr, int m_size, int* res) {
    int min_index_n_arr = 0;
    int max_index_n_arr = n_size - 1;
    int res_size = 0;

    // определяем диапоазно степенями двойки
    for (int count = 1; count < n_size && n_arr[count] < m_arr[m_size - 1]; count *= 2) {
        if (n_arr[count] < m_arr[0])
            min_index_n_arr = count;
        max_index_n_arr = count;
    }
    if (min_index_n_arr == 1)
        min_index_n_arr = 0;
    if (max_index_n_arr * 2 < n_size)
        max_index_n_arr *= 2;
    else
        max_index_n_arr = n_size - 1;


    for (int i = 0; i < m_size; i++) {
        int index = looking_number(n_arr + min_index_n_arr, max_index_n_arr + 1 - min_index_n_arr, m_arr[i]);

        if (index > -1) {
            res[res_size] = m_arr[i];
            min_index_n_arr += index + 1;
            res_size++;
        }
    }

    return res_size;
}

int main() {
    int n_size = 0;
    int m_size = 0;
    std::cin >> n_size >> m_size;

    int *n_arr, *m_arr, *res;
    n_arr = new int[n_size];
    m_arr = new int[m_size];
    res = new int[n_size];

    for (int i = 0; i < n_size; i++)
        std::cin >> n_arr[i];

    for (int i = 0; i < m_size; i++)
        std::cin >> m_arr[i];

    int res_size = get_crossing(n_arr, n_size, m_arr, m_size, res);

    for (int i = 0; i < res_size; i++)
        std::cout << res[i] << std::endl;

    delete [] n_arr;
    delete [] m_arr;
    delete [] res;

    return 0;
}