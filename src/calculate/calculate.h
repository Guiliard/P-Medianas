#ifndef CALCULATE_H
#define CALCULATE_H

#include "../utils/utils.h"

float calculate_distance(float x1, float y1, float x2, float y2);
float calculate_total_cost(problem *prob, solution *sol);
void assign_customers_to_nearest_facility(problem *prob, solution *sol);
float calculate_gap(float solution_cost, float best_known_cost);

#endif