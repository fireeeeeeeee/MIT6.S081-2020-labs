#include "kernel/types.h"
#include "user/user.h"

void MakeSubProc(int *p)
{
    int t;
    int nex[2];
    int havSub = 0;
    int first = 1;
    int prim;
    close(p[1]);
    while (1)
    {
        read(p[0], &t, 4);
        if (t == 0)
        {
            if (havSub)
            {
                write(nex[1], &t, 4);
            }
            break;
        }
        if (first)
        {
            prim = t;
            first = 0;
            printf("prime %d\n", prim);
        }
        if (t % prim != 0)
        {
            if (!havSub)
            {
                if (pipe(nex) == -1)
                {
                    printf("error when open pipe\n");
                    exit(1);
                }
                if (fork() == 0)
                {
                    MakeSubProc(nex);
                    return;
                }
                havSub = 1;
            }
            write(nex[1], &t, 4);
        }
    }
}

int main(int argc, char *argv[])
{
    int p[2];
    if (pipe(p) == -1)
    {
        printf("error when open pipe\n");
        exit(1);
    }
    if (fork() == 0)
    {
        MakeSubProc(p);
    }
    else
    {
        for (int i = 2; i <= 35; i++)
        {
            write(p[1], &i, 4);
        }
        int i = 0;
        write(p[1], &i, 4);
    }
    wait(0);
    exit(0);
}
