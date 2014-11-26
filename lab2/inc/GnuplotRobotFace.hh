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
	/*!
    * \brief Zapisuje parametry ust do pliku
    */   
	bool SaveMouth();
	/*!
    * \brief Zapisuje parametry oka do pliku
    */   	
	bool SaveEyes(int id);
	/*!
    * \brief Zapisuje parametry brwi do pliku
    */   	
	bool SaveEyebrows(int id);
	/*!
    * \brief Zapisuje cala twarz
    */   	
	bool SaveAll();

public:
	GnuplotRobotFace();

	/*!
    * \brief Inicjalizuje lacze do gnuplota
    */   
	void Init();

	/*!
    * \brief Zapisuje parametry oka do pliku i odrysowuje twarz.
    */    
	void UpdateEyes(int id);
	/*!
    * \brief Zapisuje parametry brwi do pliku i odrysowuje twarz.
    */   
	void UpdateEyebrows(int id);
  	/*!
    * \brief Zapisuje parametry ust do pliku i odrysowuje twarz.
    */   	
	void UpdateMouth();

  	/*!
    * \brief Odrysowuje twarz.
    */   
	void Draw();

  	/*!
    * \brief Zapisuje wektor punktow do pliku.
    */  
	bool SaveFile(const std::vector<Wektor2D>& points, std::ostream&  out, int cx, int cy);

} ;