#include <stdio.h>
#include<iostream>
#include<string.h>
#include "aLex.h"
using namespace std;

extern int yylex();
extern int yylineno;
extern char* yytext;

int main(void){
    int ntoken, vtoken;

    ntoken=yylex();
    while(ntoken){
        string txt = "";
        int sz = strlen(yytext);
        for(int i=0; i<sz; i++){
            txt+=yytext[i];
        }
        cout<<txt<<" : "<<ntoken<<endl;
        ntoken = yylex();
    }
    return 0;
}