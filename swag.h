#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <signal.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/sem.h>

#define KEY 0xD00D5EED
#define NAME "swag.txt"

union semun {
    int val;
    struct semid_ds * buf;
    unsigned short * array;
    struct seminfo * __buf;
};