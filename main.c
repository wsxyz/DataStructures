/**
 *
 * @File: main.c
 * @Def: Main entry point to the program to try and verify the designed data structures.
 *       Sorted Bidirectional List 1.0.0
 * @Author: Oleksiy Byelyayev
 * @Date: 06/10/2018
 *
 **/
 
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
    int n = INT_MAX/100000000;
    time_t t;
    srand((unsigned)time(&t));

    printf("\n---- Consult Test ----\n");
    printf("Number of Elements to Insert: %d\n", n);

    for (i = 0; i < n; i++) {
        e.num = rand() % n;
        SBL_insertOrdered(&list, e);
    }

    printf("ASC Order:\n");
    SBL_goToHead(&list);
    while (!SBL_isLast(list)) {
        e = SBL_consult(list);
        printf("\tElement: %d\n", e.num);
        SBL_goToNext(&list);
    }

    printf("\nDESC Order:\n");
    SBL_goToLast(&list);
    while (!SBL_isHead(list)) {
        e = SBL_consult(list);
        printf("\tElement: %d\n", e.num);
        SBL_goToPrev(&list);
    }

    SBL_destroy(&list);

    return 0;
}

/**
 * @Name: testConsult
 * @Def: A test function designed to verify if the first and the last element are the expected
 * @Args: ----.
 * @Ret: Returns 0 if this test reaches successfully the return statement.
 *
 **/
int testConsult() {

    Sbl list = SBL_create();
    Element e;
    int i = 0;
    int n = 10;
    time_t t;
    srand((unsigned)time(&t));

    printf("\n---- Consult Test ----\n");
    printf("Number of Elements to Insert: %d\n\n", n);

    for (i = 0; i < n; i++) {
        e.num = rand() % n;
        SBL_insertOrdered(&list, e);
    }

    SBL_goToHead(&list);
    while (!SBL_isLast(list)) {
        e = SBL_consult(list);
        printf("\tElement: %d\n", e.num);
        SBL_goToNext(&list);
    }

    SBL_goToHead(&list);
    e = SBL_consult(list);
    printf("\nFirst Element of the List: %d\n", e.num);

    SBL_goToLast(&list);
    e = SBL_consult(list);
    printf("First Element of the List: %d\n", e.num);

    SBL_destroy(&list);

    return 0;
}


/**
 * @Name: testDelete
 * @Def: A test function designed to verify if the delete function is working as expected.
 * @Args: ----.
 * @Ret: Returns 0 if this test reaches successfully the return statement.
 *
 **/
int testDelete() {

    Sbl list = SBL_create();
    Element e;
    int i = 0;
    int n = 10;
    time_t t;
    srand((unsigned)time(&t));

    printf("\n---- Delete Test ----\n");
    printf("Number of Elements to Insert: %d\n", n);

    for (i = 0; i < n; i++) {
        e.num = rand() % n;
        SBL_insertOrdered(&list, e);
    }

    printf("Before Deletion: \n");
    SBL_goToHead(&list);
    while (!SBL_isLast(list)) {
        e = SBL_consult(list);
        printf("\tElement: %d\n", e.num);
        SBL_goToNext(&list);
    }

    SBL_goToHead(&list);
    while (!SBL_isLast(list)) {
        SBL_delete(&list);
        SBL_goToNext(&list);
    }

    if (SBL_getSize(list) != 0) {
        printf("\nDELETE TEST FAILED\n");
        printf("\nAfter Deletion: \n");
        SBL_goToHead(&list);
        while (!SBL_isLast(list)) {
            e = SBL_consult(list);
            printf("\tElement: %d\n", e.num);
            SBL_goToNext(&list);
        }
    } else {
        printf("\nDELETE TEST SUCCESSFUL\n");
    }

    SBL_destroy(&list);

    return 0;
}

int main() {
    printf("Data Structures in C!\n");
    testInsertion();
    testConsult();
    testDelete();
    return 0;
}