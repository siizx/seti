#include <stdio.h>
#include <errno.h>
#include <string.h>

int main()
{
    FILE *file;

    file = fopen("non_existent_file.txt", "r");
    if (file == NULL)
    {
        perror("Error opening file");
        printf("errno: %d\n", errno);
        printf("Error message: %s\n", strerror(errno));
        return 1;
    }

    // Rest of the program...

    return 0;
}