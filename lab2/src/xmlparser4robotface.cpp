#include <xercesc/util/PlatformUtils.hpp>
#include "xmlparser4robotface.hh"
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

#ifndef XMLSize_t
# define XMLSize_t unsigned int
#endif


using namespace std;



/*!
 * Konstruktor klasy. Tutaj należy zainicjalizować wszystkie
 * dodatkowe pola.
 * (Ten opis należy odpowiednio uzupełnić)
 */
XMLParser4RobotFace::XMLParser4RobotFace(RobotFace * robot_face)
{
  this->robot_face = robot_face;
}


/*!
 * Metoda wywoływana jest bezpośrednio przed rozpoczęciem
 * przetwarzana dokumentu XML.
 */
void XMLParser4RobotFace::startDocument()
{
  //cout << "*** Rozpoczecie przetwarzania dokumentu XML." << endl;
}


/*!
 * Metoda wywoływana jest bezpośrednio po zakończeniu
 * przetwarzana dokumentu XML.
 */
void XMLParser4RobotFace::endDocument()
{
  //cout << "=== Koniec przetwarzania dokumentu XML." << endl;
}



float XMLParser4RobotFace::getAttrValue(const   xercesc::Attributes&     attrs)
{
  char* atrr_name = xercesc::XMLString::transcode(attrs.getQName(1));
  if(strcmp(atrr_name, "Value")){
    cerr << "Zla nazwa atrybutu";
  }
  char* attr_value = xercesc::XMLString::transcode(attrs.getValue(static_cast<XMLSize_t>(1)));
  string s = string(attr_value);
  return std::stof(s);
}

  std::string XMLParser4RobotFace::getName(const   xercesc::Attributes&     attrs)
  {
    char* atrr_name = xercesc::XMLString::transcode(attrs.getQName(0));
    if(strcmp(atrr_name, "Name")){
      cerr << "Zla nazwa atrybutu";
    }
    char* attr_value = xercesc::XMLString::transcode(attrs.getValue(attrs.getQName(0)));
    string s = string(attr_value);
    return s;
  }

  void XMLParser4RobotFace::Twarz(const   xercesc::Attributes&     attrs)
  {
    std::string name = getName(attrs);
    float value = getAttrValue(attrs);
    //cout << name << " " << value << "\n";
    if(name == "Szerokosc")
      robot_face->width = value;
    else if(name == "Wysokosc")
      robot_face->height = value;
  }

  void XMLParser4RobotFace::Oko(const   xercesc::Attributes&     attrs)
  {
    std::string name = getName(attrs);
    float value = getAttrValue(attrs);
    //cout << name << " " << value << "\n";
    if(name == "Wspolrzedna_x")
      robot_face->eye_cx[eye_id] = value;
    else if(name == "Wspolrzedna_y")
      robot_face->eye_cy[eye_id] = value;
    else if(name == "Id")
      eye_id = (int)value - 1;
  }


  void XMLParser4RobotFace::Brew(const   xercesc::Attributes&     attrs)
  {
    std::string name = getName(attrs);
    float value = getAttrValue(attrs);
    //cout << object_name << " " << name << " " << value << "\n";
    if(name == "Wspolrzedna_x")
      robot_face->eyebrow_cx[eyebrow_id] = value;
    else if(name == "Wspolrzedna_y")
      robot_face->eyebrow_cy[eyebrow_id] = value;
    else if(name == "Id")
      eyebrow_id = (int)value - 1;
  }

  void XMLParser4RobotFace::Usta(const   xercesc::Attributes&     attrs)
  {
    std::string name = getName(attrs);
    float value = getAttrValue(attrs);
    //cout << name << " " << value << "\n";
    if(name == "Wspolrzedna_x")
      robot_face->mouth_cx = value;
    else if(name == "Wspolrzedna_y")
      robot_face->mouth_cy = value;
  }


/*!
 * Wykonuje operacje związane z wystąpieniem danego elementu XML.
 * W przypadku elementu \p "Action" będzie to utworzenie obiektu
 * reprezentującego odpowiednią działanie robota.
 * W przypadku elementu \p "Parameter" będzie to zapisanie parametrów
 * związanych z danym działaniem.
 * \param[in] ElemName -
 * \param[in] Attrs - (\b we,) atrybuty napotkanego elementu XML.
 */
void XMLParser4RobotFace::WhenStartElement( const std::string       &ElemName,
		                      const xercesc::Attributes   &Attrs
                                    )
{
  if(ElemName == "Object")
  {
      this->object_name = getName(Attrs);
  }
  if(ElemName == "Parameter")
  {
    if(object_name == "Twarz")
      Twarz(Attrs);
    else if(object_name == "Oko")
      Oko(Attrs);
    else if(object_name == "Usta")
      Usta(Attrs);
    else if(object_name == "Brew")
      Brew(Attrs);    
  }
}




