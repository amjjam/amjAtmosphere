INSTALLDIR=~/lib/
FLAGS=-g -I

ATMOSPHERE_SRC=Atmosphere.C
ATMOSPHERE_OBJ=$(ATMOSPHERE_SRC:.C=.o)


install: libAtmosphere.a
	cp libAtmosphere.a $(INSTALLDIR)

uninstal:
	rm $(INSTALLDIR)/libAtmosphere.a

clean:
	rm $(ATMOSPHERE_OBJ)

libAtmosphere.a: $(ATMOSPHERE_OBJ)
	ar rc $@ $^
