#include "calculate.h"

float calculate_distance(float x1, float y1, float x2, float y2) {
    float dx = x1 - x2;
    float dy = y1 - y2;
    return sqrtf(dx * dx + dy * dy);
}

float calculate_total_cost(problem *prob, solution *sol) {
    float total_cost = 0.0f;
    
    for (int i = 0; i < prob->num_customers; i++) {
        int facility_index = sol->customer_assignments[i];
        if (facility_index >= 0 && facility_index < prob->num_facilities) {
            total_cost += prob->distance_matrix[i][facility_index];
        }
    }
    
    return total_cost;
}

void assign_customers_to_nearest_facility(problem *prob, solution *sol) {
    for (int i = 0; i < prob->num_customers; i++) {
        float min_distance = FLT_MAX;
        int best_facility = -1;
        
        for (int j = 0; j < prob->num_facilities; j++) {
            if (sol->opened_facilities[j]) {
                float distance = prob->distance_matrix[i][j];
                if (distance < min_distance) {
                    min_distance = distance;
                    best_facility = j;
                }
            }
        }
        
        if (best_facility != -1) {
            sol->customer_assignments[i] = best_facility;
        }
    }
    
    sol->total_cost = calculate_total_cost(prob, sol);
}

float calculate_gap(float solution_cost, float best_known_cost) {
    if (solution_cost <= best_known_cost) {
        return 0.0f;
    }
    
    return ((solution_cost - best_known_cost) / best_known_cost) * 100.0f;
}