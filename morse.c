#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
- .... .. ... / .. ... / .- / .--. .-. --- --. .-. .- -- / .-- .-. .. - - . -. /
.. -. / -.-. / - --- / - .-. .- -. ... .-.. .- - . / -... . - .-- . . -. / --
--- .-. ... . / -.-. --- -.. . / .- -. -.. / - . -..- - -.-.--
*/

// .-- .... .- - / .... .- - .... / --. --- -.. / .-- .-. --- ..- --. .... -

char *morse_input();
char *text_input();
char decode_morse_token(const char *token);
char *morse_to_text(char *morse);
const char *decode_text_char(const char character);
char *text_to_morse(char *text);

// Struct to hold character and morse code equivalent
struct morse_entry {
  char character;
  const char *morse_code;
};

// Array of structs to store character-to-Morse mappings
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
  char *translation;

  printf("Have you always wanted to use an outdated form of communcation?\n");
  printf(
      "Type 'M' to input Morse code, or 'T' to input text, and press enter: ");
  scanf("%c", &selection);

  if (selection == 'm' || selection == 'M') {
    morse = morse_input();
    translation = morse_to_text(morse);
    printf("Translation: %s\n", translation);
  } else if (selection == 't' || selection == 'T') {
    text = text_input();
    translation = text_to_morse(text);
    printf("Translation: %s\n", translation);
  } else {
    printf("Invalid Choice!\n");
  }

  return 0;
}

char *morse_input() {
  char *input = malloc(1024 * sizeof(char));
  if (input == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(1);
  }

  printf("Enter Morse code ('.' for dot/dit, '-' for dash/dah, using spaces "
         "between\nletters and '/' between words, be sure to put spaces "
         "around '/' as well)\nWill return '#' for an invalid Morse code "
         "sequence:\n");

  // Consume char in input buffer
  while (getchar() != '\n')
    ;

  fgets(input, 1024, stdin);

  // Remove newline character from input
  input[strcspn(input, "\n")] = '\0';

  for (int i = 0; input[i]; i++) {
    if (input[i] != '.' && input[i] != '-' && input[i] != ' ' &&
        input[i] != '/') {
      printf("Invalid Morse code! Use only '.', '-', '/', and ' '\n");
      exit(1);
    }
  }

  return input;
}

char *text_input() {
  char *input = malloc(1024 * sizeof(char));

  printf("Enter text (alphanumeric and .,?'!/()&:;=+-_$@):\n");

  // Consume char in input buffer
  while (getchar() != '\n')
    ;
  fgets(input, 1024, stdin);

  // Remove newline character from input
  input[strcspn(input, "\n")] = '\0';

  for (int i = 0; input[i]; i++) {
    if (!isalnum(input[i]) && input[i] != ' ' && input[i] != '.' &&
        input[i] != ',' && input[i] != '?' && input[i] != '\'' &&
        input[i] != '!' && input[i] != '/' && input[i] != '(' &&
        input[i] != ')' && input[i] != '&' && input[i] != ':' &&
        input[i] != ';' && input[i] != '=' && input[i] != '+' &&
        input[i] != '-' && input[i] != '_' && input[i] != '$' &&
        input[i] != '@') {
      printf("Invalid text! Alphanumeric (A-Z, a-z, 0-9), .,?'!/()&:;=+-_$@, "
             "and spaces only!\n");
      exit(1);
    }
  }

  return input;
}

char decode_morse_token(const char *token) {
  if (token == NULL) {
    printf("token is null\n");
  }

  for (size_t i = 0; i < sizeof(morse_table) / sizeof(morse_table[0]); i++) {
    if (strcmp(token, morse_table[i].morse_code) == 0) {
      // Return corresponding character
      return morse_table[i].character;
    }
  }
  // Unmatched character
  return '#';
}

char *morse_to_text(char *morse) {
  char *decoded_message = malloc(1024 * sizeof(char));
  char *token = strtok(morse, " ");

  while (token != NULL) {

    // Decode Morse token and append to message string
    char decoded_token = decode_morse_token(token);

    strncat(decoded_message, &decoded_token, 1);

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
    if (toupper(character) == morse_table[i].character) {
      // Return corresponding morse
      return morse_table[i].morse_code;
    }
  }
  // Unmatched character
  return "#";
}

char *text_to_morse(char *text) {
  char *decoded_message = malloc(1024 * sizeof(char));

  // Longest we will consider is 7 chars
  char *decoded_char = malloc(7 * sizeof(char));

  for (int i = 0; text[i]; i++) {
    // Cast to char * to avoid const issue
    decoded_char = (char *)decode_text_char(text[i]);

    strcat(decoded_message, decoded_char);
    strcat(decoded_message, " "); // Append space between characters
  }

  return decoded_message;
}
