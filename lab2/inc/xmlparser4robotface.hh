#ifndef XMLParser4RobotFace_HH
#define XMLParser4RobotFace_HH


#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/sax/Locator.hpp>

#include <xercesc/sax2/Attributes.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>

//XERCES_CPP_NAMESPACE_USE
#include <string>
#include "robotface.hh"

/*!
 * \brief Implementuje reakcje na napotkane elementu opisu akcji
 *
 * Klasa zawiera zestaw metod, które wywoływane są w trakcie czytania i analizy
 * pliku XML.
 */
class XMLParser4RobotFace : public xercesc::DefaultHandler {
private:
  std::string object_name = "";  
  int eye_id = -1;
  int eyebrow_id = -1;

  float getAttrValue(const   xercesc::Attributes&     attrs);
  std::string getName(const   xercesc::Attributes&     attrs);
  void Twarz(const   xercesc::Attributes&     attrs);
  void Oko(const   xercesc::Attributes&     attrs);
  void Usta(const   xercesc::Attributes&     attrs);
  void Brew(const   xercesc::Attributes&     attrs);







  public:
   /*!
    * \brief Inicjalizuje obiekt i kojarzy go ze sceną
    */
  XMLParser4RobotFace(RobotFace *robot_face);

   /*!
    * \brief Wywoływana jest na początku dokumentu
    */
    virtual void startDocument();
   /*!
    * \brief Wywoływana jest na końcu dokumentu
    */
    virtual void endDocument();

   /*!
    * \brief Wywoływana jest po napotkaniu nowego elementu XML
    */
    virtual void startElement(
                    const XMLCh *const pURI, 
                    const XMLCh *const pLocalName, 
                    const XMLCh *const pQNname,
                    const   xercesc::Attributes&     attrs
                  );

   /*!
    * \brief Wywoływana jest po dojściu do końca elementu XML
    */
    virtual  void endElement(
                    const XMLCh *const pURI, 
                    const XMLCh *const pLocalName, 
                    const XMLCh *const pQNname
                   );
   /*!
    * \brief Wywoływana jest gdy napotkany zostanie błąd fatalny
    */
    void fatalError(const xercesc::SAXParseException&);

   /*!
    * \brief Wywoływana jest gdy napotkany zostanie błąd
    */
    void error(const xercesc::SAXParseException &exc);

   /*!
    * \brief Wywoływana jest gdy parser sygnalizuje ostrzeżenie
    */
    void warning(const xercesc::SAXParseException &exc);

    /*!
     * \brief Wykonuje końcowe operacje związane z danym elementem XML
     */
    void WhenEndElement(const std::string& ElemName);

    /*!
     * \brief Wykonuje operacje związane z danym elementem XML
     */
    void WhenStartElement( const std::string&             ElemName,
		           const xercesc::Attributes&     Attrs
                         );
  private:
  /*!
   *  \brief Zawiera wskaźnik do modyfikowanej sceny
   *
   *  Zawiera wskaźnik na obiekt, do którego mają zostać wpisane
   *  informacje z wczytywanego pliku.
   */
    RobotFace* robot_face;
};

#endif
