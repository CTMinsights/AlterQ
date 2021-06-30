#ifndef CREATE_STMT_H
#define CREATE_STMT_H

#include "statement.h"

namespace alp{
    enum createType{cNorm, cAs, cView};//Check which type of CREATE stmt this is

    struct createStmt : statement
    {
        createType cT;
        //cAs
        std::string stmt;
        std::string tableName;
        bool create;
        bool table;
        bool global;
        bool local;
        bool temp;
        bool unlogged;
        bool ifnotexists;
        bool as;
        std::string asStr;
        bool withdata;
        bool withnodata;

        //cNorm
        std::vector<columnDets> colVec;
        //etc

        std::vector<int> tokVec;
        std::vector<std::string> strVec;
        
        createStmt(std::string query) : statement(query){
            stmt = query;
            tableName={};
            cT={};
            global=temp;
            local=false;
            temp=false;
            unlogged=false;
            ifnotexists=false;
            as=false;
            asStr={};
            withdata=false;
            withnodata=false;

            std::pair<std::vector<int>, std::vector<std::string>> par = lex(query);
            tokVec = par.first; 
            strVec = par.second; 
            int sz = tokVec.size();
            if(tokVec[0]!=CREATE && tokVec[0]!=CREATETABLE){
                std::cout<<"ERROR: Not a CREATE statement!"<<std::endl;
            }
            if(tokVec[sz-1]!=SEMICOLON){
                std::cout<<"ERROR: Needs a ; at the end!"<<std::endl;
            }
            bool tableLook=true;
            bool asLook=false;
            columnDets tempCol;
            std::vector<int> tempInt;
            std::vector<std::string> tempStr;
            bool parenOpen=false;
            for(int i = 0; i<sz-1; i++){
                switch(tokVec[i]){
                    case CREATE:
                        create=true;
                        break;
                    case TABLE:
                        table=true;
                        break;
                    case CREATETABLE:
                        create=true;
                        table=true;
                        break;
                    case STRINGNOQUOTES:
                        if(tableLook){
                            tableName=strVec[i];
                            tableLook=false;
                        }
                        else if(asLook){
                            asStr = strVec[i];
                            asLook=false;
                        }
                        break;
                    case STRING:
                        if(tableLook){
                            tableName=strVec[i];
                            tableLook=false;
                        }
                        else if(asLook){
                            asStr = strVec[i];
                            asLook=false;
                        }
                        break;
                    case GLOBAL:
                        global=true;
                        break;
                    case LOCAL:
                        local=true;
                        break;
                    case TEMP:
                        temp=true;
                        break;
                    case UNLOGGED:
                        unlogged=true;
                        break;
                    case IFNOTEXISTS:
                        ifnotexists=true;
                        break;
                    case AS:
                        as=true;
                        asLook=true;
                        break;
                    case WITHDATA:
                        withdata=true;
                        break;
                    case WITHNODATA:
                        withnodata=true;
                        break;
                    case OPENPAREN:
                        tempInt.push_back(tokVec[i+1]);
                        tempInt.push_back(tokVec[i+2]);
                        tempStr.push_back(strVec[i+1]);
                        tempStr.push_back(strVec[i+2]);
                        i+=2;
                        tempCol.colDets(tempInt, tempStr);
                        colVec.push_back(tempCol);
                        tempInt.clear();
                        tempStr.clear();
                        parenOpen=true;
                        break;
                    case COMMA:
                        if(parenOpen){
                            tempInt.push_back(tokVec[i+1]);
                            tempInt.push_back(tokVec[i+2]);
                            tempStr.push_back(strVec[i+1]);
                            tempStr.push_back(strVec[i+2]);
                            i+=2;
                            tempCol.colDets(tempInt, tempStr);
                            colVec.push_back(tempCol);
                            tempInt.clear();
                            tempStr.clear();
                        }
                        break;
                    case CLOSEPAREN:
                        parenOpen=false;
                        break;
                }
            }
        }

