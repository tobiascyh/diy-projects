/*
 * Author: Yee Hong Chu
 * ID: 0773285
 * Assignment: 3
 * Course: CIS*2500
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define filename "inventory.dat"

struct part {
    char *name;
    float price;
    int quantity;
};

/* This function will prompt the user for the part's name, price and quantity.
    The name of the part is stored in a temporary array so that it can be used
    identify the input's length in order to allocate appropriate memory size.
    Once everything is stored in the structure, it will then saved the data
    into the file. */
void addFunction(int count, struct part *partList, FILE *partFile)
{
    char input[100];

    printf("Enter part's name: ");
    fgets(input, sizeof(input), stdin);

    printf("Enter part's price: ");
    scanf("%f", &partList[count].price);

    /* The %*c in scanf is used to pickup the newline character generated
        from pressing the enter key but it will not be stored anywhere.
        This is to prevent the newline character from staying in the
        program that will mess up the menu looping system. */
    printf("Enter part's quantity: ");
    scanf("%d%*c",&partList[count].quantity);

    /* Allocating just the right amount of memory depending on the size of
        the input name entered by the user. */
    partList[count].name = malloc(sizeof(char) * strlen(input));
    strncpy(partList[count].name, input, strlen(input));

    /* Changing the last character in the array from newline character to
        null character. */
    partList[count].name[strlen(input)-1] = '\0';

    /* Printing the data into the file, 1 variable per line. */
    fprintf(partFile, "%s\n", partList[count].name);
    fprintf(partFile, "%.2f\n", partList[count].price);
    fprintf(partFile, "%d\n", partList[count].quantity);
}

/* The function that will print the list of all the parts that have been
    read from the file when the program starts or recently added by the
    user. The variable count store the value that indicate the number of
    parts available in the program. */
void printFunction(int count, struct part *partList)
{
    int check;

    for(check = 0 ; check < count ; check++)
    {
        printf("Part's name: %s\n", partList[check].name);
        printf("Part's price: $%.2f\n", partList[check].price);
        printf("Part's quantity: %d\n\n", partList[check].quantity);
    }
}

/* This read function will read the data from the file and stored in its
    buffer. Also, it will read the user's selection from the given menu
    display until the user choose to quit the program. */
void readFunction(struct part *partList, FILE *partFile)
{
    char select[100], read[100];
    int count, limit, i;

    /* The limit variable is use to allocate spaces for the part
       structure, initially with 3 spaces and additional 3 when more
       spaces are needed. */
    count = 0;
    limit = 3;

    /* Read the content of the inventory.dat file and store in the
        program's memory while re-allocting more spaces as needed. */
    while(fgets(read, sizeof(read), partFile) != NULL)
    {
        /* Check if more spaces are needed then increase them by 3. */
        if(count == limit)
        {
            limit+=3;
            partList = realloc(partList, sizeof(*partList) * limit);
        }

        /* Allocating just the right amount of memory depending on the size of
            the data read from the file. */
        partList[count].name = malloc(sizeof(char) * strlen(read));
        strncpy(partList[count].name, read, strlen(read));

        /* Changing the last character in the array from newline character to
            null character. */
        partList[count].name[strlen(read)-1] = '\0';

        /* Read the following two lines of data from the file and convert it
            into float and integer respectively, its the price and quantity */
        fgets(read, sizeof(read), partFile);
        partList[count].price = atof(read);

        fgets(read, sizeof(read), partFile);
        partList[count].quantity = atoi(read);

        /* Count act as the counter to keep track of the number of data
            available in the program. */
        ++count;
    }

    /* An infinite loop that will redirect the user back to the menu screen
        after the user finished adding or printing data. */
    while(1)
    {
        printf("The Inventory System v2.01(alpha)\n");
        printf("Menu\n[A]dd\n[P]rint\n[Q]uit\nSelection: ");
        fgets(select, sizeof(select), stdin);
        printf("\n");

        /* Based on user's selection, the program will check and execute the
            desired function. Upon executing the add function, it will first
            check if more spaces are needed. Data is wrtten into the file
            directly after the user enters them. */
        if(select[0] == 'a' || select[0] == 'A')
        {
            if(count == limit)
            {
                limit+=3;
                partList = realloc(partList, sizeof(*partList) * limit);
            }

            addFunction(count, (struct part *) partList, (FILE *) partFile);
            printf("Data successfully added.\n\n");

            ++count;
        }
        /* Print out the content of the file that is already buffered in the
            program's memory or print empty if the content is empty. */
        else if(select[0] == 'p' || select[0] == 'P')
        {
            if(count != 0)
            {
                printFunction(count, (struct part *) partList);
                printf("End of list.\n\n");
            }
            else
            {
                printf("The list is empty.\n\n");
            }
        }
        /* Break out from the infinite loop if the user chooese to quit the
            program. */
        else if(select[0] == 'q' || select[0] == 'Q')
        {
            printf("Good Bye!\n\n");
            break;
        }
        /* An error message is displayed to the screen if the user entered an
            invalid selection, other than a, p and q. */
        else
        {
            printf("Invalid selection!\nTry again.\n\n");
        }
    }

    /* Free up the memory allocated to the name pointer in the structure. */
    for(i = 0 ; i < count ; i++)
    {
        free(partList[i].name);
    }

    /* Before terminating the program, we have to free up the memory allocated
        to the structure and close the file pointer or else the data entered
        will not be saved. */
    free(partList);
    fclose(partFile);
}

int main(int argv, char *argc[])
{
    /* This clear screen function is the command commonly used in linux
        terminal to clear the screen. */
    system("clear");

    FILE *partFile = NULL;

    /* Create the file is it does not exist or else point the file
        pointer at the end of the file content. This allows new data
        able to be appended into the file without rewriting it. */
    partFile = fopen(filename, "a+");

    /* Exit the program if error occurred when openning file, for
        example, if the user does not have the permission to do so. */
    if(partFile == NULL)
    {
        fprintf(stderr, "Error opening file!\n");
        return -1;
    }

    /* Initialize the part structure with initially 3 spaces. */
    struct part *partList;
    partList = malloc(sizeof(*partList) * 3);

    /* Modularize the main function to make it as simple as possible */
    readFunction((struct part *) partList, (FILE *) partFile);

    return 0;
}
