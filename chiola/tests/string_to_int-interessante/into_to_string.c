#include <stdio.h>
#include <stdlib.h>

const bool debug = false;


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

    char *strinput = NULL;
    int num; // Your integer value

    printf("Inserisci un intero: ");
    scanf("%m[^\n]", &strinput);

    num = atoi(strinput); // converto ascii to integer.

    char str[countDigits(num)]; // 
    
    if(debug)
        printf("num size = %d, str size = %ld\n", countDigits(num), sizeof(str)); //stampo il numero di cifre + numero di caratteri per controllare la correttezza.

    sprintf(str, "%d", num); // Convert int to string

    printf("Integer as string: %s\n", str);

    return 0;
}

