//
// Sorted Bidirectional List
// Created by Oleksiy Byelyayev on 02/10/2018.
//

#include "sbl.h"

Sbl SBL_create() {

    Sbl l;
    l.head = (Node *) malloc(sizeof(Node));

    if (l.head == NULL) {
        printf("Create Error: Malloc Failed\n");
    } else {
        l.last = (Node *) malloc(sizeof(Node));
        if (l.last == NULL) {
            printf("Create Error: Malloc Failed\n");
            free(l.head);
        } else {
            l.size = (long *) malloc(sizeof(long));
            if (l.size == NULL) {
                printf("Create Error: Malloc Failed\n");
                free(l.head);
                free(l.last);
            } else {
                *(l.size) = 0;
                l.curr = l.last;
                (*l.head).next = l.last;
                (*l.head).prev = NULL;
                (*l.last).prev = l.head;
                (*l.last).next = NULL;
            }
        }
    }
    return l;
}

Element SBL_consult(Sbl l) {

    Element e;
    e.num = -1;

    if (l.curr != l.head && l.curr != l.last) {
        e = (*l.curr).e;
    } else {
        printf("Consult Error: ");
        if (l.curr == l.head) {
            printf("Unable to consult HEAD node\n");
        } else {
            printf("Unable to consult LAST node\n");
        }
    }
    return e;
}

void SBL_destroy(Sbl *l) {

    Node *aux;

    while ((*l).head != NULL) {
        aux = (*l).head;
        (*l).head = (*(*l).head).next;
        free(aux);
    }

    (*l).curr = NULL;
    (*l).last = NULL;
    free((*l).size);
    (*l).size = NULL;
}