#ifndef ALTER_STMT_H
#define ALTER_STMT_H

#include "statement.h"

namespace alp{
    
    struct alterStmt : statement
    {
        std::vector<std::string> strVec;
        std::vector<int> tokVec;

        //Need something for colType(enum?)
        std::string stmt;
        std::string tableName;
        std::string colName;
        std::string colType;
        std::string fromName;
        std::string toName;
        std::string constraintStr;
        std::string schemaStr;
        std::string partitionStr;
        columnDets colDets;
        bool add;
        bool addcol;
        bool drop;
        bool dropcol;
        bool ifexists;
        bool ifnotexists;
        bool only;
        bool rename;
        bool column;
        bool ast;
        bool constraint;
        bool schema;
        bool set;
        bool detach;
        bool partition;
        
        alterStmt(std::string query) : statement(query){
            stmt = query;
            tableName = {};
            colName = {};
            colType = {};
            fromName = {};
            toName = {};
            colDets= {};
            constraintStr={};
            schemaStr = {};
            partitionStr={};
            addcol=false;
            dropcol=false;
            detach=false;
            partition=false;
            ifexists = false;
            ifnotexists = false;
            only = false;
            rename = false;
            column = false;
            add = false;
            drop = false;
            ast = false;
            constraint=false;
            schema=false;
            set=false;
            std::pair<std::vector<int>, std::vector<std::string>> par = lex(query);
            tokVec = par.first; 
            strVec = par.second; 
            int sz = tokVec.size();

            bool tabNameLook = true;
            bool colNameLook = false;
            bool constraintLook = false;
            bool schemaLook = false;
            bool partitionLook =false;
            if(tokVec[0]!=ALTERTABLE){
                std::cout<<"ERROR: Not a ALTER TABLE statement!"<<std::endl;
            }
            if(tokVec[sz-1]!=SEMICOLON){
                std::cout<<"ERROR: Needs a ; at the end!"<<std::endl;
            }
            for(int i = 1; i<sz-1; i++){
                switch(tokVec[i]){
                    case STRINGNOQUOTES://also need to check for colname, and skip if already done(like after TO)
                        if(tabNameLook){
                            tableName = strVec[i];
                            tabNameLook=false;
                        }else if(colNameLook){
                            colName = strVec[i];
                            colNameLook = false;
                        }else if(constraintLook){
                            constraintStr=strVec[i];
                            constraintLook=false;
                        }else if(schemaLook){
                            schemaStr=strVec[i];
                            schemaLook=false;
                        }else if(partitionLook){
                            partitionStr=strVec[i];
                            partitionLook=false;
                        }
                        break;
                    case IFEXISTS:
                        ifexists=true;
                        break;
                    case IFNOTEXISTS:
                        ifnotexists=true;
                        break;
                    case ONLY:
                        only=true;
                        break;
                    case RENAME:
                        rename=true;
                        colNameLook = true;
                        break;
                    case COLUMN:
                        column=true;
                        //how to tell when the col is done...?
                        if(tokVec[i-1]!=RENAME){
                            colDets = colDets.colDets(tokVec, strVec);//should be newTokVec, newStrVec
                            //then skip newTokVec size(i+?)
                        }
                        colNameLook = true;
                        break;
                    case CONSTRAINT:
                        constraint=true;
                        constraintLook=true;
                        break;
                    case DETACH:
                        detach=true;
                        break;
                    case PARTITION:
                        partition=true;
                        partitionLook=true;
                        break;
                    case TO:
                        toName=strVec[i+1];//should store this since it could be colName or constraintName
                        i++;
                        break;
                    case SCHEMA:
                        schema=true;
                        schemaLook=true;
                        break;
                    case SET:
                        set=true;
                        break;
                    case ADD:
                        add=true;
                        break;
                    case ADDCOL:
                        addcol=true;
                        colName = strVec[i+1];
                        colType = strVec[i+2];
                        i+=2;
                        break;
                    case DROP:
                        drop=true;
                        break;
                    case DROPCOL:
                        dropcol=true;
                        colName = strVec[i+1];
                        i++;
                        break;
                    case AST:
                        ast = true;
                        break;
                }
            }
        }

