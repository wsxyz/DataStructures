//
// Sorted Bidirectional List
// Created by Olekssiy Byelyayev on 02/10/2018.
//

#ifndef _SBL_H
#define _SBL_H

#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int num;
}Element;

typedef struct n {
    Element e;
    struct n *next;
    struct n *prev;
}Node;

typedef struct {
    Node *head;
    Node *last;
    Node *curr;
    long *size;
}Sbl;

Sbl SBL_create ();
Element SBL_consult (Sbl l);
void SBL_delete (Sbl *l);

void SBL_insertBefore (Sbl *l, Element e);
void SBL_insertAfter (Sbl *l, Element e);
void SBL_insertOrdered (Sbl *l, Element e);

void SBL_goToHead (Sbl *l);
void SBL_goToLast (Sbl *l);
void SBL_goToNext (Sbl *l);
void SBL_goToPrev (Sbl *l);

int SBL_isLast (Sbl l);
int SBL_isHead (Sbl l);
int SBL_isEmpty (Sbl l);
long SBL_getSize (Sbl l);
void SBL_destroy (Sbl *l);

#endif //_SBL_H
