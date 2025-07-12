#ifndef InitMBAppConstH
#define InitMBAppConstH
//---------------------------------------------------------------------------
#include <System.hpp>
#include "uGlobalVar.h"
/*
	Zasady nazewnictwa zmiennych globalnych dla aplikacji.
	App - Aplikacja
	C - Constans
	Fun - Funkcja
	Table - Tablica
	Ustr - UnicodeString
	Lpsz - Long pointer string
	WCh - Wide Char
	L - Long
	I - int
	W - Word
	Ch - Char
	F - Float
	D - Double
	_Typ tablicy, lub nazwa przeznaczenia funkcji lub zmiennej
*/
// --------------------------------- Funkcje --------------------------------
extern __fastcall UnicodeString AppFun_GetStringAddressVers(const UnicodeString &custrTextAddress);

// -------------------------------- Struktury -------------------------------
/*============================================================================
 =													STRUKTURA InfoAllBooks													 =
 ============================================================================*/
typedef struct _InfoAllBooks
				{
					const unsigned char ucIndex;					//Numer księgi
					const UnicodeString FullNameBook;			//Pełna nazwa księgi
					const UnicodeString ShortNameBook;	 //Skrót księgi
					const unsigned char ucCountChapt;			//Ilość rozdziałów
					_InfoAllBooks(unsigned char _ucIndex, UnicodeString _FullNameBook, UnicodeString _ShortNameBook, unsigned char _ucCountChapt) : ucIndex(_ucIndex),
						FullNameBook(_FullNameBook), ShortNameBook(_ShortNameBook), ucCountChapt(_ucCountChapt)
					/**
						OPIS METOD(FUNKCJI): Konstruktor klasy _InfoAllBooks
						OPIS ARGUMENTÓW:
						OPIS ZMIENNYCH:
						OPIS WYNIKU METODY(FUNKCJI):
					*/
					{

					};
				} InfoAllBooks, *PInfoAllBooks;

// --------------------------------- Zmienne --------------------------------
// Tablica struktur InfoAllBooks, z parametrami ksiąg biblijnych
extern const InfoAllBooks AppCTable_InfoAllBooks[GlobalVar::Global_NumberBooks];

//---------------------------------------------------------------------------
#endif
