
#include "my_system.h"

int my_system(char  *argv)
{
    execv("/bin/echo",(char **const)argv);
}

