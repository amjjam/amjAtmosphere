LIBDIR=~/lib
INCLUDEDIR=~/include

FLAGS=-g -I $(INCLUDEDIR) -L $(LIBDIR)
CPPFLAGS=$(FLAGS)
CPP=g++ $(FLAGS)

TESTATMOSPHERE_SRC=testAtmosphere.C ../../src/Atmosphere.C
TESTATMOSPHERE_OBJ=$(TESTATMOSPHERE_SRC:.C=.o)

all: testAtmosphere

testAtmosphere: $(TESTATMOSPHERE_OBJ)
	$(CPP) -o $@ $^ -lrandom -lz -lamjMemory
