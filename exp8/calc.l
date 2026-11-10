%{
#include <stdlib.h>
#include "calc.tab.h"
%}

%%
[0-9]+ {yylval.value = atoi(yytext);return DIGIT;}
[ \n\t\r] ;
. {return yytext[0];}
%%

int yywrap(){return 1;}