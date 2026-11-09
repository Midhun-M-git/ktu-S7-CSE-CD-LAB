%{
#include <stdio.h>
int yylex(void);
void yyerror(const char *s);
%}

%token NUMBER ID

%left '+' '-'
%left '*' '/'
%right UMINUS

%%
input : expr  ;

expr : expr '-' expr |expr '+' expr|'(' expr ')'|expr '*' expr | expr '/' expr | '-' expr %prec UMINUS |NUMBER | ID;

%%

void yyerror(const char *s){
    printf("\ninvalid expression");
}

int main(){
    printf("enter the expression : ");
    if(yyparse()==0){printf("valid expression");}
    return 0;
}
