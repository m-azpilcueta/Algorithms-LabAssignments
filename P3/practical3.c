/*
    Author 1: Javier Escribano Salgado (javier.escribano)
    Author 2: Martín Azpilcueta Rabuñal (m.azpilcueta)
    Practical 3
    Group 6.1
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

#define SZ 256000
#define N 7
#define TEST 32000

typedef struct {
  int vector[SZ];
  int last;
}heap;

double microseconds() { /* obtains the system time in microseconds */
    struct timeval t;
        if (gettimeofday(&t, NULL) < 0 ){
            return 0.0;
        }
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void random_init(int v [], int n) { /* we generate pseudorandom numbers between -n and +n */
    int i, m = 2*n+1;
    for (i = 0; i < n; i++)
	v[i] = (rand() % m) - n;
}

void init_seed() {
    srand(time(NULL));
}

int test_ord(int v[], int n){ // Checks if the array is ascending 
    int i;
    for(i = 0; i < n-1;i++){
	if(v[i]<=v[i+1]){
		continue;
	}
	else return 0;
	break;
    }
    return 1;
}

void ascending_init(int v[], int n) {
    int i;
    for (i = 0; i < n; i++)
	v[i] = i;	
}


void descending_init(int v[], int n){
    int i,total;
    total = n;
    for(i = 0;i < total;i++){
	v[i] = n-1;
	n = n - 1; 
    }
}

void print_array (int v [], int n) {
    int i;
    printf("[");
    for (i = 0; i < n; i++) {
        printf(" %2d ",v[i]);
    }
    printf("]\n");
}

void print_pointer(heap *h){
    printf("[");
    for (int i = 0; i < h->last; i++){
        printf(" %2d ", h->vector[i]);
    }
    printf("]\n");
}

void swap(int index1, int index2, heap *h){
    int temp = h->vector[index1];
    h->vector[index1] = h->vector[index2];
    h->vector[index2] = temp;
}

void sink(heap *h, int i){
    int RightChild, LeftChild, j;
    while(j != i){
        LeftChild = 2*i + 1;
        RightChild = 2*i + 2;
        j = i;
        if ((RightChild < h->last) && (h->vector[RightChild] < h->vector[j])){
            i = RightChild;
            swap(i,j,h);   
        }
        if ((LeftChild < h->last) && (h->vector[LeftChild] < h->vector[j])){
            i = LeftChild;
            swap(i,j,h);       
        }
    }
}

void create_heap(int a[], int n, heap *h){
    for(int i=0; i < n; i++) {
	h->vector[i] = a[i];
    }
    h->last = n;	
    for(int i=(h->last)/2; i>=0; i--){
	sink(h,i);
    }  
}

int get_min(const heap *h){
    return h->vector[0];
}

int remove_min(heap *h){
    int x;
    if (h->last == 0){
        free(h);
        perror("Empty Heap");
    }
    else {
        x = h->vector[0];
        h->vector[0] = h->vector[h->last-1];
        h->last--;
        if ((h->last > 0) && (h->last != 2)){
            sink(h,0);
        }
        else if (h->last == 2){
            if(h->vector[0] > h->vector[1]){
                swap(1,0,h);
            }
        }
    }
    return x;
}

void heapsort(int a[], int n){
    heap *h;
    h = (heap *) malloc(sizeof(heap));
    create_heap(a,n,h);
    for (int i = 0; i < n; i++){
        a[i] = get_min(h);
        remove_min(h);
    }
}

void testget_min(){
    int a[N];
    heap *h;
    h = (heap *) malloc(sizeof(heap));

    printf("Check of get_min:\n");
    random_init(a,N);
    create_heap(a,N,h);
    print_pointer(h);
    printf("%d is the minimum value",get_min(h));
    printf("\n");
    free(h);
}

void testremove_min(){
    int a[N];
    heap *h;
    h = (heap *) malloc(sizeof(heap));

    printf("Check if the minimum value is removed and the heap is reordered\n");
    random_init(a,N);
    print_array(a,N);
    printf("Min Heap\n");
    create_heap(a,N,h);
    print_pointer(h);
    printf("%d is the element removed\n",remove_min(h));
    print_pointer(h);
    printf("\n");
    free(h);
}

void testCreate(){
    int a[N];
    heap *h;
    h = (heap *) malloc(sizeof(heap));
    printf("Create Heap with Random Initialization\n");
    random_init(a,N);
    print_array(a,N);
    create_heap(a,N,h);
    print_pointer(h);
    printf("\n");

    printf("Create Heap with Ascending Initialization\n");
    ascending_init(a,N);
    print_array(a,N);
    create_heap(a,N,h);
    print_pointer(h);
    printf("\n");

    printf("Create Heap with Descending Initialization\n");
    descending_init(a,N);
    print_array(a,N);
    create_heap(a,N,h);
    print_pointer(h);
    printf("\n");
    free(h);
}

