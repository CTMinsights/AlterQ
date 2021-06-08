#include <stdio.h>
#include <iostream>
#include <string.h>
#include <assert.h>
#include <vector>
#include <fstream>
#include "aLex.h"
using namespace std;

extern int yylex();
extern FILE* yyset_in(FILE* file);
extern int yylineno;
extern char* yytext;


/**lexxerCmd function is for developing
 * Takes input from cmd line and prints out parsing details
 * 
 */
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

/**lexxer function adds input to a file then parses that file
 * Input: SQL query as string
 * Output: Tokenized query in a vector
 */
vector<int> lexxer(string str){
    vector<int> vec;
    ofstream myfile;
    myfile.open("test.txt");
    myfile << str;
    myfile.close();
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
/**runTests function runs tests
 *
 */ 
void runTests(){
    cout<<"Running tests"<<endl;

    vector<int> testvec = {40, 207, 105, 207, 111, 207, 106, 207, 105, 206, 111, 201, 106, 102};
    assert(lexxer("INSERT INTO table(col1, col2) VALUES ('hey', 24);")==testvec);

    testvec = {18, 207, 105, 207, 313, 111, 207, 331, 106, 102};
    assert(lexxer("CREATE TABLE table1(col1 integer, col_2_two varchar );")==testvec);

    cout<<"All tests passed"<<endl;
}

int main(void){
    //string testStr = "test";//Change this to whatever you want to test
    //vector<int> vec;
    //vec = lexxer(testStr);//Use this on input from file

    //runTests();//Run tests

    lexxerCmd();//Use this on input from cmd line and to see details printed

    
    return 0;
}