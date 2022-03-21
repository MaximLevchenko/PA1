#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>



typedef struct
{
    char name[101];
    int count;

} words;

void printMax(words *numbers, int number_count)
{
    if (number_count < 10)
    {
        for (int i = 0; i < number_count; i++)
        {
            printf("%s %d\n", numbers[i].name, numbers[i].count);
        }
    }
    else
    {
        for (int i = 0; i < 10; i++)
        {
            printf("%s %d\n", numbers[i].name, numbers[i].count);
        }
    }
}

int inArray(words *numbers, char *buffer, int number_count, int *position_found)
{
    for (int i = 0; i < number_count; i++)
    {
        if (strcmp(buffer, numbers[i].name) == 0)
        {
            *position_found = i;
            return 1;
        }
    }
    return 0;
}

int isValid(char *buffer)
{
    int length = strlen(buffer);
    for (int i = 0; i < length; i++)
    {
        if (!isdigit(buffer[i]))
            return 0;
    }
    return 1;
}
int compare(const void *a, const void *b)
{
    words *orderA = (words *)a;
    words *orderB = (words *)b;
    return (orderB->count - orderA->count);
}

int main(void)
{

    words *numbers = (words *)malloc(sizeof(*numbers) * 100);
    char *buffer;
    int current_memory = 0, memory_allocated = 10, read = 0, number_count = 0, position_found;
    while (!feof(stdin))
    {
        buffer = (char *)malloc(sizeof(*buffer) * 100);
        memset(buffer, '\0', sizeof(*buffer) * 100);
        while ((read = scanf(" %s", buffer)) != feof(stdin) && isValid(buffer))
        {
            if (feof(stdin) && read != 0)
            {
                qsort(numbers, number_count, sizeof(words), compare);
                printMax(numbers, number_count);
                free(numbers);
                free(buffer);
                return 0;
            }
            if (++current_memory < 1 / 2 * memory_allocated)
            {
                memory_allocated += (memory_allocated > 100) ? memory_allocated * 1 / 2 : 10;
                numbers = (words *)realloc(numbers, memory_allocated * sizeof(*numbers));
            }

            if (inArray(numbers, buffer, number_count, &position_found))
            {
                numbers[position_found].count++;
                free(buffer);
                break;
            }
            numbers[number_count].count = 1;
            strcpy(numbers[number_count].name, buffer);
            free(buffer);

            number_count++;
            break;
        }
        // if (buffer != NULL)
        // {
        //     printf("Nespravny vstup.\n");
        //     free(buffer);
        //     free(numbers);
        // }
    }

    return 0;
}
