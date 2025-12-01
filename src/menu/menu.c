#include "menu.h"

void print_menu() {
    printf("\n========================================\n");
    printf("   MENU - Problema das P Medianas\n");
    printf("========================================\n");
    printf("1. Carregar problema\n");
    printf("2. Resolver com metaheurística\n");
    printf("3. Sair\n");
    printf("========================================\n");
    printf("Escolha uma opção: ");
}

void print_heuristic_menu() {
    printf("\n========================================\n");
    printf("   Escolha a Metaheurística\n");
    printf("========================================\n");
    printf("1. GRASP\n");
    printf("2. Filtered GRASP\n");
    printf("3. ILS\n");
    printf("4. Smart ILS\n");
    printf("========================================\n");
    printf("Escolha uma opção: ");
}

void print_problem_menu() {
    printf("\n========================================\n");
    printf("   Escolha o Problema\n");
    printf("========================================\n");
    printf("1. Problema Pequeno (Small) - Clientes: 14 - Facilidades: 6 - P: 3\n");
    printf("2. Problema Grande (Big) - Clientes: 50 - Facilidades: 20 - P: 10\n");
    printf("========================================\n");
    printf("Escolha uma opção: ");
}
