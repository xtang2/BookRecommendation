//Xiaoli Tang and Richi Mizuno
//Program1 Header (.h) file for double linked list ADT
//This contains the operations and types exported by the module. each elemennt is linked to the prev and next element.

#ifndef __LIST_H__
#define __LIST_H__

#include <stdbool.h>
typedef struct List *ListRef;

//typedef struct ListType *List;
// Constructors
/*** Constructors-Destructors ***/
ListRef newList(void);
void freeList(ListRef* pL);
/*** Access functions ***/
bool isEmpty(ListRef L); // returns true is list is empty else returns false.
bool offEnd(ListRef L);  // returns true is current == NULL
bool atFirst(ListRef L); // returns true if current == first and !offEnd()
bool atLast(ListRef L);  // returns true if current == last and !offEnd()
long getFirst(ListRef L); // return the first element; pre: !isEmpty()
long getLast(ListRef L);  // return the last element; pre: !isEmpty()
long getCurrent(ListRef L); // return the current element pre: !offEnd()
int getLength(ListRef L);  // return the length of the list
bool equals (ListRef A, ListRef B); // return true iff the two lists have the same keys
// in the same order
/*** Manipulation procedures ***/
void makeEmpty(ListRef L); // make the list empty. Post: isEmpty()
void moveFirst(ListRef L); // set current marker to the first element in the list
// Pre: !isEmpty(); Post: !offEnd()
void moveLast(ListRef L);  // set current marker to the last element in the list
// Pre: !isEmpty(); Post: !offEnd()
void movePrev(ListRef L);  // set current marker one step backward.
// Pre: !offEnd();   Post: offEnd() only if atFirst() was true
void moveNext(ListRef L);  // set current marker one step forward.
// Pre: !offEnd();   Post: offEnd() only if atLast() was true
void insertBeforeFirst(ListRef L, long data);  // Inserts new element before first
// Post: !isEmpty()
void insertAfterLast(ListRef L, long data);    // Inserts new element after last one
// Post: !isEmpty()
void insertBeforeCurrent(ListRef L, long data); // Inserts new element before current one
// Pre: !offEnd(); Post: !isEmpty(), !offEnd()
void insertAfterCurrent(ListRef L, long data);  // Inserts new element after current  one
// Pre: !offEnd(); Post: !isEmpty(), !offEnd()

void deleteFirst(ListRef L); // delete the first element. Pre: !isEmpty()
void deleteLast(ListRef L);  // delete the last element. Pre: !isEmpty()
void deleteCurrent(ListRef L); // delete the current element.
// Pre: !isEmpty(), !offEnd(); Post: offEnd()
/****other operation ***/
void printList(ListRef L);
ListRef copyList(ListRef L);
void insertSort(ListRef L, long data);//insert the element in sorted order
//Pre:!offEnd(), Post:!isEmpty()
bool add(ListRef L, long data);
//add element to the list, add up the count if they are already in the list
//pre:!offEnd(); Post:!isEmpty()
long getRecommend(ListRef L, ListRef a);
bool findElement(ListRef L, long data);

#endif

