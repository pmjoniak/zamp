#pragma once
#include "FacePart.h"

  /*!
   * \brief Klasa oka 
   *
   * trzyma parametry oka i odpowiada za jego animacje
   */
class Oko : public FacePart
{
private:
	int up, down;

public:
		     /*!
      * Inicjalizuje obiekt.
      *  \param lacze - referencja do obiektu lacza na ktorym bede sie dana czesc rysowac,
      *  \param file - nawa pliku przez który bedzie komunikowac sie z gnuplotem,
      *  \param cx - przesuniecie elementu w osi x.
      *  \param cy - przesuniecie elementu w osi y.
      */
	Oko(PzG::LaczeDoGNUPlota&  lacze, std::string file, int cx, int cy);

	/*!
      * Animuje obiekt.
      *  \param new_up - docelowe polozenie gornej powieki,
      *  \param new_down - docelowe polozenie dolnej powieki,
      *  \param v - predkosc zmian.
      */
	void animate(int new_up, int new_down, int v);

	/*!
      * Inicjalizuje obiekt
      *  \param up - polozenie gornej powieki,
      *  \param down - polozenie dolnej powieki,
      */
	void init(int up, int down);

	/*!
      * zapisuje aktualny stan oka.
      *  \return - true - jesli wszytko sie powiedzie
      */
	bool save();

	/*!
      * zapisuje konretny stan oka.
      *  \param up - polozenie gornej powieki,
      *  \param down - polozenie dolnej powieki,
      *  \return - true - jesli wszytko sie powiedzie
      */
	bool save(int up, int down);
};