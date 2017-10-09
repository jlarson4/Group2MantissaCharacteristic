
CFLAGS		=	-std=c++11 -Wall

#typing make will by default build the consumer and producer executables
all: driver

#because both executables require CFLAGS and LIB, we put them in this way
driver:	main.cpp
	g++ $(CFLAGS) main.cpp -o driver


clean:	
	-rm -f driver