#ifndef TABLE_DETS_H
#define TABLE_DETS_H

#include "../lex/aLex.h"

namespace alp{
    struct tableDets
    {
    //std::string stmt;
    
    tableDets(std::pair<std::vector<int>, std::vector<std::string>> par){
        stmt = query;
        std::vector<int> tokVec = par.first; 
        std::vector<std::string> strVec = par.second; 
        int sz = tokVec.size();

        for(int i = 1; i<sz-1; i++){
            switch(tokVec[i]){
                case STRINGNOQUOTES:
                    name = strVec[i];
                    break;
            }
            
        }
    }

    ~tableDets(){}
};

#endif