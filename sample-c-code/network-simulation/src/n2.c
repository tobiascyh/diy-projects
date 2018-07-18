/*
  Author       : Yee Hong Chu
  Date created : 10/04/2013
  Date modified: 11/09/2013
*/

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_BUF 128

/* Node2 is linked to Node1 */
/* Node4 is linked to Node2 */
int main(int argc, char *argv[])
{
    int fd, out_loop, in_loop, i;
    char message[MAX_BUF] = "";
    char buffer[MAX_BUF] = "";
    char receiver[MAX_BUF] = "";
    char ack[7] = "Nx_ack";
    char stop[8] = "N2_stop";
    char pipe1[12] = "./tmp/link1";
    char pipe3[12] = "./tmp/link3";

    /* Create named pipes with read and write permission */
    mkfifo(pipe3, S_IRUSR| S_IWUSR);

    /* Loop the program until user chooses to quit */
    i = 0;
    out_loop = 1;
    while(out_loop)
    {
        /* Keep reading the pipe for incoming message */
        in_loop = 1;
        while(in_loop)
        {
            fd = open(pipe1, O_RDONLY);
            read(fd, buffer, MAX_BUF);
            close(fd);
            if(strlen(buffer) == 3)
            {
                /* Check if this node is the destination node */
                if(buffer[2] == '2')
                {
                    message[i] = buffer[0];
                    if(buffer[0] != EOF)
                    {
                        i++;
                    }
                    else
                    {
                        message[i] = '\0';
                        i = 0;
                        in_loop = 0;
                        printf("N2, message received:\n%s\n", message);
                        ack[1] = buffer[2];
                    }
                }
                else
                {
                    /* Open the pipe to write into it and then closing it */
                    fd = open(pipe3, O_WRONLY);
                    write(fd, buffer, strlen(buffer));
                    close(fd);

                    /* Keep reading the pipe for incoming message */
                    in_loop = 1;
                    while(in_loop)
                    {
                        fd = open(pipe3, O_RDONLY);
                        if(read(fd, receiver, MAX_BUF) >= 0)
                        {
                            in_loop = 0;
                        }
                        close(fd);
                    }
                    ack[1] = buffer[2];
                }

                /* Open the pipe to write into it and then closing it */
                fd = open(pipe1, O_WRONLY);
                write(fd, ack, strlen(ack));
                close(fd);
            }
            else
            {
                if(strlen(buffer) == 1)
                {
                    in_loop = 0;

                    /* Open the pipe to write into it and then closing it */
                    fd = open(pipe3, O_WRONLY);
                    write(fd, buffer, strlen(buffer));
                    close(fd);

                    /* Keep reading the pipe for incoming message */
                    in_loop = 1;
                    while(in_loop)
                    {
                        fd = open(pipe3, O_RDONLY);
                        if(read(fd, receiver, MAX_BUF) >= 0)
                        {
                            in_loop = 0;
                        }
                        close(fd);
                    }
                    printf("N2, %s received\n", receiver);
                }
            }
        }

        /* Check user input for stop signal */
        if(strcmp(buffer, "q") == 0 || strcmp(buffer, "Q") == 0)
        {
            out_loop = 0;

            /* Open the pipe to write into it and then closing it */
            fd = open(pipe1, O_WRONLY);
            write(fd, stop, strlen(stop));
            close(fd);
        }

        /* Reset the buffer and message */
        memset(&buffer, 0, MAX_BUF);
        memset(&message, 0, MAX_BUF);
    }

    /* Remove the created named pipes */
    unlink(pipe3);

    return 0;
}
