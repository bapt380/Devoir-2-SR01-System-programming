
#include "my_system.h"

my_system(char  *argv)
{
    execv("/bin/echo",(char **const)argv);
}

