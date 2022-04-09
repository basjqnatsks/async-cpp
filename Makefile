all:
	g++ main.cpp -o o -pthread -L/usr/lib/x86_64-linux-gnu/libcurl.so.4 -pthread -lcurl
