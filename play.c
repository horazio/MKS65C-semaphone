#include "swag.h"

int main(){
  int semd = semget(KEY, 1, 0);
  
  //Acquiring semaphore and downing
  struct sembuf boof;
  boof.sem_num = 0;
  boof.sem_flg = SEM_UNDO;
  boof.sem_op = -1;
  semop(semd, &boof, 1);

  
  //Acquiring shared memory
  int id = shmget(KEY, sizeof(int) , 0777 | IPC_CREAT);
  int * data = shmat(id, NULL, 0);
  
  //Acquiring file
  int fd = open(NAME, O_APPEND | O_RDWR);
  
  //The last line of the file:
  if(* data == 0){
      printf("Woah you get the first line...\n");
  }else{
     char buffy[* data];
     lseek(fd, (* data) * -1, SEEK_END);
     read(fd, buffy, * data);
     printf("The latest line is:\n%s\n", buffy);
  }
  
  //Taking user unput for line
   char inlin[256];
   printf("Your sentence: ");
   fgets(inlin, 256, stdin);
   inlin[strlen(inlin)-1] = '\0';
   printf("'%s'\n", inlin);
   int len = strlen(inlin);
  
  //writing into the file
   lseek(fd, 0, SEEK_END);
   write(fd, inlin, len);
  
  //writing into the shared memory
   * data = len;
  
  //Releasing shared memoy
  shmdt(data);
  
  //upping
  boof.sem_op = 1;
  semop(semd, &boof, 1);
  
  return 0;
}