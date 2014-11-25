#include "robotface.hh"

RobotFace::RobotFace()
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
	mouth_cy = -30;
	mouth_down = -60;
	mouth_up = -40;
	mouth_side = 20;

	eyebrow_angle[0] = -20;
	eyebrow_angle[1] = 20;

	eyebrow_pos[0] = 20;
	eyebrow_pos[1] = 20;

	eyebrow_cx[0] = 10;
	eyebrow_cx[1] = 50;
	eyebrow_cy[0] = 100; 
	eyebrow_cy[1] = 100; 
}