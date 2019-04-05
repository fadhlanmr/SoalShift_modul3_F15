#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>

int WakeUp_Status;
int Spirit_Status;
pthread_t tid[777];

void* Agmal(void* arg){
    int num = *((int *) arg);
    if(num == 1){
        printf("Agmal WakeUp_Status = %d\n", WakeUp_Status);
    }
    else if(num == 2){
        WakeUp_Status += 15;
        printf("Agmal mulai bangun\n");
    }
}

void* Iraj(void* arg){
    int num = *((int *) arg);
    if(num == 1){
        printf("Iraj Spirit_Status = %d\n", Spirit_Status);
    }
    else if(num == 3){
        Spirit_Status -= 20;
        printf("Iraj mulai ngantuk\n");
    }
}

int main(void){
    WakeUp_Status = 0;
    Spirit_Status = 100;
    int i[777],temp,countW,countS;
    int j=1,ja=1;
    char read[77];
    int *p=&temp;
    while(WakeUp_Status<100 || Spirit_Status>0){
        fgets(read,777,stdin);
        //printf("strcmp = %d\n",strcmp(read,"All Status"));
        if(strcmp(read,"All Status")==10){
            temp = 1;
        }
        else if (strcmp(read,"Agmal Ayo Bangun")==10){
            if(countS==3){
                printf("Agmal Ayo Bangun disabled 10 s");
                countS=0;
            }
            else{
                temp = 2;
                countW +=1;   
            }
        }
        else if (strcmp(read,"Iraj Ayo Tidur")==10){
            if(countW==3){
                printf("Iraj Ayo Tidur disabled 10 s");
                countW=0;
            }
            else{
                temp = 3;
                countS +=1;   
            }
        }
        //printf("temp = %d, countW = %d, countS = %d, j = %d, &p = %d, read = %s\n", temp, countW, countS, j, *p, read);
        i[j]=pthread_create(&(tid[j]), NULL, &Agmal, (void*) p);
        if(i[j]!=0){
			fprintf(stderr,"Error - pthread_create() return code: %d\n",i[j]);
			exit(EXIT_FAILURE);
		}/*
		else{
			//printf("Thread berhasil dibuat\n");
		}*/
        i[j+1]=pthread_create(&(tid[j+1]), NULL, &Iraj, (void*) p);
        if(i[j+1]!=0){
			fprintf(stderr,"Error - pthread_create() return code: %d\n",i[j+1]);
			exit(EXIT_FAILURE);
		}/*
		else{
			//printf("Thread berhasil dibuat\n");
		}*/
        pthread_join(tid[ja], NULL);
        pthread_join(tid[ja+1], NULL);
        j+=2;
        if(WakeUp_Status == 100){
            printf("Agmal Terbangun, mereka bangun pagi dan berolahraga\n");
            break;
        }
        else if(Spirit_Status == 0){
            printf("Iraj ikut tidur, dan bangun kesiangan bersama Agmal\n");
            break;
        }
    }/*
	while(ja<=j){
		pthread_join(tid[ja], NULL);
        pthread_join(tid[ja+1], NULL);
		//printf("thread ke-%d\n", iter);
		ja+=2;
	}*/
    
    return 1;
    
}