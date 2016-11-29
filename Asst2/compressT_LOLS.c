//
//
// compressT_LOLS.c
//
//  Created by Nishit Anand on 11/16/16.
//  Created by Yash Phansalkar on 11/16/16.
//  Copyright © 2016 Nishit Anand. All rights reserved.
//  Copyright © 2016 Yash Phansalkar. All rights reserved.

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>

/*
 * This is the structure we use to save and use data in Compress.
 */
typedef struct FileDetails {
    int InitialIndex; // Has the initial index location of the string.
    int FinalIndex;// Has the final index of the location in Array.
    int Num;//To check which thread is it. TO create new file.
    char* Filename; //To store name of the file.
    int Flag; //To check if that is the first thread only.
} fileData; // Creation of File Data.


/*
 typedef struct CopyData{
 char alp; // for alphabet
 int rep; // to count repetetion.
 } copyData;
 */

/*
 * The function where we read the file and compress the string.
 */
void* compress( void* Sttruct ){
    
    fileData Array = *(fileData *) Sttruct; //Dereferencing the void parameter.
    int InitialIndex = Array.InitialIndex; //initial Index of the string.
    int FinalIndex = Array.FinalIndex; //final Index of string to compress.
    int Num = Array.Num; // No of threads.
    
    char* file = Array.Filename; // local copy for the name of the file.
    
    //printf("We made it! %d and %d and %s\n", InitialIndex, FinalIndex, file);
    
    FILE *filePtr; // File pointer.
    filePtr =fopen(file, "r"); // open the file to read the string in compression and copy data.
    // If there is not file to open.
    if(filePtr == NULL){
        printf("There is no text file to open.\n");
        exit(0);
    }
    char CompString[FinalIndex-InitialIndex]; // Array of the length of the string to be compressed.
    int count=0;
    int index=0;
    char c; // to store the character at the particular location of file pointer.
    
    //This function copies the whole string from the
    do
    {
        c = fgetc(filePtr);
        // till the end of file pointer.
        if( feof(filePtr) )
        {
            break ;
        }
        // only works if it is an alphabet, else discards the space or number or symbol.
        if(index >= InitialIndex && index <=FinalIndex && isalpha(c)!=0 ){
            CompString[count]= c;
            count++;
        }
        index++;
    }while(1);
    CompString[count]= '\0';
    fclose(filePtr); // Close the read file.
    
    count=1;
    index=0;// first character of the string.
    int i =0; // to iterate through the sting.
    int letter=0; // index of the letter.
    char compressedpart[strlen(CompString)]; // to store the compressed string. like 4a3b
    // will run till the end of the string.
    while( i < strlen(CompString))
    {
        // this loop would work till the time the i is smaller than the short string length.
        while(count < strlen(CompString))
        {
            if( CompString[i] == CompString[count])
            {
                index++;
                count++;
            }else{
                break;
            }
            
        }
        // check if index is 0,1 or greater according to LOLS rules
        switch( index){
                //only one letter found;
            case 0: // if there is no repetetion.
                compressedpart[letter] = CompString[i];
                index=0;
                i= count;
                letter++;
                
                break;
            case 1: // if the letter repeats once.
                compressedpart[letter] = CompString[i];
                letter++;
                compressedpart[letter] = CompString[i]; // assigns the letter to the temp array.
                index = 0;
                i=count;
                count++;
                letter++;
                
                break;
            default: // if the letter repeats multiple times.
                compressedpart[letter] = (index+1) + '0';
                letter++;
                compressedpart[letter] = CompString[i]; // assigns the letter to the temp array.
                index = 0;
                i=count;
                count++;
                letter++;
        }
    }
    compressedpart[letter] = '\0'; // terminate the string.
    //printf("This is the compressed string of characters: %s\n",compressedpart);
    
    //create new file with compressed part;
    char newfile[ strlen(file)+6];
    strcpy(newfile, file);
    i=0;
    while(i < strlen(file)){
        if(newfile[i] == '.')
        { // this removes the .txt from the file name and replaces it with _.
            newfile[i] = '_';
            break;
        }
        i++;
    }
    // this is to add _LOLS to the file name;
    newfile[i+4]= '_';
    newfile[i+5]= 'L';
    newfile[i+6]= 'O';
    newfile[i+7]= 'L';
    newfile[i+8]= 'S';
    
    if(Array.Flag == 0)
    { // if the it is the only file.
        //only one part.
        newfile[i+9]= '\0';
    }else
    {   // if there are multiple file strings.
        newfile[i+9]= Num + '0';
        newfile[i+10]= '\0';
    }
    
    //printf("The name of the new file is: %s\n", newfile);
    // this is to write the array/the string to the file.
    filePtr = fopen(newfile, "w");
    fputs(compressedpart, filePtr); // prints it in the file.
    fclose(filePtr); // closes the file.
    return 0;
}


