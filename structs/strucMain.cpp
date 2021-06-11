#include <iostream>
#include <vector>

#include "strucMain.h"
#include "../lex/aLex.h"
#include "dropStmt.h"

using namespace std;

void foo()
{
    dropStmt ds = dropStmt("DROP TABLE tab;");
    cout<<"Success"<<endl;
}