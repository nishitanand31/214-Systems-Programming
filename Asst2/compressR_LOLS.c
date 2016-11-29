#include <unistd.h> /*fork declared here*/
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include <sys/time.h>

int main(int argc, char ** argv) {
	struct timeval stop, start;
	gettimeofday(&start,NULL);
	
	int filLen=0;
	int p=atoi(argv[2]);
	FILE* fp; // file pointer to open the text file.
    fp = fopen(argv[1], "r");
	if( fp == NULL )  {
      printf("Error opening file\n");
      return 0;
	}
	fseek(fp, 0, SEEK_END);
	filLen = ftell(fp);
	fclose(fp);
	int part1len= filLen/p;
	part1len=part1len + (filLen%p);
	int part2len=(filLen)/p;
	//printf("%d file one length\n", part1len);
	//printf("%d file two length\n", part2len);
	pid_t myid = getpid();
	int status;
	pid_t id = fork();
	waitpid(id, &status, 0);
	if (id == -1) exit(1); // fork failed 
	if (id > 0)
	{
		printf("I'm the parent, Forked PID:%d\n",id); 
	 }else{
		int start=0, end=0;
		int pr=0;
		for(pr=0;pr<atoi(argv[2]);pr++){
			printf("b\n");
			if(pr==0){
				start=0;
				end=start+part1len;
				//pr++;
			}
			else{
				start=end;
				end=start+part2len;
				//pr++;
			}
			char* um = (char*)malloc(sizeof(char*)+filLen+1);
			sprintf(um, "%d", start);
			char* um1 = (char*)malloc(sizeof(char*)+filLen+1);
			sprintf(um1, "%d", end);
			char* um2 = (char*)malloc(sizeof(char*)+filLen+1);
			sprintf(um2, "%d", pr+1);
			execlp("./compressR_worker_LOLS",argv[1],um2, um, um1, (char*)NULL);
			gettimeofday(&stop,NULL);
			//printf("Time Required: %lu microseconds. \n", stop - start);
		}
	}
	return 0;
	//please compile both the worker and parent file and then run the parent file with two arguements. 
	//Arguement 1 is the name of the textfile and arguement two is how many processes you have
}