/* We will be writing the program to simulate the working of the lexical
analyzer. This is an optional program in the syllabus, the experiments may start 
with the lex or yacc programs.

author : Midhun M
email: mmidhun781@gmail.com
github : Midhun-M-git
*/

#include <stdio.h>  // header file for input output functions such as printf, scanf etc
#include <stdlib.h> // includes malloc, calloc, atoi etc.. and other macro functions
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

// Now we will be creating the reservedtable that consist of the reserve words.
const char *reservedtable[] = { 
    "int", "char", "long", "double", "do", "while", "if", "else", "break", "continue"
};

bool isReserved(char *word) 
{
    for(int i = 0; i < 10; i++) 
    {
        // FIX 1: Must explicitly check if strcmp returns 0
        if(strcmp(word, reservedtable[i]) == 0) 
        {
            return true;
        }
    }
    return false;
}                           

int main () // This is the main function where the program entry begins
{     
    char ch;          // Variable to read characters
    char buffer[100]; // Buffer to store the strings
    int index = 0;    // The buffer index
    FILE *fp;         // Create a file pointer

    fp = fopen("a.c", "r");  // open the c file in read mode using the fopen() 
    
    if(fp == NULL) // if the file pointer is empty
    {
        printf("Error: The file could not be opened!\n");
        return 1;    
    }
    
    printf("The file opened successfully.\n\n");

    while ((ch = fgetc(fp)) != EOF) // we will be reading till the end of the file
    {
        if(isalnum(ch) || ch == '_') // if it is number, letter or underscore
        {
            buffer[index++] = ch;
        }
        else 
        {
            // FIX 2: Everything involving a finished word must happen inside this block
            if(index > 0) 
            {
                buffer[index] = '\0'; // Null-terminate the string
                
                if (isReserved(buffer)) 
                {
                    printf("keyword : %s\n", buffer);
                }
                
                index = 0; // Reset index for the next word
            }
        }
    }

    fclose(fp); // Always a good habit to close the file when you are done!
    return 0;
}