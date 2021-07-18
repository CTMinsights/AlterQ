TARGET = prog

$(TARGET): main.o lib.a
	g++ $^ -o $@

main.o: main.cpp
	g++ -c $< -o $@

lib.a: lib1.o lib2.o lib3.o
	ar rcs $@ $^

lib1.o: lex/aLex.cpp
	g++ -c -o $@ $<

lib2.o: structs/strucMain.cpp
	g++ -c -o $@ $<

lib3.o: lex/aLexxer.c
	g++ -c -o $@ $<

clean:
	rm -f *.o *.a $(TARGET) test.txt
