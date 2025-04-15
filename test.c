#include "parsing.h"
int main()
{
    char *test[] = {"a=b" , NULL};
    execve(test[0] , test , NULL);
    printf("%s " , test[0]);
    perror("execve");
}