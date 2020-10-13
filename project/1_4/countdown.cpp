#include "countdown.h"

int interaction_user(){
    int num = 0;
    int kill = 0;

    std::cin >> num >> kill;
    if (num == 0)
        return 0;

    std::cout << found_number(num, kill);
}

int found_number(int number_people, int number_kill){

    list *first = (list*)malloc(sizeof(list));
    list *tec = first;
    tec->point = first;
    tec->value = 1;
    for (int i = 2; i <= number_people; i++) {
        tec->point = (list*)malloc(sizeof(list));
        tec = tec->point;
        tec->value = i;
        tec->point = first;
    }

    tec = first;
    while (tec->point != tec) {
        for(int i = 0; i < number_kill - 2; i++)
            tec = tec->point;

        list *del = tec->point;
        tec->point = del->point;
        tec = tec->point;
        free(del);
    }

    int res = tec->value;
    free(tec);

    return res;
}
