#include "mymalloc.h"
#include <stdio.h>
#define block_SIZE_SIZE 5000
#define ENTRY_SIZE sizeof( Node )


static char block[5000] = {'0'};

static char init = '0';
//
//
//  Created by Nishit Anand on 10/10/16.
//  Created by Yash Phansalkar on 10/10/16.
//

#include "mymalloc.h"
#include <stdio.h>

//
//
//  Created by Nishit Anand on 10/10/16.
//  Created by Yash Phansalkar on 10/10/16.
//

#include "mymalloc.h"
#include <stdio.h>


int main(int argc, char** argv)
{
    // ADD PRINT STATEMENTS TO ALL TEST CASES.
    //--------------------Test case A---------------------------//
    
    //printf("\nSize of Node: %d \n", sizeof(Node));
    
    printf("\n\n\n//////////////////////// Test Case A ////////////////////////\n");
    char* ptr = malloc(sizeof(char)*3000);
    printf("Test A: Malloced 1 bit 3000 times.\n ");
    //printf("value: %p\n\n", &ptr);
    //char* ptr1 = malloc(4); //TEST
    //printf("Ptr1 Val: %p.\n \n \n ", &ptr1); // TEST
    free(ptr);
    printf("Freed 3000 1 byte pointers. \n");
    
    //----------------------------------------------------------------------
    
    //--------------------Test case B---------------------------//
    
    printf("\n\n\n//////////////////////// Test Case B ////////////////////////\n");
    char* ptr1 = malloc(sizeof(8));
    printf("Test B: Malloced 1 byte.\n ");
    //printf("Ptr1 Val: %p.\n \n \n ", &ptr1); // TEST
    int a=0;
    while(a<3000){
        free(ptr1);
        a++;
    }
    printf("Freed pointer 3000 times. \n  ");
    
    
    //----------------------------------------------------------------------
    
    //--------------------Test case C---------------------------//
    int count = 0;
    printf("\n\n\n//////////////////////// Test Case C ////////////////////////\n");
    char* ptr2 = malloc(sizeof(8));
    printf("Test C: Malloced 1 byte.\n ");
    count = sizeof(ptr2);
    printf("Size of the pointer is %d \n", sizeof(count));
    
    //----------------------------------------------------------------------
    
    //--------------------Test case D---------------------------//
    int count1 = 0;
    printf("\n\n\n//////////////////////// Test Case D ////////////////////////\n");
    char* ptr3 = malloc(sizeof(1500));
    printf("Test D: Malloced 1500 bits.\n ");
    count1 = sizeof(ptr3);
    
    //----------------------------------------------------------------------
    
    //--------------------Test case E ---------------------------//
    printf("\n\n\n//////////////////////// Test Case E ////////////////////////\n");
    char* ptr4 = malloc(sizeof(int)*200);
    printf("Test E: Malloced size of int*200 bits.\n ");
    free(ptr4);
    printf("\nFreed pointer. \n  ");
    
    //--------------------Test case F ---------------------------//
    printf("\n\n\n//////////////////////// Test Case F ////////////////////////\n");
    char* ptr5 = malloc(sizeof(2)*600);
    printf("Test F: Malloced size of 2bits*600 bits.\n ");
    free(ptr5);
    printf("\nFreed pointer. \n  ");
    free(ptr2);
    free(ptr3);
    printf("\nFreed pointer of test case C. \n  ");
    printf("\nFreed pointer of test case D. \n  ");
    
    
    return 0;
}

