#include <stdio.h>
#include <iostream>
#include <string.h>
#include <assert.h>
#include <vector>
#include "aLex.h"
using namespace std;

extern int yylex();
extern FILE* yyset_in(FILE* file);
extern int yylineno;
extern char* yytext;

bool test(){
    return true;
}

void lexxerCmd(){
    int ntoken, vtoken;
    ntoken=yylex();
    int i=0;
    while(ntoken){
        string txt = "";
        int sz = strlen(yytext);//strlen might not get correct length(needs \0)
        for(int i=0; i<sz; i++){
            txt+=yytext[i];
        }
        cout<<txt<<" : "<<ntoken<<endl;
        ntoken = yylex();
    }
}

vector<int> lexxerFile(string str){
    vector<int> vec;
    int ntoken, vtoken;
    FILE *fd;
    fd = fopen("test.txt", "r");
    yyset_in(fd);
    ntoken=yylex();
    while(ntoken){
        vec.push_back(ntoken);
        ntoken = yylex();
    }
    return vec;
}

int main(void){
    string testStr = "test";
    vector<int> vec;
    
    vec = lexxerFile(testStr);//Use this on input from file

    lexxerCmd();//Use this on input from cmd line and to see details printed

    
    return 0;
}