#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "../utils/utils.h"
#include "../reader/reader.h"
#include "../calculate/calculate.h"

problem* init_environment(char* customer_file, char* facility_file, char* solution_file, char* pmedian_file, char* time_file);
void calculate_distance_matrix(problem* prob);

#endif