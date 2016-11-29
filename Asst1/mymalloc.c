#include "mymalloc.h"
#include <stdio.h>
#define block_SIZE_SIZE 5000
#define ENTRY_SIZE sizeof( Node )


static char block[5000] = {'0'};

static char init = '0';

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


