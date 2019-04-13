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
