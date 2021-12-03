/*
    Practical 4
    Javier Escribano Salgado (javier.escribano)
    Martín Azpilcueta Rabuñal (m.azpilcueta)
    Group 6.1
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <math.h>

#define MAX_SIZE 1000
#define EX1 5
#define EX2 4
#define N 8

typedef int ** matrix;

matrix createMatrix(int n) {
    int i;
    matrix aux;
    if ((aux = malloc(n*sizeof(int *))) == NULL)
        return NULL;
    for (i=0; i<n; i++)
        if ((aux[i] = malloc(n*sizeof(int))) == NULL)
            return NULL;
    return aux;
}

double microseconds() { /* obtains the system time in microseconds */
    struct timeval t;
        if (gettimeofday(&t, NULL) < 0 ){
            return 0.0;
        }
    return (t.tv_usec + t.tv_sec * 1000000.0);
}


/* Pseudorandom initialization [1..MAX_SIZE] of a complete undirected graph
with n nodes, represented by its adjacency matrix */
void initMatrix(matrix m, int n) {
    int i, j;
    for (i=0; i<n; i++)
        for (j=i+1; j<n; j++)
            m[i][j] = rand() % MAX_SIZE + 1;
    for (i=0; i<n; i++)
        for (j=0; j<=i; j++)
            if (i==j)
                m[i][j] = 0;
            else
                m[i][j] = m[j][i];
}

void freeMatrix(matrix m, int n) {
    int i;
    for (i=0; i<n; i++)
        free(m[i]);
    free(m);
}

void print_matrix(matrix matrix, int sz){
    for (int i = 0; i < sz; i++){
        printf("[ ");
        for (int j = 0; j < sz; j++){
            printf("%3d  ",matrix[i][j]);
        }
        printf("]\n");
    }
}

int minDistance(int *distances, int *unvisited,int sz){
    int min = INT_MAX, min_index;
    for (int i = 0; i < sz; i++){
        if(unvisited[i] && distances[i] <= min){
            min = distances[i];
            min_index = i;
        }
    }
    return min_index;
}

void dijkstra(matrix graph, matrix distances, int sz) {
    int n, i, v = 0;
    int *unvisited = malloc(sz*sizeof(int));
    for (n=0; n<sz; n++) {
        for (i=0; i<sz; i++) {
            unvisited[i] = 1;
            distances[n][i] = graph[n][i];
        }
        for (int count = 0; count < sz - 1; count++){
            v = minDistance(distances[n],unvisited,sz);
            unvisited[v] = 0;
            for (int w = 0; w < sz ; w++){
                if (distances[n][w] > distances[n][v] + graph[v][w]){
                    distances[n][w] = distances[n][v] + graph[v][w];
                }
            }
        }
    }
    free(unvisited);
}

void test1(){
    matrix m = createMatrix(EX1);
    matrix d = createMatrix(EX1);
    int array[EX1*EX1] = {
            0,1,8,4,7,
            1,0,2,6,5,
            8,2,0,9,5,
            4,6,9,0,3,
            7,5,5,3,0
    };
    for (int i = 0; i < EX1; i++){
        for(int j = 0; j < EX1; j++){
            m[i][j] = array[EX1*i + j];
        }
    }
    print_matrix(m,EX1);
    dijkstra(m,d,EX1);
    printf("\n");
    printf("Minimum distances\n");
    print_matrix(d,EX1);
    freeMatrix(m,EX1);
    freeMatrix(d,EX1);
}

void test2(){
    matrix m = createMatrix(EX2);
    matrix d = createMatrix(EX2);
    int array[EX1*EX1] = {
            0,1,4,7,
            1,0,2,8,
            4,2,0,3,
            7,8,3,0
    };
    for (int i = 0; i < EX2; i++){
        for(int j = 0; j < EX2; j++){
            m[i][j] = array[EX2*i + j];
        }
    }
    print_matrix(m,EX2);
    dijkstra(m,d,EX2);
    printf("\n");
    printf("Minimum distances\n");
    print_matrix(d,EX2);
    freeMatrix(m,EX2);
    freeMatrix(d,EX2);
}


void test3(){
    matrix m,d;
    m = createMatrix(EX1);
    initMatrix(m,EX1);
    print_matrix(m,EX1);
    d = createMatrix(EX1);
    dijkstra(m,d,EX1);
    printf("\n");
    printf("Minimum Distances\n");
    print_matrix(d,EX1);
    freeMatrix(m,EX1);
    freeMatrix(d,EX1);
}

double under500(matrix m, matrix d, int n){
    int k = 0;
    double ta, tb, t1, t2, tt;
    ta = microseconds();
    while (k < 1000){
        initMatrix(m,n);
        dijkstra(m,d,n);
        k++;
    }
    tb = microseconds();
    t1 = tb - ta;
    ta = microseconds();
    k = 0;
    while (k < 1000){
        initMatrix(m,n);
        k++;
    }
    tb = microseconds();
    t2 = tb - ta;
    tt = (t1-t2)/1000;
    return tt;
}

void time1(){
    matrix d, m;
    int n = N;
    double t1, t2, t, under, over, tight;
    printf("%10s%17s%20s%20s%20s\n","n","t(n)","n/t(n)^2.5","n/t(n)^2.95","n/t(n)^3.4");
    for(int i = 0; i < 7; i++){
        m = createMatrix(n);
        d = createMatrix(MAX_SIZE);
        initMatrix(m,n);
        t1 = microseconds();
        dijkstra(d,m,n);
        t2 = microseconds();
        t = t2-t1;
        if (t < 500){
            t = under500(m,d,n);
            printf("(*)");
        }
        tight = t/(pow(n,2.95));
        under = t/(pow(n,2.5));
        over = t/(pow(n,3.4));
        printf("%8d%17.2f%20.7f%20.7f%20.7f\n",n,t,under,tight,over);
        freeMatrix(m,n);
        freeMatrix(d,n);
        n = n*2;
    }
}

int main() {
    printf("Test Figure 2\n");
    test1();
    printf("\n");
    printf("Test Figure 3\n");
    test2();
    printf("\n");
    printf("Test Random Graph\n");
    test3();
    printf("\n");
    printf("Time Complexity\n");
    time1();
    return 0;
}