#include "swag.h"

int main(){
  
    char inlin[3];
    printf("What do you want?");
    fgets(inlin, 3, stdin);
   
    //Open the file
    int fd = open(NAME, O_CREAT | O_APPEND | O_RDWR, 0777);

    //Check for the input
    if(!(strcmp(inlin, "-c"))){

        //SHARED MEMORY
       
       if(shmget(KEY, sizeof(int) , 0777 | IPC_CREAT) == -1){
            printf("Errror: %s\n", strerror(errno));
            exit(1);
        }

        //SEMOPHORES
        int semd = semget(KEY, 1, IPC_CREAT | IPC_EXCL);
      
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
        printf("%i", size);
        char buffer[size];
        read(fd, buffer, size);
       
      //remaining choices
      if(!(strcmp(inlin, "-r"))){
        //Getting the semaphore
        int semd = semget(KEY, 1, 0);
        struct sembuf boof;
        boof.sem_num = 0;
        semop(semd, &boof, 1);
        
        //Shared memory gonzo
        int id = shmget(KEY, sizeof(int), 0);
        shmctl(id, IPC_RMID, NULL);
        
        //semophore gonzo
        semctl(semd, 0, IPC_RMID);
        
        //Printing out the story
        printf("Everything reset, this was the file:\n%s\n", buffer);
      } else if(!(strcmp(inlin, "-v"))){
        
        printf("%s\n", buffer);
      }
    }

    close(fd);
    return 0;
}
