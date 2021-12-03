/*
    Author 1: Javier Escribano Salgado (javier.escribano)
    Author 2: Martín Azpilcueta Rabuñal (m.azpilcueta)
    Practical 1
    Group 6.1
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <math.h>

int maxSubSum1(int v[], int n) {
    int i,j;
    int thisSum, maxSum = 0;
    for (i = 0; i < n; i++) {
        thisSum = 0;
        for (j = i; j < n; j++) {
            thisSum += v[j];
            if (thisSum > maxSum) {
                maxSum = thisSum;
            }
        }
    }
    return maxSum;
}


int maxSubSum2 (int v[], int n) {
    int j;
    int thisSum = 0, maxSum = 0;
    for (j = 0; j < n; j++) {
        thisSum = thisSum + v[j];
        if (thisSum > maxSum) {
            maxSum = thisSum;            
        }
        else if (thisSum < 0) {
            thisSum = 0;
        }
    }
    return maxSum;
}

void print_array (int v [], int n) {
    int i;
    printf("[");
    for (i = 0; i < n; i++) {
        printf(" %2d ",v[i]);
    }
    printf("]");
}

void init_seed() {
    srand(time(NULL));
    /* set the seed of a new sequence of pseudo-random integers */
}

void random_init(int v [], int n) {
    int i, m = 2*n+1;
    for (i=0; i < n; i++)
    v[i] = (rand() % m) - n;
    /* generate pseudo-random numbers between -n and +n */
}

double microseconds() { /* obtains the system time in microseconds */
    struct timeval t;
        if (gettimeofday(&t, NULL) < 0 ){
            return 0.0;
        }
    return (t.tv_usec + t.tv_sec * 1000000.0);
}


void test_1 () {
    int v [6][5] = 
    {
        {-9, 2, -5, -4, 6},
        {4, 0, 9, 2, 5},
        {-2, -1, -9, -7, -1},
        {9, -2, 1, -7, -8},
        {15, -2, -5, -4, 16},
        {7, -5, 6, 7, -7},

    };
    int a, b, i; 
    printf("test 1\n");
    printf("%s%15s%15s\n", "", "maxSubSum1", "maxSubSum2");
    for (i = 0; i < 6; i++) {
        a = maxSubSum1(v[i],5);
        b = maxSubSum2(v[i],5);
        printf("%15d%15d\n", a, b); 
    }
     
}

void test_2 () {
    int i, a, b;
    int v[9];
    printf("test 2\n");
    printf("%40s%15s%15s\n", "", "maxSubSum1", "maxSubSum2");
    for (i = 0; i < 10; i++) {
        random_init(v,9);
        print_array(v,9);
        a = maxSubSum1(v,9);
        b = maxSubSum2(v,9);
        printf("%15d%15d\n", a, b);
    }

}


void time_1(){
    int k,n=500;
    int v[32000];
    double t1,t2,t,ta,tb,nsquared,npow1_8,npow2_2;
    random_init(v,32000);
    printf("maxSubSum1\n");
    printf("%10s%17s%20s%20s%20s\n","n","t(n)","t(n)/n^1.8","t(n)/n^2","t(n)/n^2.2"); 
    for(int i=0;i<7;i++){
        t1 = microseconds();
        maxSubSum1(v,n);
        t2 = microseconds();
        t = t2-t1;
        if (t < 500) {
            ta = microseconds();
            k = 0;
            while (k < 1000){
                random_init(v,32000);
                maxSubSum1(v,n);
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
        nsquared = t/pow(n,2);
        npow1_8 = t/pow(n,1.8);
        npow2_2 = t/pow(n,2.2);
        printf("%10d%17.2f%20.7f%20.7f%20.7f\n",n,t,npow1_8,nsquared,npow2_2);
        n*=2;
    }
}

void time_2(){
    int k, n=500;
    int v[32000];
    double t1,t2,t,ta,tb,divn,npow0_8,npow1_2;
    random_init(v,32000);
    printf("maxSubSum2\n");
    printf("%10s%17s%20s%20s%20s\n","n","t(n)","t(n)/n^0.8","t(n)/n","t(n)/n^1.2");
    for(int i=0;i<7;i++){
        t1 = microseconds();
        maxSubSum2(v,n);
        t2 = microseconds();
        t = t2-t1;
        if (t < 500) {
            ta = microseconds();
            k = 0;
            while (k < 1000){
                random_init(v,32000);
                maxSubSum2(v,n);
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
            printf("%3s","(*)"); 
        }
        divn = t/n;
        npow0_8 = t/pow(n,0.8);
        npow1_2 = t/pow(n,1.2);
        printf("%7d%17.2f%20.7f%20.7f%20.7f\n",n,t,npow0_8,divn,npow1_2);
        n*=2;
    }   
}


int main() {
    init_seed();
    test_1();
    printf("\n");
    test_2();
    printf("\n");
    time_1();
    printf("\n");
    time_2();
    return 0;
}