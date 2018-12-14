#include "swag.h"

int main(){
  
    char inlin[3];
    printf("What do you want?\n");
    fgets(inlin, 3, stdin);
   
    //Open the file
    int fd = open(NAME, O_CREAT | O_RDWR, 0777);

    //Check for the input
    if(!(strcmp(inlin, "-c"))){

        //SHARED MEMORY
       
       int id = shmget(KEY, sizeof(int) , 0777 | IPC_CREAT);
       if(id == -1){
            printf("Errror: %s\n", strerror(errno));
            exit(1);
        }else{
            int * data = shmat(id, NULL, 0);
            * data = 0; 
            shmdt(data);
        }

        //SEMOPHORES
        int semd = semget(KEY, 1, IPC_CREAT | IPC_EXCL | IPC_NOWAIT);
      
        if(semd == -1){
          printf("Errror: %s\n", strerror(errno));
          exit(1);
        }else{
            union semun us;
            us.val = 1;
            semctl(semd, 0, SETVAL, us);
        }

        
    } else {
        //Reading all contents out of file
        struct stat info;
        stat(NAME, &info);
        int size = info.st_size;
        char buffer[size];
        read(fd, buffer, size);
       
      //remaining choices
      if(!(strcmp(inlin, "-r"))){
        //Getting the semaphore
        int semd = semget(KEY, 1, 0);
        struct sembuf boof;
        boof.sem_num = 0;
        if (semop(semd, &boof, 1) == -1) {
            printf("Errror: %s\n", strerror(errno));
            exit(1);
        }
        
        //Shared memory gonzo
        int id = shmget(KEY, sizeof(int), 0);
        shmctl(id, IPC_RMID, NULL);
        
        //semophore gonzo
        semctl(semd, 0, IPC_RMID);
        
        //file gonzo
        fd = open(NAME, O_CREAT | O_TRUNC, 0777);
        write(fd, "", 1);
        
        //Printing out the story
        printf("Everything reset, this was the file:\n%s\n", buffer);
      } else if(!(strcmp(inlin, "-v"))){
        printf("%s\n", buffer);
      }
    }

    close(fd);
    return 0;
}
