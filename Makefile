CC = gcc
CFLAGS = -g -Wall -std=gnu99 `pkg-config --cflags gtk+-2.0`
LDFLAGS = `pkg-config --libs gtk+-2.0`

PROGRAMS = client server

default: $(PROGRAMS)

server: server.o common.o util.o

client: client.o common.o util.o window.o dialog_connect_server.o

clean:
	rm -rf $(PROGRAMS) *.o

Makefile: Makefile.dep
Makefile.dep: *.c *.h
	$(CC) -MM *.c > $@

-include Makefile.dep

