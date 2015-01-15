//Xiaoli Tang and Richi Mizuno
//this is the driver program to test the table and list ADT
#include <stdio.h>
#include "List.h"
#include "hashtable.h"


int main(){
    ListRef listB=newList();
    ListRef listA=newList();
   // insertAfterLast(listA, num2);
//insertAfterLast(listA, 234);
   add(listB, 455);
   add(listB, 234);
   add(listB, 455);
   add(listB, 123);
   add(listB, 123);
   printList(listB);
    
    add(listA, 234);
    add(listA, 333);
    hashset_ref hashsetA= new_hashset(15);
    insert_hashtable(hashsetA, 34289);
    insert_hashtable(hashsetA, 234);
    insert_hashtable(hashsetA, 333);
    add(find(hashsetA,34289), 333);
 
   // sortList(find(hashsetA,34289));

//    if(find(hashsetA,342)==NULL){
  //      printf("print NULL\n");
   // }
    
    add(find(hashsetA,34289),45667);
    
   if(add(listA,333)==false){
    printf("true");
    }

    
    if(add(listA, 34289)==true){//if new book is add to the customer list
        printf("new bookID inserted \n");
         
        if(find(hashsetA,34289)==NULL){//go to the hashset, check if the bookId exit
           insert_hashtable(hashsetA, 34289);
            printf("455 inserted\n");
            //if the bookId is not already exit, create a new slot for it
        }
        else{
            printf("creating new slot\n");
            ListRef new=find(hashsetA,34289);
            moveLast(listA);
            movePrev(listA);
            while(!offEnd(listA)){
            add(new,getCurrent(listA));//add the previous one to 333's list
          
            //add 333 to the previou's bookId's list
            add(find(hashsetA,getCurrent(listA)),getLast(listA));
            movePrev(listA);//move the previous one in the customer's list
            }//end of while
            //also add 333 to the previous bookId's list
            
        }
    
    
     }
    printList(listA);

  print_hashset(hashsetA);
}


