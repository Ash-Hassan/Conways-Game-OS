//SingleThread
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

int M = 10, N = 10, i, j, l, m, master, gencounter = 1;
double total=0,avg=0;
int future[10][10]={
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
    int grid[10][10],last[10][10]; 

void* threadFunction(void* input) 
{ 
  
  int ngen=(int)input;
  for (int master = 0; master < ngen; master++)
	{
  clock_t t;
  t = clock();
	// Loop through every cell
	for (int l = 1; l < M - 1; l++)
	{
		for (int m = 1; m < N - 1; m++)
		{
			// finding no Of Neighbours
			// that are alive
			int aliveNeighbours = 0;
			for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					aliveNeighbours += grid[l + i][m + j];
				}
			}

			// The cell needs to be subtracted
			// from its neighbours as it was
			// counted before
			aliveNeighbours -= grid[l][m];

			// Implementing the Rules of Life

			// Cell is lonely and dies
			if ((grid[l][m] == 1) && (aliveNeighbours < 2))
			{
				future[l][m] = 0;
			}

			// Cell dies due to over population
			else if ((grid[l][m] == 1) && (aliveNeighbours > 3))
			{
				future[l][m] = 0;
			}

			// A new cell is born
			else if ((grid[l][m] == 0) && (aliveNeighbours == 3))
			{
				future[l][m] = 1;
			}

			// Remains the same
			else
			{
				future[l][m] = grid[l][m];
			}
		}
	}
  t = clock() - t;
	double time_taken = ((double)t)/CLOCKS_PER_SEC; 
  total=total+time_taken;
  avg=total/50;

  int i,n;
  char str[100];
  char str1[100];
  int arr[2][2]={{1,2},{1,3}};
		
    FILE *fptr = fopen("Output.txt", "a");
    sprintf(str1, "Generation %d :\n", gencounter);
    fputs(str1, fptr);
	  gencounter++; 
    for (int i=0;i<M;i++)
    {
      for(int j = 0; j < N;j++)
      {
        sprintf(str, "%d ", future[i][j]);
        fputs(str, fptr);
      }
      fputs("\n", fptr);
    }
  fclose (fptr);
  
		for (i = 0; i < 10; i++)
		{
			for (j = 0; j < 10; j++)
			{
				grid[i][j] = future[i][j];
        last[i][j]=future[i][j];
        future[i][j] = 0;
			}
		}
 
  }
}

int main(void) {
  int gen;
  printf("Enter no of Generations?");
  scanf("%d",&gen);

 FILE *fp = fopen("Input.txt", "r");
    int get;

//Filling the array:
for(int i=0; i < M; i++){
    for(int j=0; j < N; j++){
        fscanf(fp, " %d", &get);
        grid[i][j] = get;
    }
}
//Printing the array
printf("Orignal: \n");
for(int i=0; i < M; i++){
    for(int j=0; j < N; j++)
        printf("%d ", grid[i][j]);
        printf("\n");
    }

  printf("\n");
   fclose(fp);

//Single Thread
  pthread_t tid1;
	pthread_create(&tid1,NULL,&threadFunction,(void*)gen);
	pthread_join(tid1,NULL);
  

  //Printing the array
printf("Last Generation: \n");
for(int i=0; i < M; i++){
    for(int j=0; j < N; j++)
        printf("%d ", last[i][j]);
        printf("\n");
    }
    printf("Average time: %f seconds\n",avg);
    printf("Total timetaken: %f seconds",total);
    //Append time
    char str[100],str1[100];
    FILE *fptr = fopen("Output.txt", "a");
  sprintf(str,"Average time: %f seconds\n",avg); 
  fputs(str,fptr);
  sprintf(str1,"Total timetaken: %f seconds",total);
  fputs(str1,fptr);
  fclose (fptr);

  return 0;
}
