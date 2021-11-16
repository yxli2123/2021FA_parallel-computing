//
// Created by Yixiao Li on 11/16/21.
//

#ifndef PARALLEL_COMPUTING_UTILS_H
#define PARALLEL_COMPUTING_UTILS_H

#endif //PARALLEL_COMPUTING_UTILS_H


void initialize_random(double* array, int size);
void initialize_zeros(double* array, int size);
void initialize_ones(double* array, int size);
void arr_cp(const double* source, double* target, int size);
double value_poly(const double* array, double x, int size);
void derivative_poly(const double* source, double* derivative, int size);
void arr_print(const double* array, int size);
