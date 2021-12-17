all:
	g++ ./src/*.cpp ./src/layers/*.cpp main.cpp -o exe
	
run:
	./exe