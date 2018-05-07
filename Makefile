
MAIN = yoga-cli

CC = gcc
CPP = g++

CPPFLAGS += -Wall
CPPFLAGS += -g
CPPFLAGS += -std=gnu++17
CPPFLAGS += -fdiagnostics-color=auto
CPPFLAGS += -Iinclude/
LDFLAGS += -lpthread
LDFLAGS += -lusb-1.0

SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:.cpp=.o)
ELF = $(MAIN).elf


all: $(ELF)

run: $(ELF)
	./$(ELF)

$(ELF): $(OBJS)
	$(CPP) $^ $(CPPFLAGS) $(LDFLAGS) -o $@

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -c $^ -o $@

clean:
	rm -f $(OBJS) $(ELF)
