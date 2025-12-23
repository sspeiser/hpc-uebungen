#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define N 5000

void printTemp(int iteration, double temp[N+2]) {
    printf("%4d  |  ", iteration);
    for(int i = 0; i < N + 2; i++) {
        printf("%5.2f ", temp[i]);
    }
    printf("\n");
}

int main() {
    double temp[N + 2];
    double newtemp[N + 2];
    temp[0] = 20.0;
    temp[N + 1] = 0.0;

    printTemp(0, temp);

    double delta = 0.0;
    int iteration = 1;
    do {
        delta = 0.0;
        for(int i = 1; i <= N; i++) {
            newtemp[i] = (temp[i-1] + temp[i] + temp[i+1]) / 3.0;
        }
        for(int i = 1; i <= N; i++) {
            delta += fabs(newtemp[i] - temp[i]); 
            temp[i] = newtemp[i];
        }
        printTemp(iteration, temp);
        iteration++;
    } while(delta >= 0.00000001);
}
