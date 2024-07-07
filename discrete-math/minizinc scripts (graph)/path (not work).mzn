
int: n = 10;

array[1..n*n] of var 0..1: adjacency_matrix_arr = 
[0, 1, 1, 1, 1, 1, 1, 0, 0, 0,
1, 0, 1, 0, 0, 0, 1, 0, 0, 0,
1, 1, 0, 1, 0, 0, 0, 1, 0, 0,
1, 0, 1, 0, 1, 0, 0, 0, 0, 0,
1, 0, 0, 1, 0, 1, 0, 0, 1, 0,
1, 0, 0, 0, 1, 0, 1, 0, 0, 0,
1, 1, 0, 0, 0, 1, 0, 0, 0, 1,
0, 0, 1, 0, 0, 0, 0, 0, 1, 1,
0, 0, 0, 0, 1, 0, 0, 1, 0, 1,
0, 0, 0, 0, 0, 0, 1, 1, 1, 0];


array[1..n, 1..n] of var 0..1: adjacency_matrix = array2d(1..n, 1..n, adjacency_matrix_arr);

set of int: V = 1..n;

int: size_walk = 10;

array[1..size_walk] of var V: walk;

% Ограничения
% Каждая вершина должна быть посещена не менее одного раза
constraint forall(i in V) (
  exists(j in walk)(i = j)
);
 

% Цикл должен быть замкнутым
constraint forall(i in 1..size_walk - 1) (
  adjacency_matrix[walk[i], walk[i + 1]] = 1
);


% Решение задачи
solve satisfy;

% Вывод результатов
output ["Closed walk size: \(size_walk)\n",        "Walk vertices: {\(show(walk))}"];
