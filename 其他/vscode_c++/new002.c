#include <stdio.h>

int main()
{
    int n;
    scanf("%d", &n);
    int a[1000]; //原输入
    int b[1000]; //分割数
    int c[1000]; //最终排序
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    int j = 0;   //a
    int k = 1;   //b
    int x = 0;   //c
    b[0] = a[0]; //b[0]=3;
    while (j < n)
    {
        for (int i = 0; i <= k; i++)
        {
            if (a[j] == b[i])
            {
                c[x] = a[j];
                x++;
                break;
            }
        }
        while (a[j] >= 1)
        {
            if (a[j] % 2 == 0 && a[j] != 0)
            {
                b[k] = a[j];
                a[j] /= 2;
                k++;
                if (a[j] == 0)
                    break;
            }
            else
            {
                b[k] = a[j];
                a[j] = ((a[j] * 3) + 1) / 2;
                k++;
                if (a[j] == 0)
                    break;
            }
        }
        j++;
    }
    printf("%d %d", c[0], c[1]);
    return 0;
}