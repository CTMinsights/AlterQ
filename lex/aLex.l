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
"SELECT"            return SELECT;
"SUM"               return SUM;
"UPDATE"            return UPDATE;
"WHERE"             return WHERE;
"DROP TABLE"        return DROPTABLE;
"TEXT"              return TEXT;
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
"RENAME COLUMN"     return RENAMECOL;
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
"CONTINUE IDENTITY" return CONTIDEN;
"RESTART IDENTITY"  return RESIDEN;

"text"|"TEXT"                                   return TEXT;
"int"|"integer"|"int4"|"INT"|"INTEGER"|"INT4"   return INT_T;
"smallint"|"int2"|"SMALLINT"|"INT2"             return SMALLINT_T;
"bigint"|"int8"|"BIGINT"|"INT8"                 return BIGINT_T; 
"smallserial"|"serial2"|"SMALLSERIAL"|"SERIAL2" return SMALLSERIAL;
"serial"|"serial4"|"SERIAL"|"SERIAL4"           return SERIAL;
"bigserial"|"serial8"|"BIGSERIAL"|"SERIAL8"     return BIGSERIAL;
"boolean"|"bool"|"BOOLEAN"|"BOOL"               return BOOLEAN;
"bit"|"BIT"                                     return BIT;
"varbit"|"bit varying"|"VARBIT"|"BIT VARYING"   return VARBIT;
"box"|"BOX"                                     return BOX;
"bytea"|"BYTEA"                                 return BYTEA;
"character"|"char"|"CHARACTER"|"CHAR"           return CHAR;
"character varying"|"varchar"|"VARCHAR"|"CHARACTER VARYING" return VARCHAR_T;
"cidr"                  return CIDR;
"circle"                return CIRCLE;
"date"                  return DATE;
"double precision"|"float8" return DOUBLE_T;
"inet"                  return INET;
"interval"              return INTERVAL;
"json"                  return JSON;
"jsonb"                 return JSONB;
"line"                  return LINE;
"lseg"                  return LSEG;
"macaddr"               return MACADDR;
"macaddr8"              return MACADDR8;
"money"                 return MONEY_T;
"numeric"|"decimal"     return NUMERIC;
"path"                  return PATH;
"pg_lsn"                return PGLSN;
"pg_snapshot"           return PGSNAP;
"point"                 return POINT;
"polygon"               return POLYGON;
"real"|"float4"         return REAL;
"time"                  return TIMENOZONE;//Need to add zone/nozone and other [] stuff
"time2"|"timetz"        return TIMEWITHZONE;//Need to add zone/nozone and other [] stuff
"timestamp"|"TIMESTAMP"    return TIMESTAMPNOZONE;//Need to add zone/nozone and other [] stuff
"timestamp2"|"timestamptz" return TIMESTAMPWITHZONE;//Need to add zone/nozone and other [] stuff
"tsquery"               return TSQUERY;
"tsvector"              return TSVECTOR;
"txid_snapshot"         return TXIDSNAP;
"uuid"                  return UUID;
"xml"                   return XML;
                    
[$][0-9]*[.]?[0-9]*     return MONEY;  //example, not actually how we will parse money
[0-9]+                  return (yyleng<=3 ? SMALLINT : yyleng<=8 ? INTEGER : BIGINT);//Check integer sizes (need to check for leading 0s)//Maybe change numbers to numbers. So do yylval=atoi(yytext); return NUM;think i need .y bison file for this
['][a-zA-Z_ - 0-9]*[']  return (yyleng==2 ? NULLCHAR : yyleng==3 ? CHARACTER : STRING);//Check string sizes
["][a-zA-Z_ - 0-9]*["]  return (yyleng==2 ? NULLCHAR : yyleng==3 ? CHARACTER : STRING);//Check string sizes
[0-1]?[0-9][/][0-3]?[0-9][/][0-9][0-9][0-9][0-9] return DATE; //prolly a better way to check for 4 numbers
[0-9]+[.][0-9]+         return (yyleng<=8 ? FLOAT : DOUBLE);//need to check for leading 0s
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
