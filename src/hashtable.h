//Xiaoli Tang and Richi Mizuno
//This is the header file for hashtable

#ifndef __HASHSET_H__
#define __HASHSET_H__

#include "List.h"


typedef struct hashset *hashset_ref;

//
// Create a new hashtable with a default number of elements.
//
hashset_ref new_hashset (void);

//
// Frees the hashtable, and the words it points at.
//
void free_hashset (hashset_ref);

//
// Inserts a new data into the hashtable.
//
void insert_hashtable (hashset_ref, long);


//find if the data is in the hashtable
ListRef find(hashset_ref, long);

//print the hashtable
void print_hashset(hashset_ref hashset);

//delete the hashtable
void dump_table(hashset_ref hashset);

//include list structure to check all the conditions to insert in the correct list
void insertHash(ListRef listA, long book, hashset_ref hashtable);

//get the book to recommend to the customer
//long getRecommend(ListRef L);

#endif

