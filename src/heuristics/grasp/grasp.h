#ifndef GRASP_H
#define GRASP_H

#include "../../utils/utils.h"
#include "../../calculate/calculate.h"
#include "../../heuristics/local_search/local_search.h"

solution* grasp(problem* prob, int grasp_max, float alpha);
solution* filtered_grasp(problem* prob, int grasp_max, float alpha, int filter_k);
solution* create_initial_solution_grasp(problem* prob, float alpha);

#endif