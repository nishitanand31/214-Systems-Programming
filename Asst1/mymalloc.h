//
//
//  
//
//  Created by Nishit Anand on 10/10/16.
//  Created by Yash Phansalkar on 10/10/16.
//


#ifndef mymalloc_h
#define mymalloc_h


#define malloc(x) mymalloc(x,__FILE__,__LINE__);
#define free(x) myfree(x,__FILE__,__LINE__);



typedef struct Node Node;


struct Node{
	//The previous entry
	struct Node* previous;
	//The next entry
	struct Node* next;
	//Checks to see if node is free
	int isFree;
	//Size of the data that is stored
	int dataSize;
};


/*
 *  Our malloc implementation
 */
void* mymalloc(unsigned int, char*, int );
/*
 *  Our free implementation
 */
void myfree(void*, char*, int);

#endif
