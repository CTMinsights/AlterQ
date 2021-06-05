%{
    #include "aLex.h"
%}

%option outfile="aLexxer.c"

%%
"quit"              return 0;
"ALTER"             return ALTER;
"ALTER TABLE"       return ALTERTABLE;
"AND"               return AND;
"AS"                return AS;
"AVG"               return AVG;
"BETWEEN"           return BETWEEN;
"CASE"              return CASE;
"COUNT"             return COUNT;
"CREATE TABLE"      return CREATETABLE;
"DELETE"            return DELETE;
"GROUP BY"          return GROUPBY;
"HAVING"            return HAVING;
"INNER JOIN"        return INNERJOIN;
"INSERT"            return INSERT;
"INSERT INTO"       return INSERTINTO;
"IS NULL"           return ISNULL;
"IS NOT NULL"       return ISNOTNULL;
"LIKE"              return LIKE;
"LIMIT"             return LIMIT;
"MAX"               return MAX;
"MIN"               return MIN;
"ORDER BY"          return ORDERBY;
"OR"                return OR;
"OUTER JOIN"        return OUTERJOIN;
"ROUND"             return ROUND;
"SELECT DISTINCT"   return SELECTDISTINCT;
"SELECT"            return SELECT;
"SUM"               return SUM;
"UPDATE"            return UPDATE;
"WHERE"             return WHERE;
"DROP"              return DROP;

[$][0-9]*[.]?[0-9]*     return MONEY;  //example, not actually how we will parse money
[0-9]+                  return (yyleng<=3 ? SMALLINT : yyleng<=8 ? INTEGER : BIGINT);//Check integer sizes (need to check for leading 0s)
['][a-zA-Z_]*[0-9]*[']  return (yyleng==2 ? NULLCHAR : yyleng==3 ? CHARACTER : STRING);//Check string sizes
["][a-zA-Z_]*[0-9]*["]  return (yyleng==2 ? NULLCHAR : yyleng==3 ? CHARACTER : STRING);//Check string sizes
[0-1]?[0-9][/][0-3]?[0-9][/][0-9][0-9][0-9][0-9] return DATE; //prolly a better way to check for 4 numbers
[0-9]+[.][0-9]+         return (yyleng<=8 ? FLOAT : DOUBLE);//need to check for leading 0s
:                       return COLON;
;                       return SEMICOLON;
"("                     return OPENPAREN;
")"                     return CLOSEPAREN;
"["                     return OPENBRACKET;
"]"                     return CLOSEBRACKET;
"{"                     return OPENBRACE;
"}"                     return CLOSEBRACE;
","                     return COMMA;
[a-zA-Z][a-zA-Z0-9_]+   return STRINGNOQUOTES;
[a-zA-Z]                return CHARACTER;
[ \t\n]                 ;
.                       printf("unexpected character\n");

%%

int yywrap(void){
    return 1;
}
