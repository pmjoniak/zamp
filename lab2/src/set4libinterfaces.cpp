#include "set4libinterfaces.hh"

using namespace std;



/*!
 *
 */
Set4LibInterfaces::~Set4LibInterfaces()
{
  for(auto& lib : (*this))
    delete lib.second;
}



/*!
 * \brief Dodaje nowa biblioteke
 *
 * Dodaje nowa bibliotekę, która zawiera implementację nowego 
 * polecenia.
 * \param[in] sLibName - nazwa pliku z biblioteką, która ma zostać
 *                       załadowana i dodana do zbioru bibliotek zawierających
 *                       implementację poszczególnych poleceń.
 * \retval true - operacja powiodła się,
 * \retval false - w przypadku przeciwnym.
 */
bool Set4LibInterfaces::AddLib(const char*  sLibName)
{
  LibInterface   *pInterf4Copy = new LibInterface();

  if (!pInterf4Copy->Init4Lib(sLibName)) { delete pInterf4Copy;  return false; }

  insert(pair<string,LibInterface*>
			(pInterf4Copy->GetCmdName(),pInterf4Copy));

  return true;
}



bool Set4LibInterfaces::SubLib(const char*  sCmdName)
{
  auto  iter = map<string,LibInterface*>::find(sCmdName);

  if (iter == end()) return false;

  delete iter->second;
  this->erase(iter);
  return true;
}

/*!
 * Szuka obiektu pełniącego rolę interfejsu biblioteki, który 
 * odpowiada poleceniu o podanej nazwie np. Move.
 *
 * \param sCmdName - nazwa polecenia, dla którego szukany jest
 *                   interfejs do biblioteki zawierającej 
 *                   implementację danego polecenia.
 * \return Jeśli obiekt reprezentujący interfejs biblioteki 
 *         danego polecenia zostanie znaleziony, to zwracany
 *         jest jego adres. W przypadku przeciwnym zwracany
 *         jest adres \p NULL.
 */
const LibInterface* Set4LibInterfaces::FindLib4Cmd(const char*  sCmdName) const
{
  map<string,LibInterface*>::const_iterator  Iter = 
                                       map<string,LibInterface*>::find(sCmdName);

  if (Iter == end()) return NULL;
  return Iter->second;
}

