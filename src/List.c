//Xiaoli Tang and Richi Mizuno
//This contains the implementation of the operations of the linked list ADT


#include <stdio.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "List.h"

typedef struct Node {//node structure
    long data;
    int count;
    struct Node* next;
    struct Node* prev;
} NodeType;

typedef struct List {//linked list header
    NodeType* first;
    NodeType* last;
    NodeType* current;
} ListType;


//Constructors
ListRef newList(void){ // Creates a new struct list.
    ListRef list = malloc(sizeof(struct List));
    assert (list != NULL);
    list->first = NULL;
    list->current = NULL;
    list->last = NULL;
    return list;
}

void freeList (ListRef *L){
    while((*L)->first!=NULL){
        NodeType *tmp = (*L)->first;
        (*L)->first = (*L)->first->next;
        free(tmp);
    }
    free (L);//or*L?
}


//Access functions
bool isEmpty(ListRef L){ // returns true is list is empty else returns false.
   return L->first == NULL;

}


bool offEnd(ListRef L){  // returns true if current == NULL
    return L->current==NULL;
}

bool atFirst(ListRef L){ // returns true if current == first and !offEnd()
    return L->current==L->first && !offEnd(L);
}

bool atLast(ListRef L){  // returns true if current == last and !offEnd()
    return L->current==L->last && !offEnd(L);
}

long getFirst(ListRef L){ // return the first element; pre: !isEmpty()
    assert(!isEmpty(L));
    return L->first->data;
}

long getLast(ListRef L){ // return the last element; pre: !isEmpty()
    assert(!isEmpty(L));
    return L->last->data;
}

long getCurrent(ListRef L){ // return the current element pre: !offEnd()
    assert(!offEnd(L));
    return L->current->data;
    
}

int getLength(ListRef L){ // return the length of the list
    int size=0;
    NodeType *tmp = L->first;
    while(tmp!= NULL){
        ++size;
        tmp=tmp->next;
    }
    return size;
}

bool equals (ListRef A, ListRef B){ // return true iff the two lists have the same keys
    // in the same order
    if(getLength(A)!= getLength(B)){//check if the two list has the same length
        return false;//if not return false
    }
    NodeType *currA = A->first;//set two pointers to point to the first element of the lists
    NodeType *currB = B->first;
    
    for (int i=0; i<getLength(A);++i){
        if(currA->data!=currB->data){//check if the element have the same data
            return false;
        }
        currA=currA->next;//move to the next element of listA
        currB=currB->next;//move to the next element of listB
    }
    
    return true;
}

/*** Manipulation procedures ***/


void moveFirst(ListRef L){// set current marker to the first element in the list
    // Pre: !isEmpty(); Post: !offEnd()
    assert(!isEmpty(L));
    L->current=L->first;
}

void makeEmpty (ListRef L){
    moveFirst(L);
    L->first =NULL;
}

void moveLast(ListRef L){ // set current marker to the last element in the list
    // Pre: !isEmpty(); Post: !offEnd()
    assert(!isEmpty(L));
    L->current=L->last;
    assert(!offEnd(L));
}


void movePrev(ListRef L){ // set current marker one step backward.
    // Pre: !offEnd();   Post: offEnd() only if atFirst() was true
    assert(!offEnd(L));
    L->current=L->current->prev;
}

void moveNext(ListRef L){  // set current marker one step forward.
    // Pre: !offEnd();   Post: offEnd() only if atLast() was true
    assert(!offEnd(L));
    L->current=L->current->next;

}



void insertBeforeFirst(ListRef L, long data){ // Inserts new element before first
    // Post: !isEmpty()
    NodeType *new = malloc(sizeof (struct Node));
    new->data=data;
    if(L->first==NULL){//the list is empty
        L->first=new;//set the first to the new and set the next and prev
        new->next=NULL;
        new->prev=NULL;
    }else{
        //inserting node in front of the first node
        new->next=L->first;//set the prev and next pointer for the new element
        new->prev=NULL;
        L->first->prev=new;//link it back so it's doubly linked
        L->first=new;
    }
    
    L->current=new;
}
//l->header->first=new;

void insertAfterLast(ListRef L, long data){  // Inserts new element after last one
    // Post: !isEmpty()
    NodeType *new = malloc(sizeof (struct Node));
    new->data=data;
    if(L->first==NULL){//the list is empty
        L->first=L->last=new;
        new->next=NULL;
        new->prev=NULL;
    }else if(!isEmpty(L)){//similar to insertBeforeFirst
        new->prev=L->last;
        new->next=NULL;
        L->last->next=new;
        L->last = new;
        
    }
    L->current=new;
    
}


void insertBeforeCurrent(ListRef L, long data){// Inserts new element before current  one
    NodeType *new = malloc(sizeof (struct Node));
    new->data=data;
    if (!offEnd(L)){
        if(L->current==L->first){//if current is the first node
            insertBeforeFirst(L,data);
        }else{
            new->next=L->current;
            new->prev=L->current->prev;
            new->prev->next=new;
            L->current->prev=new;
        }
    }
}


