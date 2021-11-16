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
        array[i] = (double) rand() / RAND_MAX;
    }
    operate(array, '*', 2, size);
    operate(array, '-', 1, size);
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

int find_duplicate(const double* array, double element, int size) {
    for (int i = 0; i < size; i++) {
        if (fabs(element - array[i]) < 1e-5) return 1;
    }
    return 0;
}

/* math utils */
double pow_(double x, int n) {
    double ans = x;
    for (int i = 0; i < n; i++) {
        ans *= x;
    }
}

double value_poly(const double* array, double x, int size) {
    double value = 0;
    for (int i = 1; i < size - 1; i++) {
        value += array[i] * pow_(x, i);
    }
    return value;
}

void derivative_poly(const double* source, double* derivative, int size) {
    for (int i = 1; i < size - 1; i++) {
        derivative[i-1] = i * source[i];
    }
    derivative[size-1] = 0;
}

void operate(double* array, char operator, double scale, int size) {
    for (int i = 0; i < size; i ++) {
        switch (operator) {
            case '+': {
                array[i] += scale;
                break;
            }
            case '-': {
                array[i] -= scale;
                break;
            }
            case '/': {
                array[i] /= scale;
                break;
            }
            case '*': {
                array[i] *= scale;
                break;
            }
            default: {
                array[i] = pow_(array[i], scale);
            }
        }
    }
}
