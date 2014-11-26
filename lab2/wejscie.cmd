/*
* Zakładamy, ˙ze startujemy od neutralnego wygl ˛adu twarzy.
*/

#define SZYB_ZMIAN_DLA_USMIECHU 300
#define TRANZYCJA_OKA_USMIECH 20, 80, SZYB_ZMIAN_DLA_USMIECHU

Pauza 300000;

/*
* Przejscie do fazy usmiechu
*/

Oko 0, TRANZYCJA_OKA_USMIECH;
Oko 1, TRANZYCJA_OKA_USMIECH;
Pauza 300000;
Usta -60, -40, 30, SZYB_ZMIAN_DLA_USMIECHU;

Pauza 3000000;
/*
* Przez 1s utrzymujemy ekspresj˛e twarzy niezmienion ˛a.
*/

//zdenerwowanie
START_PARALLEL
Oko 0, -20, -20, 300;
Oko 1, -20, -20, 300;
END_PARALLEL
START_PARALLEL
Brew 0, 5, 50, 300;
Brew 1, 5, -50, 300;
END_PARALLEL

Usta 25, 30, 30, 300;


Pauza 1000000;

//zdenerwowanie
START_PARALLEL
Oko 0, -30, 30, 300;
Oko 1, -30, 30, 300;
Usta -40, 20, 0, 300;
Brew 0, 5, 0, 300;
Brew 1, 5, 0, 300;
END_PARALLEL


Pauza 1000000;

