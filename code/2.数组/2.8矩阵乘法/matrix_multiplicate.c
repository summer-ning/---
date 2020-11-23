/******************************************************************************
 *  题目说明：请编程实现矩阵乘法，并考虑当矩阵规模较大时的优化方法。
    解法：一种是暴力求解法
******************************************************************************/
#include <stdio.h>

#define  M      (3)
#define  N      (4)
#define  P      (3)

int matrixMultiplication_bruteForce(int *a, int *b, int *product, int m, int n, int p)
{
    int i, j, k;

    for (i = 0; i < m; i++)
    {
        for (j = 0; j < p; j++)
        {
            product[i*p+j] = 0;
            for (k = 0; k < n; k++)
            {
                product[i*p+j] += a[i*n+k] * b[k*p+j];
            }
        }
    }
}

int main()
{
    int a[M][N] = {
        {1,2,3,4},
        {2,3,4,5},
        {3,4,5,6},
    };
    int b[N][P] = {
        {1,2,3},
        {2,3,4},
        {3,4,5},
        {4,5,6},
    };
    int product[M][P];

    matrixMultiplication_bruteForce(&a[0][0], &b[0][0], &product[0][0], M, N, P);

    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < P; j++)
        {
            printf("%d ",product[i][j]);
        }
        printf("\n");
    }
    return 0;
}