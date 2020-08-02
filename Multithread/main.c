/*
 * Programmer: M.Hassan Zaheer
 * Name: Conways Game
 * Desc: Simulation of Conways game in a multi threaded program
 * Date: 30th July 2020
 */

//--Includding Files--//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h> 

struct thread_args
{
    bool *i;
    bool *o;
};
struct thread_args Structthread1;

//--Global Variables--//
FILE *filePtr;//pointer for reading and writing to file.
bool **gridIn;//pionter to a pointer variable to be used as 2D array 
bool **gridOut;//pionter to a pointer variable to be used as 2D array
int n;//size of the grid NxN
int numGens;//Number of generations to run
char fileName[20];//Name of the input output file
int nTh;//No of threads to use


//--Function Declarations--//
void printGrid(bool *ptr[],int len);
void Out2File(bool *ptr[],int len);
void nextGen(bool *in[], bool *out[], int len,int nth);
bool isLiving(bool *in[],int x, int y, int len);
void* thread2(void*ptr);
void* thread4(void*ptr);
void* thread6(void*ptr);
void* thread8(void*ptr);
void* thread10(void*ptr);

//--Main Function--//
int main(int argc, char const *argv[]) {
	//--Get inputs from Command Line--//
	printf("%ld, %ld, %ld, %ld\n",sizeof(int),sizeof(bool),sizeof(double),sizeof(char) );
	if (argc < 4) {
		printf("%s\n","ERROR: Wrong usage of the program! Sample Correct usage is:-\n:\\conway.run text.txt 1 10 2\n");
		return 0;
	}
	strcpy(fileName,argv[1]);
	numGens = atoi(argv[2]);
	if (numGens<0)
	{
		printf("%s\n","ERROR: Wrong usage of the program! Number of generations can not be negative.\n:\\conway.run text.txt 1 10\n");
		return 0;
	}
	n = atoi(argv[3]);
	if (n<5)
	{
		printf("%s\n","ERROR: Grid Size can not be less than 5.\n:\\conway.run text.txt 1 10\n");
		return 0;
	}
  nTh = atoi(argv[4]);
  if (nTh!=2)
  {
    printf("%s\n","ERROR: No of threads must be the divisble by 2 (max 10).\n:\\conway.run text.txt 1 10 2\n");
		return 0;
  }
	//--End Get Input from Command Line--//

	//--Initialize Grids--//
	printf("%s\n","Initializing the GRIDS" );
	bool **gridIn = (bool **)malloc(n * sizeof(bool *));
	bool **gridOut = (bool **)malloc(n * sizeof(bool *));
	for (int i = 0; i < n; ++i)	{
		gridIn[i] = (bool *)malloc(n * sizeof(bool));
		gridOut[i] = (bool *)malloc(n * sizeof(bool));
		for (int j = 0; j < n; ++j){
			gridIn[i][j] = false;
			gridOut[i][j] = false;
		}
	}

	//-- Read from File --//
	printf("%s\n","Reading File!" );
	filePtr = fopen(fileName,"r");
	if(filePtr == NULL){
		printf("%s\n","ERROR: Invalid File name or file not found!\n" );
		return 0;
	}//end if filePtr Null
	ssize_t charRead ; size_t len=0;
	char *line, *token;
	printf("%s\n","Entering While Loop!" );
	int row = 0;
	while ((charRead = getline(&line, &len, filePtr))!=-1){
/*		printf("%s\n",line );*/
		token = strtok(line,", ");
		for (int i = 0; i < n-1; ++i)	{
			gridIn[row][i] = atoi(token);
			token = strtok(NULL,", ");
		}//end for
		++row;
	}//end while
	printGrid(gridIn,n);
	bool **temp;
	for (int i = 0; i < numGens-1; ++i)
	{
		//printf("%s\n","Entered Generation Calc Loop!" );
		nextGen(gridIn,gridOut,n,nTh);
		temp = gridIn;
		gridIn = gridOut;
		gridOut = temp;
	}//end for
	printf("%s\n","Calculating Last Gen!" );
	nextGen(gridIn,gridOut,n,nTh);

	printf("%s\n","Printing Grid to File" );
	Out2File(gridOut,n);
	return 0;
}//end main
//--End main function--//

