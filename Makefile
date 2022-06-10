stg1: Stage1.cpp
	g++ -std=c++11 -o stg1 Stage1.cpp -lncursesw
	./stg1

stg2: Stage2.cpp
	g++ -std=c++11 -o stg2 Stage2.cpp -lncursesw
	./stg2

stg3: Stage3.cpp
	g++ -std=c++11 -o stg3 Stage3.cpp -lncursesw
	./stg3

stg4: Stage4.cpp
	g++ -std=c++11 -o stg4 Stage4.cpp -lncursesw
	./stg4

stg5: Stage5.cpp
	g++ -std=c++11 -o stg5 Stage5.cpp -lncursesw
	./stg5

test: test.cpp
	g++ -std=c++11 -o test test.cpp -lncursesw
	./test