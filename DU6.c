#ifndef __PROGTEST__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#endif /* __PROGTEST__ */
#include <stdbool.h>
const char *delim = ">~[]':;/&*{}+=_\"()\n?!@#$%^|1234567890 \t.,-<";

typedef struct
{
    char *name;
} STRING1, STRING2;
// typedef struct
// {
//     char *name;
// } STRING2;

int compare(const void *a, const void *b) // code from stackoverflow
{
    STRING1 *orderA = (STRING1 *)a;
    STRING1 *orderB = (STRING1 *)b;
    return strcasecmp(orderA->name, orderB->name);
}
int compare2(const void *a, const void *b) // code from stackoverflow
{
    STRING2 *orderA = (STRING2 *)a;
    STRING2 *orderB = (STRING2 *)b;
    return strcasecmp(orderA->name, orderB->name);
}
int inArray(STRING1 *string_array, char *word_to_find, int count_words)
{
    for (int i = 0; i < count_words; i++) //not <= because we are not iterating the count before calling the function
    {
        if (strcasecmp(string_array[i].name, word_to_find) == 0)
        {
            return 1;
        }
    }
    return 0;
}

int compareStrings(STRING1 *string_array1, int length1, STRING2 *string_array2, int length2)
{
    if (length1 != length2)
    {
        return 0;
    }
    for (int i = 0; i < length2; i++)
    {
        if (strcasecmp(string_array1[i].name, string_array2[i].name))
        {
            return 0;
        }
    }
    return 1;
}
int inArray2(STRING2 *string_array2, char *word_to_find, int count_words)
{
    for (int i = 0; i < count_words; i++) //not <= because we are not iterating the count before calling the function
    {
        if (strcasecmp(string_array2[i].name, word_to_find) == 0)
        {
            return 1;
        }
    }
    return 0;
}
void allocateWords(STRING1 **whatAllocate, const int lengthWhatAllocate)
{
    (*whatAllocate) = (STRING1 *)malloc(lengthWhatAllocate * sizeof(**whatAllocate));
}
void allocateWords2(STRING2 **whatAllocate, const int lengthWhatAllocate)
{
    (*whatAllocate) = (STRING2 *)malloc(lengthWhatAllocate * sizeof(**whatAllocate));
}
int sameWords(const char *a, const char *b)
{
    STRING1 *string1 = NULL;
    int realloc_variable = 15, count = 0, counter_mem = 0;
    allocateWords(&string1, realloc_variable);
    char *first_str = strdup(a);
    char *token_first = strtok(first_str, delim);
    while (token_first != NULL)
    {
        if (++counter_mem >= realloc_variable / 4) //TODO:resizing the memory amount based on the amount of space left
        {
            realloc_variable += (realloc_variable > 100) ? realloc_variable * 1 / 2 : 10;
            string1 = (STRING1 *)realloc(string1, (realloc_variable + 1) * sizeof(*string1));
        }
        if (inArray(string1, token_first, count))
        {
            token_first = strtok(NULL, delim);
            continue;
        }
        string1[count].name = token_first;
        token_first = strtok(NULL, delim);
        count++;
    }
    STRING2 *string2 = NULL;
    int counter_mem2 = 0, realloc_variable2 = 15, count2 = 0;
    allocateWords2(&string2, realloc_variable2);
    char *second_str = strdup(b);
    char *token_second = strtok(second_str, delim);

    while (token_second != NULL)
    {

        if (++counter_mem2 >= realloc_variable2 / 4) //TODO:resizing the memory amount based on the amount of space left
        {
            realloc_variable2 += (realloc_variable2 > 100) ? realloc_variable2 * 1 / 2 : 10;
            string2 = (STRING2 *)realloc(string2, (realloc_variable2 + 1) * sizeof(*string2));
        }
        if (inArray2(string2, token_second, count2))
        {
            token_second = strtok(NULL, delim);
            continue;
        }
        string2[count2].name = token_second;
        token_second = strtok(NULL, delim);
        count2++;
    }
    qsort(string1, count, sizeof(STRING1), compare);
    qsort(string2, count2, sizeof(STRING2), compare2);
    if (compareStrings(string1, count, string2, count2))
    {
        free(string1), free(string2), free(first_str), free(second_str);
        return 1;
    }
    free(string1), free(string2), free(first_str), free(second_str);
    return 0;
}

#ifndef __PROGTEST__
int main(int argc, char *argv[])
{

    assert(sameWords(" He said 'hello!'", "'Hello.' he   said.") == 1);
    assert(sameWords("He said he would do it.", "IT said: 'He would do it.'") == 1);
    assert(sameWords("one two three", "one two five") == 0);
    return 0;
}
#endif /* __PROGTEST__ */