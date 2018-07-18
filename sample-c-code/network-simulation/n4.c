/*
  Author       : Yee Hong Chu
  ID           : 0773285
  Course       : CIS3210
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

/* Node4 is linked to Node2 */
int main(int argc, char *argv[])
{
    int fd, out_loop, in_loop, i;
    char message[MAX_BUF] = "";
    char buffer[MAX_BUF] = "";
    char ack[7] = "ack";
    char stop[8] = "N4_stop";
    char pipe3[12] = "./tmp/link3";

    /* Loop the program until user chooses to quit */
    i = 0;
    out_loop = 1;
    while(out_loop)
    {
        /* Keep reading the pipe for incoming message */
        in_loop = 1;
        while(in_loop)
        {
            fd = open(pipe3, O_RDONLY);
            read(fd, buffer, MAX_BUF);
            close(fd);
            if(strlen(buffer) == 3)
            {
                message[i] = buffer[0];
                /* Check for end-of-message transmission */
                if(buffer[0] != EOF)
                {
                    i++;
                }
                else
                {
                    message[i] = '\0';
                    i = 0;
                    in_loop = 0;
                    printf("N4, message received:\n%s\n", message);
                }

                /* Acknowledge receiving packet */
                fd = open(pipe3, O_WRONLY);
                write(fd, ack, strlen(ack));
                close(fd);
            }
            else
            {
                /* Keep reading if buffer is empty */
                if(strlen(buffer) == 1)
                {
                    in_loop = 0;
                }
            }
        }

        /* Check packet for stop signal */
        if(strcmp(buffer, "q") == 0 || strcmp(buffer, "Q") == 0)
        {
            out_loop = 0;

            /* Acknowledge stop signal to sender node */
            fd = open(pipe3, O_WRONLY);
            write(fd, stop, strlen(stop));
            close(fd);
        }

        /* Reset the buffer and message */
        memset(&buffer, 0, MAX_BUF);
        memset(&message, 0, MAX_BUF);
    }

    return 0;
}
