#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include "lacze_do_gnuplota.hh"
#include "Usta.hh"
#include "Oko.hh"
#include <memory>

  /*!
   * \brief Klasa wykonująca program z pliku 
   *
   * trzyma wszystkie elementy twarzy i lacze.
   */
class ProgramExecutor
{

private:
	PzG::LaczeDoGNUPlota  lacze;
	std::vector<std::shared_ptr<Oko>> oka;
	std::shared_ptr<Usta> usta;

public:

	/*!
      * Inicjalizuje obiekt.
      */
	ProgramExecutor();

	/*!
      * Niszczy obiekt.
      */
	virtual ~ProgramExecutor();


	/*!
      * Inicjalizuje obiekt. Tworzy wykres i elementy twarzy
      */
	void init();



	/*!
      * Przetwarza plik przez preprocesor
      *  \param file_name - nazwa pliku,
      *  \param istringstream - wynik dzialania preprocesora 
      *  \return - true - jesli wszytko sie powiedzie
      */
	bool execPreprocesor(const char* file_name, std::istringstream &iSStream);

	/*!
      * Animuje Oko.
      *  \param i_stream - strumien z poleceniami,
      *  \return - true - jesli wszytko sie powiedzie
      */
	bool Animuj_Oko(std::istringstream& i_stream);

	/*!
      * Animuje Usta.
      *  \param i_stream - strumien z poleceniami,
      *  \return - true - jesli wszytko sie powiedzie
      */
	bool Animuj_Usta(std::istringstream& i_stream);

	/*!
      * Animuje Pauze.
      *  \param i_stream - strumien z poleceniami,
      *  \return - true - jesli wszytko sie powiedzie
      */
	bool Animuj_Pauza(std::istringstream& i_stream);


	/*!
      * Rozpoczyna wykonywanie poleceń ze strumienia
      *  \param i_stream - strumien z poleceniami,
      *  \return - true - jesli wszytko sie powiedzie
      */
	bool execute(std::istringstream& i_stream);

	/*!
      * Rozpoczyna wykonywanie poleceń z pliku
      *  \param file_name -nazwa pliku,
      *  \return - true - jesli wszytko sie powiedzie
      */
	bool execute(std::string file_name);
};
