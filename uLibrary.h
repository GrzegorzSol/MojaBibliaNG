/*
Biblioteka wspólnych metod dla wszystkich klas i modułów aplikacji. Główną klasą jest klasa Library całkowicie publiczna i statyczna.
Klasa ta jednak nie jest i nie bedzie jedynie wykorzystana do budowy aplikacji Moja Biblia NG, lecz będzie w przyszłości wykorzystywana
do innych projektów. Z tego powodu jej wszystkie funkcje i metody, musza być konstruowane jako uniwersalne.
*/
//---------------------------------------------------------------------------

#ifndef uLibraryH
#define uLibraryH

#include <wtypes.h>
//---------------------------------------------------------------------------
struct Library
{
	static TCHAR *GetInfo(TCHAR *InfoItem=const_cast<TCHAR *>(TEXT("FileVersion")));
};

//---------------------------------------------------------------------------
#endif
