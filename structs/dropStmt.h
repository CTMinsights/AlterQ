#include <string>
#include <vector>
#include "../lex/aLex.h"

struct dropStmt
{
    std::string stmt;
    std::string name;
    bool ifexists;
    bool cascade;
    bool restrict;
    dropStmt(std::string query){
        stmt = query;
        name = "";
        ifexists = false;
        cascade = false;
        restrict = false;

        std::vector<int> lexVec = lexxer(query);
        int sz = lexVec.size();
        if(lexVec[0]!=DROPTABLE){
            std::cout<<"ERROR: Not a DROP TABLE statement!"<<std::endl;
        }
        if(lexVec[sz-1]!=SEMICOLON){
            std::cout<<"ERROR: Needs a ; at the end!"<<std::endl;
        }
        for(int i = 1; i<sz-1; i++){
            switch(i){
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
