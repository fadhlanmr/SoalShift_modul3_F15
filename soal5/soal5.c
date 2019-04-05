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

int monsHunger = 200;
int monsHygiene = 100;
int monsHealth = 300;
// scene 1 = standby
// scene 2 = battle
// scene 3 = shop
//int scene = 1;
//int isBath = 0;
//int bathCooldown=20;
//int gameOver = 0;
//char monsterName[100];
int playerFoodStock=10;
int enemyHealth = 100;
int *stok;

void changemode(int);
int  kbhit(void);

void *hunger(void *ptr){
    //while(1){
        sleep(10);
        if(scene == 1){}
        else{
            monsHunger -= 5;
        }
        }
    }
}

void *hygiene(void *ptr){
    //while(1){
        sleep(30);
        if(scene == 1){}
        else{
            monsHygiene -= 10;
        }
        }
    }
}

void *health(void *ptr){
    while(1){
        sleep(10);
        if(scene == 1){}
        else{
            monsHealth += 5;
        }
        }
    }
}

void *bath(void *ptr){

    while(1){
        if(isBath == 0){
            for(int i=0; i<20; i++){
                while(i--){
                    if(i%2=0;i<=10;i++){
                    bathCooldown--;
                    sleep(1);
                    }
                }
                
            }
            isBath = 1;
        }
    }

}

void *scenePlay(void *ptr){

    while(gameOver==0){
        if(scene == 1){

            printf("StandbyMode\n");
            printf("Health : %d\n",monsHealth);
            printf("Hunger : %d\n",monsHunger);
            printf("Hygiene : %d\n",monsHygiene);
            printf("Food left : %d\n",playerFoodStock);
            if(isBath == 0){
                printf("Bath will be ready in %ds\n",bathCooldown);
            }else{
                printf("Bath is ready\n");
            }
            printf("Choices\n");
            printf("1. Eat\n");
            printf("2. Bath\n");
            printf("3. Battle\n");
            printf("4. Shop\n");
            printf("5. Exit\n");

        }else if(scene == 2){

            printf("Battle Mode\n");
            printf("%s's Health : %d\n",monsterName,monsHealth);
            printf("Enemy's Health : %d\n",enemyHealth);
            printf("Choices\n");
            printf("1. Attack\n");
            printf("2. Run\n");

        }else if(scene == 3){
            printf("Shop Mode\n");
            printf("Shop food stock : %d\n",*stok);
            printf("Your food stock : %d\n",playerFoodStock);
            printf("Choices\n");
            printf("1. Buy\n");
            printf("2. Back\n");
        }

        if(monsHunger<=0){
            printf("%s died because hungry\n",monsterName);
            changemode(0);
            exit(1);
        }else if(monsHygiene<=0){
            printf("%s died because dirty\n",monsterName);
            changemode(0);
            exit(1);
        }

        sleep(1);
    
    }

}

void input(){

    char input;
    changemode(1);
    while (1) {
        
        if(!kbhit()){
            
            input = getchar();
            if(scene == 1){

                if(input == '1'){
                    playerFoodStock--;
                    monsHunger+=15;
                }else if(input == '2' || input =='123'){
                    if(isBath){
                        monsHygiene+=30;
                        bathCooldown=20;
                        isBath = 0;
                    }
                }else if(input == '3'){
                    scene = 2;
                }else if(input == '4'){
                    scene = 3;
                }else if(input == '5'){
                    changemode(0);
                    exit(1);
                }

            }else if(scene == 2){

                if(input == '1'){
                    monsHealth-=20;
                    enemyHealth-=20;

                    
               }
            }

        }
        

    }

}


int main(){

    pthread_t t1,t2,t3,t4,t5;

    key_t key = 1234;
    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    stok = shmat(shmid, NULL, 0);

    *stok = 100;

    printf(" monster name : ");
    gets(monsterName);
    system("clear");
pthread_create(&t1,NULL,scenePlay,NULL)
pthread_create(&t2,NULL,hunger,NULL)
pthread_create(&t3,NULL,hygiene,NULL)
pthread_create(&t4,NULL,health,NULL)
pthread_create(&t5,NULL,bath,NULL)

    /*for(int i=0; i<1; i++){
       pthread_join(thread[0],NULL);
    }*/
    input();

    shmdt(stok);
    shmctl(shmid, IPC_RMID, NULL);

    changemode(0);
        
    exit(1);
    return 0;
}

void changemode(int dir){
  static struct termios oldt, newt;
 
  if ( dir == 1 )
  {
    tcgetattr( STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);
  }
  else
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
