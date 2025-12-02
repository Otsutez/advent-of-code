all: $(patsubst %.cpp, %, $(wildcard *.cpp))

%: %.cpp
	g++ -std=c++11 -Wall $< -o $@

clean:
	rm -f $(patsubst %.cpp, %, $(wildcard *.cpp))

