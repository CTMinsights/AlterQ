#ifndef STATEMENT_H
#define STATEMENT_H

#include "columnDets.h"
#include "Equation.h"

namespace alp {
    enum type {Drop, Truncate, Create, Delete, Insert, Select, Alter, Update, None};
    struct statement
    {
        std::string stmt;
        type stmtType;

        statement(std::string query){
            stmt = query;
            stmtType = None;
            std::pair<std::vector<int>, std::vector<std::string>> par = lex(query);
            std::vector<int> tokVec = par.first; 
            std::vector<std::string> strVec = par.second; 
            int sz = tokVec.size();
        
            if(tokVec[sz-1]!=SEMICOLON){
                std::cout<<"ERROR: Needs a ; at the end!"<<std::endl;
            }

            for(int i = 0; i<sz-1; i++){
                switch(tokVec[i]){
                    case DROPTABLE:
                        stmtType = Drop;
                        break;
                    case CREATETABLE:
                        stmtType = Create;
                        break;
                    case SELECT:
                        stmtType = Select;
                        break;
                    case INSERTINTO:
                        stmtType = Insert;
                        break;
                    case DELETE:
                        stmtType = Delete;
                        break;
                    case UPDATE:
                        stmtType = Update;
                        break;
                    case TRUNCATE:
                        stmtType = Truncate;
                        break;
                    case ALTERTABLE:
                        stmtType = Alter;
                        break;
                }
            }
        }

        void printStatementInfo(){
            std::cout<<"print"<<std::endl;
        }
        
        ~statement(){}
    };
}

#endif