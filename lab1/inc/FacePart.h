#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "lacze_do_gnuplota.hh"
#include "Wektor2D.hh"


  /*!
   * \brief Klasa bazowa dla częsci twarzy
   *
   * zawiera podstawowe informacje wspolne dla wszystkich czesci twarzy
   */
class FacePart
{
protected:
	int cx, cy;
	PzG::LaczeDoGNUPlota&  lacze;
	std::string file;

public:
	     /*!
      * Inicjalizuje obiekt.
      *  \param lacze - referencja do obiektu lacza na ktorym bede sie dana czesc rysowac,
      *  \param file - nawa pliku przez który bedzie komunikowac sie z gnuplotem,
      *  \param cx - przesuniecie elementu w osi x.
      *  \param cy - przesuniecie elementu w osi y.
      */
	FacePart(PzG::LaczeDoGNUPlota&  lacze, std::string file, int cx, int cy);

protected:

	 /*!
      * zapisuje informacje o punktach do pliku.
      *  \param points - wektor punktów,
      *  \param out - strumien wyjsciowy
      *  \return - true - jesli wszytko sie powiedzie
      */
	bool saveFile(const std::vector<Wektor2D>& points, std::ostream&  out);

	 /*!
      * przesuwa punkty
      *  \param points - wektor punktów do przesuniecia,
      *  \param x - offset x
      *  \param y - offset y
      */
	void trnslate(std::vector<Wektor2D>& points, int x, int y);


};