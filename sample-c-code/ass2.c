/*
 * Author: Yee Hong Chu
 * ID: 0773285
 * Assignment: 2
 * Course: CIS*2500
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/* The function that will loop through the 1000 digit numbers to get the
   largest product of two 5 digits number */
long long greatestProduct(char samples[], int *product1, int *product2)
{
    long long temp;
    int  i, j;
    char num1[5], num2[5];
    char *ptr1, *ptr2;

    temp = 0;
    ptr1 = &samples[0];
    ptr2 = &samples[0];

    /* The first loop that will control ptr1 for the first 5 digit number */
    for(i = 0 ; i < 1000 ; i++)
    {
        /* The control that will move the pointer to the next number in the
           given 1000 digit numbers */
        ptr1 = &samples[i];

        /* Copy the 5 digit numbers where the ptr1 is pointing at and store
           in the num1 variable */
        strncpy(num1, ptr1, 5);

        /* The second loop for the second 5 digit number of ptr2 */
        for(j = 0 ; j < 1000 ; j++)
        {
            ptr2 = &samples[j];

            strncpy(num2, ptr2, 5);

            /* Checking for the largest of product of the first and second
               5 digit numbers then store it to temp variable */
            if(atoll(num1) * atoll(num2) > temp)
            {
                /* atoll is used instead of atoi is because the production
                   of num1 and num2 is larger than what an integer datatype
                   can handle, so we need to use the long long datatype */
                temp = atoll(num1) * atoll(num2);

                /* By using the pass by reference, the value of num1 and
                   num2 can be identified when the largest product result
                   is returned */
                *product1 = atoi(num1);
                *product2 = atoi(num2);
            }
        }
    }

    /* Return the largest product */
    return temp;
}

int main(int argc, char *argv[])
{
    char samples[1000] = "73167176531330624919225119674426574742355349194934"
                         "96983520312774506326239578318016984801869478851843"
                         "85861560789112949495459501737958331952853208805511"
                         "12540698747158523863050715693290963295227443043557"
                         "66896648950445244523161731856403098711121722383113"
                         "62229893423380308135336276614282806444486645238749"
                         "30358907296290491560440772390713810515859307960866"
                         "70172427121883998797908792274921901699720888093776"
                         "65727333001053367881220235421809751254540594752243"
                         "52584907711670556013604839586446706324415722155397"
                         "53697817977846174064955149290862569321978468622482"
                         "83972241375657056057490261407972968652414535100474"
                         "82166370484403199890008895243450658541227588666881"
                         "16427171479924442928230863465674813919123162824586"
                         "17866458359124566529476545682848912883142607690042"
                         "24219022671055626321111109370544217506941658960408"
                         "07198403850962455444362981230987879927244284909188"
                         "84580156166097919133875499200524063689912560717606"
                         "05886116467109405077541002256983155200055935729725"
                         "71636269561882670428252483600823257530420752963450";

    int product1, product2;
    /* The product of 5 digit numbers are too much for int and long int to store */
    long long result;

    /* The address of product1 and producy2 variables are passed to the function */
    result = greatestProduct(samples, &product1, &product2);

    printf("The largest value is:\n%d x %d = %lld\n", product1, product2, result);

    return 0;
}
