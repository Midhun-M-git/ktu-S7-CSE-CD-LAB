%{
#include <stdio.h>
int lines =0;
int character =0;
int words = 0;

%}

%%
[^ \t\n\r]+ {words++;character+=yyleng;}
[\t]+ {character++;}
[\n]+ {lines++;}
. ;

%%

int main(){
printf("enter the string");
yylex();
printf("\nNumber of words = %d",words);
printf("\nNumber of characters = %d",character);
printf("\nNumber of lines = %d",lines);
    return 0;
}


int yywrap(){
    return 1;
}