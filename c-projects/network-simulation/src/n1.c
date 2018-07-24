/*
  Author       : Tobias Chu
  Date created : 10/04/2013
  Date modified: 11/09/2013
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_BUF 128
#define TRUE 1
#define FALSE 0

int validateInput(char *, char *, int *);

/* Node1 is the gateway to other nodes */
/* Node2 and Node3 are linked to Node1 */
int main(int argc, char *argv[])
{
    int verbose = FALSE;
    int fd, out_loop, in_loop, validate, node, i;
    char option[MAX_BUF] = "";
    char input[MAX_BUF] = "";
    char buffer[MAX_BUF] = "";
    char receiver[MAX_BUF] = "";
    char packet[4] = "xnx";
    char pipe1[12] = "./tmp/link1";
    char pipe2[12] = "./tmp/link2";

    /* Create named pipes with read and write permission */
    mkfifo(pipe1, S_IRUSR| S_IWUSR);
    mkfifo(pipe2, S_IRUSR| S_IWUSR);

    printf("|------------------------------------------|\n");
    printf("| Network Simulation v2.8i                 |\n");
    printf("|  by Yee Hong Chu (0773285)               |\n");

    /* Loop the program until user chooses to quit */
    out_loop = 1;
    while(out_loop)
    {
        validate = TRUE;
        printf("|                                          |\n");
        printf("| Enter a filename followed by destination |\n");
        printf("|  node to start simulation                |\n");
        printf("|  Eg: test.txt n2 or test.txt N2          |\n");
        printf("|  or q(Q) to exit                         |\n");
        printf("|------------------------------------------|\n\n");
        printf("Message: ");
        fgets(input, MAX_BUF, stdin);

        /* Run validation function */
        validate = validateInput(input, buffer, &node);
        if(validate)
        {
            /* Broadcast stop signal packet to neighbouring nodes */
            if(strlen(buffer) == 1)
            {
                /* Nodes on link 1 */
                fd = open(pipe1, O_WRONLY);
                write(fd, buffer, strlen(buffer));
                close(fd);
                in_loop = 1;
                while(in_loop)
                {
                    fd = open(pipe1, O_RDONLY);
                    if(read(fd, receiver, MAX_BUF) >= 0)
                    {
                        in_loop = 0;
                    }
                    close(fd);
                }
                printf("N1, %s received\n", receiver);

                /* Nodes on link 2 */
                fd = open(pipe2, O_WRONLY);
                write(fd, buffer, strlen(buffer));
                close(fd);
                in_loop = 1;
                while(in_loop)
                {
                    fd = open(pipe2, O_RDONLY);
                    if(read(fd, receiver, MAX_BUF) >= 0)
                    {
                        in_loop = 0;
                    }
                    close(fd);
                }
                printf("N1, %s received\n", receiver);
            }
            else
            {
                /* Option to enable verbose mode */
                printf("Enable verbose mode? (Y/N): ");
                fgets(option, MAX_BUF, stdin);
                if(option[0] == 'y' || option[0] == 'Y')
                {
                    verbose = TRUE;
                }

                /* Sending packet(s) to a specific destination node */
                for(i = 0; i < strlen(buffer); i++)
                {
                    /* Encapsulate a single character into a packet */
                    if(i == (strlen(buffer) - 1))
                    {
                        packet[0] = EOF;
                    }
                    else
                    {
                        packet[0] = buffer[i];
                    }
                    packet[2] = (char)(node + 48);

                    /* Verbose mode for sending packet */
                    if(verbose)
                    {
                        printf("Send packet: %s\n", packet);
                    }

                    /* Open and send the packet to the link corresponding to
                         the destination node */
                    if(node == 2 || node == 4)
                    {
                        fd = open(pipe1, O_WRONLY);
                    }
                    if(node == 3 || node == 5 || node == 6 || node == 7)
                    {
                        fd = open(pipe2, O_WRONLY);
                    }
                    write(fd, packet, strlen(packet));
                    close(fd);

                    /* Keep reading for ack packet(s) from destination node */
                    in_loop = 1;
                    while(in_loop)
                    {
                        /**/
                        if(node == 2 || node == 4)
                        {
                            fd = open(pipe1, O_RDONLY);
                        }
                        if(node == 3 || node == 5 || node == 6 || node == 7)
                        {
                            fd = open(pipe2, O_RDONLY);
                        }
                        if(read(fd, receiver, MAX_BUF) >= 0)
                        {
                            in_loop = 0;
                        }
                        close(fd);
                    }

                    /* Verbose mode for receiving packet */
                    if(verbose)
                    {
                        printf("Receive packet: %s\n", receiver);
                    }
                }
                printf("N1, %s received\n", receiver);
            }

            /* Check user input for stop signal */
            if(strcmp(buffer, "q") == 0 || strcmp(buffer, "Q") == 0)
            {
                out_loop = 0;

                printf("N1_stop\n\n");
            }
            else
            {
                printf("Message successfully sent.\n\n");
            }
        }

        /* Disable verbose mode */
        verbose = FALSE;

        /* Reset the input, buffer and receiver */
        memset(&input, 0, MAX_BUF);
        memset(&option, 0, MAX_BUF);
        memset(&buffer, 0, MAX_BUF);
        memset(&receiver, 0, MAX_BUF);
    }

    /* Remove the created named pipes */
    unlink(pipe1);
    unlink(pipe2);

    return 0;
}

