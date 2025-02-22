bacon: main.o
	g++ -g -o bacon main.o -lcurl

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm *.o bacon