void insertAfterCurrent(ListRef L, long data){ // Inserts new element after current  one
    // Pre: !offEnd(); Post: !isEmpty(), !offEnd()
    NodeType *new = malloc(sizeof (struct Node));
    new->data=data;
    
    if (!offEnd(L)){//do the insertion
        if(L->current==L->last){//if current is the last node
            insertAfterLast(L,data);
        }else{
            new->prev=L->current;
            new->next=L->current->next;
            new->next->prev=new;
            L->current->next=new;
        }
    }
    
}


void insertSort(ListRef L, long data){//insert the elemnt in sorted order
    if (isEmpty(L)){//check if it's a empty list
        insertAfterLast(L, data);//if so just insert as normal
    }else{
        L->current=L->first;//set the current point to the first element in the list
        long length = getLength(L);//get the length of the list
        for(int i=0; i<length;i++){//loop to compare the data
            //if the data to be inserted is greater than the element in the list
            if(data>getCurrent(L)){
                if(atLast(L)) {//check if the element in the list is the last element
                    insertAfterLast(L,data);//if so insert after last
                    break;//exit the loop once node inserted
                }else{
                    moveNext(L);//move to the next element in the list
                }
            }
            else{//if data<the current element in the list
                insertBeforeCurrent(L,data);//insert before the current element
                break;//we don't want the loop to continue after we already put the id
            }
        }
    }
    
}

void deleteFirst(ListRef L){ // delete the first element. Pre: !isEmpty()
    assert(!isEmpty(L));
    moveFirst(L);//set the pointer to the first element;
    L->first=L->first->next;//delete the element
    L->first->prev = NULL;
    L->current=L->first;//make current point to the first element
}

void deleteLast(ListRef L){ // delete the last element. Pre: !isEmpty()
    assert(!isEmpty(L));
    // moveLast(L);
    L->last=L->last->prev;
    L->last->next=NULL;
    L->current = L->last;
}


void deleteCurrent(ListRef L){ // delete the current element.
    assert(!isEmpty(L));
    if(atFirst(L)){//check if we are deleting the first element
        deleteFirst(L);
    }else if(atLast(L)){//check if we are deleting the last element
        deleteLast(L);
    }else{
        L->current->prev->next = L->current->next;
        L->current->next->prev = L->current->prev;
        L->current=L->current->next;
    }
    
}



/*** Other operations ***/
void printList(ListRef L){
    moveFirst(L);
    while(!offEnd(L)){
        printf("%ld ",getCurrent(L));
        printf("Count %d ", L->current->count);
        moveNext(L);
    }
    printf("\n");
}


ListRef copyList(ListRef L){
    ListRef listNew=newList();//create a new list
    NodeType *l = L->first;//set a pointer point to the first element of list L
    
    while(l!=NULL){
        insertAfterLast(listNew, l->data);//insert the node to list l with the data of list L
        l=l->next;
    }
    //printList(K);
    return listNew;
}

bool add(ListRef L, long book){//add the book into the lsit
   if(isEmpty(L)) {
        insertAfterLast(L, book);//if the list is empty
        L->first->count=1;//set the count
    }else{
        
      moveFirst(L);
      while(!offEnd(L)){
         if(L->current->data==book){//if the listNode for the book exits, add 1 to the count
          ++L->current->count;
         return false;
         }else {
             moveNext(L);//go to the next listNode
         }
      }
        insertAfterLast(L, book);//if no listNode for the book exits, insert new listNode
        L->current->count=1;
        }
      return true;
  }



void swap(NodeType *a, NodeType *b){
    NodeType *tmp = a;
    a->data=b->data;
    b->data=tmp->data;
    
}




/*void sortList(ListRef L, long book){
    if(!isEmpty(L)){
    
    while(!offEnd(L)) {
        if(L->current->prev!=NULL&&L->current->count>L->current->prev->count){
            swap(L->current,L->current->prev);
        }else if (L->current->next!=NULL&&L->current->count<L->current->next->count){
            swap(L->current,L->current->next);
            
        }
        moveNext(L);
        
    }}
}
*/

bool inList(ListRef L, long data){
    if(isEmpty(L)){
        printf("the list is empty");
    }else{
    moveFirst(L);
    while(!offEnd(L)){
        if(L->current->data==data){
            return true;
        }
        moveNext(L);
    }
    }
    return false;
}






long getRecommend(ListRef L,ListRef a){//get the data of the node tat has the maximum count
      NodeType *max=L->first;
    if(isEmpty(L)){
        printf("nothing to recommend");
    }else{
    moveFirst(L);
        moveNext(L);
        max = L->current;
        moveNext(L);
    while(!offEnd(L)&&L->current->next!=NULL){
        if(L->current->count>L->current->next->count&&!inList(a,L->current->data)){
            max=L->current;
            moveNext(L);
        }else {
            moveNext(L);//go to the next listNode
        }
    
    }
    }
     return max->data;
    
}





