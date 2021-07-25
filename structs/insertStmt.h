#ifndef INSERT_STMT_H
#define INSERT_STMT_H

#include "statement.h"

namespace alp{
    struct insertStmt : statement
    {
        std::string stmt;
        std::string tableName;
        bool as;
        std::string aliasStr;
        bool values;
        bool returning;
        bool returningStar;
        std::vector<std::string> colNames;
        std::vector<std::string> valuesVec;

        std::vector<int> tokVec;
        std::vector<std::string> strVec;

        insertStmt(std::string query) : statement(query){
            stmt = query;
            tableName = {};
            as=false;
            aliasStr={};
            colNames={};
            valuesVec={};
            returning=false;
            returningStar=false;

            std::pair<std::vector<int>, std::vector<std::string>> par = lex(query);
            tokVec = par.first; 
            strVec = par.second; 
            int sz = tokVec.size();

            bool tableNameLook = true;
            bool aliasLook = false;
            bool parenOpen = false;
            bool colLook = true;
            bool valLook = false;

            if(tokVec[0]!=INSERTINTO){
                std::cout<<"ERROR: Not an INSERT INTO statement!"<<std::endl;
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
                        }else if(parenOpen&&colLook){
                            colNames.push_back(strVec[i]);
                        }else if(parenOpen&&valLook){
                            valuesVec.push_back(strVec[i]);
                        }
                        break;
                    case STRING:
                        if(tableNameLook){
                            tableName = strVec[i];
                            tableNameLook=false;
                        }else if(aliasLook){
                            aliasStr = strVec[i];
                            aliasLook=false;
                        }else if(parenOpen&&colLook){
                            colNames.push_back(strVec[i]);
                        }else if(parenOpen&&valLook){
                            valuesVec.push_back(strVec[i]);
                        }
                        break;
                    case NUMBER:
                        if(parenOpen&&colLook){
                            colNames.push_back(strVec[i]);
                        }else if(parenOpen&&valLook){
                            valuesVec.push_back(strVec[i]);
                        }
                        break;
                    case NUMWDEC:
                        if(parenOpen&&colLook){
                            colNames.push_back(strVec[i]);
                        }else if(parenOpen&&valLook){
                            valuesVec.push_back(strVec[i]);
                        }
                        break;
                    case AS:
                        as=true;
                        aliasLook=true;
                        break;
                    case RETURNING:
                        returning=true;
                        break;
                    case RETURNINGSTAR:
                        returningStar=true;
                        break;
                    case OPENPAREN:
                        parenOpen=true;
                        break;
                    case CLOSEPAREN:
                        parenOpen=false;
                        colLook=false;
                        valLook=false;
                        break;
                    case VALUES:
                        values=true;
                        valLook=true;
                        break;
                }
            }
        }

        insertStmt(statement sql) : statement(sql){
            std::string query = sql.stmt;
            tableName={};
            stmt = query;
            as=false;
            aliasStr={};
            colNames={};
            valuesVec={};
            returning=false;
            returningStar=false;

            std::pair<std::vector<int>, std::vector<std::string>> par = lex(query);
            tokVec = par.first; 
            strVec = par.second; 
            int sz = tokVec.size();

            bool tableNameLook = true;
            bool aliasLook = false;
            bool parenOpen = false;
            bool colLook = true;
            bool valLook = false;

            if(tokVec[0]!=INSERTINTO){
                std::cout<<"ERROR: Not an INSERT INTO statement!"<<std::endl;
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
                        }else if(parenOpen&&colLook){
                            colNames.push_back(strVec[i]);
                        }else if(parenOpen&&valLook){
                            valuesVec.push_back(strVec[i]);
                        }
                        break;
                    case STRING:
                        if(tableNameLook){
                            tableName = strVec[i];
                            tableNameLook=false;
                        }else if(aliasLook){
                            aliasStr = strVec[i];
                            aliasLook=false;
                        }else if(parenOpen&&colLook){
                            colNames.push_back(strVec[i]);
                        }else if(parenOpen&&valLook){
                            valuesVec.push_back(strVec[i]);
                        }
                        break;
                    case NUMBER:
                        if(parenOpen&&colLook){
                            colNames.push_back(strVec[i]);
                        }else if(parenOpen&&valLook){
                            valuesVec.push_back(strVec[i]);
                        }
                        break;
                    case NUMWDEC:
                        if(parenOpen&&colLook){
                            colNames.push_back(strVec[i]);
                        }else if(parenOpen&&valLook){
                            valuesVec.push_back(strVec[i]);
                        }
                        break;
                    case AS:
                        as=true;
                        aliasLook=true;
                        break;
                    case RETURNING:
                        returning=true;
                        break;
                    case RETURNINGSTAR:
                        returningStar=true;
                        break;
                    case OPENPAREN:
                        parenOpen=true;
                        break;
                    case CLOSEPAREN:
                        parenOpen=false;
                        colLook=false;
                        valLook=false;
                        break;
                    case VALUES:
                        values=true;
                        valLook=true;
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
        
        std::vector<std::string> getColNames(){
            return colNames;
        }
        void setColNames(std::vector<std::string> cn){
            colNames=cn;
        }

        std::vector<std::string> getValues(){
            return valuesVec;
        }
        void setValues(std::vector<std::string> cv){
            valuesVec=cv;
        }

        std::string printInsertStmt(){
            reconstructStmt();
            return stmt;
        }

        void reconstructStmt(){
            std::string newStmt = "INSERT INTO ";
            int sz = tokVec.size();
            bool tableNameLook = true;
            bool aliasLook = false;
            bool parenOpen = false;
            bool colLook = true;
            bool valLook = false;
            for(int i = 1; i<sz-1; i++){
                switch(tokVec[i]){
                    case STRINGNOQUOTES:
                        if(tableNameLook){
                            newStmt+=tableName+" ";
                            tableNameLook=false;
                        }else if(aliasLook){
                            newStmt += aliasStr +" ";
                            aliasLook=false;
                        }else if(parenOpen&&colLook){
                            newStmt+=printVec(colNames);
                            colLook=false;//gotta be a better way
                        }else if(parenOpen&&valLook){
                            newStmt+=printVec(valuesVec);
                            valLook=false;//gotta be a better way
                        }
                        break;
                    case STRING:
                        if(tableNameLook){
                            newStmt+=tableName+" ";
                            tableNameLook=false;
                        }else if(aliasLook){
                            newStmt += aliasStr +" ";
                            aliasLook=false;
                        }else if(parenOpen&&colLook){
                            newStmt+=printVec(colNames);
                            colLook=false;//gotta be a better way
                        }else if(parenOpen&&valLook){
                            newStmt+=printVec(valuesVec);
                            valLook=false;//gotta be a better way
                        }
                        break;
                    case NUMBER://Need to account for any type here :/ somehow
                        if(parenOpen&&colLook){
                            newStmt+=printVec(colNames);
                            colLook=false;//gotta be a better way
                        }else if(parenOpen&&valLook){
                            newStmt+=printVec(valuesVec);
                            valLook=false;//gotta be a better way
                        }
                        break;
                    case NUMWDEC:
                        if(parenOpen&&colLook){
                            newStmt+=printVec(colNames);
                            colLook=false;//gotta be a better way
                        }else if(parenOpen&&valLook){
                            newStmt+=printVec(valuesVec);
                            valLook=false;//gotta be a better way
                        }
                        break;
                    case AS:
                        newStmt+="AS ";
                        aliasLook=true;
                        break;
                    case RETURNING:
                        newStmt+="RETURNING ";
                        break;
                    case RETURNINGSTAR:
                        newStmt+="RETURNING * ";
                        break;
                    case OPENPAREN:
                        parenOpen=true;
                        break;
                    case CLOSEPAREN:
                        parenOpen=false;
                        colLook=false;
                        valLook=false;
                        break;
                    case VALUES:
                        newStmt+="VALUES ";
                        valLook=true;
                        break;
                    case COMMA://use this later for multirows
                        break;
                }
            }
            newStmt+=";";
            stmt=newStmt;
        }

        std::string printVec(std::vector<std::string> vec){
            std::string str = "(";
            int sz = vec.size();
            for(int i=0; i<sz-1; i++){
                str+=vec[i]+", ";
            }
            str+=vec[sz-1]+") ";
            return str;
        }
        ~insertStmt(){}
    };
}

#endif