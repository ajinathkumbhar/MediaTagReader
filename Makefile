# This is makefile to build mediatagReader project

CC = gcc
CFLAG = -g -Wall -Werror -Iinclude

all: getMp3Info

getMp3Info: mp3ID3v2.o
	$(info building target : $@ ...)
	$(CC) $(CFLAG) mp3ID3v2.o -o bin/getMp3Info

mp3ID3v2.o: src/mp3ID3v2.cpp
	$(info building target : $@ ...)
	$(CC) $(CFLAG) -c src/mp3ID3v2.cpp

clean:
	$(info cleaning ...)
	rm -rf mp3ID3v2.o getMp3Info

