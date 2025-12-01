#include "environment/environment.h"
#include "heuristics/grasp/grasp.h"
#include "heuristics/ils/ils.h"
#include "metrics/metrics.h"
#include "menu/menu.h"

int main() {
    problem* prob = NULL;
    int option;
    int problem_loaded = 0;

    while (1) {
        print_menu();
        scanf("%d", &option);

        switch (option) {
            case 1: {
                printf("\n");
                print_problem_menu();
                int problem_option;
                scanf("%d", &problem_option);

                if (problem_option == 1) {
                    printf("\nCarregando problema pequeno (Small)...\n");
                    if (problem_loaded && prob != NULL) {
                        free_problem(prob);
                    }
                    prob = init_environment(
                        "dataset/small/customers.txt", 
                        "dataset/small/facilities.txt", 
                        "dataset/small/solution.txt", 
                        "dataset/small/pmedian.txt",
                        "dataset/small/time.txt"
                    );
                    print_problem(prob);
                    print_matrix(prob->num_customers, prob->num_facilities, prob->distance_matrix, "output/small/distance_matrix.txt");
                    problem_loaded = 1;
                    printf("\nProblema carregado com sucesso! Matriz de distâncias salva em output/small/distance_matrix.txt\n");
                } else if (problem_option == 2) {
                    printf("\nCarregando problema médio (Medium)...\n");
                    if (problem_loaded && prob != NULL) {
                        free_problem(prob);
                    }
                    prob = init_environment(
                        "dataset/medium/customers.txt", 
                        "dataset/medium/facilities.txt", 
                        "dataset/medium/solution.txt", 
                        "dataset/medium/pmedian.txt",
                        "dataset/medium/time.txt"
                    );
                    print_problem(prob);
                    print_matrix(prob->num_customers, prob->num_facilities, prob->distance_matrix, "output/medium/distance_matrix.txt");
                    problem_loaded = 1;
                    printf("\nProblema carregado com sucesso! Matriz de distâncias salva em output/medium/distance_matrix.txt\n");
                } else if (problem_option == 3) {
                    printf("\nCarregando problema grande (Big)...\n");
                    if (problem_loaded && prob != NULL) {
                        free_problem(prob);
                    }
                    prob = init_environment(
                        "dataset/big/customers.txt", 
                        "dataset/big/facilities.txt", 
                        "dataset/big/solution.txt", 
                        "dataset/big/pmedian.txt",
                        "dataset/big/time.txt"
                    );
                    print_problem(prob);
                    print_matrix(prob->num_customers, prob->num_facilities, prob->distance_matrix, "output/big/distance_matrix.txt");
                    problem_loaded = 1;
                    printf("\nProblema carregado com sucesso! Matriz de distâncias salva em output/big/distance_matrix.txt\n");
                } else {
                    printf("\nOpção inválida!\n");
                }
                break;
            }

            case 2: {
                if (!problem_loaded) {
                    printf("\n========================================\n");
                    printf("   AVISO: Problema não carregado!\n");
                    printf("========================================\n");
                    printf("Por favor, carregue um problema primeiro (opção 1).\n");
                    break;
                }

                print_heuristic_menu();
                int heuristic_option;
                scanf("%d", &heuristic_option);

                if (heuristic_option == 1) {
                    printf("\n========================================\n");
                    printf("   Executando GRASP\n");
                    printf("========================================\n");
                    
                    metrics* m = create_metrics();
                    start_metrics(m);
                    
                    solution* sol_grasp = grasp(prob, MAX_ITER, ALPHA);
                    
                    stop_metrics(m);
                    
                    printf("\n========================================\n");
                    printf("   Resultado GRASP\n");
                    printf("========================================\n");
                    print_solution_with_gap(sol_grasp, prob->num_facilities, prob->num_customers, prob->best_known_cost);
                    print_metrics(m, prob->reference_time);
                    
                    free_solution(sol_grasp);
                    free_metrics(m);
                } else if (heuristic_option == 2) {
                    printf("\n========================================\n");
                    printf("   Executando Filtered GRASP\n");
                    printf("========================================\n");
                    
                    metrics* m = create_metrics();
                    start_metrics(m);
                    
                    solution* sol_filtered_grasp = filtered_grasp(prob, MAX_ITER, ALPHA, LIMIT);
                    
                    stop_metrics(m);
                    
                    printf("\n========================================\n");
                    printf("   Resultado Filtered GRASP\n");
                    printf("========================================\n");
                    print_solution_with_gap(sol_filtered_grasp, prob->num_facilities, prob->num_customers, prob->best_known_cost);
                    print_metrics(m, prob->reference_time);
                    
                    free_solution(sol_filtered_grasp);
                    free_metrics(m);
                } else if (heuristic_option == 3) {
                    printf("\n========================================\n");
                    printf("   Executando ILS\n");
                    printf("========================================\n");
                    
                    metrics* m = create_metrics();
                    start_metrics(m);
                    
                    solution* sol_ils = ils(prob, MAX_ITER);
                    
                    stop_metrics(m);
                    
                    printf("\n========================================\n");
                    printf("   Resultado ILS\n");
                    printf("========================================\n");
                    print_solution_with_gap(sol_ils, prob->num_facilities, prob->num_customers, prob->best_known_cost);
                    print_metrics(m, prob->reference_time);
                    
                    free_solution(sol_ils);
                    free_metrics(m);
                } else if (heuristic_option == 4) {
                    printf("\n========================================\n");
                    printf("   Executando Smart ILS\n");
                    printf("========================================\n");
                    
                    metrics* m = create_metrics();
                    start_metrics(m);
                    
                    solution* sol_smart_ils = smart_ils(prob, MAX_ITER, LIMIT);
                    
                    stop_metrics(m);
                    
                    printf("\n========================================\n");
                    printf("   Resultado Smart ILS\n");
                    printf("========================================\n");
                    print_solution_with_gap(sol_smart_ils, prob->num_facilities, prob->num_customers, prob->best_known_cost);
                    print_metrics(m, prob->reference_time);
                    
                    free_solution(sol_smart_ils);
                    free_metrics(m);
                } else {
                    printf("\nOpção inválida!\n");
                }
                break;
            }

            case 3:
                printf("\nSaindo do programa...\n");
                if (problem_loaded && prob != NULL) {
                    free_problem(prob);
                }
                return 0;

            default:
                printf("\nOpção inválida! Por favor, escolha uma opção válida.\n");
                break;
        }
    }

    return 0;
}