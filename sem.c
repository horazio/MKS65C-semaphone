#include "swag.h"

union semun {
    int val;
    struct semid_ds * buf;
    unsigned short * array;
    struct seminfo * __buf;
};


int main(){
    char inlin[3];
    printf("What do you want?\n");
    fgets(inlin, 3, stdin);
    //Open the file
    int fd = open("swag.txt", O_CREAT | O_APPEND | O_WRONLY, 0777);

    //Check for the input
    if(!(strcmp(inlin, "-c"))){

        //SHARED MEMORY
        int id;
        char * data;

        if((id = shmget(420, 200 * sizeof(char), 0664 | IPC_CREAT)) == -1){
            printf("Errror: %s\n", strerror(errno));
            exit(1);
        }
        data = shmat(id, NULL, 0);

        //SEMOPHORES
        int key = 0xD00D5EED;
        semget(key, 1, IPC_CREAT);

        close(fd);
    } else if(!(strcmp(inlin, "-r"))){
        struct stat info;


        stat("swag.txt", &info);
        int size = info.st_size;

        printf("%i", size);
        //char * buffer = malloc(sizeof(char*) * size);

        char buffer[size];
        read(fd, buffer, size);

        printf("--> %s <-- \n", buffer);

    } else if(!(strcmp(inlin, "-v"))){

    }

    return 0;
}
