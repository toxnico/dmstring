build:
	g++ -std=c++11 -c dmstring.cpp -o dmlib.o

test:
	g++ -std=c++11 -g -DCATCH_CONFIG_MAIN dmstring.cpp -o dmlibtest.out
	./dmlibtest.out
