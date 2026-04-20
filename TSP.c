#include <stdio.h>

#define N 25
#define INF 1000000000


void min_edge(int n, int matrix[N][N], int minedge[]) {
    for (int i = 0; i < n; i++) {
        minedge[i] = INF;
        for (int j = 0; j < n; j++) {
            if (i != j && matrix[i][j] < minedge[i]) {
                minedge[i] = matrix[i][j];
            }
        }
    }
}

int lowerbound(int n, int cost, int check[], int minedge[]) {
    int b = cost;
    for (int i = 0; i < n; i++) {
        if (!check[i]) {
            if (minedge[i] >= INF) return INF;
            if (b >= INF - minedge[i]) return INF;
            b += minedge[i];
        }
    }
    return b;
}

void solvelasttwo(int n, int matrix[N][N], int step, int u, int cost,
                  int check[], int path[], int final_path[], int *ans) {
    int v1 = -1, v2 = -1;

    for (int i = 0; i < n; i++) {
        if (!check[i]) {
            if (v1 == -1) v1 = i;
            else v2 = i;
        }
    }

    if (v1 == -1 || v2 == -1) return;

    if (matrix[u][v1] < INF && matrix[v1][v2] < INF && matrix[v2][0] < INF) {
        int cost1 = cost + matrix[u][v1] + matrix[v1][v2] + matrix[v2][0];
        if (cost1 < *ans) {
            *ans = cost1;
            path[step] = v1;
            path[step + 1] = v2;
            path[n] = 0;
            for (int i = 0; i <= n; i++) {
                final_path[i] = path[i];
            }
        }
    }

    if (matrix[u][v2] < INF && matrix[v2][v1] < INF && matrix[v1][0] < INF) {
        int cost2 = cost + matrix[u][v2] + matrix[v2][v1] + matrix[v1][0];
        if (cost2 < *ans) {
            *ans = cost2;
            path[step] = v2;
            path[step + 1] = v1;
            path[n] = 0;
            for (int i = 0; i <= n; i++) {
                final_path[i] = path[i];
            }
        }
    }
}

void TSP_matrix_backtrack(int n, int matrix[N][N], int step, int u, int cost,
                          int check[], int path[], int final_path[],
                          int minedge[], int *ans) {
    if (step == n - 2) {
        solvelasttwo(n, matrix, step, u, cost, check, path, final_path, ans);
        return;
    }

    for (int v = 1; v < n; v++) {
        if (!check[v] && matrix[u][v] < INF) {
            check[v] = 1;
            path[step] = v;

            int newCost = cost + matrix[u][v];
            if (lowerbound(n, newCost, check, minedge) < *ans) {
                TSP_matrix_backtrack(n, matrix, step + 1, v, newCost,
                                     check, path, final_path, minedge, ans);
            }

            check[v] = 0;
        }
    }
}

void init(int n, int path[], int final_path[], int check[], int matrix[N][N]) {
    check[0] = 1;
    path[0] = 0;
    path[n] = 0;
    final_path[0] = 0;
    final_path[n] = 0;

    for (int i = 1; i < n; i++) {
        check[i] = 0;
        path[i] = -1;
        final_path[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = INF;
        }
    }
}

void readgraph(int m, int matrix[N][N]) {
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        u--;
        v--;
        if (w < matrix[u][v]) {
            matrix[u][v] = w;
        }
    }
}

int main() {
    int n, m;
    int matrix[N][N];
    int path[N + 1];
    int final_path[N + 1];
    int check[N];
    int minedge[N];
    int ans = INF;
    scanf("%d %d", &n, &m);
    init(n, path, final_path, check, matrix);
    readgraph(m, matrix);
    min_edge(n, matrix, minedge);
    TSP_matrix_backtrack(n, matrix, 1, 0, 0, check, path, final_path, minedge, &ans);

    if (ans >= INF) {
        printf("Khong ton tai duong di.\n");
        return 0;
    }

    printf("%d\n", ans);
    for (int i = 0; i <= n; i++) {
        printf("%d ", final_path[i] + 1);
    }

    return 0;
}
