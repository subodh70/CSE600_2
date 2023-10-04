test : 
# Question 1
	g++ -c 1.cpp
	g++ -g -o debug1 1.o
	g++ -O3 -o optimize1 1.o

	./debug1