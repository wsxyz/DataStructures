#include <time.h>
#include "sbl.h"

/**
 * @Name: testInsertion
 * @Def: A test function designed to verify the correct insertion functioning of the
 *       Sorted Bidirectional List. This method simply checks if the elements in the list
 *       are in order after the insertions.
 * @Args: ----.
 * @Ret: Returns 0 if this test reaches successfully the return statement.
 *
 **/
int testInsertion() {

    Sbl list = SBL_create();
    Element e;
    int i = 0;
    int n = INT_MAX/100000;
    time_t t;
    srand((unsigned)time(&t));

    printf("Number of Elements to Insert: %d\n", n);

    for (i = 0; i < n; i++) {
        e.num = rand() % n;
        SBL_insertOrdered(&list, e);
    }

    printf("\nList Size: %ld\n", SBL_getSize(list));
    printf("ASC Order:\n");
    SBL_goToHead(&list);
    while (!SBL_isLast(list)) {
        e = SBL_consult(list);
        printf("\tElement: %d\n", e.num);
        SBL_goToNext(&list);
    }

    printf("\n*********************************\n");

    printf("\nList Size: %ld\n", SBL_getSize(list));
    printf("DESC Order:\n");
    SBL_goToLast(&list);
    while (!SBL_isHead(list)) {
        e = SBL_consult(list);
        printf("\tElement: %d\n", e.num);
        SBL_goToPrev(&list);
    }

    SBL_destroy(&list);

    return 0;
}

int main() {
    printf("Data Structures in C!\n");
    testInsertion();
    return 0;
}