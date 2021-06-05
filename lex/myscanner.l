%{
    #include "myscanner.h"
%}

%%

:           return COLON;
"db_type"   return TYPE;
"db_name"   return NAME;

%%

int yywrap(void){
    return 1;
}