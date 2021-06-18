CC=g++ 
CFLAGS=-O2 -std=c++14 -g $(DEFINES)
INCFLAGS=-I./co2/include  -I./boost_1_72_0
SOURCES=sample_cor.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=sample_cor

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCFLAGS) -c $<

.PHONY: clean

clean:
	rm -f *.o $(EXECUTABLE)

