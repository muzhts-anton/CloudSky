CC = g++
CFLAGS=-c -Wall -g
LDFLAGS = -lpq

all: pq_connect_ex

pq_connect_ex: pq_connect_ex.o
	$(CC) pq_connect_ex.o $(LDFLAGS) -o pq_connect_ex -std=c++11
pq_connect_ex.o: pq_connect_ex.cpp
	$(CC) $(CFLAGS) pq_connect_ex.cpp -o pq_connect_ex.o
pq_connect_ex2: pq_connect_ex2.o
	$(CC) pq_connect_ex2.o $(LDFLAGS) -o pq_connect_ex2 -std=c++11
pq_connect_ex2.o: pq_connect_ex2.cpp
	$(CC) $(CFLAGS) pq_connect_ex2.cpp -o pq_connect_ex2.o
	$(CC) $(CFLAGS) pq_connect_ex.cpp -o pq_connect_ex.o
serverDB: serverDB.o
	$(CC) serverDB.o $(LDFLAGS) -o serverDB -std=c++11
serverDB.o: serverDB.cpp
	$(CC) $(CFLAGS) serverDB.cpp -o serverDB.o
clean:
	rm -f *.o pq_connect_ex pq_connect_ex2 serverDB