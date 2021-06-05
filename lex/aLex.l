%{
    #include "aLex.h"
%}

%option outfile="aLexxer.c"

%%
"quit"              return 0;

[0-9]+              return (yyleng<=3 ? SMALLINT : yyleng<=8 ? INTEGER : BIGINT);//Check integer sizes
['][a-zA-Z]*[']     return (yyleng==2 ? NULLCHAR : yyleng==3 ? CHARACTER : STRING);//Check string sizes
["][a-zA-Z]*["]     return (yyleng==2 ? NULLCHAR : yyleng==3 ? CHARACTER : STRING);//Check string sizes
[$][0-9]*[.][0-9]*  return MONEY;//Example, not actually how we'll parse money
"INSERT"            return INSERT;
"SELECT"            return SELECT;
"DROP"              return DROP;
:                   return COLON;
;                   return SEMICOLON;
[a-zA-Z]            return CHARACTER;
[ \t\n]             ;
.                   printf("unexpected character\n");

%%

int yywrap(void){
    return 1;
}
