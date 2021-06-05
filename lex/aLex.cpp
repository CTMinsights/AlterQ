#include <stdio.h>
#include<iostream>
#include "aLex.h"
using namespace std;

extern int yylex();
extern int yylineno;
extern char* yytext;

int main(void){
    int ntoken, vtoken;

    ntoken=yylex();
    while(ntoken){
        cout<<ntoken<<endl;
        ntoken = yylex();
    }
    return 0;
}