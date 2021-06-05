#include <stdio.h>
#include<iostream>
#include "myscanner.h"
using namespace std;
extern int yylex();
extern int yylineno;
extern char* yytext;

int main(void){
    int ntoken, vtoken;

    ntoken=yylex();
    while(ntoken){
        //printf("%d\n", ntoken);
        cout<<ntoken<<endl;
        ntoken = yylex();
    }
    return 0;
}