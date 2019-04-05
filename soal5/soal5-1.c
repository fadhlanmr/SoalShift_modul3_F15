#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>
#include<string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <termios.h>
#include <sys/ioctl.h>

void changemode(int);
int  kbhit(void);

int *stok;

void *display(void *ptr){

        
        printf("Shop\n");
        printf("Food stock : %d\n",*stok);
        printf("Choices\n");
        printf("1. Restock\n");
        printf("2. Exit\n");

}

void input(){

    char input;
    while (input!=EOF) {
        
       if(kbhit()!=0 || input != EOF){
            
            input = gets();
            if(input == '1'){
                *stok+=1;
            }else if(input == '2'){
                exit(1);
            }
       
       }

    }

}

int main(){

    pthread_t thread;
    
    key_t key = 1234;
    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    stok = shmat(shmid, NULL, 0);

    pthread_create(&thread,NULL,display,NULL)
    input();

    shmdt(stok);
    shmctl(shmid, IPC_RMID, NULL);
        
    exit(1);
    return 0;
}

 
int kbhit (void){
  struct timeval tv;
  fd_set bole;
 
  tv.tv_sec = 0;
  tv.tv_usec = 0;
 
  FD_ZERO(&bole);
  FD_SET (STDIN_FILENO, &bole);
  return FD_ISSET(STDIN_FILENO, &bole);
}
