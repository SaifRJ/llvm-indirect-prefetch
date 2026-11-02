int indirect_sum(int *table, int *indices, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += table[indices[i]];
    }
    return sum;
}

int matrix_sum(int *m, int rows, int cols) {
    int sum = 0;
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
            sum += m[r * cols + c];
    return sum;
}

int no_loops(int a, int b) { return a + b; }