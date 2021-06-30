#ifndef SELECT_STMT_H
#define SELECT_STMT_H

#include "statement.h"

namespace alp{
    struct selectStmt : statement
    {
        std::string stmt;
        std::string selectStr;
        bool all;
        bool distinct;
        bool on;
        bool from;
        std::string fromStr;
        bool where;
        Equation whereEq;
        bool groupBy;
        std::string groupByStr;
        bool having;
        Equation havingEq;
        bool orderBy;
        std::string orderByStr;
        bool asc;
        bool desc;
        bool limit;
        std::string limitStr;
        bool offset;
        std::string offsetStr;
        bool ast;

        std::vector<int> tokVec;
        std::vector<std::string> strVec;
        
        selectStmt(std::string query) : statement(query){
            stmt = query;
            selectStr={};
            all=false;
            distinct=false;
            on=false;
            from=false;
            fromStr={};
            where=false;
            whereEq={};
            groupBy=false;
            groupByStr={};
            having=false;
            havingEq={};
            orderBy=false;
            orderByStr={};
            asc=false;
            desc=false;
            limit=false;
            limitStr={};
            offset=false;
            offsetStr={};
            ast=false;

            std::pair<std::vector<int>, std::vector<std::string>> par = lex(query);
            tokVec = par.first; 
            strVec = par.second; 
            int sz = tokVec.size();

            bool selectLook = true;
            bool groupByLook = false;
            bool orderByLook=false;
            bool limitLook=false;
            bool offsetLook=false;

            if(tokVec[0]!=SELECT && tokVec[0]!=SELECTDISTINCT){
                std::cout<<"ERROR: Not a SELECT statement!"<<std::endl;
            }
            if(tokVec[sz-1]!=SEMICOLON){
                std::cout<<"ERROR: Needs a ; at the end!"<<std::endl;
            }

            for(int i = 1; i<sz-1; i++){
                switch(tokVec[i]){
                    case STRINGNOQUOTES:
                        if(selectLook){
                            selectStr = strVec[i];
                            selectLook=false;
                        }
                        break;
                    case STRING:
                        if(selectLook){
                            selectStr = strVec[i];
                            selectLook=false;
                        }
                        break;
                    case FROM://change to from item stuff
                        from=true;
                        fromStr=strVec[i+1];
                        i++;
                        break;
                    case GROUPBY://change to grouping element stuff
                        groupBy=true;
                        groupByStr=strVec[i+1];
                        i++;
                        break;
                    case LIMIT:
                        limit=true;
                        limitStr=strVec[i+1];
                        i++;
                        break;
                    case ORDERBY:
                        orderBy=true;
                        orderByStr=strVec[i+1];
                        i++;
                        break;
                    case WHERE:
                        where=true;
                        whereEq.left = strVec[i+1];
                        whereEq.sym = strVec[i+2];
                        whereEq.right = strVec[i+3];
                        i+=3;
                        break;
                    case HAVING:
                        having=true;
                        havingEq.left = strVec[i+1];
                        havingEq.sym = strVec[i+2];
                        havingEq.right = strVec[i+3];
                        i+=3;
                        break;
                    case AST:
                        if(selectLook){
                            selectStr = strVec[i];
                            selectLook=false;
                        }
                        ast=true;
                        break;
                    case ALL:
                        all=true;
                        break;
                    case ASC:
                        asc=true;
                        break;
                    case DESC:
                        desc=true;
                        break;
                    case ON:
                        on=true;
                        break;
                    
                }
            }
        }

