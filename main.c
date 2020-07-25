#include <stdio.h>
#include <stdlib.h>
// Function to print next generation 
	static void nextGeneration(int grid[10][10],int M, int N) 
	{ 
		int future[10][10]; 

		// Loop through every cell 
		for (int l = 1; l < M - 1; l++) 
		{ 
			for (int m = 1; m < N - 1; m++) 
			{ 
				
				// finding no Of Neighbours 
				// that are alive 
				int aliveNeighbours = 0; 
				for (int i = -1; i <= 1; i++) 
					for (int j = -1; j <= 1; j++) 
						aliveNeighbours += 
								grid[l + i][m + j]; 

				// The cell needs to be subtracted 
				// from its neighbours as it was 
				// counted before 
				aliveNeighbours -= grid[l][m]; 

				// Implementing the Rules of Life 

				// Cell is lonely and dies 
				if ((grid[l][m] == 1) && 
							(aliveNeighbours < 2)) 
					future[l][m] = 0; 

				// Cell dies due to over population 
				else if ((grid[l][m] == 1) && 
							(aliveNeighbours > 3)) 
					future[l][m] = 0; 

				// A new cell is born 
				else if ((grid[l][m] == 0) && 
							(aliveNeighbours == 3)) 
					future[l][m] = 1; 

				// Remains the same 
				else
					future[l][m] = grid[l][m]; 
			} 
		} 
  FILE *fp = fopen("Output.txt", "w");
  for(int i=0; i < M; i++){
    for(int j=0; j < N; j++){
        fprintf(fp, " %d", future[i][j]);
    }
    fprintf(fp,"\n");
}
  fclose(fp);

	printf("Next: \n");
  for(int i=0; i < M; i++){
    for(int j=0; j < N; j++)
        printf("%d ", future[i][j]);
        printf("\n");
    }
  printf("\n");
}  
int main() 
{ 
	int M = 10;
  int N = 10;
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
  nextGeneration(grid, M, N);
	return 0; 
} 