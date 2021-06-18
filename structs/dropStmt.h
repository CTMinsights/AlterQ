#ifndef DROP_STMT_H
#define DROP_STMT_H

#include "statement.h"

struct dropStmt
{
    std::string stmt;
    std::string name;
    bool ifexists;
    bool cascade;
    bool restrict;

    dropStmt(std::string query){
        stmt = query;
        name = {};
        ifexists = false;
        cascade = false;
        restrict = false;
        std::pair<std::vector<int>, std::vector<std::string>> par = lex(query);
        std::vector<int> tokVec = par.first; 
        std::vector<std::string> strVec = par.second; 
        int sz = tokVec.size();
        if(tokVec[0]!=DROPTABLE){
            std::cout<<"ERROR: Not a DROP TABLE statement!"<<std::endl;
        }
        if(tokVec[sz-1]!=SEMICOLON){
            std::cout<<"ERROR: Needs a ; at the end!"<<std::endl;
        }
        for(int i = 1; i<sz-1; i++){
            switch(tokVec[i]){
                case STRINGNOQUOTES:
                    name = strVec[i];
                    break;
                case IFEXISTS:
                    ifexists=true;
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

    dropStmt(statement sql){
        std::string query = sql.stmt;
        stmt = query;
        name = {};
        ifexists = false;
        cascade = false;
        restrict = false;
        std::pair<std::vector<int>, std::vector<std::string>> par = lex(query);
        std::vector<int> tokVec = par.first; 
        std::vector<std::string> strVec = par.second; 
        int sz = tokVec.size();
        if(tokVec[0]!=DROPTABLE){
            std::cout<<"ERROR: Not a DROP TABLE statement!"<<std::endl;
        }
        if(tokVec[sz-1]!=SEMICOLON){
            std::cout<<"ERROR: Needs a ; at the end!"<<std::endl;
        }
        for(int i = 1; i<sz-1; i++){
            switch(tokVec[i]){
                case STRINGNOQUOTES:
                    name = strVec[i];
                    break;
                case IFEXISTS:
                    ifexists=true;
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
};

#endif