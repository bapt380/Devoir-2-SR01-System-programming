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
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

#include "get_time.c"


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  lauch_get_time
 *  Description:  
 * =====================================================================================
 */
    void
launch_get_time (char **arg_get_time)
{
    if (execv("./get_time", arg_get_time) == -1){
        // filename + 
        perror("execv : ");
        exit(EXIT_FAILURE);
    }
}		/* -----  end of function lauch_get_time  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  application manager
 *  Description:  
 * =====================================================================================
 */
    int
application_manager ( int argc, char *argv[] )

{
   
   //TODO ajouter les signaux/les états de chaque fils ?
   // TODO int signal1; int signal2.... ?

   
   pid_t get_time_id = fork();
   char *arg_get_time[] = {"get_time", NULL};
   /*if (get_time_id != 0){
       pid_t network_manager_id = fork();
   }*/
  switch(get_time_id){
      case -1:
          perror("fork : ");
          exit(EXIT_FAILURE);
          break;

      case 0:
          launch_get_time(arg_get_time);
          // TODO ajouter un exit ici ? exit(7) par exemple pour l'arret du processus fils (peut etre useless ^^)
          break;

      default:
          wait(NULL); // TODO wait(&signal1) ? je ne sais pas si c'est utile ou non
          // TODO ne pas renvoyer le nom de l'application qui se ferme ?
          break;
  }


    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

