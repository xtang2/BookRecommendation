//cmps101 Xiaoli Tang and Richi Mizuno
//Program3 main.c
//This is the main program that read the file
//get the customer information and their purchase history
//create a linked list for each customer.and a hashset for the book
//Find the book tat has the highest priority and recommend
//it to the user when requested to


#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <string.h>

#include "hashtable.h"
#include "List.h"


char *execname = NULL;
int exit_status = EXIT_SUCCESS;


int main (int argc, char **argv) {
    if(argc>0){
        execname = basename (argv[0]);
    }
    int nCus;
    int nPur;
    int hashSize;
    
    FILE *input = fopen (argv[1], "r");//open the file
    if (input == NULL) {//check for NULL
        fflush (NULL);
        fprintf (stderr, "%s: %s: %s\n",//print out error message
                 execname, argv[1], strerror (errno));
        fflush (NULL);
        exit_status= EXIT_FAILURE;
    }else {
        
       
        fscanf(input,"%d", &nCus);//read and store the number of customer
        fscanf(input,"%d", &nPur);//read and store the number of purchases
        fscanf(input,"%d", &hashSize);//read and store the size of the hashtable
        printf("the number of customer is: %d\n",nCus);
        printf("the number of purchase is: %d\n",nPur);
      
         ListRef list=newList();
        
        ListRef *customer=calloc(sizeof(list),nCus);
        for(int i=1;i<=nCus;++i){//make a list for each customer
            customer[i]=newList();
        }
        
        hashset_ref hashsetA=new_hashset();
        
        for(int i=0; i<nPur;i++){//keep reading the rest of the file
            int custID;
            long bookID;
            int indicator;
            fscanf(input,"%d", &custID);//get the customer ID
            fscanf(input, "%ld", &bookID);//get the book ID
            fscanf(input,"%d", &indicator);//get the indicator
            //add(customer[custID],bookID);
            //printf("new book added\n");
        
            insertHash(customer[custID], bookID,hashsetA);//insert the book id into the hashset
            long recommend;
           //       print_hashset(hashsetA);
            if(indicator==1){
                
                        recommend=getRecommend(find(hashsetA,bookID),customer[custID]);
                         
                
                printf("Customer buying book %ld also purchased %ld \n",bookID,
                       recommend);
            
        
        }
        

        }
        print_hashset(hashsetA);

             fclose (input);
        exit_status = EXIT_SUCCESS;
    
 
}

}






    