/* Validate and sanitize user input, check for file existence and identify
     destination node(s) */
int validateInput(char *input, char *buffer, int *node)
{
    FILE *filePtr = NULL;
    int i;
    int result = TRUE;
    char temp[MAX_BUF] = "";
    char fname[MAX_BUF] = "";

    /* Check for exit character */
    if(strlen(input) == 2 && input[1] == '\n')
    {
        if(input[0] == 'q' || input[0] == 'Q')
        {
            strncpy(buffer, input, 1);
        }
        else
        {
            printf("Invalid input, please try again.\n\n");
            result = FALSE;
        }
    }
    else
    {
        /* Extract filename from user input with intensive defence */
        for(i = 0; i < strlen(input); i++)
        {
            /* Look for space between filename and destination */
            if(input[i] == ' ')
            {
                /* Identify valid destination */
                if((i + 2) < strlen(input) && input[i+3] == '\n')
                {
                    if(input[i+1] == 'n' || input[i+1] == 'N')
                    {
                        /* Valid destination node range 2 to 7 */
                        if(input[i+2] > '1' && input[i+2] < '8')
                        {
                            *node = input[i+2] - 48;
                            strncpy(fname, input, i);
                            break;
                        }
                        else
                        {
                            printf("Invalid input, please try again.\n");
                            printf("Usage: n<2-7> or N<2-7>\n\n");
                            result = FALSE;
                            break;
                        }
                    }
                    else
                    {
                        printf("Invalid input, please try again.\n");
                        printf("Usage: n<2-7> or N<2-7>\n\n");
                        result = FALSE;
                        break;
                    }
                }
                else
                {
                    printf("Invalid input, please try again.\n");
                    printf("Usage: n<2-7> or N<2-7>\n\n");
                    result = FALSE;
                    break;
                }
            }
            if(i == (strlen(input) - 1))
            {
                printf("Invalid input, please try again.\n");
                printf("Usage: <filename> <destination>\n\n");
                result = FALSE;
            }
        }

        /* Read the content in the file */
        if(strlen(fname) != 0 && result != FALSE)
        {
            filePtr = fopen(fname, "r");
            if(filePtr == NULL)
            {
                /* Display error if file does not exist or not readable */
                printf("Error: File reading operation failed.\n\n");
                result = FALSE;
            }
            else
            {
                while(fgets(temp, MAX_BUF, filePtr))
                {
                    strcat(buffer, temp);
                }
                fclose(filePtr);
            }
        }
    }

    return result;
}
