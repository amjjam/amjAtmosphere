install:
	make -C include
	make -C src
clean: 
	make -C include clean
	make -C src clean
uninstall:
	make -C include uninstall
	make -C src uninstall
