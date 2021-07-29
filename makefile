alp.so: lib1.o lib2.o lib3.o
	g++ -shared -o sharedLib/alp.so $^

lib1.o: lex/aLex.cpp
	g++ -c -o $@ $< -fPIC

lib2.o: structs/strucMain.cpp
	g++ -c -o $@ $< -fPIC

lib3.o: lex/aLexxer.c
	g++ -c -o $@ $< -fPIC

clean:
	rm -f *.o sharedLib/*.so test.txt