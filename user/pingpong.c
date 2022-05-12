#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int p1[2];
    int p2[2];
    if (pipe(p1) == -1 || pipe(p2) == -1)
    {
        printf("error when open pipe\n");
        exit(1);
    }
    char msg;
    if (fork() == 0)
    {
        read(p1[0], &msg, 1);
        int id = getpid();
        printf("%d: received ping\n", id);
        write(p2[1], "u", 1);
    }
    else
    {
        write(p1[1], "u", 1);
        read(p2[0], &msg, 1);
        int id = getpid();
        printf("%d: received pong\n", id);
    }

    exit(0);
}
