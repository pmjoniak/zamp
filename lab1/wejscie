/*
* Zakładamy, ˙ze startujemy od neutralnego wygl ˛adu twarzy.
*/

#define SZYB_ZMIAN_DLA_USMIECHU 300
#define TRANZYCJA_OKA_USMIECH 20, 80, SZYB_ZMIAN_DLA_USMIECHU

Pauza 3000000;

/*
* Przejscie do fazy usmiechu
*/

Oko 0, TRANZYCJA_OKA_USMIECH;
Pauza 3000000;
Oko 1, TRANZYCJA_OKA_USMIECH;
Pauza 3000000;
Usta -60, -40, 30, SZYB_ZMIAN_DLA_USMIECHU;

Pauza 3000000;
/*
* Przez 1s utrzymujemy ekspresj˛e twarzy niezmienion ˛a.
*/


Pauza 1000000;


/*
* Puszczenie "oczka"
*/


Oko 1, 30, 30, 300; // Zmru˙zenie oka
Pauza 3000000;
Oko 1, TRANZYCJA_OKA_USMIECH; // Powrót do stanu poprzedniego
Pauza 3000000;
Pauza 1000000;