        createStmt(statement sql) : statement(sql){
            std::string query = sql.stmt;
            stmt = query;
            tableName={};
            cT={};
            global=temp;
            local=false;
            temp=false;
            unlogged=false;
            ifnotexists=false;
            as=false;
            asStr={};
            withdata=false;
            withnodata=false;

            std::pair<std::vector<int>, std::vector<std::string>> par = lex(query);
            tokVec = par.first; 
            strVec = par.second; 
            int sz = tokVec.size();
            if(tokVec[0]!=CREATE && tokVec[0]!=CREATETABLE){
                std::cout<<"ERROR: Not a CREATE statement!"<<std::endl;
            }
            if(tokVec[sz-1]!=SEMICOLON){
                std::cout<<"ERROR: Needs a ; at the end!"<<std::endl;
            }
            bool tableLook=true;
            bool asLook=false;
            for(int i = 0; i<sz-1; i++){
                switch(tokVec[i]){
                    case CREATE:
                        create=true;
                        break;
                    case TABLE:
                        table=true;
                        break;
                    case CREATETABLE:
                        create=true;
                        table=true;
                        break;
                    case STRINGNOQUOTES:
                        if(tableLook){
                            tableName=strVec[i];
                            tableLook=false;
                        }else if(asLook){
                            asStr = strVec[i];
                            asLook=false;
                        }
                        break;
                    case STRING:
                        if(tableLook){
                            tableName=strVec[i];
                            tableLook=false;
                        }
                        else if(asLook){
                            asStr = strVec[i];
                            asLook=false;
                        }
                        break;
                    case GLOBAL:
                        global=true;
                        break;
                    case LOCAL:
                        local=true;
                        break;
                    case TEMP:
                        temp=true;
                        break;
                    case UNLOGGED:
                        unlogged=true;
                        break;
                    case IFNOTEXISTS:
                        ifnotexists=true;
                        break;
                    case AS:
                        as=true;
                        asLook=true;
                        break;
                    case WITHDATA:
                        withdata=true;
                        break;
                    case WITHNODATA:
                        withnodata=true;
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

        std::vector<columnDets> getColVec(){
            return colVec;
        }
        void setColVec(std::vector<columnDets> cv){
            colVec=cv;
        }

        std::string printCreateStmt(){
            reconstructStmt();
            return stmt;
        }

        void reconstructStmt(){
            std::string newStmt = "";
            int sz = tokVec.size();
            bool tableLook=true;
            bool asLook=false;
            columnDets tempCol;
            std::vector<int> tempInt;
            std::vector<std::string> tempStr;
            bool parenOpen=false;
            int x=0;
            for(int i = 0; i<sz-1; i++){
                switch(tokVec[i]){
                    case CREATE:
                        newStmt+="CREATE ";
                        break;
                    case CREATETABLE:
                        newStmt+="CREATE TABLE ";
                        break;
                    case TABLE:
                        newStmt+="TABLE ";
                        break;
                    case STRINGNOQUOTES:
                        if(tableLook){
                            newStmt+=tableName+" ";
                            tableLook=false;
                        }else if(asLook){
                            newStmt+=asStr+" ";
                            asLook=false;
                        }
                        break;
                    case STRING:
                        if(tableLook){
                            newStmt+=tableName+" ";
                            tableLook=false;
                        }
                        else if(asLook){
                            newStmt+=asStr+" ";
                            asLook=false;
                        }
                        break;
                    case GLOBAL:
                        newStmt+="GLOBAL ";
                        break;
                    case LOCAL:
                        newStmt+="LOCAL ";
                        break;
                    case TEMP:
                        newStmt+="TEMP ";
                        break;
                    case UNLOGGED:
                        newStmt+="UNLOGGED ";
                        break;
                    case IFNOTEXISTS:
                        newStmt+="IF NOT EXISTS ";
                        break;
                    case AS:
                        newStmt+="AS ";
                        asLook=true;
                        break;
                    case WITHDATA:
                        newStmt+="WITH DATA ";
                        break;
                    case WITHNODATA:
                        newStmt+="WITH NO DATA ";
                        break;
                    case OPENPAREN:
                        i+=2;
                        newStmt+="("+colVec[x].printColDets();
                        x++;
                        parenOpen=true;
                        break;
                    case COMMA:
                        newStmt+=", ";
                        if(parenOpen){
                            i+=2;
                            newStmt+=colVec[x].printColDets();
                            x++;
                        }
                        break;
                    case CLOSEPAREN:
                        newStmt+=") ";
                        parenOpen=false;
                        break;
                }
            }
            newStmt+=";";
            stmt=newStmt;
        }
        ~createStmt(){}
    };
}
#endif