//
// Created by Yixiao Li on 11/15/21.
//
#include "stdio.h"
#include "math.h"
#include "omp.h"
#include "utils.h"

#define STEP_OUT -10
#define VALUE_OUT 10

double solver(const double* coefficients, double x, double eff, int size) {
    double derivatives[size];
    double f, df;
    int step = 0;
    derivative_poly(coefficients, derivatives, size);

    while(1) {
        f = value_poly(coefficients, x, size);
        df = value_poly(derivatives, x, size);
        x = x - f / df;
        step ++;
        if (fabs(f) < eff) return x;
        else if (step > 1000) return STEP_OUT;
        else if (fabs(f) > 1e2) return VALUE_OUT;
    }
}


int main(int argc, char* argv[]){

}
