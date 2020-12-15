
// SUPPORT DE CODE POUR UNE QUESTION

int main()
{
    int i, j, k;
    for (i=1; i<5; i++) {
        
        switch (fork())
        {
        case 0:
            printf("child %d -> pid : [%d] and ppid : [%d]\n",
                   i+1, getpid(), getppid());
            break;
        
        default:
            if (i==1) {
            printf("parent   pid : [%d] \n", getpid());
            }
            wait(0);
        }
    }
    return 0;
}



/*
int main()
{
    int i, j, k;
    for (i=1; i<5; i++) {

        if (fork()==0) {
            printf("child %d -> pid : [%d] and ppid : [%d]\n",
                   i+1, getpid(), getppid());
        break; // on passe à l'itération d'après

        } 
        else {
            if (i==1) {
            printf("parent   pid : [%d] \n", getpid());
            }
            wait(0);    
        }
    }
    return 0;
}
*/