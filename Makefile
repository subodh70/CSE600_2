test : 
# Question 1
	g++ -c 1.cpp
	g++ -g -o debug1 1.o
	g++ -O3 -o optimize1 1.o

	./debug1


# Question 2
	g++ -c 2.cpp
	g++ -g -o debug2 2.o
	g++ -O3 -o optimize2 2.o

	./debug2

# Question 3
	g++ -c 3.cpp
	g++ -g -o debug3 3.o
	g++ -O3 -o optimize3 3.o

	./debug3