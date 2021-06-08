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
"NULL"              return ISNULL;
"NOT NULL"          return ISNOTNULL;
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
"CASE"              return CASE;
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
"KEY"               return KEY;
"FULL JOIN"         return FULLJOIN;
"FULL OUTER JOIN"   return FULLOUTERJOIN;
"LEFT JOIN"         return LEFTJOIN;
"RIGHT JOIN"        return RIGHTJOIN;
"INNER JOIN"        return INNERJOIN;
"OUTER JOIN"        return OUTERJOIN;
"RENAME COLUMN"     return RENAMECOL;
"RENAME"            return RENAME;
"COLUMN"            return COLUMN;

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
"character varying"|"varchar" return VARCHAR_T;
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
"timestamp"             return TIMESTAMPNOZONE;//Need to add zone/nozone and other [] stuff
"timestamp2"|"timestamptz" return TIMESTAMPWITHZONE;//Need to add zone/nozone and other [] stuff
"tsquery"               return TSQUERY;
"tsvector"              return TSVECTOR;
"txid_snapshot"         return TXIDSNAP;
"uuid"                  return UUID;
"xml"                   return XML;

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
//Gotta add functionality for ()s or maybe just not
int yywrap(void){
    return 1;
}
