/*
	Całkowicie publiczna i statyczna klasa globalnych zmiennych, dostępnych wszystkim modułom
*/
//---------------------------------------------------------------------------
#pragma hdrstop

#include "uGlobalVar.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//----- Wersje plików i bibliotek
UnicodeString	GlobalVar::Global_ustrVerGsReadBibleTextClass = "", //Wersja biblioteki GsReadBibleTextClass
							GlobalVar::Global_ustrVerAplicMain = "", //Wersja głównej biblioteki
							//--- Ustawienia parametrów połączenia z siecią, w celu akyualizacji
							GlobalVar::Global_custrLocalVersionFile = "", //Ścieżka dostępu lokalna, do pobranego pliku wersji
							GlobalVar::Global_custrLocalApplicFile = ""; //Ścieżka dostępu lokalna, do pobranej aplikacji
const unsigned char GlobalVar::cuchABlendValue = 200; //Współczynnik przezroczystości okna, gdy jest nieaktywne

