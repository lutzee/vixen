#################################################
# Makefile for 370ct                            #
#################################################

CC = g++
CFLAGS = -g -Wall -std=c++11
LLIBS =  -lm -lSDL2
EXE = vixen

OBJS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))

#----------
vixen: $(OBJS)
	$(CC) $(LLIBS) $(OBJS) -o $(EXE)

#----------

$(OBJS): %.o : %.cpp
	$(CC) $(CFLAGS) -c $<

#----------

clean:
	rm -f *.o *.*~ *~  $(EXE)

#----------


