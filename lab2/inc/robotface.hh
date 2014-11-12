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
	int eye_up[2] = {20,20};
	int eye_down[2] = {20, 20}; 
	int eye_cx[2] = {10, 50};
	int eye_cy[2] = {30, 30}; 

	int mouth_cx = 50;
	int mouth_cy = 0;
	int mouth_down = 20;
	int mouth_up = 20;
	int mouth_side = 20;

	int eyebrow_angle[2] = {20,20};
	int eyebrow_pos[2] = {20, 20}; 
	int eyebrow_cx[2] = {10, 50};
	int eyebrow_cy[2] = {30, 30}; 
	RobotFace();

	virtual void Update() = 0;
};	




#endif
