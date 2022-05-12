#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf(":wrong parameter num\n");

        exit(1);
    }
    int s = atoi(argv[1]);
    sleep(s);
    exit(0);
}
