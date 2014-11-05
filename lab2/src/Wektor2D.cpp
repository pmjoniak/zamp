#include <iostream>
#include "Wektor2D.hh"

using namespace std;

/*!
 * \brief Wpisuje dwie współrzędne wektora
 *
 *  Wpisuje do strumienia wyjściowego dwie współrzędne
 *  wektora. tzn x oraz y (w tej kolejności). Wartości 
 *  współrzędnych rozdzielone są spacją. Przykładowa forma zapisu 
 *  wektora o współrzędnych (20,30):
    \verbatim
      20 30
    \verbatimend
 *  \param[in,out] StrmWy - strumień, do którego mają zostać wpisane
 *                       współrzędne wektora.
 *  \param[in] Wek - wektor, którego współrzędne mają być zapisane do 
 *                   strumienia.
 *  \return Zostaje zwrócna referencja do strumienia reprezentowanego
 *          przez parametr StrmWy.
 */
ostream& operator << (ostream& StrmWy, const Wektor2D & Wek )
{
  return  StrmWy << Wek.x << " " << Wek.y;
}
