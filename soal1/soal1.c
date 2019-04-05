#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>

long int n;
long long arr[777];
pthread_t tid[777];

void *fakt(void *arg){
	int i=1;
	arr[n]=1;
	for(i=1;i<=n;i++){
		arr[n] *= i;
		//printf("iterasi ke-%ld isi arr : %llu \n",i,arr[n]);
	}
	printf("%ld! = %llu \n", n, arr[n]);
}

int main(int argc, char* argv[]){
	int iter = 1, j=1, temp;
	int i[777], sort[777];
	void *p=sort;
	//long *p = &n;
	while(iter<argc){
		sort[iter] = strtol(argv[iter],NULL,10);
		iter++;
		//printf("p = %p, *p = %p, sort[%d] = %d, argv[%d] = %s\n", p, &p, iter-1, sort[iter-1], iter-1, argv[iter-1]);
	}
	for(iter=1;iter<argc;iter++){
		for(j=1;j<argc;j++){
			if(sort[j] > sort[j+1]){
				temp = sort[j+1];
				sort[j+1] = sort[j];
				sort[j] = temp;
			}
		}
	}
	//printf("argc = %d, argv[%d] = %s\n", argc, argc-1, argv[argc-1]);
	iter=1;
	while(iter<argc){
		//printf("iter = %d, argv[%d] = %s\n", iter, iter, argv[iter]);
		n = sort[iter+1];
		//n = strtol(argv[iter],NULL,10);
		//printf("n = %ld\t", n);
		i[iter]=pthread_create(&(tid[iter]), NULL, &fakt, (void*) p);
		if(i[iter]!=0){
			fprintf(stderr,"Error - pthread_create() return code: %d\n",i[iter]);
			exit(EXIT_FAILURE);
		}
		else{
			printf("Thread berhasil dibuat\n");
		}
		iter++;
	}
	iter = 1;
	while(iter<argc){
		pthread_join(tid[iter], NULL);
		//printf("thread ke-%d\n", iter);
		iter++;
	}
	
	//printf("n = %ld\t", n);
	//printf("%ld! = %llu \n", n, arr[n]);
	return 1;
}
