#ifndef DELETE_STMT_H
#define DELETE_STMT_H

#include "statement.h"

namespace alp{
    struct deleteStmt : statement
    {
        std::string stmt;
        std::string tableName;
        bool only;
        bool ast;
        bool as;
        std::string aliasStr;
        bool where;
        Equation whereEq;
        bool returning;
        bool returningStar;

        std::vector<int> tokVec;
        std::vector<std::string> strVec;
        
        deleteStmt(std::string query) : statement(query){
            stmt = query;
            tableName = {};
            only=false;
            ast=false;
            as=false;
            aliasStr={};
            where=false;
            whereEq={};
            returning=false;
            returningStar=false;

            std::pair<std::vector<int>, std::vector<std::string>> par = lex(query);
            tokVec = par.first; 
            strVec = par.second; 
            int sz = tokVec.size();
            bool tableNameLook = true;
            bool aliasLook = false;
            if(tokVec[0]!=DELETE){
                std::cout<<"ERROR: Not a DELETE statement!"<<std::endl;
            }
            if(tokVec[sz-1]!=SEMICOLON){
                std::cout<<"ERROR: Needs a ; at the end!"<<std::endl;
            }
            for(int i = 1; i<sz-1; i++){
                switch(tokVec[i]){
                    case STRINGNOQUOTES:
                        if(tableNameLook){
                            tableName = strVec[i];
                            tableNameLook=false;
                        }else if(aliasLook){
                            aliasStr = strVec[i];
                            aliasLook=false;
                        }
                        break;
                    case STRING:
                        if(tableNameLook){
                            tableName = strVec[i];
                            tableNameLook=false;
                        }else if(aliasLook){
                            aliasStr = strVec[i];
                            aliasLook=false;
                        }
                        break;
                    case ONLY:
                        only=true;
                        break;
                    case AS:
                        as=true;
                        aliasLook=true;
                        break;
                    case WHERE:
                        where=true;
                        whereEq.left = strVec[i+1];
                        whereEq.sym = strVec[i+2];
                        if(tokVec[i+3]==NUMBER){
                            whereEq.right = "'"+strVec[i+3]+"'";
                        }else{
                            whereEq.right = strVec[i+3];
                        }
                        i+=3;
                        break;
                    case AST:
                        ast=true;
                        break;
                    case RETURNING:
                        returning=true;
                        break;
                    case RETURNINGSTAR:
                        returningStar=true;
                        break;
                }
            }
        }

        deleteStmt(statement sql) : statement(sql){
            std::string query = sql.stmt;
            stmt = query;
            tableName = {};
            only=false;
            ast=false;
            as=false;
            aliasStr={};
            where=false;
            whereEq={};
            returning=false;
            returningStar=false;

            std::pair<std::vector<int>, std::vector<std::string>> par = lex(query);
            tokVec = par.first; 
            strVec = par.second; 
            int sz = tokVec.size();
            bool tableNameLook = true;
            bool aliasLook = false;
            if(tokVec[0]!=DELETE){
                std::cout<<"ERROR: Not a DELETE statement!"<<std::endl;
            }
            if(tokVec[sz-1]!=SEMICOLON){
                std::cout<<"ERROR: Needs a ; at the end!"<<std::endl;
            }
            for(int i = 1; i<sz-1; i++){
                switch(tokVec[i]){
                    case STRINGNOQUOTES:
                        if(tableNameLook){
                            tableName = strVec[i];
                            tableNameLook=false;
                        }else if(aliasLook){
                            aliasStr = strVec[i];
                            aliasLook=false;
                        }
                        break;
                    case STRING:
                        if(tableNameLook){
                            tableName = strVec[i];
                            tableNameLook=false;
                        }else if(aliasLook){
                            aliasStr = strVec[i];
                            aliasLook=false;
                        }
                        break;
                    case ONLY:
                        only=true;
                        break;
                    case AS:
                        as=true;
                        aliasLook=true;
                        break;
                    case WHERE:
                        where=true;
                        whereEq.left = strVec[i+1];
                        whereEq.sym = strVec[i+2];
                        whereEq.right = strVec[i+3];
                        i+=3;
                        break;
                    case AST:
                        ast=true;
                        break;
                    case RETURNING:
                        returning=true;
                        break;
                    case RETURNINGSTAR:
                        returningStar=true;
                        break;
                }               
            }
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

        Equation getWhere(){
            return whereEq;
        }
        void setWhereLeft(std::string str){
            whereEq.left=str;
        }
        void setWhereSymbol(std::string str){
            whereEq.sym=str;
        }
        void setWhereRight(std::string str){
            whereEq.right=str;
        }

        std::string printDeleteStmt(){
            reconstructStmt();
            return stmt;
        }

        void reconstructStmt(){
            std::string newStmt = "DELETE FROM ";
            int sz = tokVec.size();
            bool tableNameLook = true;
            bool aliasLook = false;
            for(int i = 1; i<sz-1; i++){
                switch(tokVec[i]){
                    case STRINGNOQUOTES:
                        if(tableNameLook){
                            newStmt += tableName +" ";
                            tableNameLook=false;
                        }else if(aliasLook){
                            newStmt += aliasStr +" ";
                            aliasLook=false;
                        }
                        break;
                    case STRING:
                        if(tableNameLook){
                            newStmt += tableName +" ";
                            tableNameLook=false;
                        }else if(aliasLook){
                            newStmt += aliasStr +" ";
                            aliasLook=false;
                        }
                        break;
                    case ONLY:
                        newStmt+="ONLY ";
                        break;
                    case AS:
                        newStmt+="AS ";
                        aliasLook=true;
                        break;
                    case WHERE:
                        newStmt+="WHERE ";
                        newStmt += whereEq.printEquation()+" ";
                        i+=3;
                        break;
                    case AST:
                        newStmt+="* ";
                        break;
                    case RETURNING:
                        newStmt+="RETURNING ";
                        break;
                    case RETURNINGSTAR:
                        newStmt+="RETURNING * ";
                        break;
                }
            }
            newStmt+=";";
            stmt=newStmt;
        }

        ~deleteStmt(){}
    };
}
#endif