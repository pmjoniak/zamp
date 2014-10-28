#pragma once
#include "FacePart.h"

/*!
* \brief Klasa Usta 
*
* trzyma parametry ust i odpowiada za ich animacje
*/

class Usta : public FacePart
{
private:
	int up, down, side;

public:
	/*!
      * Inicjalizuje obiekt.
      *  \param lacze - referencja do obiektu lacza na ktorym bede sie dana czesc rysowac,
      *  \param file - nawa pliku przez który bedzie komunikowac sie z gnuplotem,
      *  \param cx - przesuniecie elementu w osi x.
      *  \param cy - przesuniecie elementu w osi y.
      */
	Usta(PzG::LaczeDoGNUPlota&  lacze, std::string file, int cx, int cy);

	/*!
      * Animuje obiekt.
      *  \param new_up - docelowe polozenie gornej wargi,
      *  \param new_down - docelowe polozenie dolnej wargi,
      *  \param new_side - docelowe polozenie kącików,
      *  \param v - predkosc zmian.
      */
	void animate(int new_up, int new_down, int new_side, int v);

	/*!
      * Inicjalizuje obiekt
      *  \param up - polozenie gornej wargi,
      *  \param down - polozenie dolnej wargi,
      *  \param side - polozenie kącików,
      */
	void init(int up, int down, int side);

	/*!
      * zapisuje aktualny stan ust.
      *  \return - true - jesli wszytko sie powiedzie
      */
	bool save();

	/*!
      * zapisuje konretny stan ust.
      *  \param up - polozenie gornej wargi,
      *  \param down - polozenie dolnej wargi,
      *  \param side - polozenie kącików,
      *  \return - true - jesli wszytko sie powiedzie
      */
	bool save(int up, int down, int side);

};