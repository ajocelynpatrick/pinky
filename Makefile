# use conf-* for configuration
SHELL = /bin/sh

default: pinky

compile: \
Makefile warn-auto.sh conf-cc conf-wx
	( cat warn-auto.sh; \
	echo exec "`head -1 conf-cc`" '-c $${1+"$$@"} ' | tr '\n' ' '; \
	(`head -1 conf-wx` --cxxflags | tr '\n' ' ') \
	) > compile && echo >> compile
	chmod 755 compile

load: \
Makefile warn-auto.sh conf-ld conf-wx
	( cat warn-auto.sh; \
	echo 'main="$$1"; shift'; \
	echo exec "`head -1 conf-ld`" \
	'-o "$$main" "$$main".o $${1+"$$@"}'  | tr '\n' ' '; \
	(`head -1 conf-wx` --libs | tr '\n' ' ') \
	) > load && echo >> load
	chmod 755 load

install: \
Makefile pinky conf-home
	./cp ./pinky `head -1 conf-home`/bin &&
	chmod 755 `head -1 conf-home`/bin/pinky

conf-wx: \
Makefile 
	(which wx-config >conf-wx 2>&1) || \
	(cat WXCONFIG && exit 0)

clean: 
	rm -f *.o pinky pinky.exe load compile conf-wx

pinky: \
load pinky.o frame.o panel.o set.o board.o
	./load pinky frame.o panel.o set.o board.o

pinky.o: \
compile pinky.cpp frame.h pinky.h
	./compile pinky.cpp

frame.o: \
compile frame.cpp panel.h frame.h
	./compile frame.cpp

panel.o: \
compile panel.cpp panel.h frame.h set.h
	./compile panel.cpp

board.o: \
compile board.cpp board.h
	./compile board.cpp

set.o: \
compile set.h set.cpp
	./compile set.cpp