void createRandom(){
    int n = 500, k, i, v[TEST];
    double t1,t2,t,lower,tight,upper,ta,tb;
    heap *h;
    h = (heap *) malloc(sizeof(heap));
    random_init(v,TEST);
    printf("%10s%17s%20s%20s%20s\n","n","t(n)","t(n)/n^0.8","t(n)/n","t(n)/n^1.2");
    for(i=0;i<7;i++){
    	t1=microseconds();
    	create_heap(v,n,h);
    	t2=microseconds();
    	t=t2-t1;
    	if (t < 500) {
            ta = microseconds();
            k = 0;
            while (k < 1000){
                random_init(v,TEST);
                create_heap(v,n,h);
                k++;
            }
            tb = microseconds();
            t1 = tb-ta;
            ta = microseconds();
            k = 0;
            while (k < 1000){
                random_init(v,TEST);
                k++;
            }
            tb = microseconds();
            t2 = tb-ta;
            t = (t1-t2)/1000;
            printf("(*)");
        }
	tight = t/n;
	upper = t/(pow(n,1.2));
	lower = t/(pow(n,0.8));
    	printf("%10d%17.2f%20.7f%20.7f%20.7f\n",n,t,lower,tight,upper);
    	n=n*2;
    }
    free(h);
}

void createAscending(){
    int n = 500, k, i, v[TEST];
    double t1,t2,t,lower,tight,upper,ta,tb;
    heap *h;
    h = (heap *) malloc(sizeof(heap));
    ascending_init(v,TEST);
    printf("%10s%17s%20s%20s%20s\n","n","t(n)","t(n)/n^0.8","t(n)/n","t(n)/n^1.2");
    for(i=0;i<7;i++){
    	t1=microseconds();
    	create_heap(v,n,h);
    	t2=microseconds();
    	t=t2-t1;
    	if (t < 500) {
            ta = microseconds();
            k = 0;
            while (k < 1000){
                ascending_init(v,TEST);
                create_heap(v,n,h);
                k++;
            }
            tb = microseconds();
            t1 = tb-ta;
            ta = microseconds();
            k = 0;
            while (k < 1000){
                ascending_init(v,TEST);
                k++;
            }
            tb = microseconds();
            t2 = tb-ta;
            t = (t1-t2)/1000;
            printf("(*)");
        }
	tight = t/n;
	upper = t/(pow(n,1.2));
	lower = t/(pow(n,0.8));
    	printf("%10d%17.2f%20.7f%20.7f%20.7f\n",n,t,lower,tight,upper);
    	n=n*2;
    }
    free(h);
}

void createDescending(){
    int n = 500, k, i, v[TEST];
    double t1,t2,t,lower,tight,upper,ta,tb;
    heap *h;
    h = (heap *) malloc(sizeof(heap));
    descending_init(v,TEST);
    printf("%10s%17s%20s%20s%20s\n","n","t(n)","t(n)/n^0.8","t(n)/n","t(n)/n^1.2");
    for(i=0;i<7;i++){
    	t1=microseconds();
    	create_heap(v,n,h);
    	t2=microseconds();
    	t=t2-t1;
    	if (t < 500) {
            ta = microseconds();
            k = 0;
            while (k < 1000){
                descending_init(v,TEST);
                create_heap(v,n,h);
                k++;
            }
            tb = microseconds();
            t1 = tb-ta;
            ta = microseconds();
            k = 0;
            while (k < 1000){
                descending_init(v,TEST);
                k++;
            }
            tb = microseconds();
            t2 = tb-ta;
            t = (t1-t2)/1000;
            printf("(*)");
        }
	tight = t/n;
	upper = t/(pow(n,1.2));
	lower = t/(pow(n,0.8));
    	printf("%10d%17.2f%20.7f%20.7f%20.7f\n",n,t,lower,tight,upper);
    	n=n*2;
    }
    free(h);
}

void test(){
    int a[N];
    printf("Random Initialization\n");
    random_init(a,N);
    print_array(a,N);
    heapsort(a,N);
    print_array(a,N);
    printf("Ordered? %d\n",test_ord(a,N));
    printf("\n");

    printf("Ascending Initialization\n");
    ascending_init(a,N);
    print_array(a,N);
    heapsort(a,N);
    print_array(a,N);
    printf("Ordered? %d\n",test_ord(a,N));
    printf("\n");

    printf("Descending Initialization\n");
    descending_init(a,N);
    print_array(a,N);
    heapsort(a,N);
    print_array(a,N);
    printf("Ordered? %d\n",test_ord(a,N));
    printf("\n");
}

