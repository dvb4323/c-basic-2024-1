#include <stdio.h>
#include <string.h>

int main()
{
    char sentence[] = "";

    printf("Enter the sentence: \n");
    fgets(sentence, sizeof(sentence), stdin);

    for (int i = 0; i < strlen(sentence); i++)
    {
    }

    return 0;
}