/*
 * Author: Tobias Chu
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define filename "inventory.dat"

typedef struct part{
    char *name;
    float price;
    int quantity;
    struct part *next;
} part;

/*
 * This sortName function reads the list of parts in the memory and sort
 *  it by alphabetical order (a to z).
 */
void sortName(part **partList, int *count)
{
    int i, position, wordLength;

    part *temp = *partList;
    part *startPtr = *partList;
    part *nextPtr = startPtr->next;

    /* The number of time this loop run correspend to the number of parts
        that are in the list to ensure even if the part is at the bottom of
        the list can be moved to the first position. */
    for(i = 0 ; i < *count ; i++)
    {
        position = 0;

        /* As long as the nextPtr is not NULL then the startPtr and nextPtr
            will keep shifting to the next parts in the list. */
        while(nextPtr != NULL)
        {
            /* Check which of parts have the longest string and assign the
                value to the wordLength variable. */
            if(strlen(startPtr->name) > strlen(nextPtr->name))
            {
                wordLength = strlen(startPtr->name);
            }
            else
            {
                wordLength = strlen(nextPtr->name);
            }

            /* Using wordLength variable, compare every single characters
                between the two strings. If a positive value is returned,
                it indicates that the first string has the higher value
                compared to the second string. */
            if(strncmp(startPtr->name, nextPtr->name, wordLength) > 0)
            {
                /* If the startPtr is at position 0 (the first part in
                    the list), then it is a special case where the
                    pointer pointing to the beginning of the list will be
                    updated. Or else, the previous part's next pointer
                    will be changed to the current part's next pointer. */
                if(position == 0)
                {
                    *partList = nextPtr;
                }
                else
                {
                    temp->next = startPtr->next;
                }

                /* By using three pointers, the previous, current and
                    next pointers can be swapped around. */
                startPtr->next = nextPtr->next;
                nextPtr->next = startPtr;
                temp = nextPtr;
                nextPtr = startPtr;
                startPtr = temp;
            }

            ++position;

            /* Shift the three pointers's position to the next position in
                the list */
            temp = startPtr;
            startPtr = startPtr->next;
            nextPtr = nextPtr->next;
        }

        /* Reset the pointers to the beginning of the list after reaching
            to the end of the list in the loop above. */
        startPtr = *partList;
        nextPtr = startPtr->next;
    }

    printf("Sorting by name completed.\n\n");
}

/*
 * This sortPrice function reads the list of parts in the memory and sort
 *  its value from low to high (0-9).
 */
void sortPrice(part **partList, int *count)
{
    int i, position;

    part *temp = *partList;
    part *startPtr = *partList;
    part *nextPtr = startPtr->next;

    for(i = 0 ; i < *count ; i++)
    {
        position = 0;

        while(nextPtr != NULL)
        {
            /* Compared to the softName function, the comparison of
                float is simplier and easier. */
            if(startPtr->price > nextPtr->price)
            {
                if(position == 0)
                {
                    *partList = nextPtr;
                }
                else
                {
                    temp->next = startPtr->next;
                }

                startPtr->next = nextPtr->next;
                nextPtr->next = startPtr;
                temp = nextPtr;
                nextPtr = startPtr;
                startPtr = temp;
            }

            ++position;

            temp = startPtr;
            startPtr = startPtr->next;
            nextPtr = nextPtr->next;
        }

        startPtr = *partList;
        nextPtr = startPtr->next;
    }

    printf("Sorting by price completed.\n\n");
}

/*
 * This sortQuantity function reads the list of parts in the memory and
 *  sort its value from low to high (0-9).
 */
void sortQuantity(part **partList, int *count)
{
    int i, position;

    part *startPtr = *partList;
    part *nextPtr = startPtr->next;
    part *temp = NULL;

    for(i = 0 ; i < *count ; i++)
    {
        position = 0;

        while(nextPtr != NULL)
        {
            /* This comparison function of integer is similar to the
                comparison of float, which is simplier and easier. */
            if(startPtr->quantity > nextPtr->quantity)
            {
                if(position == 0)
                {
                    *partList = nextPtr;
                }
                else
                {
                    temp->next = startPtr->next;
                }

                startPtr->next = nextPtr->next;
                nextPtr->next = startPtr;
                temp = nextPtr;
                nextPtr = startPtr;
                startPtr = temp;
            }

            ++position;

            temp = startPtr;
            startPtr = startPtr->next;
            nextPtr = nextPtr->next;
        }

        startPtr = *partList;
        nextPtr = startPtr->next;
    }

    printf("Sorting by quantity completed.\n\n");
}

/*
 * This function is the display menu for the user to decide which type
 *  of sorting methods the user want to select.
 */
part * sortFunction(part *partList, int *count)
{
    char select[100];

    /* As long as there are more then two parts in the list, then the
        user can select the sorting method. */
    if(*count > 1)
    {
        printf("Sort by:\n[N]ame\n[P]rice\n[Q]uantity\n[B]ack\n");
        printf("Selection: ");
        fgets(select, sizeof(select), stdin);
        printf("\n");

        switch(select[0])
        {
            case 'n':
            case 'N': sortName(&partList, count);
                break;
            case 'p':
            case 'P': sortPrice(&partList, count);
                break;
            case 'q':
            case 'Q': sortQuantity(&partList, count);
                break;
            /* Case b will do nothing and transfer the user back to
                the main menu */
            case 'b':
            case 'B':
                break;
            default: printf("Invalid selection!\n\n");
        }
    }
    /* Notify the user that more parts needed or else the sorting
        of the parts will not be noticed. */
    else if(*count == 1)
    {
        printf("More parts needed in order to sort them.\n\n");
    }
    /* Notify the user of the empty list. */
    else
    {
        printf("The list is empty.\n\n");
    }

    /* Return the address of the pointer that is pointing at the
        beginning of the partList. */
    return partList;
}

