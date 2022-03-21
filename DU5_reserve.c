#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct
{
    char string_name[101];
    int count_similar;
} words;

// int binarySearch(int number_of_products, char *product_to_find, words *products) // source https://sites.google.com/a/cmrit.ac.in/c-programming/materials/binary-search-for-strings
// {
//     int low, high, mid;
//     low = 0;
//     high = number_of_products - 1;
//     while (low <= high)
//     {
//         mid = (low + high) / 2;
//         if (strcmp(product_to_find, products[mid].string_name) == 0)
//         {
//             return mid;
//         }
//         else if (strcmp(product_to_find, products[mid].string_name) > 0)
//         {
//             high = high;
//             low = mid + 1;
//         }
//         else
//         {
//             low = low;
//             high = mid - 1;
//         }
//     }

//     return -1;
// }
int ms_cmp_string1(const void *vp1, const void *vp2) //code from stackoverflow https://stackoverflow.com/questions/16933487/sorting-an-array-of-structures-in-c
{
    const words *ms1 = (words *)vp1;
    const words *ms2 = (words *)vp2;

    return strcmp(ms1->string_name, ms2->string_name);
    
}
int compare(const void *a, const void *b) // code from stackoverflow https://stackoverflow.com/questions/6105513/need-help-using-qsort-with-an-array-of-structs
{

    words *orderA = (words *)a;
    words *orderB = (words *)b;

    return (orderB->count_similar - orderA->count_similar);
}
void allocateWords(words **whatAllocate, const int lengthWhatAllocate)
{
    (*whatAllocate) = (words *)malloc(lengthWhatAllocate * sizeof(**whatAllocate));
}

bool inArray(int number_of_products, char *product_to_find, words *products, int *index_of_the_found)
{
    *index_of_the_found = binarySearch(number_of_products, product_to_find, products);
    if (*index_of_the_found == -1)
        return false;
    else
        return true;
}
void printArray(words *products, int products_to_print,int number_of_products, char sign)
{
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

//TODO: in binary search found the string, the we will add 1 to the count, in not -> create a new struct
int main(void)
{
    // char buffer[200];
    int realloc_variable = 10, counter_mem = 0, read = 0, number_of_products = 0, index_found = 0, products_to_print = 0;
    char sign;
    words *products = NULL;
    char *buffer = NULL;
    printf("Pocet sledovanych:\n");
    if (scanf(" %d", &products_to_print) != 1 || products_to_print )
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
            buffer = (char *)malloc(1000 * sizeof(char)); //allocating memory for buffer
            if (scanf(" %s", buffer) != 1 || strlen(buffer) > 99) //checking for the string input length
            {
                free(buffer);
                free(products);
                printf("Nespravny vstup.\n");
                return 1;
            }
            if (products == NULL)
                allocateWords(&products, realloc_variable); //function to allocate strings

            if (number_of_products >= 0)
                qsort(products, number_of_products, sizeof(words), ms_cmp_string1); //fucntion for quick sorting the array
            if (inArray(number_of_products, buffer, products, &index_found))        //TODO: maybe add 1 to number of products
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
            if (number_of_products == 0)
            {
                free(products);
                printf("Nejprodavanejsi zbozi: prodano 0 kusu\n");
                break;
            }
            qsort(products, number_of_products + 1, sizeof(words), compare);
            if (number_of_products < products_to_print)
            {
                printArray(products, number_of_products,number_of_products, sign); //TODO:maybe should add 1 to number_of_products
                break;
            }
            printArray(products, products_to_print,number_of_products, sign); //TODO:maybe should add 1 to number_of_products
            break;
        case '?':
            if (number_of_products == 0)
            {
                free(products);
                printf("Nejprodavanejsi zbozi: prodano 0 kusu\n");
                break;
            }
            qsort(products, number_of_products + 1, sizeof(words), compare);
            if (number_of_products < products_to_print)
            {
                printArray(products, number_of_products,number_of_products, sign);
                break;
            }

            printArray(products, products_to_print,number_of_products, sign);
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
