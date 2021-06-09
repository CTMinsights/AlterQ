SQL Parser README

Dependencies:
    sudo apt-get install flex
    cmake

To first run cmake project in src:
    1. Enter build directory
    2. Run command 'cmake ..' //This creates the Makefile
    3. Run command 'make'     //This creates the app
    4. Run command './app'
After these intitial steps you only need to follow steps 1->3->4

To run lex parser:
    1. Enter lex directory
    2. Run command 'lex aLex.l'                                    //This creates the file 'aLexxer.c'
    3. Run command 'g++ aLex.cpp aLexxer.c -o aLex'                //This compiles the code with the lex file into a 'aLex' app
    4. Run command './aLex'                                        //This runs the app
    5. Type in strings to be parsed, type 'quit' to end program
Notes:
    You only need to run step 2 when you change the .l or .h file (but it doesn't hurt to do every time)