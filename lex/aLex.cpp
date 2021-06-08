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
        cout<<ntoken<<" : "<<txt<<endl;
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
    
    //CREATE TABLE TESTS
    vector<int> testvec = {18, 207, 105, 207, 313, 111, 207, 331, 106, 102};
    assert(lexxer("CREATE TABLE table1(col1 integer, col_2_two varchar );")==testvec);
    testvec = {18, 207, 105, 207, 344, 43, 111, 207, 331, 105, 201, 106, 45, 46, 111, 207, 347, 46, 106, 102};
    assert(lexxer("CREATE TABLE table_1(user_id serial PRIMARY KEY, username VARCHAR(50) UNIQUE NOT NULL, created_on TIMESTAMP NOT NULL);")==testvec);
    testvec = {18, 207, 105, 207, 313, 46, 111, 207, 313, 46, 111, 43, 105, 207, 111, 207, 106, 111, 49, 105, 207, 106, 48, 207, 105, 207, 106, 111, 49, 105, 207, 106, 48, 207, 105, 207, 106, 106, 102};
    assert(lexxer("CREATE TABLE table_1(user_id INT NOT NULL, role_id INT NOT NULL, PRIMARY KEY (user_id, role_id), FOREIGN KEY (role_id) REFERENCES roles (role_id), FOREIGN KEY (user_id) REFERENCES accounts (user_id));")==testvec);
    testvec = {18, 50, 76, 207, 13, 207, 73, 102};
    assert(lexxer("CREATE TABLE IF NOT EXISTS table_1 AS table_2 WITH NO DATA;")==testvec);
    
    testvec = {40, 207, 105, 207, 111, 207, 106, 207, 105, 206, 111, 201, 106, 102};
    assert(lexxer("INSERT INTO table(col1, col2) VALUES ('hey', 24);")==testvec);

    cout<<"All tests passed"<<endl;
}

int main(void){
    //string testStr = "test";//Change this to whatever you want to test
    //vector<int> vec;
    //vec = lexxer(testStr);//Use this on input from file

    runTests();//Run tests

    //lexxerCmd();//Use this on input from cmd line and to see details printed

    
    return 0;
}