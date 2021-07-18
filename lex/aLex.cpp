#include <stdio.h>
#include <iostream>
#include <string>
#include <assert.h>
#include <vector>
#include <fstream>
#include <utility>

#include "aLex.h"
#include "../structs/strucMain.h"

using namespace std;

int yylex();
extern FILE* yyset_in(FILE* file);
extern int yylineno;
extern char* yytext;


/**lexxerCmd function is for developing
 * Takes input from cmd line and prints out parsing details
 * 
 */
void lexxerCmd(){
    int ntoken;
    ntoken=yylex();
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

pair<vector<int>, vector<string>> lex(string str){
    pair<vector<int>, vector<string>> par;
    vector<int> vec1;
    vector<string> vec2;
    ofstream myfile;
    myfile.open("test.txt");
    myfile << str;
    myfile.close();
    int ntoken;
    FILE *fd;
    fd = fopen("test.txt", "r");
    yyset_in(fd);
    ntoken=yylex();
    while(ntoken){
        vec1.push_back(ntoken);
        vec2.push_back(string(yytext));
        ntoken = yylex();
    }
    par.first = vec1;
    par.second = vec2;
    return par;
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
    int ntoken;
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
    //tests based off: https://www.enterprisedb.com/postgres-tutorials/postgresql-query-introduction-explanation-and-50-examples
    //CREATE TABLE tests
    vector<int> testvec = {18, 207, 105, 207, 313, 111, 207, 331, 106, 102};
    assert(lexxer("CREATE TABLE table1(col1 integer, col_2_two varchar );")==testvec);
    testvec = {18, 207, 105, 207, 344, 43, 111, 207, 331, 105, 201, 106, 45, 46, 111, 207, 347, 46, 106, 102};
    assert(lexxer("CREATE TABLE table_1(user_id serial PRIMARY KEY, username VARCHAR(50) UNIQUE NOT NULL, created_on TIMESTAMP NOT NULL);")==testvec);
    testvec = {18, 207, 105, 207, 313, 46, 111, 207, 313, 46, 111, 43, 105, 207, 111, 207, 106, 111, 49, 105, 207, 106, 48, 207, 105, 207, 106, 111, 49, 105, 207, 106, 48, 207, 105, 207, 106, 106, 102};
    assert(lexxer("CREATE TABLE table_1(user_id INT NOT NULL, role_id INT NOT NULL, PRIMARY KEY (user_id, role_id), FOREIGN KEY (role_id) REFERENCES roles (role_id), FOREIGN KEY (user_id) REFERENCES accounts (user_id));")==testvec);
    testvec = {18, 50, 76, 207, 13, 207, 73, 102};
    assert(lexxer("CREATE TABLE IF NOT EXISTS table_1 AS table_2 WITH NO DATA;")==testvec);
    
    //INSERT INTO tests
    testvec = {40, 207, 105, 207, 111, 207, 106, 207, 105, 206, 111, 201, 106, 102};
    assert(lexxer("INSERT INTO table(col1, col2) VALUES ('hey', 24);")==testvec);

    //UPDATE tests
    testvec = {37, 207, 91, 207, 112, 206, 111, 207, 112, 201, 38, 207, 112, 206, 102};
    assert(lexxer("UPDATE dummy_table SET name='GHI',age=54 WHERE address='location-D';")==testvec);
    
    //SELECT tests
    testvec = {34, 120, 93, 207, 38, 207, 112, 206, 102};
    assert(lexxer("SELECT * FROM table1 WHERE name='Alex';")==testvec);
    
    //SELECT DISTINCT tests
    testvec = {35, 207, 93, 207, 31, 201, 102};
    assert(lexxer("SELECT DISTINCT age FROM table1 ORDER BY 1;")==testvec);
    
    //DELETE FROM tests
    testvec = {19, 207, 38, 207, 113, 201, 102};
    assert(lexxer("DELETE FROM table1 WHERE age<>12;")==testvec);
    
    //TRUNCATE tests
    testvec = {88, 207, 102};
    assert(lexxer("TRUNCATE TABLE table1;")==testvec);
    
    //DROP TABLE tests
    testvec = {42, 50, 77, 207, 102};
    assert(lexxer("DROP TABLE IF EXISTS table1;")==testvec);
    
    //CREATE VIEW tests
    testvec = {94, 30, 95, 72, 207, 13, 34, 207, 93, 207, 102};
    assert(lexxer("CREATE OR REPLACE VIEW vi AS SELECT age FROM table1;")==testvec);

    //ALTER TABLE tests
    testvec = {11, 207, 1007, 207, 313, 102};
    assert(lexxer("ALTER TABLE table1 ADD col1 int;")==testvec);

    cout<<"All tests passed"<<endl;
}
