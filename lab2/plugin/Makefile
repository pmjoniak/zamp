__start__: obj ../libs/libPolecenie_Oko.so \
	   ../libs/libPolecenie_Usta.so \
	   ../libs/libPolecenie_Pauza.so \
	   ../libs/libPolecenie_Brew.so
	@echo "  Tworzenie wtyczki zakonczone."
	@echo

obj:
	mkdir obj

CPPFLAGS=-Wall -fPIC -pedantic -Iinc -I../inc -std=c++11
LDFLAGS=-Wall -shared

../libs/libPolecenie_Brew.so: obj/command4eyebrow.o obj/lacze_do_gnuplota.o obj/Wektor2D.o
	g++ ${LDFLAGS} -o ../libs/libPolecenie_Brew.so obj/command4eyebrow.o obj/lacze_do_gnuplota.o obj/Wektor2D.o
	@echo
	@echo "  Wtyczka dla polecenia 'Brew' zostala utworzona."
	@echo

../libs/libPolecenie_Oko.so: obj/command4eye.o obj/lacze_do_gnuplota.o obj/Wektor2D.o
	g++ ${LDFLAGS} -o ../libs/libPolecenie_Oko.so obj/command4eye.o obj/lacze_do_gnuplota.o obj/Wektor2D.o
	@echo
	@echo "  Wtyczka dla polecenia 'Oko' zostala utworzona."
	@echo


../libs/libPolecenie_Usta.so: obj/command4mouth.o obj/lacze_do_gnuplota.o obj/Wektor2D.o
	g++ ${LDFLAGS} -o ../libs/libPolecenie_Usta.so obj/command4mouth.o obj/lacze_do_gnuplota.o obj/Wektor2D.o
	@echo
	@echo "  Wtyczka dla polecenia 'Usta' zostala utworzona."
	@echo

../libs/libPolecenie_Pauza.so: obj/command4pause.o
	g++ ${LDFLAGS} -o ../libs/libPolecenie_Pauza.so obj/command4pause.o
	@echo
	@echo "  Wtyczka dla polecenia 'Pauza' zostala utworzona."
	@echo

obj/command4eyebrow.o: src/command4eyebrow.cpp ../inc/command.hh ../inc/lacze_do_gnuplota.hh ../inc/Wektor2D.hh\
                        inc/command4eyebrow.hh 
	g++ -c ${CPPFLAGS} -o obj/command4eyebrow.o src/command4eyebrow.cpp

obj/command4eye.o: src/command4eye.cpp ../inc/command.hh ../inc/lacze_do_gnuplota.hh ../inc/Wektor2D.hh\
                        inc/command4eye.hh 
	g++ -c ${CPPFLAGS} -o obj/command4eye.o src/command4eye.cpp


obj/command4mouth.o: src/command4mouth.cpp ../inc/command.hh\
                        inc/command4mouth.hh 
	g++ -c ${CPPFLAGS} -o obj/command4mouth.o src/command4mouth.cpp

obj/command4pause.o: src/command4pause.cpp ../inc/command.hh\
                        inc/command4pause.hh 
	g++ -c ${CPPFLAGS} -o obj/command4pause.o src/command4pause.cpp

obj/lacze_do_gnuplota.o: ../src/lacze_do_gnuplota.cpp ../inc/lacze_do_gnuplota.hh
	g++ -c ${CPPFLAGS} -o obj/lacze_do_gnuplota.o ../src/lacze_do_gnuplota.cpp	

obj/Wektor2D.o: ../src/Wektor2D.cpp ../inc/Wektor2D.hh
	g++ -c ${CPPFLAGS} -o obj/Wektor2D.o ../src/Wektor2D.cpp
	


clean:
	rm -f obj/*

cleanall: clean
	find . -name \*~ -print -exec rm {} \;
