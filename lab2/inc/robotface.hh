#ifndef  ROBOTFACE_HH
#define  ROBOTFACE_HH

/*+- SVN Keywords ----------------------------------------------------+
 *|                                                                   |
 *| $HeadURL:                                                       $:|
 *|     $Rev::                                                      $:|
 *|    $Date::                                                      $:|
 *|  $Author::                                                      $:|
 *|                                                                   |
 *+-------------------------------------------------------------------+
 */

#include <iostream>
 #include "lacze_do_gnuplota.hh"

/*!
 * \file
 * \brief Definicja klasy RobotFace
 *
 * Plik zawiera definicję klasy RobotFace
 */

/*!
 * \brief Modeluje zestaw informacji określający ekspresję twarzy robota
 *
 *  Klasa modeluje ...
 */
struct RobotFace {
  // ...
	int oko_gora0 = 20;
	int oko_gora1 = 20; 
	int oko_dol0 = 10;
	int oko_dol1 = 10;
	int oko_cx0 = 10;
	int oko_cy0 = 30; 
	int oko_cx1 = 50;
	int oko_cy1 = 30;
	int usta_cx = 50;
	int usta_cy = 0;
	int usta_dol = 20;
	int usta_gora = 20;
	int usta_kacik = 20;

	RobotFace(PzG::LaczeDoGNUPlota& lacze)
	:lacze(lacze)
	{
		oko_gora0 = 20;
		oko_gora1 = 20; 
		oko_dol0 = 10;
		oko_dol1 = 10;
		oko_cx0 = 10;
		oko_cy0 = 30; 
		oko_cx1 = 50;
		oko_cy1 = 30;
		usta_cx = 30;
		usta_cy = 0;
		usta_dol = 20;
		usta_gora = 20;
		usta_kacik = 20;
	}

	PzG::LaczeDoGNUPlota& lacze;
};	




#endif
