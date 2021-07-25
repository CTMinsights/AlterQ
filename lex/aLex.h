#include <vector>
#include <string>
#include <string.h>
#include <utility>

void lexxerCmd();
std::pair<std::vector<int>, std::vector<std::string>> lex(std::string str);
void runTests();

// Data (actual data)
#define SMALLINT 201
#define INTEGER 202
#define BIGINT 203
#define NULLCHAR 204
#define CHARACTER 205
#define STRING 206
#define STRINGNOQUOTES 207
#define MONEY 208
#define DATE 209
#define FLOAT 210
#define DOUBLE 211
#define TRUE_B 212 
#define FALSE_B 213 

// Punctuation
#define COLON 101
#define SEMICOLON 102
#define SINGQUOTE 103
#define DUBQUOTE 104
#define OPENPAREN 105
#define CLOSEPAREN 106
#define OPENBRACKET 107
#define CLOSEBRACKET 108
#define OPENBRACE 109
#define CLOSEBRACE 110
#define COMMA 111
#define EQUALS 112
#define NOTEQUALS 113
#define LESSEQUAL 114
#define GREATEQUAL 115
#define LESSER 116
#define GREATER 117
#define PLUS 118
#define MINUS 119
#define AST 120

// Datatypes (datatype labels) https://www.postgresql.org/docs/current/datatype.html

/* #define TEXT 312
#define INT_T 313
#define SMALLINT_T 314
#define BIGINT_T 315
#define BIGSERIAL 316
#define BIT 317//Might need []
#define BOX 327
#define BYTEA 329
#define VARBIT 326//Might need []
#define BOOLEAN 318
#define INET 319
#define DATE_T 320
#define JSON 321
#define JSONB 322
#define LINE 323
#define LSEG 324
#define MACADDR 325
#define CIDR 328
#define CHAR 330//Might need []
#define VARCHAR_T 331//Might need []
#define CIRCLE 332
#define DOUBLE_T 333
#define INTERVAL 335 //Might need []
#define MONEY_T 336
#define NUMERIC 337 //Might need []
#define PATH 338
#define PGLSN 339
#define POINT 340
#define POLYGON 341
#define REAL 342
#define SMALLSERIAL 343
#define SERIAL 344
#define TIMENOZONE 345 //Might need []
#define TIMEWITHZONE 346 //Might need []
#define TIMESTAMPNOZONE 347 //Might need []
#define TIMESTAMPWITHZONE 348 //Might need []
#define TSQUERY 349
#define TSVECTOR 350
#define TXIDSNAP 351
#define UUID 352
#define XML 353
#define MACADDR8 354
#define PGSNAP 355 */

// Query Types/Keywords
#define ALTER 10
#define ALTERTABLE 11
#define AND 12
#define AS 13
#define AVG 14
#define BETWEEN 15
#define CASE 16
#define COUNT 17
#define CREATETABLE 18
#define DELETE 19
#define GROUPBY 20
#define HAVING 21
#define INNERJOIN 22 //https://www.postgresqltutorial.com/postgresql-joins/
#define INSERT 23
#define LIKE 26
#define LIMIT 27
#define MAX 28
#define MIN 29
#define OR 30
#define ORDERBY 31
#define OUTERJOIN 32
#define ROUND 33
#define SELECT 34
#define SELECTDISTINCT 35
#define SUM 36
#define UPDATE 37
#define WHERE 38
#define WITH 39
#define INSERTINTO 40
#define VALUES 41
#define DROPTABLE 42
#define PRIMARYKEY 43
#define BY 44
#define UNIQUE 45
#define ISNOTNULL 46
#define ISNULL 47
#define REFERENCES 48
#define FOREIGNKEY 49 
#define IF 50
#define END 52
#define WHEN 53
#define ELSE 54
#define THEN 55
#define COALESCE 56
#define NULLIF 57
#define DEFAULT 58
#define CURRENTTIMESTAMP 59
#define CAST 60
#define GENERATED 61
#define KEY 62
#define LEFTJOIN 63
#define RIGHTJOIN 64
#define FULLJOIN 65
#define FULLOUTERJOIN 66
#define ON 67
#define RENAME 68
#define COLUMN 69
#define TO 70
#define RENAMECOL 71
#define VIEW 72
#define WITHNODATA 73
#define WITHDATA 74
#define DATA 75
#define NOTEXISTS 76
#define EXISTS 77
#define OFFSET 78
#define ROW 79
#define ONLY 80
#define FIRST 81
#define FETCH 82
#define CUBE 83
#define ROLLUP 84
#define EXTRACT 85 //add this eventually https://www.postgresqltutorial.com/postgresql-extract/
#define CROSSJOIN 86
#define NATURALJOIN 87
#define TRUNCATE 88
#define ANY 89
#define ALL 90
#define SET 91
#define RETURNING 92
#define FROM 93
#define CREATE 94
#define REPLACE 95
#define SEQUENCE 96
#define NEXTVAL 97
#define CURRVAL 98
#define ILIKE 99
#define LENGTH 100
#define FUNCTION 1001 //FIX THIS NUMBERING FROM HERE DOWN
#define PERFORM 1002
#define DECLARE 1003
#define COPY 1004
#define PGDB 1005
#define BEGIN_T 1006
#define ADD 1007
#define DROP 1008
#define INTO 1009
#define COMMENT 1010
#define COLLATE 1011
#define CONSTRAINT 1012
#define INHERITS 1013
#define PARTITION 1014
#define RANGE 1015
#define LIST 1016
#define HASH 1017
#define TEMP 1018
#define UNLOGGED 1019
#define EXCLUDE 1020
#define ASC 1021
#define DESC 1022
#define NULLS 1023
#define INCLUDING 1024
#define EXCLUDING 1025
#define GLOBAL 1026
#define LOCAL 1027
#define TABLESPACE 1028
#define IFEXISTS 1029
#define CASCADE 1030
#define RESTRICT 1031
#define CONTINUEIDEN 1032
#define RESTARTIDEN 1033
#define IFNOTEXISTS 1034
#define SCHEMA 1035
#define DETACH 1036
#define RETURNINGSTAR 1037
#define TABLE 1038
#define NUMBER 1039
#define NUMWDEC 1040