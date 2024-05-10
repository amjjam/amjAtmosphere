ifndef prefix
	prefix=/opt/amj
endif


FLAGS=-Wall -g -fPIC -I $(randominclude)
CPPFLAGS=$(FLAGS)
CPP=g++

AMJATMOSPHERE_SRC=amjAtmosphere.C
AMJATMOSPHERE_OBJ=$(AMJATMOSPHERE_SRC:.C=.o)

all: libamjAtmosphere.so

libamjAtmosphere.so: $(AMJATMOSPHERE_OBJ)
	$(CPP) -shared -Wl,-soname,$@ -o $@ $^

install: libamjAtmosphere.so ../include/amjAtmosphere.H
	mkdir -p $(prefix)/lib
	mkdir -p $(prefix)/include
	cp libamjAtmosphere.so $(prefix)/lib
	cp ../include/amjAtmosphere.H $(prefix)/include

uninstall:
	- rm $(prefix)/lib/libamjAtmosphere.so
	- rm $(prefix)/include/amjAtmosphere.H
	- rmdir $(prefix)/lib
	- rmdir $(prefix)/include

clean:
	- rm libamjAtmosphere.so $(AMJATMOSPHERE.OBJ)
