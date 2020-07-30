/*
 * Programmer: Syed Farooq Zaidi
 * Name: Conways Game
 * Desc: Simulation of Conways game in a single threaded program
 * Date: 27th July 2020
 */

//--Includding Files--//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//--Global Variables--//
FILE *filePtr;//pointer for reading and writing to file.
bool **gridIn;//pionter to a pointer variable to be used as 2D array 
bool **gridOut;//pionter to a pointer variable to be used as 2D array
int n;//size of the grid NxN
int numGens;//Number of generations to run
char fileName[20];//Name of the input output file


//--Function Declarations--//
void printGrid(bool *ptr[],int len);
void nextGen(bool *in[], bool *out[], int len);
bool isLiving(bool *in[],int x, int y, int len);

//--Main Function--//
int main(int argc, char const *argv[]) {
	//--Get inputs from Command Line--//
	printf("%ld, %ld, %ld, %ld\n",sizeof(int),sizeof(bool),sizeof(double),sizeof(char) );
	if (argc < 4) {
		printf("%s\n","ERROR: Wrong usage of the program! Sample Correct usage is:-\n:\\conway.run text.txt 1 10\n");
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
		printf("%s\n","Entered Generation Calc Loop!" );
		nextGen(gridIn,gridOut,n);
		temp = gridIn;
		gridIn = gridOut;
		gridOut = temp;
	}//end for
	printf("%s\n","Calculating Last Gen!" );
	nextGen(gridIn,gridOut,n);
	printf("%s\n","Printing Grid to File" );
	printGrid(gridOut,n);
	return 0;
}//end main
//--End main function--//

//--Function nextGen--//
void nextGen(bool *in[], bool *out[], int len){
	int aliveNebr=0;
	bool this;
	for (int i = 0; i < len; ++i)
	{
		for (int j = 0; j < len; ++j)
		{
			aliveNebr = 
			isLiving(in,i-1,j-1,len)+ //in[i-1][j-1]+
			isLiving(in,i-1, j ,len)+ //in[i-1][j]+
			isLiving(in,i-1,j+1,len)+ //in[i-1][j+1]+
			isLiving(in,i, j-1, len)+ //in[i][j-1]+
			isLiving(in,i, j+1, len)+ //in[i][j+1]+
			isLiving(in,i+1,j-1,len)+ //in[i+1][j-1]+
			isLiving(in,i+1, j, len)+ //in[i+1][j]+ 
			isLiving(in,i+1,j+1,len); //in[i+1][j+1];
			if(aliveNebr<2 || aliveNebr>3) out[i][j] = 0;
			else if(aliveNebr == 3) out[i][j] = 1;
			else out[i][j] = in[i][j];
		}//end for j
	}//end for i
}//end next gen
//--End nextGen function--//


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