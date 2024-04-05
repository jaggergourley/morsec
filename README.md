# morsec - A Morse Code Translator

# C program that translates between Morse code and text in the terminal

## Features

- Translation of Morse code to text and text to Morse code.
- Supports letters (A-Z), numbers (0-9), and basic punctuation.

## Usage

To use the program, compile the source code and run the executable in your terminal. Follow the prompts to enter your input and choose the desired translation option.

### Compilation

`make` (using GCC)

### Execution

`./morsec`

## Example

```c
Have you always wanted to use an outdated form of communcation?
Type 'M' to input Morse code, or 'T' to input text, and press enter: m
Enter Morse code ('.' for dot/dit, '-' for dash/dah, using spaces between
letters and '/' between words, be sure to put spaces around '/' as well)
Will return '#' for an invalid Morse code sequence:
-- --- .-. ... . / -.-. --- -.. .
Translation: MORSE CODE
```
