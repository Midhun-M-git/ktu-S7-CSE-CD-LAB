// This c program constitue the target code generation program of exp13 of ktu
// cse lab of 2019 scheme
/*Author : Midhun M
email : mmidhun781@gmail.com
*/

#include <stdio.h>  //include the header files for standard input output files.
#include <string.h> //include the string handelling headers

int main() // This is the entry function
{
  char icode[10][30], str[10], opr[10]; // declare 3 character array strings
  int i = 0;

  printf("Enter the set of intermediate code");
  do {
    scanf("%s", icode[i]);
  } while (strcmp(icode[i++], "exit") != 0);

  printf("\nTarget code generation");
  i = 0;
  do {
    strcpy(str, icode[i]);
    switch (str[3]) {
    case '+':
      strcpy(opr, "ADD");
      break;
    case '-':
      strcpy(opr, "SUB");
      break;
    case '*':
      strcpy(opr, "MULL");
      break;
    case '/':
      strcpy(opr, "DIV");
      break;
    }
    printf("\nMov %c ,R%d", str[2], i);
    printf("\n\t%s %c,R%d", opr, str[4], i);

  } while (strcmp(icode[i++], "exit") != 0);
  return 0;
}