int main(int argc, char** argv)
{
    // ADD PRINT STATEMENTS TO ALL TEST CASES.
    //--------------------Test case A---------------------------//
    
    //printf("\nSize of Node: %d \n", sizeof(Node));
    
    printf("\n\n\n//////////////////////// Test Case A ////////////////////////\n");
    char* ptr = malloc(sizeof(char)*3000);
    printf("Test A: Malloced 1 bit 3000 times.\n ");
    //printf("value: %p\n\n", &ptr);
    //char* ptr1 = malloc(4); //TEST
    //printf("Ptr1 Val: %p.\n \n \n ", &ptr1); // TEST
    free(ptr);
    printf("Freed 3000 1 byte pointers. \n");
    
    //----------------------------------------------------------------------
    
    //--------------------Test case B---------------------------//
    
    printf("\n\n\n//////////////////////// Test Case B ////////////////////////\n");
    char* ptr1 = malloc(sizeof(8));
    printf("Test B: Malloced 1 byte.\n ");
    //printf("Ptr1 Val: %p.\n \n \n ", &ptr1); // TEST
    int a=0;
    while(a<3000){
        free(ptr1);
        a++;
    }
    printf("Freed pointer 3000 times. \n  ");
    
    
    //----------------------------------------------------------------------
    
    //--------------------Test case C---------------------------//
    int count = 0;
    printf("\n\n\n//////////////////////// Test Case C ////////////////////////\n");
    char* ptr2 = malloc(sizeof(8));
    printf("Test C: Malloced 1 byte.\n ");
    count = sizeof(ptr2);
    printf("Size of the pointer is %d \n", sizeof(count));
    
    //----------------------------------------------------------------------
    
    //--------------------Test case D---------------------------//
    int count1 = 0;
    printf("\n\n\n//////////////////////// Test Case D ////////////////////////\n");
    char* ptr3 = malloc(sizeof(1500));
    printf("Test D: Malloced 1500 bits.\n ");
    count1 = sizeof(ptr3);
    
    //----------------------------------------------------------------------
    
    //--------------------Test case E ---------------------------//
    printf("\n\n\n//////////////////////// Test Case E ////////////////////////\n");
    char* ptr4 = malloc(sizeof(int)*200);
    printf("Test E: Malloced size of int*200 bits.\n ");
    free(ptr4);
    printf("\nFreed pointer. \n  ");
    
    //--------------------Test case F ---------------------------//
    printf("\n\n\n//////////////////////// Test Case F ////////////////////////\n");
    char* ptr5 = malloc(sizeof(2)*600);
    printf("Test F: Malloced size of 2bits*600 bits.\n ");
    free(ptr5);
    printf("\nFreed pointer. \n  ");
    free(ptr2);
    free(ptr3);
    printf("\nFreed pointer of test case C. \n  ");
    printf("\nFreed pointer of test case D. \n  ");
    
    
    return 0;
}

static struct Node* start;

void* mymalloc(unsigned int dSize,  char* File, int Line){
    if(init=='0'){
        start = (struct Node*)block;
        start->previous=NULL;
        start->next=NULL;
        start->isFree='1';
        start->dataSize =sizeof(block) - sizeof(Node)-sizeof(Node*);
        init='1';
    }
    struct Node* temp = start;
    while(temp!=NULL){
        if(temp->isFree=='1' && dSize + sizeof(Node) <= temp->dataSize){
            Node* newMem = (Node*)(((char*)temp) + sizeof(Node) + dSize);
            newMem->previous=temp;
            newMem->next=temp->next;
            temp->next=newMem;
            if(newMem->next!=NULL){
                newMem->next->previous=newMem;
            }
            newMem->isFree='1';
            newMem->dataSize = temp->dataSize - dSize - sizeof(Node);
            temp->isFree='0';
            temp->dataSize=dSize;
            //printf("%d \n", temp->isFree);
            return ((void*)(((char*) temp)+sizeof(Node)));
        }
        temp = temp->next;
    }
    if(temp==NULL){
        printf("%s:%d:Error: There is not enough consecutive memory to allocate \n", File, Line);
    }
    return NULL;
}

void myfree(void *point,  char* File, int Line){
    int done='0';
    if(init=='0')
    {
        printf("%s:%d Error nothing has been initialized \n", File, Line);
    }
    Node* te = start;
    while(te!=NULL){
        char* f = ((char*)te)+sizeof(Node);
        //printf("%p is char f %d \n", f, te->isFree );
        if((char*)point>f && ((char*)point < f + te->dataSize)){
            printf("%s:%d:Error you are trying to malloc a location that is not allocated \n");
            return;
        }else if(f == (char*)point){
            if(te->isFree=='1'){
                printf("%s:%d Error: You are trying to free memory that is already free \n", File, Line);
                return;
            }
            else{
                te->isFree= '1';
                if(te->previous!=NULL && te->previous->isFree=='1'){
                    te->previous->dataSize=te->previous->dataSize + sizeof(Node) + te->dataSize;
                    if(te->next!=NULL){
                        te->next->previous=te->previous;
                        te->previous->next=te->next;
                        te=te->previous;
                    }
                }
                if(te->next!=NULL && te->next->isFree=='1'){
                    te->dataSize= te->dataSize+ sizeof(Node) + te->next->dataSize;
                    te->next=te->next->next;
                    if(te->next!=NULL){
                        te->next->previous=te;
                    }
                }
                done='1';
                //printf("Im free \n");
                break;
            }
        }else{
            te = te->next;
        }
    }
    if(te==NULL && done!='1'){
        printf("%s:%dError: Pointer could not be found in array \n", File, Line);
    }
}


