#ifndef UTILS_H
#define UTILS_H

#include "libs.h"

#define max(x,y) ((x)<(y) ? (y) : (x))
#define min(x,y) ((x)>(y) ? (y) : (x))

#define INT_MAX __INT_MAX__
#define FLT_MAX	__FLT_MAX__

#define MAX_ITER 15
#define ALPHA 0.3f
#define LIMIT 5

typedef struct customer {
    int id;
    float x;
    float y;
} customer;

typedef struct facility {
    int id;
    float x;
    float y;
} facility;

typedef struct problem {
    customer* customers;
    facility* facilities;
    float** distance_matrix;
    int num_customers;
    int num_facilities;
    int p;
    float best_known_cost;
    float reference_time;
} problem;

typedef struct solution {
    bool* opened_facilities;
    int* customer_assignments;
    float total_cost;
} solution;

void *allocate_vector(size_t element_size, size_t count);
float **allocate_matrix(int num_rows, int num_cols);

void print_matrix(int num_rows, int num_cols, float **matrix, char* output_path);
void print_problem(problem *prob);
void print_solution(solution *sol, int num_facilities, int num_customers);
void print_solution_with_gap(solution *sol, int num_facilities, int num_customers, float best_known_cost);

solution* create_empty_solution(int num_facilities, int num_customers);
solution* copy_solution(solution* sol, int num_facilities, int num_customers);

void free_solution(solution* sol);
void free_problem(problem* prob);

#endif