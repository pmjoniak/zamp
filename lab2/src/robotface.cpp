#include "robotface.hh"

RobotFace::RobotFace(PzG::LaczeDoGNUPlota& lacze) : lacze(lacze)
{
	eye_up[0] = 20;
	eye_up[1] = 20;

	eye_down[0] = 20;
	eye_down[1] = 20;

	eye_cx[0] = 10;
	eye_cx[1] = 50;
	eye_cy[0] = 30; 
	eye_cy[1] = 30; 
	
	mouth_cx = 30;
	mouth_cy = 0;
	mouth_down = 20;
	mouth_up = 20;
	mouth_side = 20;
}