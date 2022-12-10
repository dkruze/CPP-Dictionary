dictionary: dictionary.o
	g++ dictionary.cpp -o dictionary

dictionary.o: dictionary.cpp dictionaryHash.h
	g++ - c dictionary.cpp

clean:
	rm *.o
	rm dictionary

run:
	./dictionary