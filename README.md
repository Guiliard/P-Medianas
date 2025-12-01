# Problema das P-Medianas

## Sobre o Problema

O Problema das P-Medianas consiste em selecionar **p** instalações (medianas) de um conjunto de localizações candidatas para atender um conjunto de clientes, minimizando a soma das distâncias entre cada cliente e sua instalação mais próxima. Este é um problema clássico de otimização combinatória com aplicações em logística, localização de instalações e planejamento urbano.

**Objetivo:** Minimizar o custo total de atendimento aos clientes.

## Metaheurísticas Implementadas

Este projeto implementa quatro metaheurísticas para resolver o problema:

- **GRASP** (Greedy Randomized Adaptive Search Procedure)
- **Filtered GRASP** - Variante com filtragem de soluções construtivas
- **ILS** (Iterated Local Search)
- **Smart ILS** - Variante com controle adaptativo de perturbação

Todas incluem busca local para refinamento das soluções e parada antecipada ao encontrar o ótimo conhecido.

## Estrutura do Projeto

```
src/
├── main.c              # Menu principal e fluxo de execução
├── environment/        # Inicialização e estruturas do problema
├── heuristics/         
│   ├── grasp/          # GRASP e Filtered GRASP
│   ├── ils/            # ILS e Smart ILS
│   └── local_search/   # Busca local (swap)
├── reader/             # Leitura de arquivos de entrada
├── calculate/          # Cálculos de custo e GAP
├── metrics/            # Medição de tempo e desempenho
└── utils/              # Funções auxiliares

dataset/
├── small/              # Problema pequeno (14 clientes, 6 facilidades, p=3)
├── medium/             # Problema médio (24 clientes, 9 facilidades, p=5)
└── big/                # Problema grande (50 clientes, 20 facilidades, p=10)

gusek/                  # Arquivos para execução no solver GUSEK
output/                 # Matrizes de distâncias geradas
```

## Compilação e Execução

```bash
# Limpar arquivos compilados
make clean

# Compilar
make

# Compilar e executar
make run
```

## Formato dos Arquivos de Entrada

Cada instância no diretório `dataset/` contém:

- `customers.txt` - Coordenadas (x, y) dos clientes, uma por linha
- `facilities.txt` - Coordenadas (x, y) das instalações candidatas, uma por linha
- `pmedian.txt` - Número de medianas (p) a serem abertas
- `solution.txt` - Custo da solução ótima conhecida
- `time.txt` - Tempo de referência para comparação (em segundos)

## Saída

O programa gera:
- Solução encontrada com instalações abertas e atribuições de clientes
- Custo total da solução
- GAP percentual em relação ao ótimo conhecido
- Tempo de execução e comparação com tempo de referência
- Matriz de distâncias salva em `output/<small|medium|big>/distance_matrix.txt`
