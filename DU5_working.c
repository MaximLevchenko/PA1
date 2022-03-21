#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
/**
 * @brief 
 * Struct for storing the infromation
 */
typedef struct
{
    char string_name[101];
    int count_similar;
} words;
/**
 * @brief 
 * Comparator function for sorting the array of numbers
 */
int compare(const void *a, const void *b) // code from stackoverflow https://stackoverflow.com/questions/6105513/need-help-using-qsort-with-an-array-of-structs
{
    words *orderA = (words *)a;
    words *orderB = (words *)b;
    return (orderB->count_similar - orderA->count_similar);
}

/**
 * @brief 
 * Function for allocating strings
 * @param whatAllocate strings to allocate
 * @param lengthWhatAllocate length of the array
 */
void allocateWords(words **whatAllocate, const int lengthWhatAllocate)
{
    (*whatAllocate) = (words *)malloc(lengthWhatAllocate * sizeof(**whatAllocate));
}

/**
 * @brief 
 * Checking if the string is in array
 * @param number_of_products length of the array
 * @param product_to_find string to find
 * @param products array of structs
 * @param index_of_the_found index of the found element
 * @return index of the found elements or -1 if not in the array
 */
int inArray(int number_of_products, char *product_to_find, words *products, int *index_of_the_found)
{
    for (int i = 0; i <= number_of_products; i++)
    {
        if (strcmp(product_to_find, products[i].string_name) == 0)
        {
            *index_of_the_found = i;
            return *index_of_the_found;
        }
    }
    return -1;
}
/**
 * @brief 
 * Function for printing the output for the '#'
 * @param products array of structs
 * @param products_to_print amount of products to print
 * @param number_of_products length of the array
 * @param sign '#' or '?'
 */
void printArray(words *products, int products_to_print, int number_of_products, char sign)
{
    // int temp_products_t  o_print = products_to_print;
    if (number_of_products < products_to_print)
        products_to_print = number_of_products;
    int last_el = 0, j = 0, previous_el = 0, sum_of_the_products = 0;
    for (int i = 0; i < products_to_print; i++)
    {
        j = i, last_el = i;
        while (products[j].count_similar == products[j + 1].count_similar && (j <= number_of_products)) // && (j <= products_to_print)
        {
            last_el++, j++;
        }
        if (i != last_el)
        {
            previous_el = i;
            for (; i <= last_el; i++)
            {
                if (sign == '#')
                    printf("%d.-%d. %s, %dx\n", previous_el + 1, last_el + 1, products[i].string_name, products[i].count_similar);
            }
            i--;
            continue;
        }
        if (sign == '#')
            printf("%d. %s, %dx\n", i + 1, products[i].string_name, products[i].count_similar);
    }
    for (int p = 0; p <= last_el; p++)
    {
        sum_of_the_products += products[p].count_similar;
    }
    printf("Nejprodavanejsi zbozi: prodano %d kusu\n", sum_of_the_products);
}

int main(void)
{
    int realloc_variable = 10, counter_mem = 0, read = 0, number_of_products = 0, index_found = 0, products_to_print = 0;
    char sign;
    words *products = NULL;
    char *buffer = NULL;
    printf("Pocet sledovanych:\n");
    if (scanf(" %d", &products_to_print) != 1 || products_to_print <= 0)
    {
        free(products);
        printf("Nespravny vstup.\n");
        return 1;
    }
    printf("Pozadavky:\n");
    while ((read = scanf(" %c", &sign)) != feof(stdin)) //in case of problems change it to EOF
    {
        if (read != 0 && feof(stdin))
        {
            free(products);
            return 1;
        }
        switch (sign)
        {
        case '+':
            buffer = (char *)malloc(1000 * sizeof(char));         //allocating memory for buffer
            if (scanf(" %s", buffer) != 1 || strlen(buffer) > 99) //checking for the string input length
            {
                free(buffer),free(products);
                printf("Nespravny vstup.\n");
                return 1;
            }
            if (products == NULL)
                allocateWords(&products, realloc_variable);                        //function to allocate strings
            if (inArray(number_of_products, buffer, products, &index_found) != -1) //TODO: maybe add 1 to number of products
            {
                products[index_found].count_similar += 1;
                free(buffer);
                break;
            }
            if (++counter_mem >= realloc_variable / 4) //TODO:resizing the memory amount based on the amount of space left
            {
                realloc_variable += (realloc_variable > 100) ? realloc_variable * 1 / 2 : 10;
                products = (words *)realloc(products, (realloc_variable + 1) * sizeof(*products));
            }
            products[number_of_products].count_similar = 1; //TODO: make this part to actually add or =1 whether we found the number_of_products or not
            strcpy(products[number_of_products].string_name, buffer);
            free(buffer); //deallocating cause we need to start all over again every time
            number_of_products++;
            break;
        case '#':
        case '?':
            if (number_of_products == 0)
            {
                free(products);
                printf("Nejprodavanejsi zbozi: prodano 0 kusu\n");
                break;
            }
            qsort(products, number_of_products + 1, sizeof(words), compare);
            printArray(products, products_to_print, number_of_products, sign); //TODO:maybe should add 1 to number_of_products
            break;
        default:
            free(products); //deallocating memory to avoid memory leaks
            printf("Nespravny vstup.\n");
            return 1;
            break;
        }
    }
    return 0;
}
