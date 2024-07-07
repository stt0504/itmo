% Задаем количество вершин, ребер
int: n = 10; % количество вершин
int: m = 14; % количество ребер

% Задаем матрицу инцидентности

array[1..n*m] of var 0..1: incidence_matrix_arr = 
[1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0,
0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1,
0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0];


array[1..n, 1..m] of var 0..1: incidence_matrix = array2d(1..n, 1..m, incidence_matrix_arr);

int: max_size =  3; % максимальный размер stable set

% переменная для хранения вершин в stable set
var set of 1..m: x;

% ограничение на максимальное количество вершин в stable set
constraint card(x) <= max_size;


% ограничение на смежность всех вершин в stable set
constraint forall(k in 1..n, i,j in x where i != j )(
    incidence_matrix[k, i] + incidence_matrix[k, j] <= 1
);

constraint forall(e in 1..m) (
  exists (j in x) (
    exists( k in 1..n) (
    (incidence_matrix[k, e] = 1) /\ (incidence_matrix[k, j] = 1)
    )
  )
);% максимизируем размер stable set
solve minimize card(x);

% выводим решение
output ["Minimum matching size: \(card(x))\n",        "Matching edges: {\(show(x))}"];


