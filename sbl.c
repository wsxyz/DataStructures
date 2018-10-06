//
// Sorted Bidirectional List
// Created by Oleksiy Byelyayev on 02/10/2018.
//

#include "sbl.h"

/**
 * @Name: SBL_create
 * @Def: This function creates a Sorted Bidirectional List by allocating dynamic memory.
 *       If an error occurs during memory allocation the memory is freed.
 * @Args: ----.
 * @Ret: Returns a created Sorted Bidirectional List.
 *
 **/
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

/**
 * @Name: SBL_consult
 * @Def: This function returns the element where the "curr" pointer of the list is pointing.
 *       If the "curr" pointer is pointing to the head node or to the last node, an undefined element
 *       will be returned.
 * @Args: Receives a sorted bidirectional list.
 * @Ret: Returns an element of the list.
 *
 **/
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

/**
 * @Name: SBL_delete
 * @Def: This function deletes the element where the "curr" pointer of the list is pointing.
 *       If the "curr" pointer is pointing to the head node or to the last node, an error message
 *       will be prompt. The memory of the deleted node will be freed and the size variable will be decreased.
 * @Args: Pointer to a sorted bidirectional list.
 * @Ret: ----.
 *
 **/
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

/**
 * @Name: SBL_insertBefore
 * @Def: This function inserts an element before the node where the "curr" pointer is pointing
 *       and increments the size variable. Memory allocation for a new node is done here.
 *       It's not permitted to insert before the Head node, an error will be prompt.
 *       This function was previously designed for a non-sorted bidirectional list and is used
 *       by the SBL_insertOrdered function.
 *       Should be used carefully, the order of the list will be altered if used.
 * @Args: IN/OUT: *l = pointer to a sorted bidirectional list
 *        IN: e = element to be inserted in the list.
 * @Ret: ----.
 *
 **/
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

/**
 * @Name: SBL_insertAfter
 * @Def: This function inserts an element after the node where the "curr" pointer is pointing
 *       and increments the size variable. Memory allocation for a new node is done here.
 *       It's not permitted to insert afterr the Last node, an error will be prompt.
 *       This function was previously designed for a non-sorted bidirectional list.
 *       Should be used carefully, the order of the list will be altered if used.
 * @Args: IN/OUT: *l = pointer to a sorted bidirectional list
 *        IN: e = element to be inserted in the list.
 * @Ret: ----.
 *
 **/
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

/**
 * @Name: SBL_insertOrdered
 * @Def: This function inserts an element in order and increments the size variable.
         The position of insertion is found by comparing the new element variable to be inserted
         with the elements that are already in the list.
         This process is done by moving the "curr" pointer to the first available element,
         and going forward in the list while the desired sorting condition is not achieved.
 * @Args: IN/OUT: *l = pointer to a sorted bidirectional list
 *        IN: e = element to be inserted in the list.
 * @Ret: ----.
 *
 **/
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

/**
 * @Name: SBL_goToHead
 * @Def: This function moves the "curr" pointer to the first node of the list.
 *       Don't confuse the first node with the head node, the first node it's the
 *       node where the head node "next" pointer is pointing.
 * @Args: IN/OUT: *l = pointer to a sorted bidirectional list.
 * @Ret: ----.
 *
 **/
void SBL_goToHead(Sbl *l) {
    (*l).curr = (*(*l).head).next;
}

/**
 * @Name: SBL_goToLast
 * @Def: This function moves the "curr" pointer to the last node of the list.
 *       Like the SBL_goToHead function, this one moves the "curr" pointer to the
 *       last node of the list containing an element if a previous insertion has been done.
 * @Args: IN/OUT: *l = pointer to a sorted bidirectional list.
 * @Ret: ----.
 *
 **/
void SBL_goToLast(Sbl *l) {
    (*l).curr = (*(*l).last).prev;
}

/**
 * @Name: SBL_goToNext
 * @Def: This function moves the "curr" pointer to the next node where the "curr.next"  is pointing.
 *       If the "curr" pointer is already in the last Node of the list an error will be prompt.
 * @Args: IN/OUT: *l = pointer to a sorted bidirectional list.
 * @Ret: ----.
 *
 **/
void SBL_goToNext(Sbl *l) {
    if ((*(*l).curr).next == NULL) {
        printf ("Error goToNext: You're currently at the LAST node\n");
    } else {
        (*l).curr = (*(*l).curr).next;
    }
}

/**
 * @Name: SBL_goToPrev
 * @Def: This function moves the "curr" pointer to the next node where the "curr.prev" is pointing.
 *       If the "curr" pointer is already in the Head Node of the list an error will be prompt.
 * @Args: IN/OUT: *l = pointer to a sorted bidirectional list.
 * @Ret: ----.
 *
 **/
void SBL_goToPrev(Sbl *l) {
    if ((*(*l).curr).prev == NULL) {
        printf ("Error goToPrev: You're currently at the HEAD node\n");
    } else {
        (*l).curr = (*(*l).curr).prev;
    }
}

/**
 * @Name: SBL_isLast
 * @Def: This function checks if the "curr" pointer is pointing to the Last node of the list.
 * @Args: IN/OUT: l = sorted bidirectional list.
 * @Ret: Retuns 1 if the "curr" pointer is pointing to the last node.
 *
 **/
int SBL_isLast(Sbl l) {
    return (*l.curr).next == NULL;
}

/**
 * @Name: SBL_isHead
 * @Def: This function checks if the "curr" pointer is pointing to the Head node of the list.
 * @Args: IN/OUT: l = sorted bidirectional list.
 * @Ret: Retuns 1 if the "curr" pointer is pointing to the head node.
 *
 **/
int SBL_isHead(Sbl l) {
    return (*l.curr).prev == NULL;
}

/**
 * @Name: SBL_isEmpty
 * @Def: This function checks if the list is empty.
 * @Args: IN/OUT: l = sorted bidirectional list.
 * @Ret: Retuns 1 if the "curr.next" pointer is pointing to the same node where the last pointer
 *       of the list is pointing.
 *
 **/
int SBL_isEmpty(Sbl l) {
    return (*l.head).next == l.last;
}

/**
 * @Name: SBL_getSize
 * @Def: This function returns the number of elements that the list contains.
 * @Args: IN: l = sorted bidirectional list.
 * @Ret: Returns the number of elements contained in the list.
 *
 **/
long SBL_getSize(Sbl l) {
    return *(l.size);
}

/**
 * @Name: SBL_destroy
 * @Def: This function frees all the dynamic memory used by the sorted bidirectional list.
 * @Args: IN/OUT: l = pointer to a sorted bidirectional list.
 * @Ret: ----.
 *
 **/
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