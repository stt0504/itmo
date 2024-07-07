int: n = 10; % количество вершин
array[1..n*n] of var 0..1: adjacency_matrix_arr = 
[0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
1, 0, 0, 1, 0, 0, 0, 0, 0, 0,
1, 0, 0, 1, 1, 0, 1, 0, 0, 0,
0, 1, 1, 0, 0, 1, 0, 0, 0, 0,
0, 0, 1, 0, 0, 1, 0, 0, 0, 1,
0, 0, 0, 1, 1, 0, 0, 1, 0, 0,
0, 0, 1, 0, 0, 0, 0, 0, 1, 1,
0, 0, 0, 0, 0, 1, 0, 0, 0, 1,
0, 0, 0, 0, 0, 0, 1, 0, 0, 1,
0, 0, 0, 0, 1, 0, 1, 1, 1, 0];


array[1..n, 1..n] of var 0..1: adjacency_matrix = array2d(1..n, 1..n, adjacency_matrix_arr);

int: max_size = 40; % максимальный размер клики

% переменная для хранения вершин в клике
var set of 1..n: x;

% ограничение на максимальное количество вершин в клике
constraint card(x) <= max_size;

% ограничение на смежность всех вершин в клике
constraint forall(i,j in x where i != j)(adjacency_matrix[i,j] = 1);

% максимизируем размер клики
solve maximize card(x);

% выводим решение
output ["Maximum clique size: \(card(x))\n",        "Clique vertices: {\(show(x))}"];