/*
 * This read function will read the data from the file and stored them in
 *  its linked list. The list is like a stack where the latest part will be
 *  at the top of the list. Use variable count to keep track of the number
 *  of parts that are in the list.
 */
part * readFunction(part *partList, FILE *partFile, int *count)
{
    char read[100];

    part *newPart = NULL;

    while(fgets(read, sizeof(read), partFile) != NULL)
    {
        newPart = malloc(sizeof(part));

        newPart->name = malloc(sizeof(char) * strlen(read));
        strncpy(newPart->name, read, strlen(read));
        newPart->name[strlen(read)-1] = '\0';

        fgets(read, sizeof(read), partFile);
        newPart->price = atof(read);

        fgets(read, sizeof(read), partFile);
        newPart->quantity = atoi(read);

        newPart->next = partList;
        partList = newPart;

        ++*count;
    }

    return newPart;
}

/*
 * This function will prompt the user for the part's name, price and quantity.
 *  The name of the part is stored in a temporary array so that it can be used
 *  to identify the input's length in order to allocate appropriate memory size
 *  for the name. Use variable count to keep track of the number of parts that
 *  are in the list.
 */
part * addFunction(part *partList, int *count)
{
    char input[100];

    part *newPart = NULL;

    newPart = malloc(sizeof(part));

    printf("Enter part's name: ");
    fgets(input, sizeof(input), stdin);

    newPart->name = malloc(sizeof(char) * strlen(input));
    strncpy(newPart->name, input, strlen(input));
    newPart->name[strlen(input)-1] = '\0';

    printf("Enter part's price: ");
    scanf("%f", &newPart->price);

    printf("Enter part's quantity: ");
    scanf("%d%*c", &newPart->quantity);

    newPart->next = partList;

    ++*count;

    printf("Data successfully added.\n\n");

    return newPart;
}

/*
 * The function that will print the list of all the parts that have been
 *  read from the file when the program starts or recently added by the
 *  user. The variable count store the value that indicate the number of
 *  parts available in the program.
 */
void printFunction(part *partList, int *count)
{
    int i;

    if(*count != 0)
    {
        for(i = 0 ; i < *count ; i++)
        {
            printf("Part's name: %s\n",partList->name);
            printf("Part's price: %.2f\n",partList->price);
            printf("Part's quantity: %d\n\n",partList->quantity);

            partList = partList->next;
        }
    }
    else
    {
        printf("The list is empty.\n\n");
    }
}

/*
 * The main display of all the operations that this program offers to
 *  the user. Defence programing implemented to prevent the program from
 *  crashing when the user enters invalid inputs.
 */
part * mainMenu(part *partList, int *count)
{
    char select[100];

    while(1)
    {
        printf("The Inventory System v2.01(alpha)\n");
        printf("Menu\n[A]dd\n[S]ort\n[P]rint\n[Q]uit\nSelection: ");
        fgets(select, sizeof(select), stdin);
        printf("\n");

        if(select[0] == 'a' || select[0] == 'A')
        {
            partList = addFunction(partList, count);
        }
        else if(select[0] == 's' || select[0] == 'S')
        {
            partList = sortFunction(partList, count);
        }
        else if(select[0] == 'p' || select[0] == 'P')
        {
            printFunction(partList, count);
        }
        else if(select[0] == 'q' || select[0] == 'Q')
        {
            printf("Good Bye!\n\n");
            break;
        }
        else
        {
            printf("Invalid selection!\nTry again.\n\n");
        }
    }

    return partList;
}

/*
 * This function will print all the parts in the list to the file
 *  before clearing all the memories and freeing up all the
 *  pointers.
 */
void freeList(part *partList, FILE *partFile, int count)
{
    int i;

    part *temp = partList;

    /* Writing the data to the file. */
    for(i = 0 ; i < count ; i++)
    {
        fprintf(partFile, "%s\n", temp->name);
        fprintf(partFile, "%.2f\n", temp->price);
        fprintf(partFile, "%d\n", temp->quantity);

        temp = temp->next;
    }

    /* Freeing all the used memories and pointers. */
    for(i = 0 ; i < count ; i++)
    {
        temp = partList->next;
        free(partList->name);
        free(partList);
        partList = temp;
    }
}

/*
 * The main function that holds the initial pointer to the list,
 *  the file pointer, parts counter and call the appropriate
 *  functions to executes the rest of the program. Everything
 *  starts from here and it also ends here.
 */
int main(int argv, char *argc[])
{
    system("clear");

    int count = 0;

    part *partList = NULL;

    FILE *partFile = NULL;

    /* Open the file in append+ mode to read the data and create it
        if it does not exist. */
    partFile = fopen(filename, "a+");

    if(partFile == NULL)
    {
        fprintf(stderr, "Error opening file!\n");
        return -1;
    }

    /* Read the data from the file when the program starts. */
    partList = readFunction(partList, partFile, &count);

    /* Close the reading mode of the file pointer. */
    fclose(partFile);

    /* Call the main menu function and transfer the user to the
        core function of the program. */
    partList = mainMenu(partList, &count);

    /* Open the file in write mode to write the data in the file */
    partFile = fopen(filename, "w");

    /* Free the memories and pointers, then close the file. */
    freeList(partList, partFile, count);
    fclose(partFile);

    return 0;
}
