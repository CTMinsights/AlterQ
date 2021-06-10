#include <iostream>
#include <vector>

#include "strucTest.h"
#include "../lex/aLex.h"

using namespace std;

void foo()
{
    cout << "Hello World!\n";
    vector<int> lexVec = lexxer("INSERT INTO;");
    for(int i=0; i<lexVec.size(); i++){
        cout<<lexVec[i]<<endl;
    }
}