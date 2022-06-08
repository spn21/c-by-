#include <stdio.h>

int main()
{
    int n, k, m, a[110];
    scanf("%d%d%d", &n, &k, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    //选择排序
    for (int i = 1; i < n; i++)
        for (int j = i + 1; j <= n; j++)
            if (a[i] > a[j])
            {
                int t = a[i];
                a[i] = a[j];
                a[j] = t;
            }

    if (m > n) //防止下标越界
        m = n;
    if (k == 0)
        for (int i = 1; i <= m; i++)
            printf("%d ", a[i]);
    else
        for (int i = n; i > n - m; i--)
            printf("%d ", a[i]);
}