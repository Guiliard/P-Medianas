#include "environment.h"

problem* init_environment(char* customer_file, char* facility_file, char* solution_file, char* pmedian_file, char* time_file) {
    problem* prob = allocate_vector(sizeof(problem), 1);

    char* customer_content = read_file((char*)customer_file);
    char* facility_content = read_file((char*)facility_file);
    char* solution_content = read_file((char*)solution_file);
    char* pmedian_content = read_file((char*)pmedian_file);
    char* time_content = read_file((char*)time_file);

    prob->num_customers = count_lines(customer_content);
    prob->num_facilities = count_lines(facility_content);

    prob->customers = allocate_vector(sizeof(customer), prob->num_customers);
    prob->facilities = allocate_vector(sizeof(facility), prob->num_facilities);

    for (int i = 0; i < prob->num_customers; i++) {
        char* line = get_line_of_file(customer_content, i);
        prob->customers[i].id = i;
        sscanf(line, "%f %f", &prob->customers[i].x, &prob->customers[i].y);
        free(line);
    }

    for (int i = 0; i < prob->num_facilities; i++) {
        char* line = get_line_of_file(facility_content, i);
        prob->facilities[i].id = i;
        sscanf(line, "%f %f", &prob->facilities[i].x, &prob->facilities[i].y);
        free(line);
    }

    sscanf(solution_content, "%f", &prob->best_known_cost);
    sscanf(pmedian_content, "%d", &prob->p);
    sscanf(time_content, "%f", &prob->reference_time);

    free(customer_content);
    free(facility_content);
    free(solution_content);
    free(pmedian_content);
    free(time_content);
    
    calculate_distance_matrix(prob);

    return prob;
}

void calculate_distance_matrix(problem* prob) {
    prob->distance_matrix = allocate_matrix(prob->num_customers, prob->num_facilities);
    for (int i = 0; i < prob->num_customers; i++) {
        for (int j = 0; j < prob->num_facilities; j++) {
            prob->distance_matrix[i][j] = calculate_distance(
                prob->customers[i].x, prob->customers[i].y,
                prob->facilities[j].x, prob->facilities[j].y
            );
        }
    }
}