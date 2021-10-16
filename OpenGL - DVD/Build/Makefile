all: compile run

compile:
	g++ -I ../src/include/ -I ../src/vendor/ -L ../lib/ -o ../bin/main ../main.cpp ../src/*.c ../src/*.cpp -lglfw3 -lopengl32 -lgdi32 -luser32 -lshell32
run:
	../bin/main.exe