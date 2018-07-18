/*
 * Author: Yee Hong Chu
 * ID: 0773285
 * Assignment: 1
 * Course: CIS*2500
 *
 * Sources: The logic for solving this assignment is based on Lab1.
 */

#include <stdio.h>

//The function that will calculate the prime factor of a given input and
//calculate the largest prime factor.
//The requested input was not supported by the long data type, therefore
//the long long data type is used.
long primeFactor(int i, long long hugeNumber)
{
    //Checking whether the denominator is smaller than the numerator.
    if(i < hugeNumber)
    {
        //Checking if hugeNumber can be devided by i.
        if(hugeNumber % i == 0)
        {
            //Replace the value of hugeNumber after dividing by i.
            hugeNumber /= i;
            printf("%d ", i);
        }

        //When the division of hugeNumber and i does not result in an
        //integer, the function will return itself as recursion with an
        //increment the value of i by 1, i is used as a counter.
        return primeFactor(++i, hugeNumber);
    }
    else
    {
        printf("%d ", i);

        //Return the value of i if the value of i is bigger than hugeNumber.
        //Decrease value of i by 1 to get the last value that is divisible
        //with the hugeNumber.
        return i;
    }
}

//The main function of the program.
int main(void)
{
    long long hugeNumber, result;
    //Variable i is initialized to 2 because prime number starts at 2.
    int i = 2;

    //Prompt user for input.
    printf("Enter a number: ");
    scanf("%lld", &hugeNumber);

    //Calculating largest prime factor.
    result = primeFactor(i, hugeNumber);

    //Display the result to screen.
    printf("\nThe largest prime factor: %lld\n", result);

    return 0;
}
