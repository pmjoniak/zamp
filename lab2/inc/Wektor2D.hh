#ifndef WEKTOR2D_HH
#define WEKTOR2D_HH

#include <iostream>

/*!
 * \brief Wektor w przestrzeni 2D
 *
 * Klasa modeluje wektor w dwuwymiarowej
 * przestrzeni kartezjańskiej.
 */
class Wektor2D {
   public:
   /*!
    * \brief Współrzędna x-owa
    *
    * Przechowuje wartość współrzędnej x-owej.
    */
    double  x;
   /*!
    * \brief Współrzędna y-owa
    *
    * Przechowuje wartość współrzędnej y-owej.
    */
    double  y;

   /*!
    * \brief Inicjalizuje obiekt wartościomi zerowymi
    *
    *  Inicjalizuje pola reprezntujące współrzędne
    *  wektora wartością 0.
    */
    Wektor2D(): x(), y() {}
   /*!
    * \brief Inicjalizuje obiekt zadanymi wartościomi
    *
    *  Inicjalizuje pola reprezntujące współrzędne
    *  wektora wartościami przekazanymi przez parametry
    *  wowołania konstruktora.
    *  \param[in] x - zawiera wartość wykorzystaną do zainicjalizowania
    *                 pola przechowującego wartość współrzędnej x-owej.
    *  \param[in] y - zawiera wartość wykorzystaną do zainicjalizowania
    *                 pola przechowującego wartość współrzędnej y-owej.
    */
    Wektor2D( double x, double y ): x(x), y(y) {}
};


/*!
 * \brief Wpisuje dwie współrzędne wektora
 */
std::ostream& operator << (std::ostream &StrmWy, const Wektor2D &Wek );

#endif
