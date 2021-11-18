//
// Created by Yixiao Li on 11/15/21.
//
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"
#define D1 64
#define D2 64
#define D3 64
/*
float solver(const float* coefficients, float x, float err, int size) {
    float derivatives[size];
    float f, df;
    int step = 0;
    derivative_poly(coefficients, derivatives, size);

    while(1) {
        f = value_poly(coefficients, x, size);
        df = value_poly(derivatives, x, size);
        x = x - f / df;
        step ++;
        if (fabs(f) < err) return x;
        else if (step > 1000) return -10;
        else if (fabs(f) > 1e2) return 10;
    }
}
*/
void initialize_random(float* array, const int* size) {
    int m = size[0]; int n = size[1];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++){
            array[i*n + j] = (float) rand() / RAND_MAX;
        }
    }
}

void print_mat(float* mat, const int* size) {
    int m = size[0]; int n = size[1];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++){
            printf("%.4f ", mat[i*n + j]);
        }
        printf("\n");
    }
    printf("\n");
}


void mat_multi_p(const float* mat_s1, const float* mat_s2, float* mat_t, const int* size) {
    // mat_s1 of shape (M, K)
    // mat_s2 of shape (K, N)
    // mat_t  of shape (M, N)

    int M = size[0]; int K = size[1]; int N = size[2];

#pragma omp parallel for num_threads(4)
    for (int i = 0; i < M*N; i++) {
        int m = i / N;
        int n = i % N;
        for (int k = 0; k < K; k++){
            mat_t[m*N + n] = mat_s1[m*N + k] * mat_s2[k*N + n];
        }
    }
}


void mat_multi_c(const float* mat_s1, const float* mat_s2, float* mat_t, const int* size) {
    // mat_s1 of shape (M, K)
    // mat_s2 of shape (K, N)
    // mat_t  of shape (M, N)

    int M = size[0]; int K = size[1]; int N = size[2];
    for (int i = 0; i < M*N; i++) {
        int m = i / N;
        int n = i % N;
        for (int k = 0; k < K; k++){
            mat_t[m*N + n] = mat_s1[m*N + k] * mat_s2[k*N + n];
        }
    }
}
float mat_mse(const float* mat_1, const float* mat_2, const int* size) {
    float err = 0;
    int M = size[0]; int N = size[1];
    for (int i = 0; i < M*N; i++) {
        int m = i / N;
        int n = i % N;
        err += (mat_1[m*N + n] - mat_2[m*N + n])*(mat_1[m*N + n] - mat_2[m*N + n]);
    }
    return err / (float)(M * N);
}

int main(int argc, char* argv[]){
    float A[D1][D2];
    float B[D2][D3];
    float C_p[D1][D3];
    float C_c[D1][D3];

    int a[2] = {D1, D2};
    int b[2] = {D2, D3};
    int c[2] = {D1, D3};
    int size[3] = {D1, D2, D3};

    initialize_random(*A, a);
    initialize_random(*B, b);

    long s1 = clock();
    mat_multi_p(*A, *B, *C_p, size);
    long s2 = clock();
    long time_p = s2 - s1;
    printf("Parallel: %ld\n", time_p);

    //print_mat(*A, a);
    //print_mat(*B, b);
    //print_mat(*C_p, c);

    s1 = clock();
    mat_multi_c(*A, *B, *C_c, size);
    s2 = clock();
    long time_c = s2 - s1;
    printf("Cascade : %ld\n", time_c);

    printf("faster %.2lf\n", (float)time_c / (float)time_p);

    float error = mat_mse(*C_c, *C_p, c);
    printf("MSE %.2lf\n", error);

    //print_mat(*A, a);
    //print_mat(*B, b);
    //print_mat(*C_c, c);
}