void time1(){
    int n = 500, k, i, v[64000];
    double t1,t2,t,tight,upper,lower,ta,tb;
    random_init(v,TEST);
    printf("Heap Sort with random initialization\n");
    printf("%10s%17s%7s%20s%2s%15s%2s%20s\n","n","t(n)","","t(n)/(n*(log(n))^0.8)","","t(n)/(n*(log(n))^1)","","t(n)/(n*(log(n))^1.2)");
    for(i=0;i<7;i++){
        t1=microseconds();
        heapsort(v,n);
        t2=microseconds();
        t=t2-t1;
        if (t < 500) {
            ta = microseconds();
            k = 0;
            while (k < 1000){
                random_init(v,TEST);
                heapsort(v,n);
                k++;
            }
            tb = microseconds();
            t1 = tb-ta;
            ta = microseconds();
            k = 0;
            while (k < 1000){
                random_init(v,TEST);
                k++;
            }
            tb = microseconds();
            t2 = tb-ta;
            t = (t1-t2)/1000;
            printf("(*)");
        }    
        tight = t/(n*pow(log(n),1));
        upper = t/(n*pow(log(n),1.2));
        lower = t/(n*pow(log(n),0.8));
        printf("%10d%17.2f%20.7f%20.7f%20.7f\n",n,t,lower,tight,upper);
        n=n*2;
    }
}


void time2(){
    int n = 500, k, i, v[TEST];
    double t1,t2,t,tight,upper,lower,ta,tb;
    ascending_init(v,TEST);
    printf("Heap Sort with ascending initialization\n");
    printf("%10s%17s%7s%20s%2s%15s%2s%20s\n","n","t(n)","","t(n)/(n*(log(n))^0.8)","","t(n)/(n*log(n))","","t(n)/(n*(log(n))^1.2)");
    for(i = 0;i < 7;i++){
        t1 = microseconds();
        heapsort(v,n);
        t2 = microseconds();
        t=t2-t1;
        if (t < 500) {
            ta = microseconds();
            k = 0;
            while (k < 1000){
                ascending_init(v,TEST);
                heapsort(v,n);
                k++;
            }
            tb = microseconds();
            t1 = tb-ta;
            ta = microseconds();
            k = 0;
            while (k < 1000){
                ascending_init(v,TEST);
                k++;
            }
            tb = microseconds();
            t2 = tb-ta;
            t = (t1-t2)/1000;
            printf("(*)");
        }    
        tight = t/(n*pow(log(n),1));
        upper = t/(n*pow(log(n),1.2));
        lower = t/(n*pow(log(n),0.8));
        printf("%10d%17.2f%20.7f%20.7f%20.7f\n",n,t,lower,tight,upper);
        n=n*2;
    }
}

void time3(){
    int n = 500, k, i, v[TEST];
    double t1,t2,t,tight,upper,lower,ta,tb;
    descending_init(v,TEST);
    printf("Heap Sort with descending initialization\n");
    printf("%10s%17s%7s%20s%2s%15s%2s%20s\n","n","t(n)","","t(n)/(n*(log(n))^0.8)","","t(n)/(n*(log(n))^1)","","t(n)/(n*(log(n))^1.2)");
    for(i=0;i<7;i++){
        t1=microseconds();
        heapsort(v,n);
        t2=microseconds();
        t=t2-t1;
        if (t < 500) {
            ta = microseconds();
            k = 0;
            while (k < 1000){
                descending_init(v,TEST);
                heapsort(v,n);
                k++;
            }
            tb = microseconds();
            t1 = tb-ta;
            ta = microseconds();
            k = 0;
            while (k < 1000){
                descending_init(v,TEST);
                k++;
            }
            tb = microseconds();
            t2 = tb-ta;
            t = (t1-t2)/1000;
            printf("(*)");
        }    
        tight = t/(n*pow(log(n),1));
        upper = t/(n*pow(log(n),1.2));
        lower = t/(n*pow(log(n),0.8));
        printf("%10d%17.2f%20.7f%20.7f%20.7f\n",n,t,lower,tight,upper);
        n=n*2;
    }
}

int main(){
    init_seed();
    printf("[EXERCISE 1]\n");
    printf("\n");
    testget_min();
    printf("\n");
    testremove_min();
    testCreate();
    printf("[EXERCISE 2]\n");
    printf("\n");
    printf("Check Empirically\n");
    printf("Create with Random Initialization\n");
    createRandom();
    printf("\n");
    printf("Create with Ascending Initialization\n");
    createAscending();
    printf("\n");
    printf("Create with Descending Initialization\n");
    createDescending();
    printf("\n");
    printf("[EXERCISE 3]\n");
    printf("\n");
    test();
    printf("\n");
    printf("[EXERCISE 4]\n");
    time1();
    printf("\n");
    time2();
    printf("\n");
    time3();
    printf("\n");
    
    return 0;
}
