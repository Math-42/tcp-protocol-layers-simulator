all:
	g++ ./src/*.cpp ./src/layers/*.cpp main.cpp \
 	-pthread -o exe
	
run:
	./exe