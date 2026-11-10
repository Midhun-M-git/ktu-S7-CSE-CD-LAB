%{
    #include <stdio.h>
    int yylex();
    void yyerror(const char *s);
%}

%token LETTER DIGIT

%%
input :LETTER tail ;
tail : /*empty*/ | LETTER tail | DIGIT tail ;

%%

void yyerror(const char *s){
    printf("Invalid identifier");
}

int main(){
    printf("enter the String: ");
    if(yyparse()==0){
        printf("valid identifier");
    }
    return 0;

}