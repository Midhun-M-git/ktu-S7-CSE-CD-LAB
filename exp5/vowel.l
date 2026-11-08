%{
    #include<stdio.h>
    int vowels = 0;
    int consonent = 0;
%}

%%
[AEIOUaeiou] {vowels++;}
[a-zA-Z] {consonent++;}
. ;

%%

int main(){
    printf("enter the string ");
    yylex();
    printf("\n number of vowel = %d",vowels);
    printf("\n number of consonent = %d",consonent);
    return 0;
}

int yywrap(){
    return 1;
}
