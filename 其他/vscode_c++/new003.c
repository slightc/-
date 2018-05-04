#include <stdio.h>
#include <string.h>
int main()
{
    int i, j = 0, n;
    char word[80];
    char *w[80];
    char **p;
    p = w;
    gets(word);
    n = strlen(word);
    for (i = 0; i < n; i++)
    {
        w[0] = &word[0];
        if (word[i] == ' ')
        {
            j++;
            i += 1;
            w[j] = &word[i];
        }
    }
    for (i = j; i >= 0; i--)
    {
        if (i > 0)
        {
            printf("%c ", **p++);
        }
        else
        {
            printf("%c", **p);
        }
    }
    return 0;
}