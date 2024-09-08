# Comment Extractor

## Overview

The **Comment Extractor** is a utility designed to automatically extract comments from C, C++, Python and Java source code files. It handles both multi-line (`/* ... */`) and single-line (`// ...`) comments in case of C, C++ and Java and multi-line (`""" ... """`) and single-line (`# ...`) comments in case of Python. The extracted comments are written into an output file, making it easier to understand the code without diving into the entire codebase. 

This tool is particularly useful for enhancing code maintainability, facilitating knowledge sharing, and aiding in debugging by providing a clear view of the developer's notes and explanations within the code.

## Features

- **Multi-line Comment Extraction:** Extracts comments enclosed in `/* */` in case of C, C++ and Java and `""" """` in case of Python.
- **Single-line Comment Extraction:** Extracts comments starting with `//` in case of C, C++ and Java and `#` in case of Python.
- **Efficient Parsing:** Skips non-commented sections of the code, ensuring only useful documentation is extracted.
- **Handles String Literals:** Skips over comments within string literals to avoid misinterpretation.
- **Comment Delimiter Handling:** The program intelligently handles the start and end of comments, excluding the `/*` and `*/` (in case of C, C++ and Java)  and `"""` and `"""` (in case of Python) delimiters from the extracted text.
- **Output to File:** The extracted comments are saved in a separate file (`output.txt`) for easy review.

## How It Works

The program reads a `.c`, `.cpp`, `.py` or `.java` file passed as a command-line argument, identifies the comments within the code, and extracts them to a text file. Both single-line and multi-line comments are captured, and the output is neatly formatted.

### Example

Given the following input in `example.c`:

```c
#include<stdio.h>

// This is a single-line comment

/*
 This is a multi-line comment.
 It explains the following function.
 */

void helloWorld() {
    printf("Hello, World!"); // Print message
}
```

The output file (`output.txt`) will contain:

```
This is a single-line comment

This is a multi-line comment.
It explains the following function.

Print message
```

## Usage

1. **Compile the program** using a C compiler:

   ```bash
   gcc commentExtractor.c -o commentExtractor
   ```

2. **Run the program** with a C file as an argument:

   ```bash
   ./commentExtractor example.c
   ```

   The extracted comments will be written to `output.txt` in the current directory.

## Error Handling

- **Invalid file input:** If the input file is not a C/C++/Java/Python file or does not exist, an error message is displayed, and the program terminates.
- **File read/write errors:** If there are issues with opening the file, the program will display an appropriate error message.

