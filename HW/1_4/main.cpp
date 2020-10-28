/**В круг выстроено N человек, пронумерованных числами от 1 до N.
 * Будем исключать каждого k-ого до тех пор, пока не уцелеет только один человек.
 * Например, если N=10, k=3, то сначала умрет 3-й, потом 6-й, затем 9-й, затем 2-й,
 * затем 7-й, потом 1-й, потом 8-й, за ним - 5-й, и потом 10-й. Таким образом, уцелеет 4-й.
 *
 * Необходимо определить номер уцелевшего.
 * N, k ≤ 10000.**/


#include <iostream>

struct list {
    int value;
    list *point;
};

int get_num (int num, int kill) {
    list *first = new list;
    list *tec = first;
    tec->point = first;
    tec->value = 1;
    for (int i = 2; i <= num; i++) {
        tec->point = new list;
        tec = tec->point;
        tec->value = i;
        tec->point = first;
    }

    tec = first;
    while (tec->point != tec) {
        for(int i = 0; i < kill - 2; i++)
            tec = tec->point;

        list *del = tec->point;
        tec->point = del->point;
        tec = tec->point;
        free(del);
    }

    int res =  tec->value;
    free(tec);

    return res;
}

int main() {
    int num = 0;
    int kill = 0;

    std::cin >> num >> kill;

    std::cout << get_num(num, kill);
    return 0;
}
