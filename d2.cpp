#include <stdio.h>

int main()
{
    int n, k, m, a[110];
    scanf("%d%d%d", &n, &k, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    //冒泡排序
    for (int i = 1; i < n; i++)
        for (int j = 1; j <= n - i; j++)
            if (a[j] > a[j + 1])
            {
                int t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
            }

    if (m > n)
        m = n;
    if (k == 0)
        for (int i = 1; i <= m; i++)
            printf("%d ", a[i]);
    else
        for (int i = n; i > n - m; i--)
            printf("%d ", a[i]);
}