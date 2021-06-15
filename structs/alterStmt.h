#include <string>
#include <vector>
#include "../lex/aLex.h"

struct alterStmt
{
    std::string stmt;
    std::string tableName;
    std::string fromName;
    std::string toName;
    bool ifexists;
    bool only;
    bool rename;
    bool column;
    
    alterStmt(std::string query){
        stmt = query;
        tableName = {};
        fromName = {};
        toName = {};
        ifexists = false;
        cascade = false;
        restrict = false;
        std::pair<std::vector<int>, std::vector<std::string>> par = lex(query);
        std::vector<int> tokVec = par.first; 
        std::vector<std::string> strVec = par.second; 
        int sz = tokVec.size();
        if(tokVec[0]!=ALTERTABLE){
            std::cout<<"ERROR: Not a ALTER TABLE statement!"<<std::endl;
        }
        if(tokVec[sz-1]!=SEMICOLON){
            std::cout<<"ERROR: Needs a ; at the end!"<<std::endl;
        }
        for(int i = 1; i<sz-1; i++){
            switch(tokVec[i]){
                case STRINGNOQUOTES://also need to check for colname, and skip if already done(like after TO)
                    name = strVec[i];
                    break;
                case IFEXISTS:
                    ifexists=true;
                    break;
                case ONLY:
                    only=true;
                    break;
                case RENAME:
                    rename=true;
                    break;
                case COLUMN:
                    column=true;
                    break;
                case TO:
                    toName=strVec[i+1];
                    break;
            }
            
        }
    }
};
