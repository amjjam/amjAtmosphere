libdir=$(prefix)/lib
ifndef randomprefix
	randomprefix=$(prefix)
endif
ifndef randominclude
	randominclude=$(randomprefix)/include
endif
ifndef randomlib
	randomlib=$(randomprefix)/lib
endif

CPPFLAGS=-Wall -g -fPIC -I $(randominclude)
CPP=g++

ATMOSPHERE_SRC=Atmosphere.C
ATMOSPHERE_OBJ=$(ATMOSPHERE_SRC:.C=.o)


build: libAtmosphere.a libAtmosphere.so

libAtmosphere.a: $(ATMOSPHERE_OBJ)
	ar rc $@ $^

libAtmosphere.so: $(ATMOSPHERE_OBJ)
	$(CPP) -shared -Wl,-soname,$@ -o $@ $^ -L $(randomlib) -lRandom

install: $(libdir)/libAtmosphere.a $(libdir)/libAtmosphere.so

$(libdir)/libAtmosphere.a $(libdir)/libAtmosphere.so: libAtmosphere.a libAtmosphere.so
	cp libAtmosphere.a libAtmosphere.so $(libdir)

uninstall:
	- rm -f $(libdir)/libAtmosphere.a $(libdir)/libAtmosphere.so

clean:
	- rm -f libAtmosphere.a libAtmosphere.so $(ATMOSPHERE_OBJ)
