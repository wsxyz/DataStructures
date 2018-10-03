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

void SBL_delete(Sbl *l) {

    Node *aux;

    if ((*l).curr == (*l).head || (*l).curr == (*l).last) {
        printf ("Delete Error: ");
        if ((*l).curr == (*l).head) {
            printf("Unable to delete HEAD node\n");
        } else {
            printf("Unable to delete LAST node\n");
        }
    } else {
        aux = (*l).curr;
        (*(*(*l).curr).prev).next = (*aux).next;
        (*(*(*l).curr).next).prev = (*aux).prev;
        (*l).curr = (*(*l).curr).next;
        free(aux);
        (*(*l).size)--;
    }
}

void SBL_insertBefore(Sbl *l, Element e) {

    Node *aux;
    if ((*l).curr == (*l).head) {
        printf("Insert Error: Unable to insert before HEAD node\n");
    } else {
        aux = (Node*)malloc(sizeof(Node));
        if (aux == NULL) {
            printf("Insert Error: Malloc Failed\n");
        } else {
            (*aux).e = e;
            (*aux).next = (*l).curr;
            (*aux).prev = (*(*l).curr).prev;
            (*(*(*l).curr).prev).next = aux;
            (*(*l).curr).prev = aux;
            (*(*l).size)++;
        }
    }
}

void SBL_insertAfter(Sbl *l, Element e) {

    Node *aux;
    if ((*l).curr == (*l).last) {
        printf("Insert Error: Unable to insert after LAST node\n");
    } else {
        aux = (Node*)malloc(sizeof(Node));
        if (aux == NULL) {
            printf("Insert Error: Malloc Failed\n");
        } else {
            (*aux).e = e;
            (*aux).next = (*(*l).curr).prev;
            (*aux).prev = (*l).curr;
            (*(*(*l).curr).next).prev = aux;
            (*(*l).curr).next = aux;
            (*(*l).size)++;
        }
    }
}

void SBL_insertOrdered(Sbl *l, Element e) {

    int found = 0;
    Node *aux = (*l).curr;

    (*l).curr = (*(*l).head).next;
    while (!found && (*(*l).curr).next != NULL)  {
        if ( (*(*l).curr).e.num < e.num) {
            (*l).curr = (*(*l).curr).next;
        } else{
            found = 1;
        }
    }

    SBL_insertBefore(l, e);
    (*l).curr = aux;
}

void SBL_goToHead(Sbl *l) {
    (*l).curr = (*(*l).head).next;
}

void SBL_goToLast(Sbl *l) {
    (*l).curr = (*(*l).last).prev;
}

void SBL_goToNext(Sbl *l) {
    if ((*(*l).curr).next == NULL) {
        printf ("Error goToNext: You're currently at the LAST node\n");
    } else {
        (*l).curr = (*(*l).curr).next;
    }
}

void SBL_goToPrev(Sbl *l) {
    if ((*(*l).curr).prev == NULL) {
        printf ("Error goToPrev: You're currently at the HEAD node\n");
    } else {
        (*l).curr = (*(*l).curr).prev;
    }
}

int SBL_isLast(Sbl l) {
    return (*l.curr).next == NULL;
}

int SBL_isHead(Sbl l) {
    return (*l.curr).prev == NULL;
}

int SBL_isEmpty(Sbl l) {
    return (*l.head).next == l.last;
}

long SBL_getSize(Sbl l) {
    return *(l.size);
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