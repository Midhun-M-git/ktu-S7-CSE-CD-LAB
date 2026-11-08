%{
#include <stdio.h>

%}

%%
[0-9]+ {printf(" %s Number",yytext);}
[a-zA-Z0-9]+ {printf("identifier");}
[ \t\n\r] ;
. ;

%%
int main(){
    printf("enter the statement");
    yylex();
    return 0;
}
int yywrap(){
    return 1;
}