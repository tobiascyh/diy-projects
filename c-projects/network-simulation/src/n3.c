/*
  Author       : Tobias Chu
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

/* Node3 is linked to Node1 */
/* Node5, Node6 and Node7 are linked to Node3 */
int main(int argc, char *argv[])
{
    int fd, out_loop, in_loop, i;
    char message[MAX_BUF] = "";
    char buffer[MAX_BUF] = "";
    char receiver[MAX_BUF] = "";
    char ack[7] = "Nx_ack";
    char stop[8] = "N3_stop";
    char pipe2[12] = "./tmp/link2";
    char pipe4[12] = "./tmp/link4";
    char pipe5[12] = "./tmp/link5";
    char pipe6[12] = "./tmp/link6";

    /* Create named pipes with read and write permission */
    mkfifo(pipe4, S_IRUSR| S_IWUSR);
    mkfifo(pipe5, S_IRUSR| S_IWUSR);
    mkfifo(pipe6, S_IRUSR| S_IWUSR);

    /* Loop the program until user chooses to quit */
    i = 0;
    out_loop = 1;
    while(out_loop)
    {
        /* Keep reading the pipe for incoming message */
        in_loop = 1;
        while(in_loop)
        {
            fd = open(pipe2, O_RDONLY);
            read(fd, buffer, MAX_BUF);
            close(fd);
            if(strlen(buffer) == 3)
            {
                /* Check if this node is the destination node */
                if(buffer[2] == '3')
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
                        printf("N3, message received:\n%s\n", message);
                        ack[1] = buffer[2];
                    }
                }
                else
                {
                    /* Open the pipe to write into it and then closing it */
                    if(buffer[2] == '5')
                    {
                        fd = open(pipe4, O_WRONLY);
                    }
                    else if(buffer[2] == '6')
                    {
                        fd = open(pipe5, O_WRONLY);
                    }
                    else
                    {
                        fd = open(pipe6, O_WRONLY);
                    }
                    write(fd, buffer, strlen(buffer));
                    close(fd);

                    /* Keep reading the pipe for incoming message */
                    in_loop = 1;
                    while(in_loop)
                    {
                        if(buffer[2] == '5')
                        {
                            fd = open(pipe4, O_RDONLY);
                        }
                        else if(buffer[2] == '6')
                        {
                            fd = open(pipe5, O_RDONLY);
                        }
                        else
                        {
                            fd = open(pipe6, O_RDONLY);
                        }
                        if(read(fd, receiver, MAX_BUF) >= 0)
                        {
                            in_loop = 0;
                        }
                        close(fd);
                    }
                    ack[1] = buffer[2];
                }

                /* Open the pipe to write into it and then closing it */
                fd = open(pipe2, O_WRONLY);
                write(fd, ack, strlen(ack));
                close(fd);
            }
            else
            {
                if(strlen(buffer) == 1)
                {
                    in_loop = 0;

                    /* Open the pipe to write into it and then closing it
                         to send to N5 */
                    fd = open(pipe4, O_WRONLY);
                    write(fd, buffer, strlen(buffer));
                    close(fd);

                    /* Keep reading the pipe for incoming message from N5*/
                    in_loop = 1;
                    while(in_loop)
                    {
                        fd = open(pipe4, O_RDONLY);
                        if(read(fd, receiver, MAX_BUF) >= 0)
                        {
                            in_loop = 0;
                        }
                        close(fd);
                    }
                    printf("N3, %s received\n", receiver);

                    /* Open the pipe to write into it and then closing it
                         to send to N6 */
                    fd = open(pipe5, O_WRONLY);
                    write(fd, buffer, strlen(buffer));
                    close(fd);

                    /* Keep reading the pipe for incoming message from N6 */
                    in_loop = 1;
                    while(in_loop)
                    {
                        fd = open(pipe5, O_RDONLY);
                        if(read(fd, receiver, MAX_BUF) >= 0)
                        {
                            in_loop = 0;
                        }
                        close(fd);
                    }
                    printf("N3, %s received\n", receiver);

                    /* Open the pipe to write into it and then closing it
                         to send to N7 */
                    fd = open(pipe6, O_WRONLY);
                    write(fd, buffer, strlen(buffer));
                    close(fd);

                    /* Keep reading the pipe for incoming message from N7 */
                    in_loop = 1;
                    while(in_loop)
                    {
                        fd = open(pipe6, O_RDONLY);
                        if(read(fd, receiver, MAX_BUF) >= 0)
                        {
                            in_loop = 0;
                        }
                        close(fd);
                    }
                    printf("N3, %s received\n", receiver);
                }
            }
        }

        /* Check user input for stop signal */
        if(strcmp(buffer, "q") == 0 || strcmp(buffer, "Q") == 0)
        {
            out_loop = 0;

            /* Open the pipe to write into it and then closing it */
            fd = open(pipe2, O_WRONLY);
            write(fd, stop, strlen(stop));
            close(fd);
        }

        /* Reset the buffer and message */
        memset(&buffer, 0, MAX_BUF);
        memset(&message, 0, MAX_BUF);
    }

    /* Remove the created named pipes */
    unlink(pipe4);
    unlink(pipe5);
    unlink(pipe6);

    return 0;
}
