#ifndef EQUATION_H
#define EQUATION_H

#include "../lex/aLex.h"

namespace alp{
    enum comp {
        CEQUALS,
        CNOTEQUALS,
        CLESS,
        CLESSEQUAL,
        CGREATER,
        CGREATEREQUAL
    };
    
    struct Equation{
        comp symbol;
        std::string sym;//Use enum not this later
        std::string left;
        std::string right;

        std::vector<int> tokVec;
        std::vector<std::string> strVec;

        Equation Equat(std::vector<int> tVec, std::vector<std::string> sVec){
            right = sVec[2];
            sym = sVec[1];
            left = sVec[0];
            return *this;
        }

        ~Equation(){}

        std::string printEquation(){
            return left+" "+sym+" "+right;
        }
    };
}

#endif