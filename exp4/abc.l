%{

#include <stdio.h>
%}

%%
abc {printf("ABC");}
. {ECHO;}
\n {ECHO;}
%%

int main(){
    printf("Ente the string : ");
    yylex();
    return 0;
}

int yywrap(){
    return 1;
}