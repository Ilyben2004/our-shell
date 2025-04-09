#include "parsing.h"
int main()
{
    char *test[] = {"/usr/bin/cat", "Makefile" , NULL};
    execve(test[0] , test , NULL);
    printf("%s " , test[0]);
    perror("execve");
}