#include "local_search.h"

void local_search(problem* prob, solution* sol) {
    for (int i = 0; i < prob->num_facilities; i++) {
        if (!sol->opened_facilities[i]) continue;
        
        for (int j = 0; j < prob->num_facilities; j++) {
            if (sol->opened_facilities[j]) continue;
            
            solution* temp_sol = copy_solution(sol, prob->num_facilities, prob->num_customers);
            temp_sol->opened_facilities[i] = false;
            temp_sol->opened_facilities[j] = true;
            assign_customers_to_nearest_facility(prob, temp_sol);
            
            if (temp_sol->total_cost < sol->total_cost) {
                sol->opened_facilities[i] = false;
                sol->opened_facilities[j] = true;
                assign_customers_to_nearest_facility(prob, sol);
                
                free_solution(temp_sol);
                return;
            } 
            
            free_solution(temp_sol);
        }
    }
}