//
// Created by Yixiao Li on 11/15/21.
//
#include "stdio.h"
#include "math.h"
#include "omp.h"
#include "utils.h"
#include "time.h"

#define STEP_OUT -10    // indicates the iteration steps is more than the given
#define VALUE_OUT 10    // indicates no solutions
#define SIZE_C 5        // array size of the polynomial coefficients
#define SIZE_S 100      // array size of the candidate solutions
#define ERR 1e-5        //

double solver(const double* coefficients, double x, double err, int size) {
    double derivatives[size];
    double f, df;
    int step = 0;
    derivative_poly(coefficients, derivatives, size);

    while(1) {
        f = value_poly(coefficients, x, size);
        df = value_poly(derivatives, x, size);
        x = x - f / df;
        step ++;
        if (fabs(f) < err) return x;
        else if (step > 1000) return STEP_OUT;
        else if (fabs(f) > 1e2) return VALUE_OUT;
    }
}


int main(int argc, char* argv[]){

    printf("%lf\n", pow_(2, 3));

    double coefficients[SIZE_C];
    double solutions_init[SIZE_S];
    double solutions[SIZE_S];
    long t_s, t_e;

    initialize_random(coefficients, SIZE_C);
    initialize_zeros(solutions, SIZE_S);
    initialize_random(solutions_init, SIZE_S);
    operate(solutions_init, '*', 2.0, SIZE_S);

    t_s = clock();
    for (int i = 0; i < SIZE_S; i++) {
        solutions[i] = solver(coefficients, solutions[i], ERR, SIZE_C);
    }
    t_e = clock();
    printf("Cascade: %ld\n", t_e - t_s);

    t_s = clock();
#pragma opm parallel for default(none)
    for (int i = 0; i < SIZE_S; i++) {
        solutions[i] = solver(coefficients, solutions[i], ERR, SIZE_C);
    }
    t_e = clock();
    printf("Cascade: %ld\n", t_e - t_s);
}
