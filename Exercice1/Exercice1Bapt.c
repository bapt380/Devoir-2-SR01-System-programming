#include <sys/types.h> /* Types pid_t... */ 
#include <unistd.h> /* fork()... */ 
#include <stdio.h> /* printf... */
#include <stdlib.h> /* EXIT_FAILURE... */
#include <sys/wait.h>

void pfeuille(int cle) {
 
    if (fork()==0) {
        printf("child %d -> pid : [%d] and ppid : [%d]\n", cle, getpid(), getppid());
        } 
    else {
        /*if (i==8) {
            printf("parent   pid : [%d] \n", getpid());
        }*/
            wait(0);    
        }
}

void p6() {
 
    
    for (int i=11; i<13; i++) {
        if (fork()==0) {
            printf("child %d -> pid : [%d] and ppid : [%d]\n",
                   i+1, getpid(), getppid());
            switch (i+1)
            {
            case 12:
                pfeuille(16);
                break;
            
            default:
                break;
            }
            break;
        } else {
            /*if (i==11) {
                printf("parent   pid : [%d] \n", getpid());
            }*/
            wait(0);    
        }
    }
}



void p2() {
 
    for (int i=5; i<8; i++) {
        if (fork()==0) {
            printf("child %d -> pid : [%d] and ppid : [%d]\n",
                   i+1, getpid(), getppid());
            switch (i+1)
            {
            case 6:
                p6();
                break;
            case 7:
                pfeuille(14);
            
            default:
                break;
            }
            break;
        } else {
            /*if (i==5) {
                printf("parent   pid : [%d] \n", getpid());
            }*/
            wait(0);    
        }
    }
}

void p3() {
 
    
    for (int i=8; i<10; i++) {
        if (fork()==0) {
            printf("child %d -> pid : [%d] and ppid : [%d]\n",
                   i+1, getpid(), getppid());
            switch (i+1)
            {
            case 9:
                pfeuille(15);
                break;
            
            default:
                break;
            }
            break;
            
        } else {
            /*if (i==8) {
                printf("parent   pid : [%d] \n", getpid());
            }*/
            wait(0);    
        }
    }
}




int main()
{
    int i, j, k;
    for (i=1; i<5; i++) {
        if (fork()==0) {
            printf("child %d -> pid : [%d] and ppid : [%d]\n",
                   i+1, getpid(), getppid());
            switch (i+1)
            {
            case 2:
                p2();
                break;
            case 3:
                p3();
                break;
            case 4:
                pfeuille(11);
                break;
            default:
                break;
            }

            break;
        } else {
            /*if (i==1) {
                printf("parent   pid : [%d] \n", getpid());
            }*/
            wait(0);    
        }
    }
    return 0;
}





// BROUILLON





//if you wish to having common parent for all child then go for this code instead of writing fork() no of times :
/*int main()
{
    //TODO remplacer par des switch
    pid_t pid;
    int i, j, k;
    for (i=0; i<10; i++) {
        
        switch (fork())
        {
        case -1:
            perror("main/fork");
            break;
        case 0:
           printf("child %d -> pid : [%d] and father (ppid) : [%d]\n", i+1, getpid(), getppid());
            break;
        
        default:
            if (i==0) {
                printf("parent   pid : [%d] \n", getpid());
            }
            wait(0);    // on attend le fils
            break;
        }

    }

return 0;


}*/
/*
void p2() {

   exit(0);
}
void p3() {
    if (fork() == 0) p6();
    exit(0);
}
void p1() {
    if (fork() == 0) p2();
    if (fork() == 0) p3();
    exit(0);
}

/*int main() {
   if (fork() == 0) p1();
   wait();
}
*/

//if you wish to having parent->child1->child2 i.e child2 parent is child1 like this sequence then go for this code :
/*int main()
{
    
    int i, j, k;
    for (i=0; i<10; i++) {
        if (fork()==0) {
            printf("child %d -> pid : [%d] and ppid : [%d]\n",
                   i+1, getpid(), getppid());
        } else {
            if (i==0) {
                printf("parent   pid : [%d] \n", getpid());
            }
            break;
        }
    }
    return 0;
}
*/