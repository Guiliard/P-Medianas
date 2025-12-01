param M, integer, >= 1;
param N, integer, >= 1;
param P, integer, >= 1;

set I:={1..M};
set J:={1..N};

param d{j in J, i in I};

param file, symbolic, default "P-Medianas-Small.txt";

var x{i in I, j in J} binary;
var y{i in I} binary;

minimize cost: sum{i in I, j in J}  d[j,i]*x[i,j];

s.t. demand{j in J}: sum{i in I} x[i,j] = 1;
s.t. aloc{i in I, j in J}: x[i,j] <= y[i];
s.t. knapsack: sum{i in I} y[i] = P;

solve;

printf '---------------------------------------------\n' >> file;
printf 'Cliente			Facilidade\n' >> file;
printf '---------------------------------------------\n' >> file;
printf {j in J, i in I: x[i,j] > 0.5} "%8d  %8d\n", j, i >> file;
printf '---------------------------------------------\n' >> file;
printf 'Custo total (z): ' >> file;
printf '%f \n', cost >> file;

data;

param M:=6;
param N:=14;
param P:=3;

param d :	1       2       3       4       5       6 :=
		1	13.90	13.04	18.51	18.03	7.91	9.82
		2	2.06	6.36	8.00	11.85	7.00	9.49
		3	2.50	5.15	8.25	11.07	5.00	7.62
		4	3.35	2.55	3.61	6.52	7.07	7.28
		5	7.16	5.15	2.24	3.81	10.30	9.22
		6	10.01	8.75	4.00	5.70	13.89	12.73
		7	14.01	12.35	8.00	7.78	17.46	15.81
		8	13.42	9.71	8.85	3.64	14.01	11.28
		9	11.40	7.16	8.08	2.06	11.01	8.14
		10	10.06	5.39	9.92	5.66	6.96	3.54
		11	11.05	7.83	13.46	11.24	4.61	3.20
		12	9.19	7.50	13.09	12.50	2.50	4.50
		13	6.58	2.92	8.60	7.65	3.00	2.00
		14	6.80	6.67	11.66	12.51	2.24	5.83;
end;



