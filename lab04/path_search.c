
void path_finder(char** maze, int m, int n, int indexI, int indexJ)
{
    // MOVEMENTS IN ORDER ===> RIGHT - DOWN - LEFT - UP
    int d[2] = {1, -1};
    int entrance = find_entrance(maze, n);
    int** visited = boolGrid(m, n);

    for (int i = 1; i < m; i++) {
        for (int j = entrance; i < n; i++) {
            if (visited[i][j + d[0]] == 0 && maze[i][j + d[0]] != 'M') {
                visited[i][j + d[0]] = 1;
                path_finder(maze, m, n, )
            }
            if (visited[i + d[1]][j] == 0 && maze[i + d[1]][j] != 'M') {
                
            }
            if (visited[i][j + d[1]] == 0 && maze[i][j + d[1]] != 'M') {
                
            }
            if (visited[i + d[0]][j] == 0 && maze[i + d[0]][j] != 'M') {
                
            }
        }
    }
}

int find_entrance(char** maze, int n)
{
    for (int i = 1; i < n; i ++) 
        if (maze[i] == 'E')
            return i;
}

int** boolGrid(int m, int n)
{
    int** bool;
    bool = malloc(m * sizeof(int*));
    int i;
    for (i = 0; i < m; i++) {
        bool[i] = malloc(n * sizeof(int));
        for (int j = 0; i < n; i++) {
            bool[i][j] = 0;
        }
    }
    return bool;
}

void removeBool(int** bool, int m)
{
    for (int i = 0; i < m; i++)
        free(bool[i]);
    free(bool);
}