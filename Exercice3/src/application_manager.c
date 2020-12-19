/*
 * =====================================================================================
 *
 *       Filename:  ApplicationManager.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  17/12/2020 18:10:54
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jonathan Legrand 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>



/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  wait_process
 *  Description:  
 * =====================================================================================
 */
    void
wait_process ( char* process_name )
{
    int status;
    wait(&status);
    if(WIFEXITED(status)){
        printf("Terminaison normale de %s avec le code %d\n",process_name,WEXITSTATUS(status));
    }


}		/* -----  end of function process_result  ----- */
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  launch_application
 *  Description:  
 * =====================================================================================
 */
    void
launch_application ( char *path, char **arg )
{
    if(execv(path,arg)== -1){
        perror("execv");
            exit(EXIT_FAILURE);
    }
}		/* -----  end of function launch_network_manager  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  case_get_time
 *  Description:  
 * =====================================================================================
 */
    void
case_get_time (pid_t get_time_id)
{
    char *arg_get_time[] = {"get_time", NULL};
    switch(get_time_id){
        case -1:
            perror("fork");
            exit(EXIT_FAILURE);
            break;

        case 0:
            launch_application("./bin/get_time",arg_get_time);

            break;

        default:
            wait_process("get_time");
            break;
    }

}		/* -----  end of function case_get_time  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  case_network_manager
 *  Description:  
 * =====================================================================================
 */
    void
case_network_manager (pid_t network_manager_id)
{
    char *arg_network_manager[] = {"network_manager", NULL};
    switch(network_manager_id){
        case -1:
            perror("fork");
            exit(EXIT_FAILURE);
            break;

        case 0:
            launch_application("./bin/network_manager",arg_network_manager);

            break;

        default:
            wait_process("network_manager");
            break;
    }

}		/* -----  end of function case_network_id  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  application manager
 *  Description:  
 * =====================================================================================
 */
    int
main ( int argc, char *argv[] )

{
   

    pid_t get_time_id = fork();
    if (get_time_id != 0){
      pid_t network_manager_id = fork();
      case_network_manager(network_manager_id);
      }
    case_get_time(get_time_id);
    

    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

