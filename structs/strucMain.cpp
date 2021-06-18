#include <iostream>
#include <vector>

#include "strucMain.h"
#include "../lex/aLex.h"
#include "dropStmt.h"
#include "truncateStmt.h"
#include "createStmt.h"
#include "deleteStmt.h"
#include "insertStmt.h"
#include "selectStmt.h"
#include "alterStmt.h"
#include "updateStmt.h"

using namespace std;

void foo()
{
    dropStmt ds = dropStmt("DROP TABLE tab;");
    truncateStmt ts = truncateStmt("TRUNCATE TABLE tab;");
    alterStmt as = alterStmt("ALTER TABLE tab ADD COLUMN address VARCHAR;");
    createStmt cs = createStmt("CREATE TABLE tab (nums INT, title TEXT NOT NULL);");
    insertStmt is = insertStmt("INSERT INTO tab (nums, title) VALUES (105, 'Banana');");
    deleteStmt dels = deleteStmt("DELETE FROM tab WHERE nums <> 101;");
    selectStmt ss = selectStmt("SELECT * FROM tab;");
    updateStmt us = updateStmt("UPDATE tab SET nums = 999 WHERE nums = 105;");
    cout<<"Success"<<endl;
}