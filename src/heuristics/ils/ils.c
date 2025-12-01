#include "ils.h"

#include "ils.h"

solution* ils(problem* prob, int ils_max) {
    srand(time(NULL));

    solution* initial_solution = create_initial_solution_ils(prob);
    solution* current_solution = copy_solution(initial_solution, prob->num_facilities, prob->num_customers);
    local_search(prob, current_solution);
    
    int iter = 0;
    int best_iter = 0;
    int level = 1;
    
    while ((iter - best_iter) < ils_max) {
        iter++;
        
        solution* perturbed_solution = copy_solution(current_solution, prob->num_facilities, prob->num_customers);
        perturbation(prob, perturbed_solution, level);
        
        solution* improved_solution = copy_solution(perturbed_solution, prob->num_facilities, prob->num_customers);
        local_search(prob, improved_solution);
        
        if (improved_solution->total_cost < current_solution->total_cost) {
            free_solution(current_solution);
            current_solution = copy_solution(improved_solution, prob->num_facilities, prob->num_customers);
            best_iter = iter;
            level = 1;
            
            if (current_solution->total_cost <= prob->best_known_cost) {
                free_solution(perturbed_solution);
                free_solution(improved_solution);
                return current_solution;
            }
        } else {
            level++;
        }
        
        free_solution(perturbed_solution);
        free_solution(improved_solution);
    }
    
    free_solution(initial_solution);
    
    return current_solution;
}

solution* smart_ils(problem* prob, int ils_max, int vezes_max) {
    srand(time(NULL));

    solution* initial_solution = create_initial_solution_ils(prob);
    solution* current_solution = copy_solution(initial_solution, prob->num_facilities, prob->num_customers);
    local_search(prob, current_solution);
    
    int iter = 0;
    int best_iter = 0;
    int level = 1;
    int nvezes = 1;
    
    while ((iter - best_iter) < ils_max) {
        iter++;
        
        solution* perturbed_solution = copy_solution(current_solution, prob->num_facilities, prob->num_customers);
        perturbation(prob, perturbed_solution, level);
        
        solution* improved_solution = copy_solution(perturbed_solution, prob->num_facilities, prob->num_customers);
        local_search(prob, improved_solution);
        
        if (improved_solution->total_cost < current_solution->total_cost) {
            free_solution(current_solution);
            current_solution = copy_solution(improved_solution, prob->num_facilities, prob->num_customers);
            best_iter = iter;
            level = 1;
            nvezes = 1;

            if (current_solution->total_cost <= prob->best_known_cost) {
                free_solution(perturbed_solution);
                free_solution(improved_solution);
                return current_solution;
            }
        } else {
            if (nvezes >= vezes_max) {
                level++;
                nvezes = 1;
            } else {
                nvezes++;
            }
        }
        
        free_solution(perturbed_solution);
        free_solution(improved_solution);
    }
    
    free_solution(initial_solution);
    
    return current_solution;
}

solution* create_initial_solution_ils(problem* prob) {
    solution* sol = create_empty_solution(prob->num_facilities, prob->num_customers);
    
    int facilities_opened = 0;
    
    while (facilities_opened < prob->p) {
        int random_facility = rand() % prob->num_facilities;
        
        if (!sol->opened_facilities[random_facility]) {
            sol->opened_facilities[random_facility] = true;
            facilities_opened++;
        }
    }
    
    assign_customers_to_nearest_facility(prob, sol);
    
    return sol;
}

void perturbation(problem* prob, solution* sol, int level) {
    int num_modifications = level + 1;
    
    for (int count = 0; count < num_modifications; count++) {
        int* opened = allocate_vector(sizeof(int), prob->num_facilities);
        int* closed = allocate_vector(sizeof(int), prob->num_facilities);
        int num_opened = 0, num_closed = 0;
        
        for (int i = 0; i < prob->num_facilities; i++) {
            if (sol->opened_facilities[i]) {
                opened[num_opened++] = i;
            } else {
                closed[num_closed++] = i;
            }
        }
        
        if (num_opened > 0 && num_closed > 0) {
            int idx_opened = rand() % num_opened;
            int idx_closed = rand() % num_closed;
            
            int facility_to_close = opened[idx_opened];
            int facility_to_open = closed[idx_closed];
            
            sol->opened_facilities[facility_to_close] = false;
            sol->opened_facilities[facility_to_open] = true;
        }
        
        free(opened);
        free(closed);
    }
    
    assign_customers_to_nearest_facility(prob, sol);
}