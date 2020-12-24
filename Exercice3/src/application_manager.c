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
#include <assert.h>


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
    waitpid(-1,&status,0);
    if(WIFEXITED(status)){
        printf("[application manager] Terminaison normale de %s avec le code %d\n",process_name,WEXITSTATUS(status));
    } 
    if(WIFSIGNALED(status)){
        printf("[application manager] Le processus %s a été terminé par le signal %d\n",process_name,WTERMSIG(status));
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
    printf("[application manager] lauching %s with pid %d\n",arg[0],getpid());
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
        case 0:
            launch_application("./bin/get_time",arg_get_time);
            break;

        default:
            printf("[application_manager] father process: waiting for get_time...\n");
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
        case 0:
            launch_application("./bin/network_manager",arg_network_manager);
            break;

        default:
            printf("[application manager] father process: waiting for network_manager...\n");
            sleep(10);
            kill(network_manager_id,SIGKILL);
            wait_process("network_manager");
            break;
    }

}		/* -----  end of function case_network_id  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  case_power_manager
 *  Description:  
 * =====================================================================================
 */
    void
case_power_manager ( pid_t power_manager_id )
{
    char *arg_power_manager[] = {"power_manager", "./mise_en_veille.txt", "4", NULL};
    if (power_manager_id != 0){
        printf("[application manager] father process: waiting for power_manager...\n");
        wait_process("power_manager");
    } else {
        launch_application("./bin/power_manager",arg_power_manager);
    }

}		/* -----  end of function case_power_manager  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  application manager
 *  Description:  
 * =====================================================================================
 */
    int
main ( int argc, char *argv[] )

{
    /* Déclaration des pid */
    pid_t get_time_id;
    pid_t network_manager_id;
    pid_t power_manager_id;
    pid_t father_id = getpid();

    /*  Création des processus fils */
    get_time_id = fork();
    assert(get_time_id != -1);

    if (getpid() == father_id) network_manager_id = fork();
    
    assert(network_manager_id != -1);

    if (getpid() == father_id) power_manager_id = fork();
    assert(power_manager_id != -1);


    /*On s'assure que le processus qui rentre dans case_X
     * est soit le père, soit le processus X*/
    if(get_time_id == 0 
            || getpid() == father_id ) case_get_time(get_time_id);

    if(network_manager_id == 0 
            || getpid() == father_id ) case_network_manager(network_manager_id);

    if(power_manager_id == 0 
            || getpid() == father_id ) case_power_manager(power_manager_id);


    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

