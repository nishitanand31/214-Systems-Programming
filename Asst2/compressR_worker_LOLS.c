#include <unistd.h> /*fork declared here*/
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>

typedef struct FileData
{
    char* FileName;
    int DivideValue;
    int InitialIndex;
    int FinalIndex;
    int Num; // no of thread
    
} fileData;

char* compressText(char* str, int proc){
	int len=strlen(str);
	int x=0, rep=0, tempCount=0;
	char* temp=(char*)malloc(sizeof(char*)+strlen(str)+1);
	char* letter=(char*)malloc(sizeof(char)*2);
	//temp[strlen(str)-1]='\0';
	letter[1] = '\0';
	if(len==1){
		//return str;
	}
	*letter = str[x];
	while(x<len){
		if(x==0){
			x++;
		}
		if(str[x]==*letter){
			rep++;
			x++;
		}
		else{
			if(rep==1){
				temp[tempCount]=*letter;
				temp[tempCount+1]=*letter;
				tempCount=tempCount+2;
				rep=0;
				letter[0]=str[x];
				x++;
			}
			else if(rep==0){
				temp[tempCount]=letter[0];
				tempCount++;
				letter[0]=str[x];
				x++;
			}
			if(rep>1){
				char* um = (char*)malloc(sizeof(char*)+strlen(str)+1);
				sprintf(um, "%d", rep+1);
				//printf("%s is um & %c is letter %s is temp\n", um,*letter, temp);
				um=strcat(um, letter);
				um[strlen(um)]='\0';
				//printf("%s is um\n", um);
				temp[strlen(str)]='\0';
				//printf("%s is temp \n", temp);
				temp=strcat(temp,um);
				//printf("%s is temp \n", temp);
				temp[strlen(str)]='\0';
				//printf("%s is um and %s is temp This is the concatinated part \n", um, temp);
				temp[strlen(temp)]='\0';
				tempCount=tempCount+strlen(um);
				*letter=str[x];
				x++;
				rep=0;
				//printf("This is the string as of now %s \n", temp);
			}
		}
	}
	if(rep==1){
		temp[tempCount]=*letter;
		temp[tempCount+1]=*letter;
		tempCount=tempCount+2;
		rep=0;
		*letter=str[x];
		x++;
	}
	else if(rep==0){
		temp[tempCount]=*letter;
		tempCount++;
		*letter=str[x];
		x++;
	}
	if(rep>1){
		char* um = (char*)malloc(sizeof(char*)+strlen(str)+1);
		sprintf(um, "%d", rep+1);
		//printf("%s is um & %c is letter %s is temp\n", um,*letter, temp);
		um=strcat(um, letter);
		um[strlen(um)]='\0';
		//printf("%s is um\n", um);
		temp[strlen(str)]='\0';		
		//printf("%s is temp \n", temp);
		temp=strcat(temp,um);
		//printf("%s is temp \n", temp);
		temp[strlen(str)]='\0';
		//printf("%s is um and %s is temp This is the concatinated part \n", um, temp);
		temp[strlen(temp)]='\0';
		tempCount=tempCount+strlen(um);
		*letter=str[x];
		x++;
		rep=0;
		//printf("This is the string as of now %s \n", temp);	
	}
	temp[tempCount]='\0';

	char* mu = (char*)malloc(sizeof(char*)+1);
	sprintf(mu, "%d", proc);
	//printf("%s is \n", mu);
	mu[strlen(mu)]='\0';
	printf("The is the file name for the process is  %s \n", mu);
	//printf("%s is mu\n", mu);
	FILE* fp=fopen( mu, "w" );
	fputs(temp, fp);
	fclose(fp);
	//return ;
}



//fileName is the name of the file, p is the number of the process we running
void* compressT_LOLS( char* fileName, int p, int cursor, int end){
	char *str =(char *)malloc(sizeof(char *)+1);
	int len=0;
	FILE* fp; // file pointer to open the text file.
    fp = fopen(fileName, "r");
	if( fp == NULL )  {
      printf("Error opening file\n");
      //return 0;
	}
	while(cursor<end){
		fseek(fp, cursor, SEEK_SET);
		str[len]=fgetc(fp);
		len++;
		cursor++;
	}
	str[len]= '\0';
	//int start = ftell(fp);
	fclose(fp);
	compressText(str, p);
}



int main(int argc, char ** argv) {
	printf("Im in a process\n");
	printf("%s is argv0, %s is argv1, %s is argv2, %s is argv3 this is to show the arguments being passed from the parent to worker file \n", argv[0], argv[1], argv[2], argv[3]);
	compressT_LOLS(argv[0], atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
	return 0;
	
}