# turn object file into merge executable (linking stage)
# -g for debugging info
bacon: main.o
	g++ -o bacon main.o

# create object file from source (compilation stage)
main.o: main.cpp
	g++ -c main.cpp

# remove object file and executable
clean:
	rm *.o bacon