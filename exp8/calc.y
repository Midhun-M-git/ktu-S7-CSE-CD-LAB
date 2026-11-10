%{
#include <stdio.h>
int yylex();
void yyerror(const char *s);
%}

%union {
    long value;
}

%token <value> DIGIT

%type <value> expr
%left '+' '-' '*' '/'

%%
input : expr {printf("Result = %ld",$1);};
expr : expr '+' expr {$$ = $1 + $3;} | DIGIT {$$ = $1;};
%%

void yyerror(const char *s){
    printf("not valid ");
}

int main(){
printf("Enter the expression: ");
return yyparse();
}
