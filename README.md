SQL Parser README

The purpose of this project is to parse sql statements as strings to be used/modified in cpp.
Enter your code in 'main.cpp'(or create a new file but be sure to #include alp.h and use namespace alp and modify the makefile).

Dependencies:
    sudo apt-get install flex

To run parser:
    1. ./runLex.sh                  //This will compile the static library and run your code in "main.cpp"
    OR
    1. Enter lex directory
    2. Run command 'lex aLex.l'                                    //This creates the file 'aLexxer.c'
    3. Run command 'make'                                          //This compiles the code and static lib into executable 'prog'
    4. Run command './prog'                                        //This runs the app

Notes:
    You only need to run step 2 when you change the aLex.l or aLex.h file (but it doesn't hurt to do every time)
    