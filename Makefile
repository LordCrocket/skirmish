OUTPUT := build
SRC := src

OBJECTS := main.o graphics.o gamestate.o controller.o keyboard.o serverproxy.o sound.o
CC := gcc
CFLAGS  := -Wall -std=c11 -D_GNU_SOURCE=1 -D_REENTRANT
LDLIBS := -lcsfml-window -lcsfml-graphics -lcsfml-audio -lcsfml-system -lm
LDFLAGS :=



all: main


main: $(OBJECTS) 

main.o: action.h graphics.h gamestate.h controller.h sound.h
controller.o: action.h graphics.h gamestate.h controller.h serverproxy.h sound.h
gamestate.o: gamestate.h
graphics.o: graphics.h gamestate.h
keyboard.o: keyboard.h
serverproxy.o: action.h gamestate.h serverproxy.h
sound.o: sound.h

.PHONY : clean main all

clean:
	-rm *.o

