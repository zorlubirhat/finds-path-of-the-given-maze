#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int line_count(const char *filename)
{
	int ch = 0;
  int count = 1;    
  FILE *fileHandle;

  if ((fileHandle = fopen(filename, "r")) == NULL) {
	  return -1;
  }

  do {
    ch = fgetc(fileHandle);
    if ( ch == '\n')
      count++;
  } while (ch != EOF);

  fclose(fileHandle);
  
  return count;
}

char** createArray(int length){
	char** maze = NULL; //pointer to pointer
	
	int nRow = length; //variable store number of Row
	
	int nColumn = length; //variable store number of Row
	
	
	int iRow = 0; //Variable for looping Row
	
	int iCol = 0; //Variable for looping column
	
	
	//Allocate memory for row
	maze = (char **)malloc(nRow * sizeof(char*));
	
	//Allocate memory for column
	for (iRow =0 ; iRow < nRow ; iRow++)
	{
		maze[iRow] = (char *)malloc(nColumn * sizeof(char));
		
	}
	
	
	//Copy the data in 2d Array
	
	for(iRow=0; iRow < nRow; iRow++){
		for(iCol = 0; iCol <= nColumn; iCol++){				
			maze[iRow][iCol] = ' ';
		}
	}
	
	/*
	free(maze);*/
	
	return maze;
}

char** storeData(int length, FILE* file){
	
	char** maze = NULL; //pointer to pointer
	
	int nRow = length; //variable store number of Row
	
	int nColumn = length; //variable store number of Row
	
	
	int iRow = 0; //Variable for looping Row
	
	int iCol = 0; //Variable for looping column
	
	
	//Allocate memory for row
	maze = (char **)malloc(nRow * sizeof(char*));
	
	//Allocate memory for column
	for (iRow =0 ; iRow < nRow ; iRow++)
	{
		maze[iRow] = (char *)malloc(nColumn * sizeof(char));
		/*
		//Check memory validity
		if(maze[iRow] == NULL)
		{
			return 1;
		}*/
	}
	
	//Copy the data in 2d Array
	while(!feof(file)){
		for(iRow=0; iRow < nRow; iRow++){
			for(iCol = 0; iCol <= nColumn; iCol++){
				char chr = fgetc(file);				
				maze[iRow][iCol] = chr;
			}
		}
	break;		
	}
	
	/*	
	free(maze);*/
	
	return maze;
}

void findPath(char** maze, char** second,  int row, int col, int length, FILE* outfile){
	
	if(row+1 < length && maze[row+1][col] != '1' && maze[row+1][col] != 'E' && second[row+1][col] == ' '){
		
		row = row + 1;
		second[row][col] = '*';
		printf("%s ", "S");
		fprintf(outfile, "S ");
		if(maze[row][col] != 'S' && maze[row][col] != '0'){
			printf("%c ", maze[row][col]);
			fprintf(outfile, "%c ", maze[row][col]);
		}
		findPath(maze, second, row, col, length, outfile);	
		
	}
	if(col-1 >= 0 && maze[row][col-1] != '1'&& maze[row][col-1] != 'E' && second[row][col-1] == ' '){
		
		col = col - 1;		
		second[row][col] = '*';
		printf("%s", "W ");
		fprintf(outfile, "W ");
		if(maze[row][col] != 'S' && maze[row][col] != '0'){
			printf("%c ", maze[row][col]);
			fprintf(outfile, "%c ", maze[row][col]);
		}
		findPath(maze, second, row, col, length, outfile);	

	}
  if(col+1 < length && maze[row][col+1] != '1'&& maze[row][col+1] != 'E' && second[row][col+1] == ' '){
		
		col = col + 1;		
		second[row][col] = '*';
		printf("%s", "E ");
		fprintf(outfile, "E ");
		if(maze[row][col] != 'S' && maze[row][col] != '0'){
			printf("%c ", maze[row][col]);
			fprintf(outfile, "%c ", maze[row][col]);
		}
		findPath(maze, second, row, col, length, outfile);	

	}
	if(row-1 >= 0 && maze[row-1][col] != '1'&& maze[row-1][col] != 'E' && second[row-1][col] == ' '){
		
		row = row - 1;
		second[row][col] = '*';
		printf("%s", "N ");
		fprintf(outfile, "N ");
		if(maze[row][col] != 'S' && maze[row][col] != '0'){
			printf("%c ", maze[row][col]);
			fprintf(outfile, "%c ", maze[row][col]);
		}
		findPath(maze, second, row, col, length, outfile);	

	}	

}

int main(int argc, char* argv[]) {
	
	int length = line_count(argv[1]);
	
	char const* const fileName = argv[1]; 
  FILE* file = fopen(fileName, "r");
	FILE* outfile = fopen("output.txt", "w");
	
	char** maze = NULL;
	char** second = NULL;
	maze = storeData(length, file);
	second = createArray(length);
	
	int i;
	int j;
	int sRow;
	int sCol;
	int eRow;
	int eCol;
	
	for(i=0;i<length;i++){
		for(j=0;j<length;j++){
			if(maze[i][j] == 'S'){
				sRow = i;
				sCol = j;
				second[sRow][sCol] = 'S';
			}
			if(maze[i][j] == 'E'){
				eRow = i;
				eCol = j;
			}
		}
	}
	
	printf("%s ", "Start");
	fprintf(outfile, "Start ");
	findPath(maze, second, sRow, sCol, length,outfile);
	printf("%s ", "Exit");
	fprintf(outfile, "Exit ");
	
	return 0;
}



