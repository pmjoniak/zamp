#pragma once
#include "robotface.hh"
#include "lacze_do_gnuplota.hh"
#include "Wektor2D.hh"
#include <vector>
#include <iostream>
#include <mutex>
#include <thread>

class GnuplotRobotFace : public RobotFace
{
private:
  std::mutex draw_mutex;
  PzG::LaczeDoGNUPlota  lacze;

private:
	bool SaveMouth();
	bool SaveEyes(int id);
	bool SaveEyebrows(int id);
	bool SaveAll();

public:
	GnuplotRobotFace();

	void Init();

	void UpdateEyes(int id);
	void UpdateEyebrows(int id);
	void UpdateMouth();

	void Draw();

	bool SaveFile(const std::vector<Wektor2D>& points, std::ostream&  out, int cx, int cy);

} ;