        alterStmt(statement sql) : statement(sql){
            std::string query = sql.stmt;
            stmt = query;
            tableName = {};
            colName = {};
            colType = {};
            fromName = {};
            toName = {};
            colDets= {};
            constraintStr={};
            schemaStr={};
            partitionStr={};
            addcol=false;
            dropcol=false;
            detach=false;
            partition=false;
            ifexists = false;
            ifnotexists = false;
            only = false;
            rename = false;
            column = false;
            add = false;
            drop = false;
            ast = false;
            constraint=false;
            schema=false;
            set=false;
            std::pair<std::vector<int>, std::vector<std::string>> par = lex(query);
            tokVec = par.first; 
            strVec = par.second; 
            int sz = tokVec.size();

            bool tabNameLook = true;
            bool colNameLook = false;
            bool constraintLook=false;
            bool schemaLook = false;
            bool partitionLook = false;
            if(tokVec[0]!=ALTERTABLE){
                std::cout<<"ERROR: Not a ALTER TABLE statement!"<<std::endl;
            }
            if(tokVec[sz-1]!=SEMICOLON){
                std::cout<<"ERROR: Needs a ; at the end!"<<std::endl;
            }
            for(int i = 1; i<sz-1; i++){
                switch(tokVec[i]){
                    case STRINGNOQUOTES://also need to check for colname, and skip if already done(like after TO)
                        if(tabNameLook){
                            tableName = strVec[i];
                            tabNameLook=false;
                        }else if(colNameLook){
                            colName = strVec[i];
                            colNameLook = false;
                        }else if(constraintLook){
                            constraintStr=strVec[i];
                            constraintLook=false;
                        }else if(schemaLook){
                            schemaStr=strVec[i];
                            schemaLook=false;
                        }else if(partitionLook){
                            partitionStr=strVec[i];
                            partitionLook=false;
                        }
                        break;
                    case IFEXISTS:
                        ifexists=true;
                        break;
                    case IFNOTEXISTS:
                        ifnotexists=true;
                        break;
                    case ONLY:
                        only=true;
                        break;
                    case RENAME:
                        rename=true;
                        colNameLook = true;
                        break;
                    case COLUMN:
                        column=true;
                        //how to tell when the col is done...?
                        if(tokVec[i-1]!=RENAME){
                            colDets = colDets.colDets(tokVec, strVec);
                        }
                        colNameLook = true;
                        break;
                    case TO:
                        toName=strVec[i+1];
                        i++;
                        break;
                    case CONSTRAINT:
                        constraint=true;
                        constraintLook=true;
                        break;
                    case DETACH:
                        detach=true;
                        break;
                    case PARTITION:
                        partition=true;
                        partitionLook=true;
                        break;
                    case SCHEMA:
                        schema=true;
                        schemaLook=true;
                        break;
                    case SET:
                        set=true;
                        break;
                    case ADD:
                        add=true;
                        break;
                    case ADDCOL:
                        addcol=true;
                        colName = strVec[i+1];
                        colType = strVec[i+2];
                        i+=2;
                        break;
                    case DROP:
                        drop=true;
                        break;
                    case DROPCOL:
                        dropcol=true;
                        colName = strVec[i+1];
                        i++;
                        break;
                    case AST:
                        ast = true;
                        break;
                }
            }
        }

        std::string getStmt(){
            reconstructStmt();
            return stmt;
        }

        std::string getTableName(){
            return tableName;
        }
        void setTableName(std::string tab){
            int res = vecFind(strVec, tableName);
            if(res!=-1){
                strVec[res] = tab;
                tableName = tab;
            }
            reconstructStmt();
        }

        std::string getColName(){
            return colName;
        }
        void setColName(std::string cn){
            colName=cn;
        }

        std::string getColType(){
            return colType;
        }
        void setColType(std::string ct){
            colType=ct;
        }

        std::string printAlterStmt(){
            reconstructStmt();
            return stmt;
        }
        
        void reconstructStmt(){
            std::string newStmt = "ALTER TABLE ";
            int sz = tokVec.size();

            bool tabNameLook = true;
            bool colNameLook = false;
            bool constraintLook=false;
            bool schemaLook = false;
            bool partitionLook =false;

            for(int i = 1; i<sz-1; i++){
                switch(tokVec[i]){
                    case STRINGNOQUOTES:
                        if(tabNameLook){
                            newStmt += tableName +" ";
                            tabNameLook=false;
                        }else if(colNameLook){
                            newStmt += colName+" ";
                            colNameLook = false;
                        }else if(constraintLook){
                            newStmt += constraintStr+" ";
                            constraintLook=false;
                        }else if(schemaLook){
                            newStmt += schemaStr+" ";
                            schemaLook=false;
                        }else if(partitionLook){
                            newStmt+=partitionStr+" ";
                            partitionLook=false;
                        }
                        break;
                    case IFEXISTS:
                        newStmt+="IF EXISTS ";
                        break;
                    case IFNOTEXISTS:
                        newStmt+="IF NOT EXISTS ";
                        break;
                    case ONLY:
                        newStmt+="ONLY ";
                        break;
                    case RENAME:
                        newStmt+="RENAME ";
                        colNameLook = true;
                        break;
                    case COLUMN:
                        newStmt+="COLUMN ";
                        colNameLook = true;
                        break;
                    case TO:
                        newStmt+="TO "+strVec[i+1]+" ";
                        i++;
                        break;
                    case CONSTRAINT:
                        newStmt+="CONSTRAINT ";
                        constraintLook=true;
                        break;
                    case DETACH:
                        newStmt+="DETACH ";
                        break;
                    case PARTITION:
                        newStmt+="PARTITION ";
                        partitionLook=true;
                        break;
                    case SCHEMA:
                        newStmt+="SCHEMA ";
                        schemaLook=true;
                        break;
                    case SET:
                        newStmt+="SET ";
                        break;
                    case ADD:
                        newStmt+="ADD ";
                        break;
                    case ADDCOL:
                        newStmt+="ADD COLUMN ";
                        newStmt+=colName+" "+colType+" ";
                        i+=2;
                        break;
                    case DROP:
                        newStmt+="DROP ";
                        break;
                    case DROPCOL:
                        newStmt+="DROP COLUMN " + colName +" ";
                        i++;
                        break;
                    case AST:
                        newStmt+="* ";
                }
            }
            newStmt+=";";
            stmt=newStmt;
        }

        ~alterStmt(){}
    };
}
#endif