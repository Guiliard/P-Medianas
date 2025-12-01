#include "utils.h"
#include "../calculate/calculate.h"

void *allocate_vector(size_t element_size, size_t count) {
    void *vector = calloc(count, element_size);
    if (vector == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    return vector;
}

float **allocate_matrix(int num_rows, int num_cols)
{
    float **matrix = calloc(num_rows, sizeof(float *));
    if (matrix == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i < num_rows; i++) {
        matrix[i] = calloc(num_cols, sizeof(float));
        if (matrix[i] == NULL) {
            printf("Memory allocation failed\n");
            exit(1);
        }
    }
    return matrix;
}

void print_matrix(int num_rows, int num_cols, float **matrix, char* output_path) {
    FILE* file = fopen(output_path, "w");
    if (file == NULL) {
        printf("Erro ao criar arquivo de matriz: %s\n", output_path);
        return;
    }
    
    fprintf(file, "--- Matriz de Distâncias ---\n");
    fprintf(file, "Dimensões: %d clientes x %d facilidades\n\n", num_rows, num_cols);
    
    for (int i = 0; i < num_rows; i++) {
        fprintf(file, "Cliente %2d: ", i);
        for (int j = 0; j < num_cols; j++) {
            fprintf(file, "%7.2f ", matrix[i][j]);
        }
        fprintf(file, "\n");
    }
    fprintf(file, "\n");
    
    fclose(file);
}

void print_problem(problem *prob) {
    printf("\n========================================\n");
    printf("           DETALHES DO PROBLEMA\n");
    printf("========================================\n");
    printf("Número de Clientes:     %d\n", prob->num_customers);
    printf("Número de Instalações:  %d\n", prob->num_facilities);
    printf("P (instalações a abrir): %d\n", prob->p);
    printf("Melhor custo conhecido: %.2f\n", prob->best_known_cost);
    printf("Tempo de referência:    %.6f segundos\n", prob->reference_time);
    
    printf("\n--- Coordenadas dos Clientes ---\n");
    printf("IDs: [");
    for (int i = 0; i < prob->num_customers; i++) {
        if (i > 0 && i % 15 == 0) printf("\n      ");
        printf("%d%s", prob->customers[i].id, i < prob->num_customers - 1 ? ", " : "");
    }
    printf("]\nX:   [");
    for (int i = 0; i < prob->num_customers; i++) {
        if (i > 0 && i % 15 == 0) printf("\n      ");
        printf("%.2f%s", prob->customers[i].x, i < prob->num_customers - 1 ? ", " : "");
    }
    printf("]\nY:   [");
    for (int i = 0; i < prob->num_customers; i++) {
        if (i > 0 && i % 15 == 0) printf("\n      ");
        printf("%.2f%s", prob->customers[i].y, i < prob->num_customers - 1 ? ", " : "");
    }
    printf("]\n");
    
    printf("\n--- Coordenadas das Instalações ---\n");
    printf("IDs: [");
    for (int i = 0; i < prob->num_facilities; i++) {
        if (i > 0 && i % 15 == 0) printf("\n      ");
        printf("%d%s", prob->facilities[i].id, i < prob->num_facilities - 1 ? ", " : "");
    }
    printf("]\nX:   [");
    for (int i = 0; i < prob->num_facilities; i++) {
        if (i > 0 && i % 15 == 0) printf("\n      ");
        printf("%.2f%s", prob->facilities[i].x, i < prob->num_facilities - 1 ? ", " : "");
    }
    printf("]\nY:   [");
    for (int i = 0; i < prob->num_facilities; i++) {
        if (i > 0 && i % 15 == 0) printf("\n      ");
        printf("%.2f%s", prob->facilities[i].y, i < prob->num_facilities - 1 ? ", " : "");
    }
    printf("]\n========================================\n");
}

void print_solution(solution *sol, int num_facilities, int num_customers) {
    printf("\n--- SOLUÇÃO ENCONTRADA ---\n");
    
    printf("Instalações abertas: [");
    int first = 1;
    int count = 0;
    for (int i = 0; i < num_facilities; i++) {
        if (sol->opened_facilities[i]) {
            if (!first) printf(", ");
            if (count > 0 && count % 15 == 0) printf("\n                      ");
            printf("%d", i);
            first = 0;
            count++;
        }
    }
    printf("]\n");
    
    printf("Atribuições (Cliente → Instalação):\n");
    printf("Cliente:     [");
    for (int i = 0; i < num_customers; i++) {
        if (i > 0 && i % 15 == 0) printf("\n              ");
        printf("%d", i);
        if (i < num_customers - 1) printf(", ");
    }
    printf("]\n");
    printf("Instalação:  [");
    for (int i = 0; i < num_customers; i++) {
        if (i > 0 && i % 15 == 0) printf("\n              ");
        printf("%d", sol->customer_assignments[i]);
        if (i < num_customers - 1) printf(", ");
    }
    printf("]\n");
    
    printf("Custo Total: %.2f\n", sol->total_cost);
    printf("========================================\n");
}

solution* create_empty_solution(int num_facilities, int num_customers) {
    solution* sol = allocate_vector(sizeof(solution), 1);

    sol->opened_facilities = allocate_vector(sizeof(bool), num_facilities);
    sol->customer_assignments = allocate_vector(sizeof(int), num_customers);
    sol->total_cost = 0.0f;

    return sol;
}

solution* copy_solution(solution* sol, int num_facilities, int num_customers) {
    solution* new_sol = create_empty_solution(num_facilities, num_customers);

    memcpy(new_sol->opened_facilities, sol->opened_facilities, sizeof(bool) * num_facilities);
    memcpy(new_sol->customer_assignments, sol->customer_assignments, sizeof(int) * num_customers);
    new_sol->total_cost = sol->total_cost;

    return new_sol;
}

void print_solution_with_gap(solution *sol, int num_facilities, int num_customers, float best_known_cost) {
    print_solution(sol, num_facilities, num_customers);
    
    float gap = calculate_gap(sol->total_cost, best_known_cost);
    printf("GAP: %.2f%%\n", gap);
    printf("========================================\n");
}

void free_solution(solution* sol) {
    free(sol->opened_facilities);
    free(sol->customer_assignments);
    free(sol);
}

void free_problem(problem* prob) {
    free(prob->customers);
    free(prob->facilities);
    
    for (int i = 0; i < prob->num_customers; i++) {
        free(prob->distance_matrix[i]);
    }
    free(prob->distance_matrix);
    
    free(prob);
}