        selectStmt(statement sql) : statement(sql){
            std::string query = sql.stmt;
            stmt = query;
            selectStr={};
            all=false;
            distinct=false;
            on=false;
            from=false;
            fromStr={};
            where=false;
            whereEq={};
            groupBy=false;
            groupByStr={};
            having=false;
            havingEq={};
            orderBy=false;
            orderByStr={};
            asc=false;
            desc=false;
            limit=false;
            limitStr={};
            offset=false;
            offsetStr={};
            ast=false;

            std::pair<std::vector<int>, std::vector<std::string>> par = lex(query);
            tokVec = par.first; 
            strVec = par.second; 
            int sz = tokVec.size();

            bool selectLook = true;
            bool groupByLook = false;
            bool orderByLook=false;
            bool limitLook=false;
            bool offsetLook=false;

            if(tokVec[0]!=SELECT && tokVec[0]!=SELECTDISTINCT){
                std::cout<<"ERROR: Not a SELECT statement!"<<std::endl;
            }
            if(tokVec[sz-1]!=SEMICOLON){
                std::cout<<"ERROR: Needs a ; at the end!"<<std::endl;
            }

            for(int i = 1; i<sz-1; i++){
                switch(tokVec[i]){
                    case STRINGNOQUOTES:
                        if(selectLook){
                            selectStr = strVec[i];
                            selectLook=false;
                        }
                        break;
                    case STRING:
                        if(selectLook){
                            selectStr = strVec[i];
                            selectLook=false;
                        }
                        break;
                    case FROM://change to from item stuff
                        from=true;
                        fromStr=strVec[i+1];
                        i++;
                        break;
                    case GROUPBY://change to grouping element stuff
                        groupBy=true;
                        groupByStr=strVec[i+1];
                        i++;
                        break;
                    case LIMIT:
                        limit=true;
                        limitStr=strVec[i+1];
                        i++;
                        break;
                    case ORDERBY:
                        orderBy=true;
                        orderByStr=strVec[i+1];
                        i++;
                        break;
                    case WHERE:
                        where=true;
                        whereEq.left = strVec[i+1];
                        whereEq.sym = strVec[i+2];
                        whereEq.right = strVec[i+3];
                        i+=3;
                        break;
                    case HAVING:
                        having=true;
                        havingEq.left = strVec[i+1];
                        havingEq.sym = strVec[i+2];
                        havingEq.right = strVec[i+3];
                        i+=3;
                        break;
                    case AST:
                        if(selectLook){
                            selectStr = strVec[i];
                            selectLook=false;
                        }
                        ast=true;
                        break;
                    case ALL:
                        all=true;
                        break;
                    case ASC:
                        asc=true;
                        break;
                    case DESC:
                        desc=true;
                        break;
                    case ON:
                        on=true;
                        break;
                    
                }
            }
        }
        
        std::string getFrom(){
            return fromStr;
        }
        void setFrom(std::string tab){
            fromStr=tab;
        }

        std::string getSelect(){
            return selectStr;
        }
        void setSelect(std::string tab){
            selectStr=tab;
        }

        std::string printSelectStmt(){
            reconstructStmt();
            return stmt;
        }

        void reconstructStmt(){
            std::string newStmt = "";
            int sz = tokVec.size();
            bool selectLook = true;
            for(int i = 0; i<sz-1; i++){
                switch(tokVec[i]){
                    case SELECT:
                        newStmt+="SELECT ";
                        break;
                    case SELECTDISTINCT:
                        newStmt+="SELECT DISTINCT ";
                        break;
                    case STRINGNOQUOTES:
                        if(selectLook){
                            newStmt += selectStr +" ";
                            selectLook=false;
                        }
                        break;
                    case STRING:
                        if(selectLook){
                            newStmt += selectStr +" ";
                            selectLook=false;
                        }
                        break;
                    case AST:
                        if(selectLook){
                            newStmt += selectStr +" ";
                            selectLook=false;
                        }
                        break;
                    case FROM://change to from item stuff
                        newStmt+="FROM "+fromStr+" ";
                        i++;
                        break;
                    case GROUPBY://change to grouping element stuff
                        newStmt+="GROUP BY "+groupByStr+" ";
                        i++;
                        break;
                    case LIMIT:
                        newStmt+="LIMIT "+limitStr+" ";
                        i++;
                        break;
                    case ORDERBY:
                        newStmt+="ORDER BY "+orderByStr+" ";
                        i++;
                        break;
                    case WHERE:
                        newStmt+="WHERE ";
                        newStmt += whereEq.printEquation()+" ";
                        i+=3;
                        break;
                    case HAVING:
                        newStmt+="HAVING ";
                        newStmt += havingEq.printEquation()+" ";
                        i+=3;
                        break;
                    case ALL:
                        newStmt+="ALL ";
                        break;
                    case ASC:
                        newStmt+="ASC ";
                        break;
                    case DESC:
                        newStmt+="DESC ";
                        break;
                    case ON:
                        newStmt+="ON ";
                        break;
                }
            }

            newStmt+=";";
            stmt=newStmt;
        }
        ~selectStmt(){}
    };
}
#endif