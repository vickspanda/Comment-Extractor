public class CommentExample {
    
    // This is a single-line comment explaining the main method
    public static void main(String[] args) {
        
        int num = 10;  // Inline comment explaining the variable

        /*
         * This is a multi-line comment
         * explaining the following block of code
         */
        if (num > 5) {
            System.out.println("Number is greater than 5");
        }
    }
    
    /**
     * This is a Javadoc comment
     * Used to describe the functionality of this method
     * @param a First number
     * @param b Second number
     * @return The sum of a and b
     */
    public int add(int a, int b) {
        return a + b;
    }
}

