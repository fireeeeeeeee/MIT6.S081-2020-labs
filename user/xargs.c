#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    char para[512];
    read(0, para, 512);
    char *eargv[10];

    for (int i = 1; i < argc; i++)
    {
        eargv[i - 1] = argv[i];
    }
    int l = strlen(para);
    for (int i = 0; i < l; i++)
    {
        if (para[i] == '\n')
        {
            para[i] = '\0';
        }
    }

    for (int i = 0; i < l; i++)
    {
        if (para[i] == '\0')
        {
            continue;
        }
        eargv[argc - 1] = para + i;
        if (fork() == 0)
        {
            exec(eargv[0], eargv);
        }
        wait(0);
        while (para[i++] != '\0')
        {
        }
    }

    exit(0);
}
