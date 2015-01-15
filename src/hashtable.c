//Xiaoli Tang and Richi Mizuno
//This is the hashtable implementation for the book list

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "List.h"
#include "hashtable.h"
#define HASH_NEW_SIZE 15

struct hashset {
    size_t size;
    int load;//currentsize
    ListRef *table;
}hashType;

hashset_ref new_hashset (void) {
    hashset_ref new = malloc (sizeof (struct hashset));
    assert (new != NULL);
    new->size = HASH_NEW_SIZE;
    new->load = 0;
   new->table = malloc (new->size * sizeof (ListRef*));
   assert (new->table != NULL);
   
    for(size_t i=1;i<=new->size;++i){//make a list for each customer
       new->table[i]=newList();
    }
     return new;
}

void double_array(hashset_ref hashset, long item){
    size_t starting_index = (size_t)item % hashset->size;
    ListRef *old = hashset->table;
    size_t new_length = 2*hashset->size+1;
    ListRef list=newList();
    ListRef *new = calloc(sizeof(list),new_length);
    //iterate over the old array
    for(size_t i = 0; i < hashset->size; ++i){
        //recompute the new size
        size_t index = starting_index+i;
        if(index >= hashset->size) index -= hashset->size;
        new[index] = old[index];
    }
    hashset->size=new_length;
    
    //insert
    for(size_t i=0; i<hashset->size;++i){
        size_t index = starting_index+i;
        if(index >= hashset->size) index -= hashset->size;
        if(!isEmpty(hashset->table[i])){
            add(hashset->table[i],item);
            hashset->load++;
            break;
        }
    }
    hashset->table = new;
    free(old);
    

}


void insert_hashtable (hashset_ref hashset, long book) {
  if(hashset->load * 4 > (int)hashset->size+1){
        double_array(hashset, book);
    }else{
        size_t starting_index = (size_t)book % hashset->size;
        for(size_t count=0; count<hashset->size;count++){
            size_t i = starting_index+count;
            if(i >= hashset->size) i -= hashset->size;
            //if(hashset->table[i]==NULL){
               // hashset->table[i] = book;
            if(isEmpty(hashset->table[i])){
                //insertAfterLast(hashset->table[i], book);
                add(hashset->table[i], book);
                ++hashset->load;
                return;
        }
        }
    }
}


ListRef find (hashset_ref hashset, long book) {
    size_t  starting_index = (size_t)book% hashset->size;
    size_t count = 0;
    while(count<hashset->size){
        size_t i = starting_index+count;
        if(i >= hashset->size){
         i = (hashset->size)-1;
        }
        if(isEmpty(hashset->table[i])){
        }
        else{
            if (getFirst(hashset->table[i])==book){
               return hashset->table[i];
                //return i;
            }
        
        
    }
        ++count;
   // return -1;
}
    return NULL;
}


void print_hashset(hashset_ref hashset){
    
       int size = 0;
    
    
    printf("%10d words in the hash set\n",hashset->load);
    printf("%10zd length of the hash array\n",hashset->size);
    
    
        for(size_t j=1;j<=hashset->size;++j){
            if(isEmpty(hashset->table[j])){
               
                 printf("empty slot \n");
            }else{
               //printf("%ld",getFirst(hashset->table[j]));
                printList(hashset->table[j]);
                size++;
            }
     
        }
}

void insertHash(ListRef listA, long book, hashset_ref hashtable){
    if(add(listA, book)==true){//if new book is add to the customer list
       // printf("new bookID inserted \n");
        
        if(find(hashtable,book)==NULL){//go to the hashset, check if the bookId exit
            insert_hashtable(hashtable, book);
        //    printf("creating new slot\n");
        }
            //if the bookId is not already exit, create a new slot for it
        if(find(hashtable,book)!=NULL){
         //   printf("new node add to the list");
            ListRef new=find(hashtable,book);
            moveLast(listA);
            movePrev(listA);
            while(!offEnd(listA)){
                add(new,getCurrent(listA));//add the previous one to book's list
        
                //add book to the previou's bookId's list
                add(find(hashtable,getCurrent(listA)),getLast(listA));
                movePrev(listA);//move the previous ones in the customer's list
            }//end of while
            //also add book to the previous bookId's list
            
        }
        
        
    }

}





