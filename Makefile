olleh: olleh.o
	g++ olleh.o -o olleh

olleh.o: olleh.cpp
	g++ -c olleh.cpp

clean:
	rm *.o olleh