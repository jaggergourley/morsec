#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Pointers: *
When declaring variable -> char* var declares pointer to char named 'var'

When useing pointer to access value it points to -> *var dereferences pointer
'var' to access value it points to

& is address-of -> int* ptr = &x assigns address of x to ptr
*/

char *morse_input();
char *text_input();
char decode_morse_token(const char *token);
char *morse_to_text(char *morse);
char *text_to_morse(char *text);

// define a struct to hold character and morse code equivalent
struct morse_entry {
  char character;
  const char *morse_code;
};

// array of structs to store char-morse mappings
struct morse_entry morse_table[] = {
    {'A', ".-"},      {'B', "-..."},   {'C', "-.-."},   {'D', "-.."},
    {'E', "."},       {'F', "..-."},   {'G', "--."},    {'H', "...."},
    {'I', ".."},      {'J', ".---"},   {'K', "-.-"},    {'L', ".-.."},
    {'M', "--"},      {'N', "-."},     {'O', "---"},    {'P', ".--."},
    {'Q', "--.-"},    {'R', ".-."},    {'S', "..."},    {'T', "-"},
    {'U', "..-"},     {'V', "...-"},   {'W', ".--"},    {'X', "-..-"},
    {'Y', "-.--"},    {'Z', "--.."},   {'1', ".----"},  {'2', "..---"},
    {'3', "...--"},   {'4', "....-"},  {'5', "....."},  {'6', "-...."},
    {'7', "--..."},   {'8', "---.."},  {'9', "----."},  {'0', "-----"},
    {'.', ".-.-.-"},  {',', "--..--"}, {'?', "..--.."}, {'\'', ".----."},
    {'!', "-.-.--"},  {'/', "-..-."},  {'(', "-.--."},  {')', "-.--.-"},
    {'&', ".-..."},   {':', "---..."}, {';', "-.-.-."}, {'=', "-...-"},
    {'+', ".-.-."},   {'-', "-....-"}, {'_', "..-.-"},  {'"', ".-..-."},
    {'$', "...-..-"}, {'@', ".--.-."}, {' ', "/"}};

int main() {
  char selection;
  char *morse;
  char *text;
  // char *translation;

  printf("Enter 'M' to input Morse code, or 'T' to input text.\n");
  scanf("%c", &selection);

  if (selection == 'm' || selection == 'M') {
    morse = morse_input();
    printf("Morse input from main: %s\n", morse);
    morse_to_text(morse);
  } else if (selection == 't' || selection == 'T') {
    text = text_input();
    printf("Text input from main: %s\n", text);
    text_to_morse(text);
  } else {
    printf("Invalid Choice!\n");
  }

  return 0;
}

char *morse_input() {
  char *input = malloc(256 * sizeof(char));
  if (input == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(1);
  }

  printf("Enter Morse code ('.' for dot, '-' for dash, using spaces between\n"
         "letters and '/' between words, be sure to put spaces around '/' as\n"
         "well): ");

  // Consume char in input buffer
  while (getchar() != '\n')
    ;

  fgets(input, 256, stdin);
  printf("Morse input before newline remove: %s\n", input);

  // Remove newline character from input
  input[strcspn(input, "\n")] = '\0';

  for (int i = 0; input[i]; i++) {
    if (input[i] != '.' && input[i] != '-' && input[i] != ' ' &&
        input[i] != '/') {
      printf("Invalid Morse code! Use only '.', '-', '/', and ' '\n");
      exit(1);
    }
  }

  printf("Morse input: %s\n", input);
  return input;
}

char *text_input() {
  char *input = malloc(256 * sizeof(char));

  printf("Enter text (alphanumeric): ");

  // Consume char in input buffer
  while (getchar() != '\n')
    ;
  fgets(input, 256, stdin);

  // Remove newline character from input
  input[strcspn(input, "\n")] = '\0';

  for (int i = 0; input[i]; i++) {
    if (!isalnum(input[i]) && input[i] != ' ') {
      printf("Invalid text! Alphanumeric (A-Z, a-z, 0-9) and spaces only !\n");
      exit(1);
    }
  }

  printf("Text input: %s\n", input);
  return input;
}

// takes in sequence of '.' and '-'
char decode_morse_token(const char *token) {
  if (token == NULL) {
    printf("token is null\n");
  }

  for (size_t i = 0; i < sizeof(morse_table) / sizeof(morse_table[0]); i++) {
    // printf("in the loop looking for char match: %zu\n", i);
    if (strcmp(token, morse_table[i].morse_code) == 0) {
      printf("Decoded character: %c\n", morse_table[i].character);
      // Return corresponding character
      return morse_table[i].character;
    }
  }
  // Unmatched character
  return '?';
}

// char* indicates that the function returns a pointer to a char (string)

// const char* text inidicates that function takes a pointer to a const char
//  (string that cannot be modified) as argument

// should be return a pointer to char (string)
char *morse_to_text(char *morse) {
  char *decoded_message = malloc(256 * sizeof(char));
  char *token = strtok(morse, " ");

  while (token != NULL) {
    printf("From morse_to_text sending token: %s\n", token);

    // Decode Morse token and append to message string
    char decoded_token = decode_morse_token(token);
    printf("Decoded token: %c\n", decoded_token);

    strncat(decoded_message, &decoded_token, 1);
    printf("Current message: %s\n", decoded_message);

    // Get next token
    token = strtok(NULL, " ");

    // If token is '/', append a space
    if (token != NULL && strcmp(token, "/") == 0) {
      strcat(decoded_message, " ");
      token = strtok(NULL, " "); // Move to next token after '/'
    }
  }

  return decoded_message;
}

const char *decode_text_char(const char character) {
  for (size_t i = 0; i < sizeof(morse_table) / sizeof(morse_table[0]); i++) {
    // printf("in the loop looking for char match: %zu\n", i);
    if (toupper(character) == morse_table[i].character) {
      printf("Decoded morse: %s\n", morse_table[i].morse_code);
      // Return corresponding morse
      return morse_table[i].morse_code;
    }
  }
  // Unmatched character
  return "?";
}
char *text_to_morse(char *text) {
  char *decoded_message = malloc(256 * sizeof(char));

  // Longest we will consider is 6 chars
  char *decoded_char = malloc(6 * sizeof(char));

  for (int i = 0; text[i]; i++) {
    decoded_char = (char *)decode_text_char(text[i]);
    printf("Decoded char: %s\n", decoded_char);
    strcat(decoded_message, decoded_char);
    strcat(decoded_message, " "); // Append space between characters
    printf("Current decoded message from text_to_morse: %s\n", decoded_message);
  }

  return decoded_message;
}
