#include <stdio.h>
/**
 * @param accepts size of the board and size of the individual piece
 * for int repeat is used to repeat the output of the individual row
 * for int line is used to print whether x or space
 * @if checks whether the number is odd or not 
 * if it is->prints X according to the size of individual piece,
 * if not->prints spaces with the same algorithm
 */
void print_x(int velikost, int pocet)
{
    for (int repeat = 1; repeat <= velikost; repeat++)
    {
        printf("|");
        for (int line = 1; line <= pocet; line++)
        {
            if (line % 2 == 0)
            {
                for (int space = 1; space <= velikost; space++)
                {
                    printf(" ");
                }
            }
            else
            {
                for (int X = 1; X <= velikost; X++)
                {
                    printf("X");
                }
            }
        }
        printf("|\n");
    }
}
void print_space(int velikost, int pocet)
{
    for (int repeat = 1; repeat <= velikost; repeat++)
    {
        printf("|");
        for (int line = 1; line <= pocet; line++)
        {
            if (line % 2 != 0)
            {
                for (int space = 1; space <= velikost; space++)
                {
                    printf(" ");
                }
            }
            else
            {
                for (int X = 1; X <= velikost; X++)
                {
                    printf("X");
                }
            }
        }
        printf("|\n");
    }
}
void print_outline(int velikost, int pocet)
{
    printf("+");
    for (int outline = 1; outline <= (velikost * pocet); outline++)
    {
        printf("-");
    }
    printf("+\n");
}
int main()
{
    /* The aim of this is to minimize the user input errors */
    int pocet_poli = 0, velikost_poli = 0;
    printf("Zadejte pocet poli:\n");
    if ((scanf("%d", &pocet_poli) != 1) || pocet_poli < 1)
    {
        printf("Nespravny vstup.\n");
        return 1;
    }
    printf("Zadejte velikost pole:\n");
    if ((scanf("%d", &velikost_poli) != 1) || velikost_poli < 1)
    {
        printf("Nespravny vstup.\n");
        return 1;
    }
    print_outline(velikost_poli, pocet_poli);

    for (int row = 1; row <= pocet_poli; row++)
    {
        if (row % 2 == 0)
        {
            /** 
        *@param accepts size of the board, size of the individual piece
        *@return prints "X"
        */
            print_x(velikost_poli, pocet_poli);
        }
        else
        {
            /** 
        *@param accepts size of the board, size of the individual piece
        *@return prints " "
        */

            print_space(velikost_poli, pocet_poli);
        }
        // printf("\n");
    }
    print_outline(velikost_poli, pocet_poli);

    return 0;
}