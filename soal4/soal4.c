#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
 
pthread_t tid1, tid2;
int status;
 
void* simpan(void *arg)
{
    int num = *((int *) arg);
    char intjadis[10];
    sprintf(intjadis, "%d", num);

    //awk {print} > SimpanProses$i.txt | ps -aux | head -10
    char command[777];
    strcpy(command, "ps -aux | awk {print} > SimpanProses");
    strcat(command, intjadis); 
    strcat(command, ".txt | head -10");
    //printf("%s\n", command);
    system(command);

    //zip KompresProses$i.zip SimpanProses$i.txt
    char commandz[777];
    strcpy(commandz, "zip KompresProses");
    strcat(commandz, intjadis);
    strcat(commandz, ".zip SimpanProses");
    strcat(commandz, intjadis);
    strcat(commandz, ".txt");  
    system(commandz);

    //rm SimpanProses$i.txt
    char commandr[777];
    strcpy(commandr, "rm SimpanProses"); 
    strcat(commandr, intjadis);
    strcat(commandr, ".txt");
    system(commandr);

    sleep(15); //nunggu 15 detik ya

    //unzip KompresProses$i.zip
    char commandu[777];
    strcpy(commandu, "unzip KompresProses");
    strcat(commandu, intjadis);
    strcat(commandu, ".zip");
    system(commandu);
    status = 1;
}
/*
void* kompres(void *arg)
{

    printf("Masukan nomor : ");
    scanf("%d", &nomor);
 
    status = 2;
}

void* dekompres(void *arg)
{

    printf("Masukan nomor : ");
    scanf("%d", &nomor);
 
    status = 3;
}
 */
int main(void)
{
    int i,j,temp=1, temp2=2;
    int *p=&temp;
    int *p2=&temp2;
    int err1, err2;
    err1=pthread_create(&tid1, NULL, &simpan, (void*) p);
        if(err1!=0){
			fprintf(stderr,"Error - pthread_create() return code: %d\n", err1);
			exit(EXIT_FAILURE);
	}
    err2=pthread_create(&tid1, NULL, &simpan, (void*) p2);
        if(err2!=0){
			fprintf(stderr,"Error - pthread_create() return code: %d\n", err2);
			exit(EXIT_FAILURE);
	}
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
 
    return 0;
}
