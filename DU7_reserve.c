#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

// strupr();
bool isValid(char *array) //checks whether the abbreviation is valid or not
{
    int length = strlen(array);
    for (int i = 0; i < length; i++)
    {
        if (array[i] != toupper(array[i])) //|| !isalpha(array[i])
            return false;
    }
    return true;
}

void allocateWords(char **whatAllocate, const int lengthWhatAllocate) //allocation
{
    (*whatAllocate) = (char *)malloc(lengthWhatAllocate * sizeof(**whatAllocate));
}
void makeString(char **final_str, char *str, int second_quote_pos, int first_quote_pos, int *str_length)
{
    *str_length = second_quote_pos - first_quote_pos - 1; //difference between indexes
    allocateWords(final_str, *str_length);
    strncpy(*final_str, str + first_quote_pos + 1, *str_length);
}

bool getPosition(int *first_quote_pos, int *second_quote_pos, char *abbreviation, char *buffer, int size)
{
    for (int i = 0, quotes_count = 0; i < size - 1; i++)
    {
        if (buffer[i] == '"')
        {
            quotes_count++;
            if (quotes_count == 1)
            {
                *first_quote_pos = i;
                printf("%d first pos\n", *first_quote_pos);
            }
            if (quotes_count == 2)
            {
                *second_quote_pos = i;
                printf("%d second pos\n", *second_quote_pos);
            }
            if ((quotes_count < 2 && first_quote_pos != 0 && second_quote_pos != 0))
            {
                
            }
        }
    }
    return true;
}

bool getPositionQuotations(char *buffer, char *final_string, char *abbreviation, int index,
                           int quotes_count, int *first_quote_pos, int *second_quote_pos, int flag)
{

    if (!flag)
    {
        if (quotes_count == 1)
        {
            *first_quote_pos = index;
            printf("%d first pos\n", *first_quote_pos);
        }
        if (quotes_count == 2)
        {
            *second_quote_pos = index;
            printf("%d second pos\n", *second_quote_pos);
        }
        if (quotes_count > 2)
        {
            printf("Nespravny vstup.\n");
            free(final_string), free(buffer), free(abbreviation);
            return 0;
        }
    }
    if (*first_quote_pos != 0 && *second_quote_pos != 0 && quotes_count < 2)
    {
        printf("Nespravny vstup.\n");
        free(final_string), free(buffer), free(abbreviation);
        return 0;
    }
    return 1;
}
int main()
{
    char *buffer = NULL, *final_string = NULL, *abbreviation = (char *)malloc(300 * sizeof(char));
    int quotes_count = 0, str_length = 0, first_quote_pos = 0, second_quote_pos = 0, flag;
    size_t mem_allocated = 0, mem_allocated_abbreviation;
    ssize_t size = 0; //returns the size of an array with
    printf("Zkratka:\n");
    if (getline(&abbreviation, &mem_allocated_abbreviation, stdin) == 0 || !isValid(abbreviation))
    {
        printf("Nespravny vstup.\n");
        free(abbreviation);
        return 1;
    }
    printf("%ld\n", strlen(abbreviation));
    while ((size = getline(&buffer, &mem_allocated, stdin)) != feof(stdin))
    {
        quotes_count = 0; //reseting the value of the quotes count for the next iteration
        if (feof(stdin) && size != 0)
        {
            free(buffer);
            return 1;
        }
        printf("%s %zu %ld\n", buffer, size, mem_allocated);

        for (int index = 0; index < size - 1; index++)
        {

            if (buffer[index] == '"')
            {
                quotes_count++;
                flag = 0;
                if (!getPositionQuotations(buffer, final_string, abbreviation, index, quotes_count, &first_quote_pos, &second_quote_pos, flag))
                    return 1;
                // printf("Hello nice one position is %d\n", first_quote_pos);
                // continue;
            }
        }
        flag = 1;
        if (!getPositionQuotations(buffer, final_string, abbreviation, 0, quotes_count, &first_quote_pos, &second_quote_pos, flag))
            return 1;
        makeString(&final_string, buffer, second_quote_pos, first_quote_pos, &str_length);
        printf("%d\n", str_length);
        for (int j = 0; j < str_length; j++)
            printf("%c", final_string[j]);
        printf("\n");
        free(final_string);
        final_string = NULL;
    }
    free(abbreviation);
    free(buffer);
    return 0;
}