#include <stdio.h>

int M = 10, N = 10, i, j, l, m, master, gencounter = 1;
// Function to print next generation 
	void nextGeneration(int gridd[10][10], int future[10][10], int MM, int NN)
{
	// Loop through every cell
	for (int l = 1; l < MM - 1; l++)
	{
		for (int m = 1; m < NN - 1; m++)
		{
			// finding no Of Neighbours
			// that are alive
			int aliveNeighbours = 0;
			for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					aliveNeighbours += gridd[l + i][m + j];
				}
			}

			// The cell needs to be subtracted
			// from its neighbours as it was
			// counted before
			aliveNeighbours -= gridd[l][m];

			// Implementing the Rules of Life

			// Cell is lonely and dies
			if ((gridd[l][m] == 1) && (aliveNeighbours < 2))
			{
				future[l][m] = 0;
			}

			// Cell dies due to over population
			else if ((gridd[l][m] == 1) && (aliveNeighbours > 3))
			{
				future[l][m] = 0;
			}

			// A new cell is born
			else if ((gridd[l][m] == 0) && (aliveNeighbours == 3))
			{
				future[l][m] = 1;
			}

			// Remains the same
			else
			{
				future[l][m] = gridd[l][m];
			}
		}
	}

	
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
}
 
  

int main() 
{ 
	int M = 10;
  int N = 10;
  int future[10][10] = {
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
  FILE *fp = fopen("Input.txt", "r");
    int get;
    int grid[10][10];

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
  nextGeneration(grid,future, M, N);

  for (int master = 0; master < 49; master++)
	{
		for (i = 0; i < 10; i++)
		{
			for (j = 0; j < 10; j++)
			{
				grid[i][j] = future[i][j];
			}
		}
		for (i = 0; i < 10; i++)
		{
			for (j = 0; j < 10; j++)
			{
				future[i][j] = 0;
			}
		}
    nextGeneration(grid, future, M, N);
	}
	return 0; 
} 