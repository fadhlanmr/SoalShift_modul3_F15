# SoalShift_modul3_F15
<sub><sup> Agmal emang susah dibangunin, dikelas aja suka tidur. Kalo Iraj Susah ditidurin. </sub></sup>

## Soal No 1
Buatlah program C yang bisa menghitung faktorial secara parallel lalu menampilkan hasilnya secara berurutan
Contoh:
    ./faktorial 5 3 4
    3! = 6
    4! = 24
    5! = 120
### Jawaban
1. Input diambil dalam parameter 
    ```c 
    int main(int argc, char argv[]);
    ```
    dimana argc merupakan counter dari banyak nya intputan, dan indeks argv[] merupakan value dari inputan;

2. Merubah input dalam tipe argumen menjadi integer dengan
    ```c
    int main{
        int iter, sort[777];
        sort[iter] = strtol(argv[iter],NULL,10);
    };
    ```
    mengubah input string menjadi long integer (strtol)

3. Sorting seluruh input yang ada di dalam array
    ```c
    void sort(int sort[], argc){
        int iter, temp;
        for(iter=1;iter<argc;iter++){
		    for(j=1;j<argc;j++){
			    if(sort[j] > sort[j+1]){
				    temp = sort[j+1];
				    sort[j+1] = sort[j];
				    sort[j] = temp;
			    }
	        }
	    }
    }
    ```
    dengan menggunakan bubble sort

4. Lalu membuat fungsi faktorial dengan printf, untuk melakukan threading faktorial
    ```c
    void *fakt(void *arg){
	    int i=1;
	    arr[n]=1;
	    for(i=1;i<=n;i++){
		    arr[n] *= i;
	    }
	    printf("%ld! = %llu \n", n, arr[n]);
    }
    ```
    dan threading di main seperti berikut
    ```c
    int main(){
        while(iter<argc){
            n = sort[iter+1];
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
    }
    ```
    untuk melakukan dan membuat thread sebanyak input argc.

## Soal No 2
Pada suatu hari ada orang yang ingin berjualan 1 jenis barang secara private, dia memintamu membuat program C dengan spesifikasi sebagai berikut:
- Terdapat 2 server: server penjual dan server pembeli
- 1 server hanya bisa terkoneksi dengan 1 client
- Server penjual dan server pembeli memiliki stok barang yang selalu sama
- Client yang terkoneksi ke server penjual hanya bisa menambah stok
    - Cara menambah stok: client yang terkoneksi ke server penjual mengirim string “tambah” ke server lalu stok bertambah 1
- Client yang terkoneksi ke server pembeli hanya bisa mengurangi stok
    - Cara mengurangi stok: client yang terkoneksi ke server pembeli mengirim string “beli” ke server lalu stok berkurang 1
- Server pembeli akan mengirimkan info ke client yang terhubung dengannya apakah transaksi berhasil atau tidak berdasarkan ketersediaan stok
    - Jika stok habis maka client yang terkoneksi ke server pembeli akan mencetak “transaksi gagal”
    - Jika stok masih ada maka client yang terkoneksi ke server pembeli akan mencetak “transaksi berhasil”
- Server penjual akan mencetak stok saat ini setiap 5 detik sekali
- Menggunakan thread, socket, shared memory
### Jawaban
1. Soal diselesaikan dengan 4 proses, yaitu Client&Server Pembeli dan Penjual.
2. Pembeli :
    - Client :
        1. Client terhubung pada port yang sama dengan server pembeli.
        2. Client akan mengirimkan pesan ke server.
        3. Client mengambil pesan dari server dan diletakkan pada buffer.
        4. Client Mencetak buffer yang diterima dari server.
    - Server :
       1. Server Pembeli akan memiliki shared memory dengan server penjual.
       2. Server menerima pesan dari client
       3. Jika client mengirim pesan untuk membeli, maka value shared memory berkurang
       4. Jika stok tidak ada, maka server mengirimkan pesan ke client bahwa transaksi gagal
3. Penjual :
    - Client :
        1. Client terhubung pada port yang sama dengan server pembeli.
        2. Client akan mengirimkan pesan ke server.
        3. Client mengambil pesan dari server dan diletakkan pada buffer.
        4. Client Mencetak buffer yang diterima dari server.
    - Server :
        1. Server penjual memiliki shared memory dengan server pembeli
        2. Server menerima pesan dari client
        3. Jika client mengirim pesan untuk menjual, maka value shared memory akan bertambah.

