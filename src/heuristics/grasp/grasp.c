#include "grasp.h"

solution* grasp(problem* prob, int grasp_max, float alpha) {
    srand(time(NULL));
    
    solution* best_solution = create_empty_solution(prob->num_facilities, prob->num_customers);
    best_solution->total_cost = FLT_MAX;
    
    for (int iter = 0; iter < grasp_max; iter++) {
        solution* current_solution = create_initial_solution_grasp(prob, alpha);
        local_search(prob, current_solution);
        if (current_solution->total_cost < best_solution->total_cost) {
            free_solution(best_solution);
            best_solution = current_solution;
            
            if (best_solution->total_cost <= prob->best_known_cost) {
                return best_solution;
            }
        } else {
            free_solution(current_solution);
        }
    }
    return best_solution;
}

solution* filtered_grasp(problem* prob, int grasp_max, float alpha, int filter_k) {
    srand(time(NULL));
    
    solution* best_solution = create_empty_solution(prob->num_facilities, prob->num_customers);
    best_solution->total_cost = FLT_MAX;
    
    float* recent_costs = NULL;
    int cost_index = 0;
    float cost_sum = 0.0;
    int costs_count = 0;
    
    if (filter_k > 0) {
        recent_costs = allocate_vector(sizeof(float), filter_k);
        for (int i = 0; i < filter_k; i++) {
            recent_costs[i] = FLT_MAX;
        }
    }
    
    for (int iter = 0; iter < grasp_max; iter++) {
        solution* constructed_solution = create_initial_solution_grasp(prob, alpha);
        float construction_cost = constructed_solution->total_cost;
        
        int passed_filter = 1;
        
        if (filter_k > 0 && costs_count > 0) {
            float average_cost = cost_sum / costs_count;
            float threshold = average_cost * 0.95;
            
            if (construction_cost > threshold) {
                passed_filter = 0;
            }
        }
        
        if (passed_filter) {
            local_search(prob, constructed_solution);
            
            if (filter_k > 0) {
                if (costs_count < filter_k) {
                    cost_sum += construction_cost;
                    recent_costs[cost_index] = construction_cost;
                    cost_index = (cost_index + 1) % filter_k;
                    costs_count++;
                } else {
                    cost_sum -= recent_costs[cost_index];
                    cost_sum += construction_cost;
                    recent_costs[cost_index] = construction_cost;
                    cost_index = (cost_index + 1) % filter_k;
                }
            }
            
            if (constructed_solution->total_cost < best_solution->total_cost) {
                free_solution(best_solution);
                best_solution = constructed_solution;
                
                if (best_solution->total_cost <= prob->best_known_cost) {
                    if (recent_costs != NULL) {
                        free(recent_costs);
                    }
                    return best_solution;
                }
            } else {
                free_solution(constructed_solution);
            }
        } else {
            free_solution(constructed_solution);
        }
    }
    
    if (recent_costs != NULL) {
        free(recent_costs);
    }
    
    return best_solution;
}

solution* create_initial_solution_grasp(problem* prob, float alpha) {
    solution* sol = create_empty_solution(prob->num_facilities, prob->num_customers);
    int facilities_opened = 0;
    
    while (facilities_opened < prob->p) {
        float best_cost = FLT_MAX;
        float worst_cost = -FLT_MAX;
        float* costs = allocate_vector(sizeof(float), prob->num_facilities);

        for (int j = 0; j < prob->num_facilities; j++) {
            costs[j] = FLT_MAX;
            
            if (!sol->opened_facilities[j]) {
                solution* temp_sol = copy_solution(sol, prob->num_facilities, prob->num_customers);
                temp_sol->opened_facilities[j] = true;
                assign_customers_to_nearest_facility(prob, temp_sol);
                
                costs[j] = temp_sol->total_cost;
                
                if (costs[j] < best_cost) best_cost = costs[j];
                if (costs[j] > worst_cost) worst_cost = costs[j];
                
                free_solution(temp_sol);
            }
        }
        
        int* RCL = allocate_vector(sizeof(int), prob->num_facilities);
        int RCL_size = 0;
        float threshold = best_cost + alpha * (worst_cost - best_cost);
        
        for (int j = 0; j < prob->num_facilities; j++) {
            if (!sol->opened_facilities[j] && costs[j] <= threshold) {
                RCL[RCL_size++] = j;
            }
        }
        
        if (RCL_size > 0) {
            int random_index = rand() % RCL_size;
            int selected_facility = RCL[random_index];
            sol->opened_facilities[selected_facility] = true;
            facilities_opened++;
        } else {
            for (int j = 0; j < prob->num_facilities; j++) {
                if (!sol->opened_facilities[j]) {
                    sol->opened_facilities[j] = true;
                    facilities_opened++;
                    break;
                }
            }
        }
        
        free(costs);
        free(RCL);
    }
    
    assign_customers_to_nearest_facility(prob, sol);
    
    return sol;
}