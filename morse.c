#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* morse_input();
char* text_input();
char* morse_to_text(const char* morse);
char* text_to_morse(const char* text);

struct morse_entry {
    char character;
    const char* morse_code;
};

int main()
{
    char selection;
    char* morse;
    char* text;

    printf("Enter 'M' to input Morse code, or 'T' to input text.\n");
    scanf("%c", &selection);

    if (selection == 'm' || selection == 'M')
    {
        morse = morse_input();
    }
    else if (selection == 't' || selection == 'T')
    {
        text = text_input();
    }
    else
    {
        printf("Invalid choice\n");
    }

    return 0;
}

char* morse_input()
{
    char* input = malloc(100 * sizeof(char));

    printf("Enter Morse code (. for dot, - for dash): ");
    while (getchar() != '\n'); // Consume char in input buffer

    fgets(input, sizeof(input), stdin);

    // Remove newline character from input
    input[strcspn(input, "\n")] = '\0';

    for (int i = 0; input[i]; i++) {
        if (input[i] != '.' && input[i] != '-' && input[i] != ' ') {
            printf("Invalid Morse code! Use only '.', '-', and ' '\n");
            exit(1);
        }
    }

    printf("Input: %s\n", input);
    return input;
}

char* text_input()
{
    char* input = malloc(100 * sizeof(char));
    
    printf("Enter text: ");
    while (getchar() != '\n'); // Consume char in input buffer
    fgets(input, sizeof(input), stdin);

    // Remove newline character from input
    input[strcspn(input, "\n")] = '\0';

    printf("Input: %s\n", input);
    return input;
}

char* morse_to_text(const char* text)
{

    return NULL;
}

char* text_to_morse(const char* morse)
{

    return NULL;
}
