
void path_finder(char** maze, int m, int n, int indexI, int indexJ)
{
    // MOVEMENTS IN ORDER ===> RIGHT - DOWN - LEFT - UP
    int d[2] = {1, -1};
    int entrance = find_entrance(maze, n);
    int** visited = boolGrid(m, n);

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