__start__: obj interp __plugin__
	export LD_LIBRARY_PATH="./libs"; ./interp

obj:
	mkdir obj

__plugin__:
	cd plugin; make

CPPFLAGS=-Wall -pedantic -Iinc -std=c++11 -L.local/lib -lreadline -lpthread
LDFLAGS=-Wall -lreadline -lpthread

interp: obj/main.o obj/robotface.o plugin/obj/Wektor2D.o plugin/obj/lacze_do_gnuplota.o obj/set4libinterfaces.o obj/libinterface.o obj/GnuplotRobotFace.o obj/xmlparser4robotface.o
	g++ ${LDFLAGS} -o interp  obj/main.o plugin/obj/Wektor2D.o plugin/obj/lacze_do_gnuplota.o obj/robotface.o obj/set4libinterfaces.o obj/libinterface.o obj/GnuplotRobotFace.o obj/xmlparser4robotface.o -ldl -lxerces-c

obj/main.o: src/main.cpp inc/command.hh inc/Wektor2D.hh
	g++ -c ${CPPFLAGS} -o obj/main.o src/main.cpp

obj/GnuplotRobotFace.o: src/GnuplotRobotFace.cpp inc/GnuplotRobotFace.hh
	g++ -c ${CPPFLAGS} -o obj/GnuplotRobotFace.o src/GnuplotRobotFace.cpp

obj/robotface.o: src/robotface.cpp inc/robotface.hh
	g++ -c ${CPPFLAGS} -o obj/robotface.o src/robotface.cpp

obj/set4libinterfaces.o: src/set4libinterfaces.cpp inc/set4libinterfaces.hh
	g++ -c ${CPPFLAGS} -o obj/set4libinterfaces.o src/set4libinterfaces.cpp		

obj/libinterface.o: src/libinterface.cpp inc/libinterface.hh inc/command.hh
	g++ -c ${CPPFLAGS} -o obj/libinterface.o src/libinterface.cpp

obj/xmlparser4robotface.o: src/xmlparser4robotface.cpp inc/xmlparser4robotface.hh
	g++ -c ${CPPFLAGS} -o obj/xmlparser4robotface.o src/xmlparser4robotface.cpp

clean:
	rm -f obj/* interp

cleanall: clean
	cd plugin; make cleanall
	rm -f libs/*
	find . -name \*~ -print -exec rm {} \;