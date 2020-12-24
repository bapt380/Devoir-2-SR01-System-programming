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

#define MAX 20


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

    char *arg_power_manager[] = {"power_manager", "./mise_en_veille.txt", "4", NULL};
    char *arg_get_time[] = {"get_time", NULL};
    char *arg_network_manager[] = {"network_manager", NULL};


    /*  Création des processus fils */
    get_time_id = fork();
    assert(get_time_id != -1);

    if (getpid() == father_id) network_manager_id = fork();

    assert(network_manager_id != -1);

    if (getpid() == father_id) power_manager_id = fork();
    assert(power_manager_id != -1);


    /* Lancement des applications */

    if(get_time_id == 0) launch_application("./bin/get_time",arg_get_time);


    if(network_manager_id == 0) launch_application("./bin/network_manager",arg_network_manager);


    if(power_manager_id == 0) launch_application("./bin/power_manager",arg_power_manager);



    /* Attente des processus */

    int number_child_processes = 3;
    int status;
    pid_t child_id;
    char process_name[MAX];
    while(number_child_processes>0){

        child_id = waitpid(-1,&status,0);

        if (child_id == get_time_id){
            snprintf(process_name,MAX,"get_time");
        } else if (child_id == network_manager_id){
            snprintf(process_name,MAX,"network_manager");
        } else {
            snprintf(process_name,MAX,"power_manager");
        }

        if(WIFEXITED(status)){
            printf("[application manager] Terminaison normale de %s avec le code %d\n",process_name,WEXITSTATUS(status));
            number_child_processes--;
        } 
        if(WIFSIGNALED(status)){
            printf("[application manager] Le processus %s a été terminé par le signal %d\n",process_name,WTERMSIG(status));
            number_child_processes--;
        }

    }


    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

