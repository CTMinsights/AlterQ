#include <iostream>
#include <vector>

#include "strucMain.h"
#include "../lex/aLex.h"
#include "dropStmt.h"
#include "truncateStmt.h"

using namespace std;

void foo()
{
    dropStmt ds = dropStmt("DROP TABLE tab;");
    truncateStmt ts = truncateStmt("TRUNCATE TABLE tab;");
    cout<<"Success"<<endl;
}