//--Function nextGen--//
void nextGen(bool *inn[], bool *outt[], int len,int nth)
{
Structthread1.i = inn;
Structthread1.o = outt;
pthread_t thread_id[nth];

  switch (nth){
    case 2:
    pthread_create( &thread_id[0], NULL,thread2, (void *) &Structthread1);
    pthread_create( &thread_id[1], NULL, thread2, (void *) &Structthread1);
     pthread_join( thread_id[0], NULL);
     pthread_join( thread_id[1], NULL); 
    break;
    case 4:
    pthread_create( &thread_id[0], NULL,thread4, (void *) &Structthread1);
    pthread_create( &thread_id[1], NULL, thread4, (void *) &Structthread1);
    pthread_create( &thread_id[2], NULL,thread4, (void *) &Structthread1);
    pthread_create( &thread_id[3], NULL, thread4, (void *) &Structthread1);
     pthread_join( thread_id[0], NULL);
     pthread_join( thread_id[1], NULL); 
     pthread_join( thread_id[2], NULL);
     pthread_join( thread_id[3], NULL); 
    break;
    case 6:
    pthread_create( &thread_id[0], NULL,thread6, (void *) &Structthread1);
    pthread_create( &thread_id[1], NULL, thread6, (void *) &Structthread1);
    pthread_create( &thread_id[2], NULL,thread6, (void *) &Structthread1);
    pthread_create( &thread_id[3], NULL, thread6, (void *) &Structthread1);
     pthread_create( &thread_id[4], NULL,thread6, (void *) &Structthread1);
    pthread_create( &thread_id[5], NULL, thread6, (void *) &Structthread1);
     pthread_join( thread_id[0], NULL);
     pthread_join( thread_id[1], NULL); 
     pthread_join( thread_id[2], NULL);
     pthread_join( thread_id[3], NULL); 
      pthread_join( thread_id[4], NULL);
     pthread_join( thread_id[5], NULL); 
    break;
    case 8:
    pthread_create( &thread_id[0], NULL,thread8, (void *) &Structthread1);
    pthread_create( &thread_id[1], NULL, thread8, (void *) &Structthread1);
    pthread_create( &thread_id[2], NULL,thread8, (void *) &Structthread1);
    pthread_create( &thread_id[3], NULL, thread8, (void *) &Structthread1);
     pthread_create( &thread_id[4], NULL,thread8, (void *) &Structthread1);
    pthread_create( &thread_id[5], NULL, thread8, (void *) &Structthread1);
    pthread_create( &thread_id[6], NULL,thread8, (void *) &Structthread1);
    pthread_create( &thread_id[7], NULL, thread8, (void *) &Structthread1);
     pthread_join( thread_id[0], NULL);
     pthread_join( thread_id[1], NULL); 
     pthread_join( thread_id[2], NULL);
     pthread_join( thread_id[3], NULL); 
     pthread_join( thread_id[4], NULL);
     pthread_join( thread_id[5], NULL); 
     pthread_join( thread_id[6], NULL);
     pthread_join( thread_id[7], NULL);
    break;
    case 10:
    pthread_create( &thread_id[0], NULL,thread10, (void *) &Structthread1);
    pthread_create( &thread_id[1], NULL, thread10, (void *) &Structthread1);
    pthread_create( &thread_id[2], NULL,thread10, (void *) &Structthread1);
    pthread_create( &thread_id[3], NULL, thread10, (void *) &Structthread1);
     pthread_create( &thread_id[4], NULL,thread10, (void *) &Structthread1);
    pthread_create( &thread_id[5], NULL, thread10, (void *) &Structthread1);
    pthread_create( &thread_id[6], NULL,thread10, (void *) &Structthread1);
    pthread_create( &thread_id[7], NULL, thread10, (void *) &Structthread1);
    pthread_create( &thread_id[8], NULL,thread10, (void *) &Structthread1);
    pthread_create( &thread_id[9], NULL, thread10, (void *) &Structthread1);
     pthread_join( thread_id[0], NULL);
     pthread_join( thread_id[1], NULL); 
     pthread_join( thread_id[2], NULL);
     pthread_join( thread_id[3], NULL); 
     pthread_join( thread_id[4], NULL);
     pthread_join( thread_id[5], NULL); 
     pthread_join( thread_id[6], NULL);
     pthread_join( thread_id[7], NULL);
     pthread_join( thread_id[8], NULL);
     pthread_join( thread_id[9], NULL);
    break;
    default:
    printf("Error Cannot have %d threads",nth);
    break;
  }
  //--Not able to convert these lines to multithread--//
  /*	int aliveNebr=0;
	bool this;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			aliveNebr = 
			isLiving(in,i-1,j-1,n)+ //in[i-1][j-1]+
			isLiving(in,i-1, j ,n)+ //in[i-1][j]+
			isLiving(in,i-1,j+1,n)+ //in[i-1][j+1]+
			isLiving(in,i, j-1, n)+ //in[i][j-1]+
			isLiving(in,i, j+1, n)+ //in[i][j+1]+
			isLiving(in,i+1,j-1,n)+ //in[i+1][j-1]+
			isLiving(in,i+1, j, n)+ //in[i+1][j]+ 
			isLiving(in,i+1,j+1,n); //in[i+1][j+1];
			if(aliveNebr<2 || aliveNebr>3) out[i][j] = 0;
			else if(aliveNebr == 3) out[i][j] = 1;
			else out[i][j] = in[i][j];
		}//end for j
	}//end for i*/
  //--Not able to convert these lines to multithread--//
}//end next gen
//--End nextGen function--//

