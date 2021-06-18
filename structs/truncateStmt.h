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

        truncateStmt(std::string query) : statement(query){
            stmt = query;
            tableName = {};
            continueI = false;
            restartI = false;
            cascade = false;
            restrict = false;
            std::pair<std::vector<int>, std::vector<std::string>> par = lex(query);
            std::vector<int> tokVec = par.first; 
            std::vector<std::string> strVec = par.second; 
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
                    case CONTIDEN:
                        continueI=true;
                        break;
                    case RESIDEN:
                        restartI=true;
                        break;
                    case CASCADE:
                        cascade=true;
                        break;
                    case RESTRICT:
                        restrict=true;
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
            std::pair<std::vector<int>, std::vector<std::string>> par = lex(query);
            std::vector<int> tokVec = par.first; 
            std::vector<std::string> strVec = par.second; 
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
                    case CONTIDEN:
                        continueI=true;
                        break;
                    case RESIDEN:
                        restartI=true;
                        break;
                    case CASCADE:
                        cascade=true;
                        break;
                    case RESTRICT:
                        restrict=true;
                        break;
                }
                
            }
        }

    /*     printTruncateInfo{
            std::cout<<"truncate info"<<std::endl;
        } */
            
        ~truncateStmt(){}
    };
}
#endif