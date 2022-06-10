hello: Helloworld.cpp
	g++ -std=c++11 -o hello Helloworld.cpp -lncursesw
	./hello

ex1: Example1.cpp
	g++ -std=c++11 -o ex1 Example1.cpp -lncursesw
	./ex1
	
ex2: Example2.cpp
	g++ -std=c++11 -o ex2 Example2.cpp -lncursesw
	./ex2

ex3: Example3.cpp
	g++ -std=c++11 -o ex3 Example3.cpp -lncursesw
	./ex3

ex4: Example4.cpp
	g++ -std=c++11 -o ex4 Example4.cpp -lncursesw
	./ex4

stg1: Stage1.cpp
	g++ -std=c++11 -o stg1 Stage1.cpp -lncursesw
	./stg1

stg2: Stage2.cpp
	g++ -std=c++11 -o stg2 Stage2.cpp -lncursesw
	./stg2

test: test.cpp
	g++ -std=c++11 -o test test.cpp -lncursesw
	./test