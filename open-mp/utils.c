//
// Created by Yixiao Li on 11/16/21.
//

#include "utils.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"


/* array utils */
void initialize_random(double* array, int size) {
    for (int i = 0; i < size; i++) {
        array[i] = (double)(RAND_MAX - 2 * rand()) / (2 * RAND_MAX);
    }
}

void initialize_zeros(double* array, int size) {
    for (int i = 0; i < size; i++) {
        array[i] = 0.0;
    }
}

void initialize_ones(double* array, int size) {
    for (int i = 0; i < size; i++) {
        array[i] = 1.0;
    }
}

void arr_cp(const double* source, double* target, int size) {
    for (int i = 0; i < size; i++) {
        target[i] = source[i];
    }
}

void arr_print(const double* array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%.4lf ", array[i]);
    }
    printf("\n");
}


/* math utils */
double value_poly(const double* array, double x, int size) {
    double value = 0;
    for (int i = 1; i < size - 1; i++) {
        value += array[i] * pow(x, i);
    }
    return value;
}

void derivative_poly(const double* source, double* derivative, int size) {
    for (int i = 1; i < size - 1; i++) {
        derivative[i-1] = i * source[i];
    }
    derivative[size-1] = 0;
}
