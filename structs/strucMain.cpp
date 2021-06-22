#include <iostream>
#include <vector>
#include <assert.h>

#include "strucMain.h"
#include "../lex/aLex.h"
#include "alterStmt.h"
#include "truncateStmt.h"
#include "createStmt.h"
#include "deleteStmt.h"
#include "insertStmt.h"
#include "selectStmt.h"
#include "updateStmt.h"
#include "dropStmt.h"

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


    //ALTER TESTS
    alterStmt altTest1 =alterStmt("ALTER TABLE IF EXISTS ONLY tab1 * RENAME COLUMN col1name TO col2name;");
    assert(altTest1.printAlterStmt()=="ALTER TABLE IF EXISTS ONLY tab1 * RENAME COLUMN col1name TO col2name ;");
    //alterStmt altTest1 =alterStmt("ALTER TABLE IF EXISTS ONLY tab1 RENAME COLUMN col1name TO col2name;");
    //alterStmt altTest1 =alterStmt("ALTER TABLE IF EXISTS ONLY tab1 RENAME col1name TO col2name;");
    //alterStmt altTest1 =alterStmt("ALTER TABLE IF EXISTS tab1 RENAME col1name TO col2name;");
    //alterStmt altTest1 =alterStmt("ALTER TABLE tab1 RENAME col1name TO col2name;");
    alterStmt altTest2 = alterStmt("ALTER TABLE IF EXISTS ONLY tab1 * RENAME CONSTRAINT con1 TO con2 ;");
    assert(altTest2.printAlterStmt()=="ALTER TABLE IF EXISTS ONLY tab1 * RENAME CONSTRAINT con1 TO con2 ;");
    alterStmt altTest3 = alterStmt("ALTER TABLE IF EXISTS tab1 RENAME TO newTab ;");
    assert(altTest3.printAlterStmt()=="ALTER TABLE IF EXISTS tab1 RENAME TO newTab ;");
    alterStmt altTest4 = alterStmt("ALTER TABLE IF EXISTS tab1 SET SCHEMA newSchema ;");
    assert(altTest4.printAlterStmt()=="ALTER TABLE IF EXISTS tab1 SET SCHEMA newSchema ;");
    alterStmt altTest5 = alterStmt("ALTER TABLE IF EXISTS tab1 DETACH PARTITION newPart ;");
    assert(altTest5.printAlterStmt()=="ALTER TABLE IF EXISTS tab1 DETACH PARTITION newPart ;");

    //TRUNCATE TESTS
    truncateStmt trunTest1 = truncateStmt("TRUNCATE TABLE ONLY tab * RESTART IDENTITY CASCADE ;");
    assert(trunTest1.printTruncateStmt()=="TRUNCATE TABLE ONLY tab * RESTART IDENTITY CASCADE ;");
    truncateStmt trunTest2 = truncateStmt("TRUNCATE TABLE ONLY tab * CONTINUE IDENTITY RESTRICT ;");
    assert(trunTest2.printTruncateStmt()=="TRUNCATE TABLE ONLY tab * CONTINUE IDENTITY RESTRICT ;");
    
    //DROP TESTS
    dropStmt dropTest1 = dropStmt("DROP TABLE IF EXISTS tab1 CASCADE;");
    assert(dropTest1.printDropStmt()=="DROP TABLE IF EXISTS tab1 CASCADE;");
    dropStmt dropTest2 = dropStmt("DROP TABLE tab1 RESTRICT;");
    assert(dropTest2.printDropStmt()=="DROP TABLE tab1 RESTRICT;");

    //DELETE TESTS
    deleteStmt delTest1 = deleteStmt("DELETE FROM ONLY tab WHERE nums <> 101;");
    assert(delTest1.printDeleteStmt()=="DELETE FROM ONLY tab WHERE nums <> 101;");
    deleteStmt delTest2 = deleteStmt("DELETE FROM tab WHERE nums >= 1;");
    assert(delTest2.printDeleteStmt()=="DELETE FROM tab WHERE nums >= 1;");
    deleteStmt delTest3 = deleteStmt("DELETE FROM tab * WHERE names = 'alex' RETURNING *;");
    assert(delTest3.printDeleteStmt()=="DELETE FROM tab * WHERE names = 'alex' RETURNING *;");

    cout<<"Success"<<endl;
}