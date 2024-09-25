#include <iostream>
using namespace std;

int main() {
    // This is a single-line comment explaining the main function

    int num = 10;  // Inline comment explaining the variable

    /*
     * This is a multi-line comment
     * explaining the following if block
     */
    if (num > 5) {
        cout << "Number is greater than 5" << endl;
    }

    return 0;
}

/*
 This is a multi-line comment explaining the add function.
 This function adds two integers and returns the result.
*/
int add(int a, int b) {
    return a + b;
}

