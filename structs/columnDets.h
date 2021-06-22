#ifndef COLUMN_DETS_H
#define COLUMN_DETS_H

#include "../lex/aLex.h"

namespace alp{

    enum dataType{
        tText, tInt4, tint2, tint8//, SERIAL2, SERIAL4, SERIAL8, BOOL, BIT, VARBIT, 
    };

    struct columnDets
    {
        std::string colName;
        dataType colData;

        columnDets colDets(std::pair<std::vector<int>, std::vector<std::string>> par)
        {
            //columnDets col;
            std::vector<int> tokVec = par.first; 
            std::vector<std::string> strVec = par.second; 
            int sz = tokVec.size();

            for(int i = 1; i<sz-1; i++){
                switch(tokVec[i]){
                    case STRINGNOQUOTES:
                        //name = strVec[i];
                        break;
                }
                
            }
            return *this;
        }

        ~columnDets(){}
    };
}
#endif