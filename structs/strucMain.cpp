#include <iostream>
#include <assert.h>

#include "strucMain.h"
#include "../lex/aLex.h"
#include "alterStmt.h"
#include "truncateStmt.h"
#include "createStmt.h"
#include "deleteStmt.h"
#include "insertStmt.h"
#include "selectStmt.h"
#include "updateStmt.h"
#include "dropStmt.h"

using namespace std;
using namespace alp;

//helper function to find string in vectors
int vecFind(vector<string> vec, string str){
    int index = 0;
    int sz = vec.size();
    for(int i=0; i<sz; i++){
        if(vec[i]==str){
            return i;
        }
    }
    return -1;
}