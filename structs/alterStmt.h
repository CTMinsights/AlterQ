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
        std::string fromName;
        std::string toName;
        columnDets colDets;
        bool add;
        bool drop;
        bool ifexists;
        bool ifnotexists;
        bool only;
        bool rename;
        bool column;
        bool ast;
        
        alterStmt(std::string query) : statement(query){
            stmt = query;
            tableName = {};
            colName = {};
            fromName = {};
            toName = {};
            colDets= {};
            ifexists = false;
            ifnotexists = false;
            only = false;
            rename = false;
            column = false;
            add = false;
            drop = false;
            ast = false;
            std::pair<std::vector<int>, std::vector<std::string>> par = lex(query);
            tokVec = par.first; 
            strVec = par.second; 
            int sz = tokVec.size();
            bool tabNameLook = true;
            bool colNameLook = false;
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
                        colNameLook = true;
                        break;
                    case TO:
                        toName=strVec[i+1];
                        break;
                    case ADD:
                        add=true;
                        break;
                    case DROP:
                        drop=true;
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
            fromName = {};
            toName = {};
            ifexists = false;
            ifnotexists = false;
            only = false;
            rename = false;
            column = false;
            add = false;
            drop = false;
            ast = false;
            std::pair<std::vector<int>, std::vector<std::string>> par = lex(query);
            tokVec = par.first; 
            strVec = par.second; 
            int sz = tokVec.size();
            bool tabNameLook = true;
            bool colNameLook = false;
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
                        colNameLook = true;
                        break;
                    case TO:
                        toName=strVec[i+1];
                        break;
                    case ADD:
                        add=true;
                        break;
                    case DROP:
                        drop=true;
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

        void reconstructStmt(){
            std::string newStmt = "ALTER TABLE ";
            int sz = tokVec.size();
            bool tabNameLook = true;
            bool colNameLook = false;
            for(int i = 1; i<sz; i++){
                switch(tokVec[i]){
                    case STRINGNOQUOTES:
                        if(tabNameLook){
                            newStmt += tableName +" ";
                            tabNameLook=false;
                        }else if(colNameLook){
                            newStmt += colName+" ";
                            colNameLook = false;
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
                        break;
                    case COLUMN:
                        newStmt+="COLUMN ";
                        colNameLook = true;
                        break;
                    case TO:
                        newStmt+="TO ";
                        break;
                    case SEMICOLON:
                        newStmt+=";";
                        break;
                    case ADD:
                        newStmt+="ADD ";
                        break;
                    case DROP:
                        newStmt+="DROP ";
                        break;
                }
            }
            stmt = newStmt;
        }

        ~alterStmt(){}
    };
}
#endif