#include <stdio.h>

// funzione per contare le cifre dell'intero.
int countDigits(int num) {
    int count = 0;
    if (num == 0) {
        return 1; // Special case for num = 0
    }
    if (num < 0) {
        count++; // Account for the negative sign
        num = -num; // Make num positive
    }
    while (num > 0) {
        count++;
        num /= 10; // Divide by 10 to remove the rightmost digit
    }
    return count;
}



int main() {
    int num = 123456789; // Your integer value

    char str[countDigits(num)]; // Assuming a buffer large enough to hold the string. +1 for the null terminator!
    
    printf("num size = %d, str size = %ld\n", countDigits(num), sizeof(str));

    sprintf(str, "%d", num); // Convert int to string

    printf("Integer as string: %s\n", str);

    return 0;
}

