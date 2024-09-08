#include<stdio.h>
#include<string.h>
#include<stdbool.h>


// This Function Ensures the provided file has a `.c` extension.
// Returns `1` if the file is valid, otherwise `0`.
int checkForC(char *fileName)
{
	int len = strlen(fileName);

	if(len > 2 && strcmp(&fileName[len-2],".c")==0)
		return 1;
	else
		return 0;
}

// This Function is the main Utility for the Purpose to Extracts both block (`/* ... */`) and single-line (`// ...`) comments.
// Skips over non-comment code and handles situations where comments are inside string literals.
int extractComment(FILE *file, FILE *extract)
{
	char ch;
	bool start = false, writeFlag = false, end = false, print = false, oneLineFlag = false;
	while((ch=fgetc(file))!=EOF)
	{
		if(start)
                {
                        if(ch == '*' || ch == '/'){
				if(ch == '/'){
                                        oneLineFlag = true;
                                }
				ch=fgetc(file);
                                writeFlag = true;
			}
                        start = false;
                }
                if(end)
                {
                        if(ch == '/'){
                                writeFlag = false;
				fprintf(extract,"\n\n");
			}else
				fputc('*',extract);
                        end = false;
                }

		if(ch == '/' && writeFlag == false && print == false) 
			start = true;
		if(ch == '*' && writeFlag == true && print == false)
			end = true;
		if(ch == '"' && writeFlag == false){
			if(print == false)
				print = true;
			else
				print = false;
		}
		if(writeFlag == true && end == false){
			fputc(ch,extract);
			if(oneLineFlag == true && ch == '\n')
			{
				fputc('\n',extract);
				writeFlag = false;
				oneLineFlag = false;
			}
		}
	}
}


// It is the main function which Validates input, opens the specified file for reading, and then calls the `extractComment` function to process and extract comments.
int main(int argc, char *argv[]){
	if(argc!=2){
		printf("Error: Invalid Number of Arguments\n");
		return 0;
	}

	if(!checkForC(argv[1]))
	{
		printf("Error: C File is expected as an Input\n");
		return 0;
	}
	
	FILE * file = fopen(argv[1],"r");
	if(!file){
		perror("Error: ");
		return 0;
	}

	FILE * extract = fopen("output.txt","w");

	extractComment(file,extract);

	fclose(extract);
	fclose(file);
}
