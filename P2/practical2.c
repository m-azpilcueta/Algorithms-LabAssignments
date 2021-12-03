/*
    Author 1: Javier Escribano Salgado (javier.escribano)
    Author 2: Martín Azpilcueta Rabuñal (m.azpilcueta)
    Practical 2
    Group 6.1
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <math.h>


void int_sort (int v[], int n){
	int x,j,i;
	for(i = 1;i < n; i++){
		x = v[i];
		j = i-1;
		while((j >= 0) && (v[j] > x)){
			v[j+1] = v[j];
			j = j-1;
		}
		v[j+1] = x;
	}
}

void shell_sort (int v[], int n){
	int increment = n,tmp,j,keepgoing,i;
	while(increment != 1){
		increment = increment/2;
		for(i = increment;i < n;i++){
			tmp = v[i];
			j = i;
			keepgoing = 1;
			while((j - increment >= 0) & (keepgoing)){
				if(tmp < v[j-increment]){
					v[j] = v[j-increment];
					j = j - increment;
				}
				else{
					keepgoing = 0;
				}
			}
			v[j] = tmp;
		}
	}
}

void init_seed() {
	srand(time(NULL));
}


void random_init(int v [], int n) { /* we generate pseudorandom numbers between -n and +n */
	int i, m = 2*n+1;
	for (i = 0; i < n; i++)
	v[i] = (rand() % m) - n;
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

