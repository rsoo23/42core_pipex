#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define PIPE_IN 1
#define PIPE_OUT 0

int main(int argc, char const *argv[])
{
    int pipes[2];
    pipe(pipes);
    int pid = fork();

    if (pid == 0)
    {
        char input[1234];
        read(0, input, 1234);
        write(pipes[PIPE_IN], input, 3);
        // close(pipes[PIPE_IN]);
    }
    else {
        wait(NULL);

        // read from pipe
        char readBuff[1234];
        int ret = read(pipes[PIPE_OUT], readBuff, 3);

        printf("parent childstr is %s\n", readBuff);
    }

    return 0;
}
