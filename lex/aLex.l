%{
    #include "aLex.h"
%}

%option outfile="aLexxer.c"

%%
"quit"              return 0;
"INSERT"            return INSERT;
"SELECT"            return SELECT;
"DROP"              return DROP;
:                   return COLON;
;                   return SEMICOLON;
[a-zA-Z]            return CHARACTER;
[0-9]               return INTEGER;
[ \t\n]             ;
.                   printf("unexpected character\n");

%%

int yywrap(void){
    return 1;
}
