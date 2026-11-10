%{
#include "indenty.tab.h"

%}

%%
[0-9]+ {return DIGIT;}
[a-zA-Z]+ {return LETTER;}
[ \n\t\r] ;
. {printf("%s",yytext);}
%%

int yywrap(){
    return 1;
}