#include <stdio.h>
#include <iostream>
#include <assert.h>
#include <vector>
#include<string>

#include "alp.h"


using namespace alp;
using namespace std;

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

    //EDIT: ALTER TESTS
    alterStmt altEditTest1 =alterStmt("ALTER TABLE IF EXISTS ONLY tab1 * RENAME COLUMN col1name TO col2name;");
    assert(altEditTest1.getTableName()=="tab1");
    altEditTest1.setTableName("diffname");
    assert(altEditTest1.getTableName()=="diffname");
    assert(altEditTest1.printAlterStmt()=="ALTER TABLE IF EXISTS ONLY diffname * RENAME COLUMN col1name TO col2name ;");

    //TRUNCATE TESTS
    truncateStmt trunTest1 = truncateStmt("TRUNCATE TABLE ONLY tab * RESTART IDENTITY CASCADE;");
    assert(trunTest1.printTruncateStmt()=="TRUNCATE TABLE ONLY tab * RESTART IDENTITY CASCADE ;");
    truncateStmt trunTest2 = truncateStmt("TRUNCATE TABLE ONLY tab * CONTINUE IDENTITY RESTRICT ;");
    assert(trunTest2.printTruncateStmt()=="TRUNCATE TABLE ONLY tab * CONTINUE IDENTITY RESTRICT ;");
    
    //EDIT: TRUNCATE TESTS
    truncateStmt trunEditTest1 = truncateStmt("TRUNCATE TABLE ONLY tab * RESTART IDENTITY CASCADE;");
    assert(trunEditTest1.getTableName()=="tab");
    trunEditTest1.setTableName("diffname");
    assert(trunEditTest1.getTableName()=="diffname");
    assert(trunEditTest1.printTruncateStmt()=="TRUNCATE TABLE ONLY diffname * RESTART IDENTITY CASCADE ;");

    //DROP TESTS
    dropStmt dropTest1 = dropStmt("DROP TABLE IF EXISTS tab1 CASCADE;");
    assert(dropTest1.printDropStmt()=="DROP TABLE IF EXISTS tab1 CASCADE ;");
    dropStmt dropTest2 = dropStmt("DROP TABLE tab1 RESTRICT;");
    assert(dropTest2.printDropStmt()=="DROP TABLE tab1 RESTRICT ;");


    //EDIT: DROP TESTS
    dropStmt dropEditTest1 = dropStmt("DROP TABLE IF EXISTS tab1 CASCADE;");
    assert(dropEditTest1.getTableName()=="tab1");
    dropEditTest1.setTableName("diffname");
    assert(dropEditTest1.getTableName()=="diffname");
    assert(dropEditTest1.printDropStmt()=="DROP TABLE IF EXISTS diffname CASCADE ;");

    //DELETE TESTS
    deleteStmt delTest1 = deleteStmt("DELETE FROM ONLY tab WHERE nums <> 101;");
    assert(delTest1.printDeleteStmt()=="DELETE FROM ONLY tab WHERE nums <> 101 ;");
    deleteStmt delTest2 = deleteStmt("DELETE FROM tab WHERE nums >= 1;");
    assert(delTest2.printDeleteStmt()=="DELETE FROM tab WHERE nums >= 1 ;");
    deleteStmt delTest3 = deleteStmt("DELETE FROM tab * WHERE names = 'alex' RETURNING *;");
    assert(delTest3.printDeleteStmt()=="DELETE FROM tab * WHERE names = 'alex' RETURNING * ;");

    //EDIT: DELETE TESTS
    deleteStmt delEditTest1 = deleteStmt("DELETE FROM ONLY tab WHERE nums <> 101;");
    assert(delEditTest1.getTableName()=="tab");
    delEditTest1.setTableName("diffname");
    assert(delEditTest1.getTableName()=="diffname");
    assert(delEditTest1.getWhere().printEquation()=="nums <> 101");
    delEditTest1.setWhereLeft("newNums");
    delEditTest1.setWhereSymbol(">=");
    assert(delEditTest1.getWhere().printEquation()=="newNums >= 101");
    delEditTest1.setWhereRight("0");
    assert(delEditTest1.getWhere().printEquation()=="newNums >= 0");
    assert(delEditTest1.printDeleteStmt()=="DELETE FROM ONLY diffname WHERE newNums >= 0 ;");
    
    //UPDATE TESTS
    updateStmt upTest1 = updateStmt("UPDATE ONLY tab1 * AS tabby SET col1 = 'name1' WHERE col1 = 'name5';");
    assert(upTest1.printUpdateStmt()=="UPDATE ONLY tab1 * AS tabby SET col1 = 'name1' WHERE col1 = 'name5' ;");
    
    //EDIT: UPDATE TESTS
    updateStmt upEditTest1 = updateStmt("UPDATE ONLY tab1 * AS tabby SET col1 = 'name1' WHERE col1 = 'name5';");
    assert(upEditTest1.getTableName()=="tab1");
    upEditTest1.setTableName("diffname");
    assert(upEditTest1.getTableName()=="diffname");
    assert(upEditTest1.getWhere().printEquation()=="col1 = 'name5'");//Test where
    upEditTest1.setWhereLeft("newCol");
    upEditTest1.setWhereSymbol("<>");
    assert(upEditTest1.getWhere().printEquation()=="newCol <> 'name5'");
    upEditTest1.setWhereRight("'notName5'");
    assert(upEditTest1.getWhere().printEquation()=="newCol <> 'notName5'");
    assert(upEditTest1.getSet().printEquation()=="col1 = 'name1'");//Test set
    upEditTest1.setSetLeft("newCol");
    assert(upEditTest1.getSet().printEquation()=="newCol = 'name1'");
    upEditTest1.setSetRight("'name2'");
    assert(upEditTest1.getSet().printEquation()=="newCol = 'name2'");
    assert(upEditTest1.printUpdateStmt()=="UPDATE ONLY diffname * AS tabby SET newCol = 'name2' WHERE newCol <> 'notName5' ;");
   
    //INSERT TESTS
    insertStmt inTest1 = insertStmt("INSERT INTO tab(nums, title) VALUES ('105', 'Banana');");
    assert(inTest1.printInsertStmt()=="INSERT INTO tab (nums, title) VALUES ('105', 'Banana') ;");
    insertStmt inTest2 = insertStmt("INSERT INTO tab(nums, title) VALUES (105, 'Banana');");
    assert(inTest2.printInsertStmt()=="INSERT INTO tab (nums, title) VALUES (105, 'Banana') ;");
    //insertStmt inTest3 = insertStmt("INSERT INTO tab(nums, title) VALUES (1051234, 'Banana');");
    //assert(inTest3.printInsertStmt()=="INSERT INTO tab (nums, title) VALUES (1051234, 'Banana') ;");//breaks cause int not done, same with float, etc
    
    //EDIT: INSERT TESTS
    insertStmt inEditTest1 = insertStmt("INSERT INTO tab(nums, title) VALUES ('105', 'Banana');");
    assert(inEditTest1.getTableName()=="tab");
    inEditTest1.setTableName("diffname");
    assert(inEditTest1.getTableName()=="diffname");
    assert(inEditTest1.printInsertStmt()=="INSERT INTO diffname (nums, title) VALUES ('105', 'Banana') ;");
    vector<string> edVec1={"nums", "title"};
    vector<string> edVec2={"'105'", "'Banana'"};
    assert(inEditTest1.getColNames()==edVec1);
    assert(inEditTest1.getValues()==edVec2);
    vector<string> newVec1={"newNums", "newTitle", "thirdCol"};
    inEditTest1.setColNames(newVec1);
    vector<string> newVec2={"'999'", "'The banana'", "'idk'"};
    inEditTest1.setValues(newVec2);
    assert(inEditTest1.printInsertStmt()=="INSERT INTO diffname (newNums, newTitle, thirdCol) VALUES ('999', 'The banana', 'idk') ;");


    //SELECT TESTS
    selectStmt selTest1 = selectStmt("SELECT * FROM tab;");
    assert(selTest1.printSelectStmt()=="SELECT * FROM tab ;");
    selectStmt selTest2 = selectStmt("SELECT * FROM distributors ORDER BY 2;");
    assert(selTest2.printSelectStmt()=="SELECT * FROM distributors ORDER BY 2 ;");
    selectStmt selTest3 = selectStmt("SELECT * FROM distributors GROUP BY name;");
    assert(selTest3.printSelectStmt()=="SELECT * FROM distributors GROUP BY name ;");
    selectStmt selTest4 = selectStmt("SELECT name FROM distributors ORDER BY 5 LIMIT 10;");
    assert(selTest4.printSelectStmt()=="SELECT name FROM distributors ORDER BY 5 LIMIT 10 ;");
    
    //EDIT: SELECT TESTS
    selectStmt selEditTest1 = selectStmt("SELECT * FROM tab;");
    assert(selEditTest1.getFrom()=="tab");//Test from
    selEditTest1.setFrom("diffname");
    assert(selEditTest1.getFrom()=="diffname");
    assert(selEditTest1.getSelect()=="*");//Test select
    selEditTest1.setSelect("name");
    assert(selEditTest1.getSelect()=="name");
    assert(selEditTest1.printSelectStmt()=="SELECT name FROM diffname ;");

    //CREATE TESTS
    createStmt createTest1 = createStmt("CREATE TABLE tab AS TABLE old_tab WITH NO DATA;");
    assert(createTest1.printCreateStmt()=="CREATE TABLE tab AS TABLE old_tab WITH NO DATA ;");
    createStmt createTest2 = createStmt("CREATE LOCAL TEMP UNLOGGED TABLE IF NOT EXISTS tab AS TABLE old_tab WITH NO DATA;");
    assert(createTest2.printCreateStmt()=="CREATE LOCAL TEMP UNLOGGED TABLE IF NOT EXISTS tab AS TABLE old_tab WITH NO DATA ;");
    createStmt createTest3 = createStmt("CREATE TABLE tab (nums INT);");
    assert(createTest3.printCreateStmt()=="CREATE TABLE tab (nums INT ) ;");
    createStmt createTest4 = createStmt("CREATE TABLE tab (nums INT, names VARCHAR, circ circle);");
    assert(createTest4.printCreateStmt()=="CREATE TABLE tab (nums INT , names VARCHAR , circ circle ) ;");

    //EDIT: CREATE TESTS
    createStmt createEditTest1 = createStmt("CREATE TABLE tab AS TABLE old_tab WITH NO DATA;");
    assert(createEditTest1.getTableName()=="tab");
    createEditTest1.setTableName("diffname");
    assert(createEditTest1.getTableName()=="diffname");
    assert(createEditTest1.printCreateStmt()=="CREATE TABLE diffname AS TABLE old_tab WITH NO DATA ;");

    createStmt createEditTest2 = createStmt("CREATE TABLE tab (nums INT, names VARCHAR, circ circle);");
    assert(createEditTest2.getTableName()=="tab");
    createEditTest2.setTableName("diffname");
    assert(createEditTest2.getTableName()=="diffname");
    assert(createEditTest2.printCreateStmt()=="CREATE TABLE diffname (nums INT , names VARCHAR , circ circle ) ;");
    assert(createEditTest2.getColVec()[0].printColDets()=="nums INT ");
    vector<columnDets> cv = createEditTest2.getColVec();
    columnDets colDets1 = cv[0];
    colDets1.setColName("newNums");
    colDets1.setColData("INT8"); 
    columnDets colDets2 = cv[1];
    colDets2.setColData("TEXT");
    createEditTest2.setColVec({colDets1, colDets2, cv[2]});
    assert(createEditTest2.getColVec()[0].printColDets()=="newNums INT8 ");
    assert(createEditTest2.printCreateStmt()=="CREATE TABLE diffname (newNums INT8 , names TEXT , circ circle ) ;");

    std::cout<<"Success"<<std::endl;
}

int main ( )
{
    test();

    //Enter code here you want to use the parser with

    return 0;
}