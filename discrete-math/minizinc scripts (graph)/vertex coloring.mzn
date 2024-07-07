% Задаем количество вершин и цветов
int: n = 10; % количество вершин
int: k = 10; % максимальное количество цветов

% Задаем матрицу смежности
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

array[1..n] of var 1..k: vertex_colors; % цвет каждой вершины


constraint forall(i in 1..n)(
    forall(j in 1..n where adjacency_matrix[i,j] = 1)(
        vertex_colors[i] != vertex_colors[j] % вершины, смежные с i, должны иметь различный цвет
    )
);

solve minimize max(vertex_colors);
var int: max_vertex_color = max(vertex_colors);

output ["\(i) \(vertex_colors[i])\n" | i in index_set(vertex_colors)];
output ["Минимальное число в массиве vertex_colors: \(max_vertex_color)\n"];