double microseconds() { /* obtains the system time in microseconds */
    struct timeval t;
        if (gettimeofday(&t, NULL) < 0 ){
            return 0.0;
        }
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

int test_ord(int v[], int n){ // Checks if the array is ascending 
	int i;

	for(i = 0; i < n;i++){
		if(v[i]<=v[i+1]){
			continue;
		}
		else return 0;
		break;
	}
	return 1;
}

void test1(){
	int v[17];
	random_init(v,17);
	printf("Random initialization\n");
	print_array(v,17);
	printf("Ordered? %d\n",test_ord(v,17));
	printf("\n");

	printf("Insertion Sort\n");
	int_sort(v,17);
	print_array(v,17);
	printf("Ordered? %d\n",test_ord(v,17));
	printf("\n");

	descending_init(v,17);
	printf("Descending initialization\n");
	print_array(v,17);
	printf("Ordered? %d\n",test_ord(v,17));
	printf("\n");

	printf("Insertion sort\n");
	int_sort(v,17);
	print_array(v,17);
	printf("Ordered? %d\n",test_ord(v,17));
	printf("\n");

	ascending_init(v,17);
	printf("Ascending initialization\n");
	print_array(v,17);
	printf("Ordered? %d\n",test_ord(v,17));
	printf("\n");

	printf("Insertion sort\n");
	int_sort(v,17);
	print_array(v,17);
	printf("Ordered? %d\n",test_ord(v,17));
}

void test2(){
	int v[17];
	random_init(v,17);
	printf("Random initialization\n");
	print_array(v,17);
	printf("Ordered? %d\n",test_ord(v,17));
	printf("\n");

	printf("Shell Sort\n");
	shell_sort(v,17);
	print_array(v,17);
	printf("Ordered? %d\n",test_ord(v,17));
	printf("\n");

	descending_init(v,17);
	printf("Descending initialization\n");
	print_array(v,17);
	printf("Ordered? %d\n",test_ord(v,17));
	printf("\n");

	printf("Shell sort\n");
	shell_sort(v,17);
	print_array(v,17);
	printf("Ordered? %d\n",test_ord(v,17));
	printf("\n");

	ascending_init(v,17);
	printf("Ascending initialization\n");
	print_array(v,17);
	printf("Ordered? %d\n",test_ord(v,17));
	printf("\n");

	printf("Shell sort\n");
	shell_sort(v,17);
	print_array(v,17);
	printf("Ordered? %d\n",test_ord(v,17));
}

void time1(){
	int n = 500, k, i, v[32000];
	double t1,t2,t,pow2,pow1_8,pow2_2,ta,tb;
	random_init(v,32000);
	printf("Insertion Sort with random initialization\n");
    printf("%10s%17s%20s%20s%20s\n","n","t(n)","t(n)/n^1.8","t(n)/n^2","t(n)/n^2.2");
    for(i=0;i<7;i++){
    	t1=microseconds();
    	int_sort(v,n);
    	t2=microseconds();
    	t=t2-t1;
    	if (t < 500) {
            ta = microseconds();
            k = 0;
            while (k < 1000){
                random_init(v,32000);
                int_sort(v,n);
                k++;
            }
            tb = microseconds();
            t1 = tb-ta;
            ta = microseconds();
            k = 0;
            while (k < 1000){
                random_init(v,32000);
                k++;
            }
            tb = microseconds();
            t2 = tb-ta;
            t = (t1-t2)/1000;
            printf("(*)");
        }
    	pow2=t/(pow(n,2));
    	pow1_8=t/(pow(n,1.8));
    	pow2_2=t/(pow(n,2.2));
    	printf("%10d%17.2f%20.7f%20.7f%20.7f\n",n,t,pow1_8,pow2,pow2_2);
    	n=n*2;
    }
}

void time2(){
	int n = 500, k, i, v[32000];
	double t1,t2,t,lower,tight,upper,ta,tb;
	ascending_init(v,32000);
	printf("Insertion Sort with ascending initialization\n");
    printf("%10s%17s%20s%20s%20s\n","n","t(n)","t(n)/n^0.8","t(n)/n","t(n)/n^1.2");
    for(i=0;i<7;i++){
    	t1=microseconds();
    	int_sort(v,n);
    	t2=microseconds();
    	t=t2-t1;
    	if (t < 500) {
            ta = microseconds();
            k = 0;
            while (k < 1000){
                ascending_init(v,32000);
                int_sort(v,n);
                k++;
            }
            tb = microseconds();
            t1 = tb-ta;
            ta = microseconds();
            k = 0;
            while (k < 1000){
                ascending_init(v,32000);
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
}

void time3(){
	int n = 500, k, i, v[32000];
	double t1,t2,t,pow2,pow1_8,pow2_2,ta,tb;
	descending_init(v,32000);
	printf("Insertion Sort with descending initialization\n");
    printf("%10s%17s%20s%20s%20s\n","n","t(n)","t(n)/n^1.8","t(n)/n^2","t(n)/n^2.2");
    for(i=0;i<7;i++){
    	t1=microseconds();
    	int_sort(v,n);
    	t2=microseconds();
    	t=t2-t1;
    	if (t < 500) {
            ta = microseconds();
            k = 0;
            while (k < 1000){
                descending_init(v,32000);
                int_sort(v,n);
                k++;
            }
            tb = microseconds();
            t1 = tb-ta;
            ta = microseconds();
            k = 0;
            while (k < 1000){
                descending_init(v,32000);
                k++;
            }
            tb = microseconds();
            t2 = tb-ta;
            t = (t1-t2)/1000;
            printf("(*)");
        }
    	pow2=t/(pow(n,2));
    	pow1_8=t/(pow(n,1.8));
    	pow2_2=t/(pow(n,2.2));
    	printf("%10d%17.2f%20.7f%20.7f%20.7f\n",n,t,pow1_8,pow2,pow2_2);
    	n=n*2;
    }
}

void time4(){
	int n = 500, k, i, v[32000];
	double t1,t2,t,tight,upper,lower,ta,tb;
	random_init(v,32000);
	printf("Shell Sort with random initialization\n");
    printf("%10s%17s%7s%20s%2s%15s%2s%20s\n","n","t(n)","","t(n)/(n*(log(n))^1.8)","","t(n)/(n*(log(n))^2)","","t(n)/(n*(log(n))^2.2)");
    for(i=0;i<7;i++){
    	t1=microseconds();
    	shell_sort(v,n);
    	t2=microseconds();
    	t=t2-t1;
    	if (t < 500) {
            ta = microseconds();
            k = 0;
            while (k < 1000){
                random_init(v,32000);
                shell_sort(v,n);
                k++;
            }
            tb = microseconds();
            t1 = tb-ta;
            ta = microseconds();
            k = 0;
            while (k < 1000){
                random_init(v,32000);
                k++;
            }
            tb = microseconds();
            t2 = tb-ta;
            t = (t1-t2)/1000;
            printf("(*)");
        }    
    	tight = t/(n*pow(log(n),2));
        upper = t/(n*pow(log(n),2.2));
        lower = t/(n*pow(log(n),1.8));
    	printf("%10d%17.2f%20.7f%20.7f%20.7f\n",n,t,lower,tight,upper);
    	n=n*2;
    }
}


void time5(){
	int n = 500, k, i, v[32000];
	double t1,t2,t,tight,upper,lower,ta,tb;
	ascending_init(v,32000);
	printf("Shell Sort with ascending initialization\n");
    printf("%10s%17s%7s%20s%2s%15s%2s%20s\n","n","t(n)","","t(n)/(n*(log(n))^0.8)","","t(n)/(n*log(n))","","t(n)/(n*(log(n))^1.2)");
    for(i = 0;i < 7;i++){
    	t1 = microseconds();
    	shell_sort(v,n);
    	t2 = microseconds();
    	t=t2-t1;
    	if (t < 500) {
            ta = microseconds();
            k = 0;
            while (k < 1000){
                ascending_init(v,32000);
                shell_sort(v,n);
                k++;
            }
            tb = microseconds();
            t1 = tb-ta;
            ta = microseconds();
            k = 0;
            while (k < 1000){
                ascending_init(v,32000);
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

void time6(){
	int n = 500, k, i, v[32000];
	double t1,t2,t,tight,upper,lower,ta,tb;
	descending_init(v,32000);
	printf("Shell Sort with descending initialization\n");
   	printf("%10s%17s%7s%20s%2s%15s%2s%20s\n","n","t(n)","","t(n)/(n*(log(n))^1.8)","","t(n)/(n*(log(n))^2)","","t(n)/(n*(log(n))^2.2)");
    for(i=0;i<7;i++){
    	t1=microseconds();
    	shell_sort(v,n);
    	t2=microseconds();
    	t=t2-t1;
    	if (t < 500) {
            ta = microseconds();
            k = 0;
            while (k < 1000){
                descending_init(v,32000);
                shell_sort(v,n);
                k++;
            }
            tb = microseconds();
            t1 = tb-ta;
            ta = microseconds();
            k = 0;
            while (k < 1000){
                descending_init(v,32000);
                k++;
            }
            tb = microseconds();
            t2 = tb-ta;
            t = (t1-t2)/1000;
            printf("(*)");
        }    
        tight = t/(n*pow(log(n),2));
        upper = t/(n*pow(log(n),2.2));
        lower = t/(n*pow(log(n),1.8));
    	printf("%10d%17.2f%20.7f%20.7f%20.7f\n",n,t,lower,tight,upper);
    	n=n*2;
    }
}


int main(){
	init_seed();
	test1();
	printf("\n");
	printf("\n");
	test2();
	printf("\n");
	time1();
	printf("\n");
	time2();
	printf("\n");
	time3();
	printf("\n");
	time4();
	printf("\n");
	time5();
	printf("\n");
	time6();
	return 0;
}
