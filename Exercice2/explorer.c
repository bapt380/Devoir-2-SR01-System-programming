#include "explorer.h"


void explorer(int debut, int fin) {
    int etat, pid, pid2;
    pid = fork(); // creer pere / fils

    //char *argv[3];

    if (pid == 0) { // on est dans le fils

        for (int i = debut; i <= fin; i++) {

            if (premier(i) == 1) { // si l'indice est premier
                
                pid2 = fork(); // creer fils pere
                FILE * fa;
                if (pid2 == 0) { // on rentre dans le fils
                    
                    char chaine[100];
                    char chaine2[100];

                    sprintf(chaine, "%d  est un nombre premier écrit par le processus %d", i, getpid());
                    // sprintf stocke la chaîne formatée en mémoire dans un buffer pré-alloué nommée chaine.

                    // TODO Question à se poser : pourquoi avec cette méthode la syncronisation a bien eu lieu ??
                    // EXEMPLE : on voit que les deux pid se suivent
                    // 7  est un nombre premier écrit par le processus 9020
                    // 11  est un nombre premier écrit par le processus 9021

                    fa = freopen("nbr_premiers.txt","a+",stdout);
                    // duplication et remplacement en meme temps
                    // remplacement du stdout par le fichier 
                    // le stdout est fermé et remplacé par le fichier
  
                    if (fa==NULL) {
                        perror("freop erreur :");
                        exit(0);
                    }
                    
                    /*argv[0] = "echo";
                    argv[1] = chaine;
                    argv[2] = NULL;*/
                    char *argv[4] = {"echo",chaine,NULL};

                    my_system(argv);
                    fclose(fa); // fermer le fichier pas le stdout
                    fa = freopen("/dev/tty","a+",stdout); // on remet dans le stdout sa valeur de base 


                    sleep(2); // permet d'aller dans le père (l'instruction wait dans le père sera ainsi exécutée qui va entrainer un retour dans le fils)
                    exit(0); // terminaison normale du fils
                } 
                else { // on rentre dans le pere
                    wait(&etat); // on attent le fils
                    // wait enregistre les informations sur l'état/le statut du fils dans l'entier "etat".
                    // instruction 41
                }
            }
        }

        exit(0); // terminaison normale du fils

    } 
    else {
        wait(&etat); // on attent le fils
        // wait enregistre les informations sur l'état/le statut du fils dans l'entier "etat".
        // instruction 46
    } 
}