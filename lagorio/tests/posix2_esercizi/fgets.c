#include <stdio.h>

int main()
{
    char buffer[256];

    printf("Enter a string: ");
    if (fgets(buffer, 256, stdin) != NULL)
    {
        printf("You entered: %s", buffer);
    }

    // Clear the input buffer if needed
    if (!strchr(buffer, '\n'))
    {
        // Input was too long, discard the remaining characters
        scanf("%*[^\n]"); // ... ok
        scanf("%*c");     // discard newline character
    }

    return 0;
}