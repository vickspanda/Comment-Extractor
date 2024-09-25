#include<stdio.h>
#include<string.h>
#include<stdbool.h>


/* This Function Ensures the provided file has a `.c`, '.cpp', '.py'  or '.java' extension.
 * Returns `1` if the file is valid, otherwise `0`. 
 */
int checkForExtension(char *fileName)
{
	int len = strlen(fileName);

	if(len > 2 && strcmp(&fileName[len-2],".c")==0)
		return 1;
	else if (len > 5 && strcmp(&fileName[len-5],".java")==0)
		return 1;
	else if (len> 4 && strcmp(&fileName[len-4],".cpp")==0)
		return 1;
	else if (len> 3 && strcmp(&fileName[len-3],".py")==0)
                return 2;
	else
		return 0;
}

// This Function is the main Utility for the Purpose to Extracts both block (`""" ... """`) and single-line (`# ...`) comments for Python.
// It Skips over non-comment code and handles situations where comments are inside string literals.
int extractCommentPy(FILE *file, FILE *extract)
{
	char ch;
	bool cond1 = false, writeFlag = false, cond2 = false, print = false, oneLineFlag = false;
	while((ch=fgetc(file))!=EOF)
	{
		if(print == true && ch == '"')
			print = false;

		if(cond2)
		{
			if(ch == '"')
			{
				ch=fgetc(file);
				if(!writeFlag)
					writeFlag = true;
				else
					writeFlag = false;
			}
			cond2 = false;
			cond1 = false;

		}
		if(cond1){
			if(ch == '"'){
				if(!cond2)
					cond2 = true;
				else
					cond2 = false;
			}else{
				cond1 = false;
				print = true;
			}
		}

		if(ch == '#' && writeFlag == false && print == false){
			ch=fgetc(file);
			writeFlag = true;
			oneLineFlag = true;
		}
		
		if(ch == '"' && cond2 == false && print == false){
			if(!cond1)
				cond1 = true;
			else
				cond1 = false;
		}


		if(writeFlag == true && cond1 == false && cond2 == false){
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

// This Function is the main Utility for the Purpose to Extracts both block (`/* ... */`) and single-line (`// ...`) comments for C, CPP and Java.
// It Skips over non-comment code and handles situations where comments are inside string literals.
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

	if(checkForExtension(argv[1])==0)
	{
		printf("Error: C/C++/Java/Python File is expected as an Input\n");
		return 0;
	}
	
	FILE * file = fopen(argv[1],"r");
	if(!file){
		perror("Error: ");
		return 0;
	}

	FILE * extract = fopen("output.txt","w");
	if(checkForExtension(argv[1])==2)
		extractCommentPy(file,extract);
	else
		extractComment(file,extract);

	fclose(extract);
	fclose(file);
}
