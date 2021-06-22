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
        std::string colDataStr;///Should not use this
        dataType colData;//Should use this
        bool ifnotexists;
        bool ifexists;
        bool collate;
        std::string collateStr;
        bool restrict;
        bool cascade;

        //constraints
        bool constraint;
        std::string constraintStr;
        bool null;
        bool notnull;
        bool primKey;
        bool unique;

        std::vector<int> tokVec;
        std::vector<std::string> strVec;

        columnDets colDets(std::vector<int> tVec, std::vector<std::string> sVec)
        {
            //columnDets col;
            colName={};
            colDataStr={};
            ifnotexists = false;
            ifexists=false;
            collate=false;
            collateStr="";
            restrict=false;
            cascade=false;
            constraint=false;
            constraintStr={};

            null=false;
            notnull=false;
            primKey=false;
            unique=false;

            //Helper bools
            bool colNameLook=true;
            bool dataLook = false;
            bool collateLook=false;
            bool constraintLook=false;
            
            tokVec = tVec; 
            strVec = sVec; 
            int sz = tokVec.size();

            for(int i = 1; i<sz-1; i++){
                switch(tokVec[i]){
                    case STRINGNOQUOTES:
                        if(colNameLook){
                            colName = strVec[i];
                            colNameLook=false;
                            dataLook=true;
                        }else if(dataLook){
                            colDataStr=strVec[i];
                            dataLook=false;
                        }else if(collateLook){
                            collateStr=strVec[i];
                            collateLook=false;
                        }else if(constraintLook){
                            constraintStr=strVec[i];
                            constraintLook=false;
                        }
                        break;
                    case STRING:
                        if(colNameLook){
                            colName = strVec[i];
                            colNameLook=false;
                            dataLook=true;
                        }else if(dataLook){
                            colDataStr=strVec[i];
                            dataLook=false;
                        }else if(collateLook){
                            collateStr=strVec[i];
                            collateLook=false;
                        }else if(constraintLook){
                            constraintStr=strVec[i];
                            constraintLook=false;
                        }
                        break;
                    case COLLATE:
                        collate=true;
                        collateLook=true;
                        break;
                    case CONSTRAINT:
                        constraint=true;
                        constraintLook=true;
                        break;
                    case ISNULL:
                        null=true;
                        break;
                    case ISNOTNULL:
                        notnull=true;
                        break;
                    case IFNOTEXISTS:
                        ifnotexists=true;
                        break;
                    case IFEXISTS:
                        ifexists=true;
                        break;
                    case RESTRICT:
                        restrict=true;
                        break;
                    case CASCADE:
                        cascade=true;
                        break;
                    case PRIMARYKEY:
                        primKey=true;
                        break;
                    case UNIQUE:
                        unique=true;
                        break;
                }
                
            }
            return *this;
        }

    std::string printColDets(){
        std::string colD = "";

        bool colNameLook=true;
        bool dataLook = false;
        bool collateLook=false;
        bool constraintLook=false;

        int sz = tokVec.size();

        for(int i = 1; i<sz-1; i++){
            switch(tokVec[i]){
                case STRINGNOQUOTES:
                    if(colNameLook){
                        colD += colName +" ";
                        colNameLook=false;
                        dataLook=true;
                    }else if(dataLook){
                        colD += colDataStr +" ";
                        dataLook=false;
                    }else if(collateLook){
                        colD += collateStr+" ";;
                        collateLook=false;
                    }else if(constraintLook){
                        colD += constraintStr+" ";
                        constraintLook=false;
                    }
                    break;
                case STRING:
                    if(colNameLook){
                        colD += colName +" ";
                        colNameLook=false;
                        dataLook=true;
                    }else if(dataLook){
                        colD += colDataStr +" ";
                        dataLook=false;
                    }else if(collateLook){
                        colD += collateStr+" ";;
                        collateLook=false;
                    }else if(constraintLook){
                        colD += constraintStr+" ";
                        constraintLook=false;
                    }
                    break;
                case COLLATE:
                    colD+="COLLATE ";
                    collateLook=true;
                    break;
                case CONSTRAINT:
                    colD+="CONSTRAINT ";
                    constraintLook=true;
                    break;
                case ISNULL:
                    colD+="NULL ";
                    break;
                case ISNOTNULL:
                    colD+="NOT NULL ";
                    break;
                case IFNOTEXISTS:
                    colD+="IF NOT EXISTS ";
                    break;
                case IFEXISTS:
                    colD+="IF EXISTS ";
                    break;
                case RESTRICT:
                    colD+="RESTRICT ";
                    break;
                case CASCADE:
                    colD+="CASCADE ";
                    break;
                case PRIMARYKEY:
                    colD+="PRIMARY KEY ";
                    break;
                case UNIQUE:
                    colD+="UNIQUE ";
                    break;
            }
        }
        return colD;
    }
        ~columnDets(){}
    };
}
#endif