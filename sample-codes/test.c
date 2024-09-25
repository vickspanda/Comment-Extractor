#include <stdio.h>
#include <stdlib.h>

int main() {
    /* File pointers for source and destination files */
    FILE *sourceFile, *destinationFile;
    
    /* Buffer to hold each line read from the source file */
    char buffer[256];
    
    /* Desired line number to copy */
    int lineNumber = 3; /* Change this value to copy a different line */
    
    /* Current line tracker */
    int currentLine = 1;

    /* Open the source file for reading */
    sourceFile = fopen("source.txt", "r");
    if (sourceFile == NULL) {
        /* Error handling if source file cannot be opened */
        printf("Error: Could not open source file.\n");
        return 1;
    }

    /* Open the destination file for writing */
    destinationFile = fopen("destination.txt", "w");
    if (destinationFile == NULL) {
        /* Error handling if destination file cannot be opened */
        printf("Error: Could not open destination file.\n");
        fclose(sourceFile); /* Ensure to close the source file before exiting */
        return 1;
    }

    /* Read the file line by line until the desired line is found */
    while (fgets(buffer, sizeof(buffer), sourceFile) != NULL) {
        /* If current line matches the desired line number, copy it */
        if (currentLine == lineNumber) {
            /* Write the line to the destination file */
            fprintf(destinationFile, "%s", buffer);
            break; /* Stop after writing the desired line */
        }
        /* Increment the line counter */
        currentLine++;
    }

    /* Close the files */
    fclose(sourceFile);
    fclose(destinationFile);

    /* Confirmation message */
    printf("/*Line %d has been copied to destination.txt\n*/", lineNumber);

    return 0;
}

/* Comment starts */
/* 
   This section demonstrates different types of comments 
   and test cases for your filtering code.
*/

/* Single-line comment test case */
/* printf("This is a single-line comment.\n"); */

/* Multi-line comment test case */
/*
   This is a multi-line comment
   that spans multiple lines.
*/

/* Nested comment test case */
 /*
  This is an outer comment
  /* This is a nested comment */
  End of outer comment.
 */

/* Edge case: Nested comment with extra spaces */
 /* Outer comment with spaces
  /* Nested comment with spaces */
  End of outer comment with spaces.
 */

/* Edge case: Comment inside code-like structure */
 /* printf("/* This is a comment inside code-like structure\n"); */

/* Testing with different characters */
 /* !@#$%^&*()_+-=~`[]{}|\:;"'<>,.?/ */

/* Comment ends */

