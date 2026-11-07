//This program is based on lexical analysis in c.
/*  Theory of Lexical Analysis 
-> Lexical analysis is the first phase of a compiler. It takes the input in the form of characters and produces tokens as output. The main function of lexical analysis is to read the source code and convert it into a sequence of tokens, which are meaningful sequences of characters.
-> The lexical analyzer, also known as a lexer or scanner, performs the following tasks:

eg: int a = 5;
output :    Keyword : int
            Identifier : a
            Operator : =
            Constant : 5

Algorithm for Lexical Analysis:
1.Start
2.Import the necessary header files.
3.Define the main function
4.Declare an array pointer to store keywords.
5.Read input from user;
6.Use a loop to iterate through each character of the input.
6.1.when a space is found , skip it.
6.2.when a alphanumeric character is found:
    6.2.1 check if it is a keyword or identifier.
    6.2.2 if it is a keyword, print it as a keyword.
    6.2.3 if it is an identifier, print it as an identifier.
7.if number print number.
8.if it is an operator print operator
9.if it is a seperator print separator.
end

*/

#include <stdio.h> //printf(), scanf()
#include <string.h> //strcmp()
#include <ctype.h> //isalpha(),isdigit()

int main(void){
 const char *keywords[] = {"int", "float", "if", "else", "while", "return"};
 char input[100];
 printf("Enter the string : ");
 if (fgets(input, sizeof(input), stdin) == NULL) {
     return 1;
 }

 for (int i = 0; input[i] != '\0';) {
     if (isspace((unsigned char)input[i])) {
         i++;
     } else if (isalpha((unsigned char)input[i]) || input[i] == '_') {
         char token[100];
         int found = 0;
         int j = 0;

         while (isalnum((unsigned char)input[i]) || input[i] == '_') {
             token[j++] = input[i++];
         }
         token[j] = '\0';

         for (size_t k = 0; k < sizeof(keywords) / sizeof(keywords[0]); k++) {
             if (strcmp(token, keywords[k]) == 0) {
                 found = 1;
                 break;
             }
         }
         printf("%s : %s\n", found ? "Keyword" : "Identifier", token);
     } else if (isdigit((unsigned char)input[i])) {
         while (isdigit((unsigned char)input[i])) {
             putchar(input[i++]);
         }
         if (input[i] == '.' && isdigit((unsigned char)input[i + 1])) {
             putchar(input[i++]);
             while (isdigit((unsigned char)input[i])) {
                 putchar(input[i++]);
             }
         }
         printf(" : Number\n");
     } else if (strchr("+-*/%=<>!&|", input[i]) != NULL) {
         char op = input[i++];
         if ((op == '+' && input[i] == '+') || (op == '-' && input[i] == '-') ||
             input[i] == '=' || (op == '&' && input[i] == '&') ||
             (op == '|' && input[i] == '|')) {
             printf("%c%c : Operator\n", op, input[i++]);
         } else {
             printf("%c : Operator\n", op);
         }
     } else if (strchr("{}();:,[]", input[i]) != NULL) {
         printf("%c : Separator\n", input[i++]);
     } else {
         printf("%c : Invalid character\n", input[i++]);
     }
 }

 return 0;
}