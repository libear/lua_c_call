#Makefile
CC=gcc
CFLAGS=-I/usr/local/lua/include/ -L/usr/local/lua/lib/ /usr/local/lib/liblua.a -llua -lm -ldl
LDFLAGS=

testlua: testlua.c
	$(CC) -o testlua $(LDFLAGS) md5.c testlua.c $(CFLAGS)
clean: testlua
	rm -f testlua
