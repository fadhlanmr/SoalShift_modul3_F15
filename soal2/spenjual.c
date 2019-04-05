#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <pthread.h>
#define PORT 9090

void* print(void* arg){
    while(1){
        int num = *((int *) arg);
        printf("Stok : %d\n", num);
        sleep(5);
    }    
}

int main(int argc, char const *argv[]) {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    char *hello = "Stok Bertambah";
    int addrlen = sizeof(address);
      
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
      
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    key_t key = 1234;
    int *value;

    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    value = shmat(shmid, NULL, 0);

    int *p=value;
    pthread_t tid1;
    pthread_create(&tid1, NULL, print, (void*) p);

    while(1){
        char buffer[1024] = {0};
        valread = read( new_socket , buffer, 1024);
        printf("Penjual %s Stok\n",buffer );
        if(strcmp(buffer, "tambah")==0 || strcmp(buffer, "Tambah")==0){
            *value += 1;
            send(new_socket , hello , strlen(hello) , 0 );
            printf("Stok Bertambah\n");
        }
        pthread_join(tid1, NULL);
        
    }

    shmdt(value);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}