Untuk membuat Client dan server, kita mengikuti format dari modul 3 yaitu dengan menggunakan
```c
//server
int main(int argc, char const *argv[]) {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char *habis = "Stok Habis, Transaksi Gagal";
    char *ada = "Stok Ada, Transaksi Berhasil";
      
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

    char buffer[1024] = {0};
    valread = read( new_socket , buffer, 1024);
    send(new_socket , ada , strlen(ada) , 0 );
    printf("Transaksi Berhasil, Stok Berkurang\n");
}
```
menggukanan gets() untuk meng-input pesan dari client
```c
gets(&hello);
send(sock , hello , strlen(hello) , 0 );
```
lalu server akan mendapatkan pesan dari client, di server sendiri kita inisialisasi shared memory dengan mengikuti modul
```c
key_t key = 1234;
int *value;

int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
value = shmat(shmid, NULL, 0);

*value = 0;

shmdt(value);
shmctl(shmid, IPC_RMID, NULL);
``` 
yang akan bertambah dan berkurang jika menerima pesan dari client berupa "Tambah" atau "Beli".
```c
//server penjual
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

//server pembeli
while(1){
        char buffer[1024] = {0};
        valread = read( new_socket , buffer, 1024);
        if(*value==0){
            send(new_socket , habis , strlen(habis) , 0 );
            printf("Gagal Transaksi, Stok Habis\n");
        }
        else
        {
            if (strcmp(buffer, "beli")==0 || strcmp(buffer, "Beli")==0){
                *value -= 1;
                send(new_socket , ada , strlen(ada) , 0 );
                printf("Transaksi Berhasil, Stok Berkurang\n");
            }  
        }
}
```
dan untuk print banyak stok setiap 5 detik, menggunakan thread yang loopnya infinite, dan di sleep selama 5 detik
```c
void* print(void* arg){
    while(1){
        int num = *((int *) arg);
        printf("Stok : %d\n", num);
        sleep(5);
    }    
}

pthread_t tid1;
pthread_create(&tid1, NULL, print, (void*) p);
```

