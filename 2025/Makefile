all: $(patsubst %.cpp, %, $(wildcard *.cpp))

%: %.cpp
	g++ -std=c++23 -Wall $< -o $@

clean:
	rm -f $(patsubst %.cpp, %, $(wildcard *.cpp))

