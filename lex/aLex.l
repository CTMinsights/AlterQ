%{
    #include "aLex.h"
    //#include "aLex.tab.h"
    //int yylex();
%}

%option outfile="aLexxer.c"

%%
"quit"              return 0;
"ALTER TABLE"       return ALTERTABLE;
"ALTER"             return ALTER;
"AND"               return AND;
"AS"                return AS;
"AVG"               return AVG;
"BETWEEN"           return BETWEEN;
"CASE"              return CASE;
"COUNT"             return COUNT;//check ()
"CREATE TABLE"      return CREATETABLE;
"CREATE"            return CREATE;
"DELETE FROM"       return DELETE;
"GROUP BY"          return GROUPBY;
"HAVING"            return HAVING;
"INNER JOIN"        return INNERJOIN;
"INSERT"            return INSERT;
"INSERT INTO"       return INSERTINTO;
"INTO"              return INTO;
"LIKE"              return LIKE;
"LIMIT"             return LIMIT;
"MAX"               return MAX;
"MIN"               return MIN;
"ORDER BY"          return ORDERBY;
"OR"                return OR;
"FULL OUTER JOIN"   return FULLOUTERJOIN;
"OUTER JOIN"        return OUTERJOIN;
"ROUND"             return ROUND;
"SELECT DISTINCT"   return SELECTDISTINCT;
"SELECT ALL"        return SELECT;
"SELECT"            return SELECT;
"SUM"               return SUM;
"UPDATE"            return UPDATE;
"WHERE"             return WHERE;
"DROP TABLE"        return DROPTABLE;// "TEXT"              return TEXT;

"true"|"TRUE"       return TRUE_B;
"false"|"FALSE"     return FALSE_B;
"PRIMARY KEY"       return PRIMARYKEY;
"FOREIGN KEY"       return FOREIGNKEY;
"KEY"               return KEY;
"BY"                return BY;
"UNIQUE"            return UNIQUE;
"REFERENCES"        return REFERENCES;
"IF"                return IF;
"END"               return END;
"WHEN"              return WHEN;
"ELSE"              return ELSE;
"THEN"              return THEN;
"COALESCE"          return COALESCE;
"NULLIF"            return NULLIF;
"CURRENT TIMESTAMP" return CURRENTTIMESTAMP;
"DEFAULT"           return DEFAULT;
"CAST"              return CAST;
"GENERATED"         return GENERATED;
"FULL JOIN"         return FULLJOIN;
"LEFT JOIN"         return LEFTJOIN;
"RIGHT JOIN"        return RIGHTJOIN;
"RENAME"            return RENAME;
"COLUMN"            return COLUMN;
"WITH NO DATA"      return WITHNODATA;
"WITH DATA"         return WITHDATA;
"WITH"              return WITH;
"DATA"              return DATA;
"NOT EXISTS"        return NOTEXISTS;
"IF EXISTS"         return IFEXISTS;
"EXISTS"            return EXISTS;
"OFFSET"            return OFFSET;
"ROW"               return ROW;
"ONLY"              return ONLY;
"FIRST"             return FIRST;
"FETCH"             return FETCH;
"CUBE"              return CUBE;
"ROLLUP"            return ROLLUP;
"EXTRACT"           return EXTRACT;
"CROSS JOIN"        return CROSSJOIN;
"NATURAL JOIN"      return NATURALJOIN;
"TRUNCATE TABLE"    return TRUNCATE;
"ANY"               return ANY;
"ALL"               return ALL;
"SET"               return SET;
"RETURNING"         return RETURNING;
"RETURNING *"       return RETURNINGSTAR;
"FROM"              return FROM;
"REPLACE"           return REPLACE;
"VIEW"              return VIEW;
"SEQUENCE"          return SEQUENCE;
"NEXTVAL"           return NEXTVAL;
"CURRVAL"           return CURRVAL;
"ILIKE"             return ILIKE;
"LENGTH"            return LENGTH;
"FUNCTION"          return FUNCTION;
"PERFORM"           return PERFORM;
"DECLARE"           return DECLARE;
"COPY"              return COPY;
"PG_DATABASE"       return PGDB;
"BEGIN"             return BEGIN_T;
"ADD"               return ADD;
"DROP"              return DROP;
"COMMENT"           return COMMENT;
"COLLATE"           return COLLATE;
"INHERITS"          return INHERITS;
"PARTITION BY"      return PARTITION;
"RANGE"             return RANGE;
"LIST"              return LIST;
"HASH"              return HASH;
"TEMP"|"TEMPORARY"  return TEMP;
"UNLOGGED"          return UNLOGGED;
"EXCLUDE"           return EXCLUDE;
"ASC"               return ASC;
"DESC"              return DESC;
"NULLS"             return NULLS;
"NOT NULL"          return ISNOTNULL;
"NULL"              return ISNULL;
"INCLUDING"         return INCLUDING;
"EXCLUDING"         return EXCLUDING;
"GLOBAL"            return GLOBAL;
"LOCAL"             return LOCAL;
"TABLESPACE"        return TABLESPACE;
"CASCADE"           return CASCADE;
"CONTINUE IDENTITY" return CONTINUEIDEN;
"RESTART IDENTITY"  return RESTARTIDEN;
"IF NOT EXISTS"     return IFNOTEXISTS;
"TO"                return TO;
"CONSTRAINT"        return CONSTRAINT;
"SCHEMA"            return SCHEMA;
"DETACH"            return DETACH;
"PARTITION"         return PARTITION;
"RESTRICT"          return RESTRICT;
"VALUES"            return VALUES;
"TABLE"             return TABLE;
"ADD COLUMN"        return ADDCOL;
"DROP COLUMN"       return DROPCOL;
                    
[0-9]+                  return NUMBER;//Check integer sizes (need to check for leading 0s)//Maybe change numbers to numbers. So do yylval=atoi(yytext); return NUM;think i need .y bison file for this
[0-9]+[.][0-9]+         return NUMWDEC;//need to check for leading 0s
['][a-zA-Z_ - 0-9]*[']  return (yyleng==2 ? NULLCHAR : yyleng==3 ? CHARACTER : STRING);//Check string sizes
["][a-zA-Z_ - 0-9]*["]  return (yyleng==2 ? NULLCHAR : yyleng==3 ? CHARACTER : STRING);//Check string sizes
[0-1]?[0-9][/][0-3]?[0-9][/][0-9][0-9][0-9][0-9] return DATE; //prolly a better way to check for 4 numbers
:                       return COLON;
;                       return SEMICOLON;
"<>"                      return NOTEQUALS;
"<="                     return LESSEQUAL;
">="                      return GREATEQUAL;
"<"                     return LESSER;
">"                       return GREATER;
=                       return EQUALS;
"+"                     return PLUS;
"-"                     return MINUS;
"*"                     return AST;
"("                     return OPENPAREN;
")"                     return CLOSEPAREN;
"["                     return OPENBRACKET;
"]"                     return CLOSEBRACKET;
"{"                     return OPENBRACE;
"}"                     return CLOSEBRACE;
","                     return COMMA;
[a-zA-Z][a-zA-Z0-9_-]+   return STRINGNOQUOTES;//Need to add more accepted chars
[a-zA-Z]                return CHARACTER;
[ \t\n]                 ;
.                       printf("unexpected character\n");

%%
//Gotta add functionality for ()s or maybe just not
int yywrap(void){
    return 1;
}