int main( int argc, char* argv[] )
{
    
    // gets the time of the day to calculate the running time.
    struct timeval stop, start;
    gettimeofday(&start, NULL);
    
    char* file = argv[1]; // Name of text file.
    char* divide = argv[2]; // No of parts.
    int numpart= atoi(divide);
    
    // if the commandline arguments is less  than or more than the required.
    if(argc != 3){
        printf("Invalid Number of inputs\n");
        exit(0);
    }
    //printf("number of parts= %d\n", numpart);
    FILE *filePtr; // File pointer.
    filePtr =fopen(file, "r"); // this is where we open the file.
    
    //If the file is not there.
    if(filePtr == NULL){
        printf("There is no text file to open.\n");
        exit(0);
    }
    int stringsize=0;
    //If there is a file and is open.
    if(filePtr){
        // to set the file pointer.
        fseek(filePtr,0, SEEK_END); //Sets the pointer.
        stringsize= ftell(filePtr); // Get the string size.
        rewind(filePtr); // puts the pointer to the beginning of the file.
        
    }
    //To find the length of each string.
    int i = 0; // to transverse
    int FinalIndex=0; //Final index.
    int InitialIndex=0; // Initial index of the string.
    int count= 0; // to iterate and keep a track of work.
    fileData Array[numpart]; // Array the structure to store multiple structures in it.
    
    //Assign structure to array.
    while(count < numpart){
        fileData structure; //creating struct for each part of the Array.
        Array[count] = structure; // Assigning the struct.
        count++;
    }
    count= 0; // to reuse count without re-declaring a new variable.
    pthread_t threads[numpart]; // create an array of threads which would accomoate the threads upto total number of parts.
    while (i< stringsize){
        if( i == 0)
        {   // this is for the first string only. We add the mod of number of string to first string.
            FinalIndex += (stringsize/numpart) + (stringsize % numpart) - 1;
            i= FinalIndex+1;
        }else{
            FinalIndex = (stringsize/numpart) + InitialIndex- 1; // if not the first string.
            i=FinalIndex+1;
        }
        if(numpart==1)
        {
            //This is the false value.
            Array[count].Flag = 0; // Assigning the flag if the .
        }
        else
        {
            //This is the true value.
            Array[count].Flag = 1;
        }
        Array[count].InitialIndex = InitialIndex; // Assigning initial index to struct
        Array[count].FinalIndex = FinalIndex; // Assigning final index to struct
        Array[count].Num= count; // Assigning current thread number to struct
        Array[count].Filename = file; // File name to struct.;
        
        // Create a thread.
        pthread_create(&threads[count], NULL, compress, &Array[count] );
        InitialIndex = i;
        count++;
    }
    
    // To join the threads together.
    int counter=0; // this is to iterate through joining threads.
    while( counter < count)
    {
        pthread_join(threads[counter], NULL); // This is where we join the threads.
        counter++; // incrementing the counter.
    }
    //printf("End of Main Method. \n");
    
    // this gets the time it takes to run the program
    printf("\n");
    gettimeofday(&stop, NULL);
    printf("Time Required: %lu microseconds. \n", stop.tv_usec - start.tv_usec);
    
    return 0;
}
