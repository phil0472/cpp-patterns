$(warning hello) parse: $(warning in prerequisite list)main.cpp
	g++ -std=c++17 main.cpp -o parse 

test:
	./parse test.cfg && echo "Test file:" && cat test.cfg	