//--Function thread2--//
void* thread2(void*ptr)
{
  struct thread_args *args = (struct thread_args *)ptr;
   bool *in = args->i;
  bool *out= args->o;
  //--Stuck here mentioned in report--//
  pthread_exit(NULL);
}
//--End thread2 Function--//
void* thread4(void *ptr)
{
  //--Code--//
  pthread_exit(NULL);
}
void* thread6(void *ptr)
{
  //--Code--//
  pthread_exit(NULL);
}
void* thread8(void *ptr)
{
  //--Code--//
  pthread_exit(NULL);
}
void* thread10(void *ptr)
{
  //--Code--//
  pthread_exit(NULL);
}
//--Function isLiving--//
bool isLiving(bool *in[],int x, int y, int len){
/*	printf("( %d, %d) , ",x,y );*/
	if (x<0 || y<0 || x>=len || y>=len) return false;
	else return in[x][y];
	return false;
}
//--End Function isLiving--//

//--Function printGrid--//
void printGrid(bool *ptr[],int len){
	for (int i = 0; i < len; ++i)
	{
		for (int j = 0; j < len-1; ++j)
		{
			printf("%d, ", ptr[i][j]);
		}
		printf("%d\n", ptr[i][len]);
	}
}
//--End printGrid function--//

//--Function Out2File--//
void Out2File(bool *ptr[],int len)
{
  char *str[100];
  char *str1[100];
  FILE *fptr = fopen("Output.txt", "a");
    sprintf(str1, "Last Generation:\n");
    fputs(str1, fptr);
    for (int i=0;i<len;i++)
    {
      for(int j = 0; j < len;j++)
      {
        sprintf(str, "%d, ", ptr[i][j]);
        fputs(str, fptr);
      }
      sprintf(str,"%d\n", ptr[i][len]);
      fputs(str, fptr);
    }
  fclose (fptr);
}
//--End Out2File Function--//
