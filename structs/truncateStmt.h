#ifndef TRUNCATE_STMT_H
#define TRUNCATE_STMT_H

#include "statement.h"

namespace alp{
    struct truncateStmt : statement
    {
        std::string stmt;
        std::string tableName;
        bool restartI;
        bool continueI;
        bool cascade;
        bool restrict;
        bool ast;
        std::vector<int> tokVec;
        std::vector<std::string> strVec;
        
        truncateStmt(std::string query) : statement(query){
            stmt = query;
            tableName = {};
            continueI = false;
            restartI = false;
            cascade = false;
            restrict = false;
            ast=false;
            std::pair<std::vector<int>, std::vector<std::string>> par = lex(query);
            tokVec = par.first; 
            strVec = par.second; 
            int sz = tokVec.size();
            if(tokVec[0]!=TRUNCATE){
                std::cout<<"ERROR: Not a TRUNCATE TABLE statement!"<<std::endl;
            }
            if(tokVec[sz-1]!=SEMICOLON){
                std::cout<<"ERROR: Needs a ; at the end!"<<std::endl;
            }
            for(int i = 1; i<sz-1; i++){
                switch(tokVec[i]){
                    case STRINGNOQUOTES:
                        tableName = strVec[i];
                        break;
                    case STRING:
                        tableName = strVec[i];
                        break;
                    case CONTINUEIDEN:
                        continueI=true;
                        break;
                    case RESTARTIDEN:
                        restartI=true;
                        break;
                    case CASCADE:
                        cascade=true;
                        break;
                    case RESTRICT:
                        restrict=true;
                        break;
                    case AST:
                        ast = true;
                        break;
                }
                
            }
        }

        truncateStmt(statement sql) : statement(sql){
            std::string query = sql.stmt;
            stmt = query;
            tableName = {};
            continueI = false;
            restartI = false;
            cascade = false;
            restrict = false;
            ast=false;
            std::pair<std::vector<int>, std::vector<std::string>> par = lex(query);
            tokVec = par.first; 
            strVec = par.second; 
            int sz = tokVec.size();
            if(tokVec[0]!=TRUNCATE){
                std::cout<<"ERROR: Not a TRUNCATE TABLE statement!"<<std::endl;
            }
            if(tokVec[sz-1]!=SEMICOLON){
                std::cout<<"ERROR: Needs a ; at the end!"<<std::endl;
            }
            for(int i = 1; i<sz-1; i++){
                switch(tokVec[i]){
                    case STRINGNOQUOTES:
                        tableName = strVec[i];
                        break;
                    case STRING:
                        tableName = strVec[i];
                        break;
                    case CONTINUEIDEN:
                        continueI=true;
                        break;
                    case RESTARTIDEN:
                        restartI=true;
                        break;
                    case CASCADE:
                        cascade=true;
                        break;
                    case RESTRICT:
                        restrict=true;
                        break;
                    case AST:
                        ast = true;
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
        
        std::string printTruncateStmt(){
            reconstructStmt();
            return stmt;
        }

        void reconstructStmt(){
            std::string newStmt = "TRUNCATE TABLE ";
            int sz = tokVec.size();
            for(int i = 1; i<sz-1; i++){
                switch(tokVec[i]){
                    case STRINGNOQUOTES:
                        newStmt += tableName +" ";
                        break;
                    case STRING:
                        newStmt += tableName +" ";
                        break;
                    case ONLY:
                        newStmt+="ONLY ";
                        break;
                    case RESTARTIDEN:
                        newStmt+="RESTART IDENTITY ";
                        break;
                    case CONTINUEIDEN:
                        newStmt+="CONTINUE IDENTITY ";
                        break;
                    case CASCADE:
                        newStmt+="CASCADE ";
                        break;
                    case RESTRICT:
                        newStmt+="RESTRICT ";
                        break;
                    case AST:
                        newStmt+="* ";
                        break;
                }
            }
            newStmt+=";";
            stmt=newStmt;
        }
            
        ~truncateStmt(){}
    };
}
#endif