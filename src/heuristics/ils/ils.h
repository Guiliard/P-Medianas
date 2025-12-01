#ifndef ILS_H
#define ILS_H

#include "../../utils/utils.h"
#include "../../calculate/calculate.h"
#include "../../heuristics/local_search/local_search.h"

solution* ils(problem* prob, int ils_max);
solution* smart_ils(problem* prob, int ils_max, int vezes_max);
solution* create_initial_solution_ils(problem* prob);
void perturbation(problem* prob, solution* sol, int level);

#endif