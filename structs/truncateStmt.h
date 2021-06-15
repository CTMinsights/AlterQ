#include <string>
#include <vector>
#include "../lex/aLex.h"

struct truncateStmt
{
    std::string stmt;
    std::string name;
    bool restartI;
    bool continueI;
    bool cascade;
    bool restrict;

    truncateStmt(std::string query){
        stmt = query;
        name = {};
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
                    name = strVec[i];
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
};