## Soal No 3
Agmal dan Iraj merupakan 2 sahabat yang sedang kuliah dan hidup satu kostan, sayangnya mereka mempunyai gaya hidup yang berkebalikan, dimana Iraj merupakan laki-laki yang sangat sehat,rajin berolahraga dan bangun tidak pernah kesiangan sedangkan Agmal hampir menghabiskan setengah umur hidupnya hanya untuk tidur dan ‘ngoding’. Dikarenakan mereka sahabat yang baik, Agmal dan iraj sama-sama ingin membuat satu sama lain mengikuti gaya hidup mereka dengan cara membuat Iraj sering tidur seperti Agmal, atau membuat Agmal selalu bangun pagi seperti Iraj. Buatlah suatu program C untuk menggambarkan kehidupan mereka dengan spesifikasi sebagai berikut:
1. Terdapat 2 karakter Agmal dan Iraj
2. Kedua karakter memiliki status yang unik
    - Agmal mempunyai WakeUp_Status, di awal program memiliki status 0
    - Iraj memiliki Spirit_Status, di awal program memiliki status 100
    - Terdapat 3 Fitur utama
        - All Status, yaitu menampilkan status kedua sahabat
            Ex: Agmal WakeUp_Status = 75, 
            Iraj Spirit_Status = 30
        - “Agmal Ayo Bangun” menambah WakeUp_Status Agmal sebesar 15 point
        - “Iraj Ayo Tidur” mengurangi Spirit_Status Iraj sebanyak 20 point
    - Terdapat Kasus yang unik dimana:
        - Jika Fitur “Agmal Ayo Bangun” dijalankan sebanyak 3 kali, maka Fitur “Iraj Ayo Tidur” Tidak bisa dijalankan selama 10 detik (Dengan mengirim pesan ke sistem “Fitur Iraj Ayo Tidur disabled 10 s”)
        - Jika Fitur  “Iraj Ayo Tidur” dijalankan sebanyak 3 kali, maka Fitur “Agmal Ayo Bangun” Tidak bisa dijalankan selama 10 detik (Dengan mengirim pesan ke sistem “Agmal Ayo Bangun disabled 10 s”)
    - Program akan berhenti jika Salah Satu :
        - WakeUp_Status Agmal >= 100 (Tampilkan Pesan “Agmal Terbangun,mereka bangun pagi dan berolahraga”)
        - Spirit_Status Iraj <= 0 (Tampilkan Pesan “Iraj ikut tidur, dan bangun kesiangan bersama Agmal”
    - Syarat Menggunakan Lebih dari 1 Thread
### Jawaban
1. Membuat thread agmal yang akan menambah, memberhentikan, print status jika input sesuai
    ```c
    void* Agmal(void* arg){
        int num = *((int *) arg);
        if(statusa==1){
            sleep(10);
            statusa = 0;
        }
        else{
            if(num == 1){
                printf("Agmal WakeUp_Status = %d\n", WakeUp_Status);
            }
            else if(num == 2){
                WakeUp_Status += 15;
                printf("Agmal mulai bangun\n");
            }
        }
    }
    ```
2. Membuat thread Iraj yang juga seperti thread Agmal
    ```c
    void* Iraj(void* arg){
    int num = *((int *) arg);
        if(statusi==1){
            sleep(10);
            statusi = 0;
        }
        else{
            if(num == 1){
                printf("Iraj Spirit_Status = %d\n", Spirit_Status);
            }
            else if(num == 3){
                Spirit_Status -= 20;
                printf("Iraj mulai ngantuk\n");
            }
        }
    }
    ```
3. Membaca input, selama status kedua karakter tidak melebih kondisi selesai
    ```c
    while(WakeUp_Status<100 || Spirit_Status>0){
        fgets(read,777,stdin);
        if(strcmp(read,"All Status")==10){
            temp = 1;
        }
        else if (strcmp(read,"Agmal Ayo Bangun")==10){
            if(countS==3){
                temp=0;
                statusa=1;
                countS=0;
            }
            else{
                temp = 2;
                countW +=1;
                if(countW==3){
                    printf("Iraj Ayo Tidur disabled 10 s\n");
                }   
            }
        }
        else if (strcmp(read,"Iraj Ayo Tidur")==10){
            if(countW==3){
                temp=0;
                statusi=1;
                countW=0;
            }
            else{
                temp = 3;
                countS +=1;   
                if(countS==3){
                    printf("Agmal Ayo Bangun disabled 10 s\n");
                }
            }
        }
    ```    
4. Membuat thread yang memasukkan nilai temp sebagai indikator menjalankan perintah
    ```c
    i[j]=pthread_create(&(tid[j]), NULL, &Agmal, (void*) p);
    if(i[j]!=0){
		fprintf(stderr,"Error - pthread_create() return code: %d\n",i[j]);
		exit(EXIT_FAILURE);
	}
    i[j+1]=pthread_create(&(tid[j+1]), NULL, &Iraj, (void*) p);
    if(i[j+1]!=0){
		fprintf(stderr,"Error - pthread_create() return code: %d\n",i[j+1]);
		exit(EXIT_FAILURE);
	}
    ```
## Soal 4
Buatlah sebuah program C dimana dapat menyimpan list proses yang sedang berjalan (ps -aux) maksimal 10 list proses. Dimana awalnya list proses disimpan dalam di 2 file ekstensi .txt yaitu  SimpanProses1.txt di direktori /home/Document/FolderProses1 dan SimpanProses2.txt di direktori /home/Document/FolderProses2 , setelah itu masing2 file di  kompres zip dengan format nama file KompresProses1.zip dan KompresProses2.zip dan file SimpanProses1.txt dan SimpanProses2.txt akan otomatis terhapus, setelah itu program akan menunggu selama 15 detik lalu program akan mengekstrak kembali file KompresProses1.zip dan KompresProses2.zip 
Dengan Syarat : 
- Setiap list proses yang di simpan dalam masing-masing file .txt harus berjalan bersama-sama
- Ketika mengkompres masing-masing file .txt harus berjalan bersama-sama
- Ketika Mengekstrak file .zip juga harus secara bersama-sama
- Ketika Telah Selesai melakukan kompress file .zip masing-masing file, maka program akan memberi pesan “Menunggu 15 detik untuk mengekstrak kembali”
- Wajib Menggunakan Multithreading
- Boleh menggunakan system
### Jawaban
1. Membuat 2 thread (memastikan semua proses berjalan bersamaan).
2. Thread 1 : Membuat file > Mengkompres > Meremove > Mengekstrak.
3. Thread 2 bekerja seperti thread 1, dengan nama yang berbeda.
4. Semua perintah bisa dijalankan.

## Soal 5
Angga, adik Jiwang akan berulang tahun yang ke sembilan pada tanggal 6 April besok. Karena lupa menabung, Jiwang tidak mempunyai uang sepeserpun untuk membelikan Angga kado. Kamu sebagai sahabat Jiwang ingin membantu Jiwang membahagiakan adiknya sehingga kamu menawarkan bantuan membuatkan permainan komputer sederhana menggunakan program C. Jiwang sangat menyukai idemu tersebut. Berikut permainan yang Jiwang minta. 

    a. Pemain memelihara seekor monster lucu dalam permainan. Pemain dapat memberi nama pada monsternya.

    b. Monster pemain memiliki hunger status yang berawal dengan nilai 200 (maksimalnya) dan nanti akan berkurang 5 tiap 10 detik.Ketika hunger status mencapai angka nol, pemain akan kalah. Hunger status dapat bertambah 15 apabila pemain memberi makan kepada monster, tetapi banyak makanan terbatas dan harus beli di Market.

    c. Monster pemain memiliki hygiene status yang berawal dari 100 dan nanti berkurang 10 tiap 30 detik. Ketika hygiene status mencapai angka nol, pemain akan kalah. Hygiene status' dapat bertambah 30 hanya dengan memandikan monster. Pemain dapat memandikannya setiap 20 detik(cooldownnya 20 detik).

    d. Monster pemain memiliki health status yang berawal dengan nilai 300. Variabel ini bertambah (regenerasi)daa 5 setiap 10 detik ketika monster dalam keadaan standby.

    e. Monster pemain dapat memasuki keadaan battle. Dalam keadaan ini, food status(fitur b), hygiene status'(fitur c), dan ‘regenerasi’(fitur d) tidak akan berjalan. Health status dari monster dimulai dari darah saat monster pemain memasuki battle. Monster pemain akan bertarung dengan monster NPC yang memiliki darah 100. Baik monster pemain maupun NPC memiliki serangan sebesar 20. Monster pemain dengan monster musuh akan menyerang secara bergantian. 

    f. Fitur shop, pemain dapat membeli makanan sepuas-puasnya selama stok di toko masih tersedia.
        - Pembeli (terintegrasi dengan game)
            - Dapat mengecek stok makanan yang ada di toko.
            - Jika stok ada, pembeli dapat membeli makanan.
        -Penjual (terpisah)
            - Bisa mengecek stok makanan yang ada di toko
            - Penjual dapat menambah stok makanan.

Spesifikasi program:
    
1. Program mampu mendeteksi input berupa key press. (Program bisa berjalan tanpa perlu menekan tombol enter)
2. Program terdiri dari 3 scene yaitu standby, battle, dan shop.
3. Pada saat berada di standby scene, program selalu menampilkan health status, hunger status, hygiene status, stok makanan tersisa, dan juga status kamar mandi (“Bath is ready” jika bisa digunakan, “Bath will be ready in [bath cooldown]s” jika sedang cooldown). Selain itu program selalu menampilkan 5 menu, yaitu memberi makan, mandi, battle, shop, dan exit. Contoh :

        Standby Mode
        Health : [health status]
        Hunger : [hunger status]
        Hygiene : [hygiene status]
        Food left : [your food stock]
        Bath will be ready in [cooldown]s
        Choices
        1. Eat
        2. Bath
        3. Battle
        4. Shop
        5. Exit

4. Pada saat berada di battle scene, program selalu menampilkan health status milik pemain dan monster NPC. Selain itu, program selalu menampilkan 2 menu yaitu serang atau lari. Contoh :

        Battle Mode
        Monster’s Health : [health status]
        Enemy’s Health : [enemy health status]
        Choices
        1. Attack
        2. Run

5. Pada saat berada di shop scene versi pembeli, program selalu menampilkan food stock toko dan milik pemain. Selain itu, program selalu menampilkan 2 menu yaitu beli dan kembali ke standby scene. Contoh :

	    Shop Mode
	    Shop food stock : [shop food stock]
	    Your food stock : [your food stock]
	    Choices
        1. Buy
        2. Back

6. Pada program penjual, program selalu menampilkan food stock toko. Selain itu, program juga menampilkan 2 menu yaitu restock dan exit. Contoh :

        Shop
        Food stock : [shop food stock]
        Choices
        1. Restock
        2. Exit

7. Pastikan terminal hanya mendisplay status detik ini sesuai scene terkait (hint: menggunakan system(“clear”))
### Jawaban
