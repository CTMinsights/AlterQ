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
using namespace alp;

//helper function to find string in vectors
int vecFind(vector<string> vec, string str){
    int index = 0;
    int sz = vec.size();
    for(int i=0; i<sz; i++){
        if(vec[i]==str){
            return i;
        }
    }
    return -1;
}

void test()
{
    dropStmt ds = dropStmt("DROP TABLE tab;");
    truncateStmt ts = truncateStmt("TRUNCATE TABLE tab;");
    alterStmt as = alterStmt("ALTER TABLE tab ADD COLUMN address VARCHAR;");
    createStmt cs = createStmt("CREATE TABLE tab (nums INT, title TEXT NOT NULL);");
    insertStmt is = insertStmt("INSERT INTO tab (nums, title) VALUES (105, 'Banana');");
    deleteStmt dels = deleteStmt("DELETE FROM tab WHERE nums <> 101;");
    selectStmt ss = selectStmt("SELECT * FROM tab;");
    updateStmt us = updateStmt("UPDATE tab SET nums = 999 WHERE nums = 105;");

    statement stmt1 = statement("ALTER TABLE tab ADD COLUMN address VARCHAR;");
    alterStmt as2 = alterStmt(stmt1);
    //as2.setStmt("ALTER TABLE tab DEL COLUMN address VARCHAR;");
    as2.setTableName("newTable");
    cout<<as2.stmt<<endl;

    
 
    statement stmt2 = statement("SELECT * FROM tab;");
    selectStmt sel2 = selectStmt(stmt2);

    statement stmt3 = statement("DROP TABLE tab;");
    dropStmt ds2 = dropStmt(stmt3);

    statement stmt4 = statement("TRUNCATE TABLE tab;");
    truncateStmt ts2 = truncateStmt(stmt4);

    statement stmt5 = statement("CREATE TABLE tab (nums INT, title TEXT NOT NULL);");
    createStmt cs2 = createStmt(stmt5);

    statement stmt6 = statement("INSERT INTO tab (nums, title) VALUES (105, 'Banana');");
    insertStmt is2 = insertStmt(stmt6);

    statement stmt7 = statement("DELETE FROM tab WHERE nums <> 101;");
    deleteStmt dels2 = deleteStmt(stmt7);

    statement stmt8 = statement("UPDATE tab SET nums = 999 WHERE nums = 105;");
    updateStmt us2 = updateStmt(stmt8);

    cout<<"Success"<<endl;
}