/*!
 * Metoda jest wywoływana po napotkaniu nowego elementu XML, np.
 * gdy zostanie napotkany element:
   \verbatim
     <Action Name="Rotate">
   \endverbatim
 *  to poprzez parametr \e xscElemName jest dostęp do nazwy elementu
 *  tzn. \p Action, 
 *  \param[in] pLocalName -  umożliwia dostęp do nazwy elementu XML.
 *                 W podanym przykładzie nazwą elementu XML jest "Action".
 *  \param[in] Attrs -  lista atrybutów danego symbolu XML.
 *                 W przykładzie pokazanym powyżej listę atrybutów
 *                 będą stanowiły napisy:
 */
/*
 * Te metode nalezy odpowiednio zdekomponowac!!!
 */
void XMLParser4RobotFace::startElement(  const   XMLCh* const    pURI,
                                       const   XMLCh* const    pLocalName,
                                       const   XMLCh* const    pQNname,
				       const   xercesc::Attributes&     Attrs
                                    )
{
  char* sElemName = xercesc::XMLString::transcode(pLocalName);
  //cout << "+++ Poczatek elementu: "<< sElemName << endl;

  WhenStartElement(sElemName, Attrs);

  xercesc::XMLString::release(&sElemName);
}




/*!
 * Metoda zostaje wywołana w momencie zakończenia danego elementu
 * XML, np. jeżeli w pliku jest wpis:
   \verbatim
     <Action Name="Rotate">
     </Action>
   \endverbatim
 * to metoda ta zostanie wywołana po napotkaniu znacznika
 * \p </Action>. Jeżeli element XML ma formę skróconą, tzn.
   \verbatim
     <Parametr Name="Rotate"/>
   \endverbatim
 * to wówczas wywołana metoda wywołana zostanie w momencie
 * napotkania sekwencji "/>"
 *  \param[in] pLocalName -  umożliwia dostęp do nazwy elementu XML.
 *                 W podanym przykładzie nazwą elementu XML jest "Action".
 */
void XMLParser4RobotFace::endElement(  const   XMLCh* const    pURI,
                                     const   XMLCh* const    pLocalName,
                                     const   XMLCh* const    pQName
                                  )
{
   char* sElemName = xercesc::XMLString::transcode(pLocalName);
   //cout << "--- Koniec elementu: "<< sElemName << endl;

   WhenEndElement(sElemName);

   xercesc::XMLString::release(&sElemName);
}



/*!
 * Wykonuje końcowe operacje związane z danym elementem XML. 
 * W przypadku \p "Action" jest to dodanie utworzonego wcześniej
 * obiektu do listy poleceń robota.
 * Metoda wywoływana jest w momencie napotkania znacznika końca
 * danego elementu XML.
 * \param[in] ElemName -  nazwa elementu XML
 */
void XMLParser4RobotFace::WhenEndElement(const std::string& ElemName)
{
  //cout << "       ---> Tu na koniec moge wykonac jakies dzialanie (o ile jest potrzebne)"
  //     << endl << endl;
}



/*!
 * Metoda wywoływana jest, gdy napotkany zostanie błąd fatalny,
 * np.
  \verbatim
    <Action Name="Rotate">
    </Parametr>
  \endverbatim
 */
void XMLParser4RobotFace::fatalError(const xercesc::SAXParseException&  Exception)
{
   char* sMessage = xercesc::XMLString::transcode(Exception.getMessage());
   char* sSystemId = xercesc::XMLString::transcode(Exception.getSystemId());

   cerr << "Blad fatalny! " << endl
        << "    Plik:  " << sSystemId << endl
        << "   Linia: " << Exception.getLineNumber() << endl
        << " Kolumna: " << Exception.getColumnNumber() << endl
        << " Informacja: " << sMessage 
        << endl;

   xercesc::XMLString::release(&sMessage);
   xercesc::XMLString::release(&sSystemId);
}

/*!
 * Metoda jest wywoływana, gdy napotkany zostanie błąd, który nie
 * jest traktowany jako fatalny. W ten sposób traktowane są błędy
 * występujące w opisie gramatyki dokumentu.
 * \param[in] Except - zawiera informacje dotyczące błędu. Informacje
 *                     te to opis błędu oraz numer linii, w której
 *                     wystąpił błąd.
 */
void XMLParser4RobotFace::error(const xercesc::SAXParseException&  Exception)
{
  cerr << "Blad ..." << endl;

  /*
   * Tutaj należy wstawić odpowiedni kod. Tekst wyświetlany powyżej
   * jest tylko "atrapą".
   */
}


/*!
 *
 */
void XMLParser4RobotFace::warning(const xercesc::SAXParseException&  Exception)  
{
  cerr << "Ostrzezenie ..." << endl;

  /*
   * Tutaj należy wstawić odpowiedni kod. Tekst wyświetlany powyżej
   * jest tylko "atrapą".
   */
}
