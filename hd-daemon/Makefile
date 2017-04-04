CC=g++

EXEC = hd-daemon

LINK = -D_BSD_SOURCE -O3

SRC = hd-daemon.cpp config-master.cpp config-slave.cpp ip.cpp

all: $(EXEC) 

$(EXEC): $(SRC)
	$(CC) -o $(EXEC) $(SRC) $(LINK)

clean:
	rm -rf $(EXEC) 

run:
	./hd-daemon startmaster 2 192.168.47.10 192.168.47.21
