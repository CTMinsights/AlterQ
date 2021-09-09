# SQL Parser README

The purpose of this project is to parse sql statements as strings to be used/modified in cpp.
Enter your code in 'main.cpp'(or create a new file but be sure to include '#include alp.h' and 'using namespace alp' and modify the makefile).

## Dependencies:
    sudo apt-get install flex

## To run parser*:
    1. ./runLex.sh                  //This will compile the static library and run your code in "main.cpp"
    OR
    1. Run command 'lex lex/aLex.l'                                //This creates the file 'aLexxer.c'
    2. Run command 'make'                                          //This compiles the code and static lib into executable 'prog' and library alp.so
    3. Run command './prog'                                        //This runs the app
    *In branch 'main' this will run as listed above
    *In branch 'sharedLib' this will create the shared library you may use to include this library in another project.
## Notes:
You only need to run step 2 when you change the aLex.l or aLex.h file (but it doesn't hurt to do every time)
    
## License

AlterQ is licensed as open source after the MIT License which is declared in the LICENSE file of this project.

## Contributors

* Alex Kubecka

## Contributing

Anyone is welcome to contribute to this project. Issues and things that need work can be found in the documentation/Statements folder. 
Information on how to use the library tools can be found in the documentation/UsageDoc document.
Feel free to ask any questions or bring any issues to the communities attention in the discussion tab.

