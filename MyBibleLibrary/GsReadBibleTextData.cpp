#pragma hdrstop

#include "MyBibleLibrary.h"
#include "GsReadBibleTextdata.h"
#include <System.IOUtils.hpp>
#include <System.StrUtils.hpp>
#include "MyBibleCoreDataImages.h" //Dane dla grafiki (Pojedyńcch obrazów i list obrazów)
/****************************************************************************
 *							Całkowicie statyczna KLASA GsReadBibleTextData							*
 ****************************************************************************/
void __fastcall GsReadBibleTextData::GsInitGlobalImageList(TForm *pMainForm)	//Inicjalizacja zmiennych klasy
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW: TForm *pMainForm - Wskaźnik na główne okno
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(!pMainForm) throw(Exception("Błąd wyłuskania objektu głównego oka aplikacji"));
	//---
	GsReadBibleTextData::_GsImgListData = new TImageList(pMainForm);	//Inicjalizacja objektu klasy TImageList, z określeniem
																																 //wymierów przyszłych obrazków na 16x16 pikseli w wersji nieaktywnej
	if(! GsReadBibleTextData::_GsImgListData) throw(Exception("Błąd otwarcia objektu TImageList"));
	GsReadBibleTextData::_GsImgListData->ColorDepth = cd32Bit;		 //Głębia kolorów przyszłych obrazków
	GsReadBibleTextData::_GsImgListData->DrawingStyle = dsTransparent;
	//---
	GsReadBibleTextData::_GsImgListDataDisable = new TImageList(pMainForm);	 //Inicjalizacja objektu klasy TImageList, z określeniem
																																				//wymierów przyszłych obrazków na 16x16 pikseli w wersji nieaktywnej
	if(!GsReadBibleTextData::_GsImgListDataDisable) throw(Exception("Błąd otwarcia objektu TImageLists"));
	GsReadBibleTextData::_GsImgListDataDisable->ColorDepth = cd32Bit;			//Głębia kolorów przyszłych obrazków
	GsReadBibleTextData::_GsImgListDataDisable->DrawingStyle = dsTransparent;
	//---
	TIcon *pIcon=nullptr;
	TMemoryStream *pMemoryStr=nullptr;
	try
	{
		pIcon = new TIcon();
		if(!pIcon) throw(Exception("Błąd metody TIcon"));
		pMemoryStr = new TMemoryStream();
		if(!pMemoryStr) throw(Exception("Błąd metody TMemoryStream"));
		//***************************************** WERSJA IKON AKTYWNYCH *****************************************
		//--- 0.Ikona korzenia drzewiastej struktury Bibli
		pMemoryStr->WriteBuffer(ID_ROOT_BOOKS, ARRAYSIZE(ID_ROOT_BOOKS)); //Zapis do strumienia danych
		pMemoryStr->Position = 0;																					//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);																//Wczytanie danych ze strumienia do objektu, klasy TIcon
		GsReadBibleTextData::_GsImgListData->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 1.Ikona części bibli
		pMemoryStr->WriteBuffer(ID_PART_BOOKS, ARRAYSIZE(ID_PART_BOOKS)); //Zapis do strumienia danych
		pMemoryStr->Position = 0;																					//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);																//Wczytanie danych ze strumienia do objektu, klasy TIcon
		GsReadBibleTextData::_GsImgListData->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 2.Ikona pojedyńczej księgi
		pMemoryStr->WriteBuffer(ID_BOOK, ARRAYSIZE(ID_BOOK));							//Zapis do strumienia danych
		pMemoryStr->Position = 0;																					//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);																//Wczytanie danych ze strumienia do objektu, klasy TIcon
		GsReadBibleTextData::_GsImgListData->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 3.Ikona pojedyńczego rozdziału
		pMemoryStr->WriteBuffer(ID_CHAPTER, ARRAYSIZE(ID_CHAPTER));							//Zapis do strumienia danych
		pMemoryStr->Position = 0;																					//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);																//Wczytanie danych ze strumienia do objektu, klasy TIcon
		GsReadBibleTextData::_GsImgListData->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 4.Ikona następnej księgi
		pMemoryStr->WriteBuffer(ID_TONEXT_BOOK, ARRAYSIZE(ID_TONEXT_BOOK));							//Zapis do strumienia danych
		pMemoryStr->Position = 0;																					//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);																//Wczytanie danych ze strumienia do objektu, klasy TIcon
		GsReadBibleTextData::_GsImgListData->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 5.Ikona następnego rozdziału
		pMemoryStr->WriteBuffer(ID_NEXTCHAPTER, ARRAYSIZE(ID_NEXTCHAPTER));							//Zapis do strumienia danych
		pMemoryStr->Position = 0;																					//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);																//Wczytanie danych ze strumienia do objektu, klasy TIcon
		GsReadBibleTextData::_GsImgListData->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 6.Ikona poprzedniego rozdziału
		pMemoryStr->WriteBuffer(ID_PREVCHAPTER, ARRAYSIZE(ID_PREVCHAPTER));							//Zapis do strumienia danych
		pMemoryStr->Position = 0;																					//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);																//Wczytanie danych ze strumienia do objektu, klasy TIcon
		GsReadBibleTextData::_GsImgListData->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 7.Ikona poprzedniej księgi
		pMemoryStr->WriteBuffer(ID_TOPREV_BOOK, ARRAYSIZE(ID_TOPREV_BOOK));							//Zapis do strumienia danych
		pMemoryStr->Position = 0;																					//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);																//Wczytanie danych ze strumienia do objektu, klasy TIcon
		GsReadBibleTextData::_GsImgListData->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 8.Ikona wyświetlenia wybranego werseu
		pMemoryStr->WriteBuffer(ID_DISPLAYVERS, ARRAYSIZE(ID_DISPLAYVERS));							//Zapis do strumienia danych
		pMemoryStr->Position = 0;																					//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);																//Wczytanie danych ze strumienia do objektu, klasy TIcon
		GsReadBibleTextData::_GsImgListData->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 9.Ikona wyświetlenia wyboru tłumaczeń
		pMemoryStr->WriteBuffer(ID_TRANSLATES, ARRAYSIZE(ID_TRANSLATES));							//Zapis do strumienia danych
		pMemoryStr->Position = 0;																					//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);																//Wczytanie danych ze strumienia do objektu, klasy TIcon
		GsReadBibleTextData::_GsImgListData->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 10.Ikona wyboru wiersza
		pMemoryStr->WriteBuffer(ID_SELECTVERS, ARRAYSIZE(ID_SELECTVERS));							//Zapis do strumienia danych
		pMemoryStr->Position = 0;																					//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);																//Wczytanie danych ze strumienia do objektu, klasy TIcon
		GsReadBibleTextData::_GsImgListData->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 11.Ikona informacji i pomocy
		pMemoryStr->WriteBuffer(ID_INFOHELP, ARRAYSIZE(ID_INFOHELP));							//Zapis do strumienia danych
		pMemoryStr->Position = 0;																					//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);																//Wczytanie danych ze strumienia do objektu, klasy TIcon
		GsReadBibleTextData::_GsImgListData->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 12.Przeniesienie wybranego tekstu nazakładkę
		pMemoryStr->WriteBuffer(ID_COPYTOSHEET, ARRAYSIZE(ID_COPYTOSHEET));							//Zapis do strumienia danych
		pMemoryStr->Position = 0;																					//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);																//Wczytanie danych ze strumienia do objektu, klasy TIcon
		GsReadBibleTextData::_GsImgListData->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 13.Ikona kolumny greckich słów
		pMemoryStr->WriteBuffer(ID_GRECWORD_COLUMN, ARRAYSIZE(ID_GRECWORD_COLUMN));							//Zapis do strumienia danych
		pMemoryStr->Position = 0;																					//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);																//Wczytanie danych ze strumienia do objektu, klasy TIcon
		GsReadBibleTextData::_GsImgListData->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 14.Ikona kolumny greckich słów stronga
		pMemoryStr->WriteBuffer(ID_GRECSTRONG_COLUMN, ARRAYSIZE(ID_GRECSTRONG_COLUMN));							//Zapis do strumienia danych
		pMemoryStr->Position = 0;																					//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);																//Wczytanie danych ze strumienia do objektu, klasy TIcon
		GsReadBibleTextData::_GsImgListData->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 15.Ikona kolumny greckich słów tłumaczenia
		pMemoryStr->WriteBuffer(ID_GRECDICTIONARY_COLUMN, ARRAYSIZE(ID_GRECDICTIONARY_COLUMN));							//Zapis do strumienia danych
		pMemoryStr->Position = 0;																					//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);																//Wczytanie danych ze strumienia do objektu, klasy TIcon
		GsReadBibleTextData::_GsImgListData->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 16.Ikona kolumny greckich pozycja
		pMemoryStr->WriteBuffer(ID_GRECWORDITEM_COLUMN, ARRAYSIZE(ID_GRECWORDITEM_COLUMN));							//Zapis do strumienia danych
		pMemoryStr->Position = 0;																					//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);																//Wczytanie danych ze strumienia do objektu, klasy TIcon
		GsReadBibleTextData::_GsImgListData->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 17.Ikona przełącznika ulubionego wersetu
		pMemoryStr->WriteBuffer(ID_SELECTFAV_VERSET, ARRAYSIZE(ID_SELECTFAV_VERSET));							//Zapis do strumienia danych
		pMemoryStr->Position = 0;																					//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);																//Wczytanie danych ze strumienia do objektu, klasy TIcon
		GsReadBibleTextData::_GsImgListData->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 18.Ikona zapisywania
		pMemoryStr->WriteBuffer(ID_SAVEICON, ARRAYSIZE(ID_SAVEICON));							//Zapis do strumienia danych
		pMemoryStr->Position = 0;																					//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);																//Wczytanie danych ze strumienia do objektu, klasy TIcon
		GsReadBibleTextData::_GsImgListData->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 19.Ikona usuwania
		pMemoryStr->WriteBuffer(ID_DELETEICON, ARRAYSIZE(ID_DELETEICON));							//Zapis do strumienia danych
		pMemoryStr->Position = 0;																					//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);																//Wczytanie danych ze strumienia do objektu, klasy TIcon
		GsReadBibleTextData::_GsImgListData->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 20.Ikona do selekcji textu
		pMemoryStr->WriteBuffer(ID_VIEWSELECTTEXT, ARRAYSIZE(ID_VIEWSELECTTEXT));							//Zapis do strumienia danych
		pMemoryStr->Position = 0;																					//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);																//Wczytanie danych ze strumienia do objektu, klasy TIcon
		GsReadBibleTextData::_GsImgListData->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 21.Ikona do wyłącznie czytania teksty
		pMemoryStr->WriteBuffer(ID_VIEWONLYREADTEXT, ARRAYSIZE(ID_VIEWONLYREADTEXT));							//Zapis do strumienia danych
		pMemoryStr->Position = 0;																					//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);																//Wczytanie danych ze strumienia do objektu, klasy TIcon
		GsReadBibleTextData::_GsImgListData->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 22.Ikona do rozpoczęcia edycji
		pMemoryStr->WriteBuffer(ID_EDITTEXT, ARRAYSIZE(ID_EDITTEXT));							//Zapis do strumienia danych
		pMemoryStr->Position = 0;																					//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);																//Wczytanie danych ze strumienia do objektu, klasy TIcon
		GsReadBibleTextData::_GsImgListData->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 23.Ikona do wyświetlania informacji o przekładach
		pMemoryStr->WriteBuffer(ID_INFOSTRANSLATES, ARRAYSIZE(ID_INFOSTRANSLATES));							//Zapis do strumienia danych
		pMemoryStr->Position = 0;																					//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);																//Wczytanie danych ze strumienia do objektu, klasy TIcon
		GsReadBibleTextData::_GsImgListData->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//************************************** WERSJA IKON NIEAKTYWNYCH **************************************
		//--- 0.Ikona korzenia drzewiastej struktury Bibli
		pMemoryStr->WriteBuffer(ID_ROOT_BOOKS_DIS, ARRAYSIZE(ID_ROOT_BOOKS_DIS)); //Zapis do strumienia danych
		pMemoryStr->Position = 0;																					//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);																//Wczytanie danych ze strumienia do objektu, klasy TIcon
		GsReadBibleTextData::_GsImgListDataDisable->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 1.Ikona części bibli
		pMemoryStr->WriteBuffer(ID_PART_BOOKS_DIS, ARRAYSIZE(ID_PART_BOOKS_DIS)); //Zapis do strumienia danych
		pMemoryStr->Position = 0;																					//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);																//Wczytanie danych ze strumienia do objektu, klasy TIcon
		GsReadBibleTextData::_GsImgListDataDisable->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 2.Ikona pojedyńczej księgi
		pMemoryStr->WriteBuffer(ID_BOOK_DIS, ARRAYSIZE(ID_BOOK_DIS));							//Zapis do strumienia danych
		pMemoryStr->Position = 0;																					//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);																//Wczytanie danych ze strumienia do objektu, klasy TIcon
		GsReadBibleTextData::_GsImgListDataDisable->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 3.Ikona pojedyńczego rozdziału
		pMemoryStr->WriteBuffer(ID_CHAPTER_DIS, ARRAYSIZE(ID_CHAPTER_DIS));							//Zapis do strumienia danych
		pMemoryStr->Position = 0;																					//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);																//Wczytanie danych ze strumienia do objektu, klasy TIcon
		GsReadBibleTextData::_GsImgListDataDisable->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 4.Ikona następnej księgi
		pMemoryStr->WriteBuffer(ID_TONEXT_BOOK_DIS, ARRAYSIZE(ID_TONEXT_BOOK_DIS));							//Zapis do strumienia danych
		pMemoryStr->Position = 0;																					//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);																//Wczytanie danych ze strumienia do objektu, klasy TIcon
		GsReadBibleTextData::_GsImgListDataDisable->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 5.Ikona następnego rozdziału
		pMemoryStr->WriteBuffer(ID_NEXTCHAPTER_DIS, ARRAYSIZE(ID_NEXTCHAPTER_DIS));							//Zapis do strumienia danych
		pMemoryStr->Position = 0;																					//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);																//Wczytanie danych ze strumienia do objektu, klasy TIcon
		GsReadBibleTextData::_GsImgListDataDisable->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 6.Ikona poprzedniego rozdziału
		pMemoryStr->WriteBuffer(ID_PREVCHAPTER_DIS, ARRAYSIZE(ID_PREVCHAPTER_DIS));							//Zapis do strumienia danych
		pMemoryStr->Position = 0;																					//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);																//Wczytanie danych ze strumienia do objektu, klasy TIcon
		GsReadBibleTextData::_GsImgListDataDisable->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 7.Ikona poprzedniej księgi
		pMemoryStr->WriteBuffer(ID_TOPREV_BOOK_DIS, ARRAYSIZE(ID_TOPREV_BOOK_DIS));							//Zapis do strumienia danych
		pMemoryStr->Position = 0;																					//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);																//Wczytanie danych ze strumienia do objektu, klasy TIcon
		GsReadBibleTextData::_GsImgListDataDisable->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 8.Ikona wyświetlenia wybranego werseu
		pMemoryStr->WriteBuffer(ID_DISPLAYVERS_DIS, ARRAYSIZE(ID_DISPLAYVERS_DIS));							//Zapis do strumienia danych
		pMemoryStr->Position = 0;																					//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);																//Wczytanie danych ze strumienia do objektu, klasy TIcon
		GsReadBibleTextData::_GsImgListDataDisable->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 9.Ikona wyświetlenia wyboru tłumaczeń
		pMemoryStr->WriteBuffer(ID_TRANSLATES_DIS, ARRAYSIZE(ID_TRANSLATES_DIS));							//Zapis do strumienia danych
		pMemoryStr->Position = 0;																					//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);																//Wczytanie danych ze strumienia do objektu, klasy TIcon
		GsReadBibleTextData::_GsImgListDataDisable->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 10.Ikona wyboru wiersza
		pMemoryStr->WriteBuffer(ID_SELECTVERS_DIS, ARRAYSIZE(ID_SELECTVERS_DIS));							//Zapis do strumienia danych
		pMemoryStr->Position = 0;																					//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);																//Wczytanie danych ze strumienia do objektu, klasy TIcon
		GsReadBibleTextData::_GsImgListDataDisable->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 11.Ikona informacji i pomocy
		pMemoryStr->WriteBuffer(ID_INFOHELP_DIS, ARRAYSIZE(ID_INFOHELP_DIS));							//Zapis do strumienia danych
		pMemoryStr->Position = 0;																					//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);																//Wczytanie danych ze strumienia do objektu, klasy TIcon
		GsReadBibleTextData::_GsImgListDataDisable->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 12.Przeniesienie wybranego tekstu nazakładkę
		pMemoryStr->WriteBuffer(ID_COPYTOSHEET_DIS, ARRAYSIZE(ID_COPYTOSHEET_DIS));							//Zapis do strumienia danych
		pMemoryStr->Position = 0;																					//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);																//Wczytanie danych ze strumienia do objektu, klasy TIcon
		GsReadBibleTextData::_GsImgListDataDisable->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 13.Ikona kolumny greckich słów
		pMemoryStr->WriteBuffer(ID_GRECWORD_COLUMN_DIS, ARRAYSIZE(ID_GRECWORD_COLUMN_DIS));							//Zapis do strumienia danych
		pMemoryStr->Position = 0;																					//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);																//Wczytanie danych ze strumienia do objektu, klasy TIcon
		GsReadBibleTextData::_GsImgListDataDisable->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 14.Ikona kolumny greckich słów stronga
		pMemoryStr->WriteBuffer(ID_GRECSTRONG_COLUMN_DIS, ARRAYSIZE(ID_GRECSTRONG_COLUMN_DIS));							//Zapis do strumienia danych
		pMemoryStr->Position = 0;																					//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);																//Wczytanie danych ze strumienia do objektu, klasy TIcon
		GsReadBibleTextData::_GsImgListDataDisable->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 15.Ikona kolumny greckich słów tłumaczenia
		pMemoryStr->WriteBuffer(ID_GRECDICTIONARY_COLUMN_DIS, ARRAYSIZE(ID_GRECDICTIONARY_COLUMN_DIS));							//Zapis do strumienia danych
		pMemoryStr->Position = 0;																					//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);																//Wczytanie danych ze strumienia do objektu, klasy TIcon
		GsReadBibleTextData::_GsImgListDataDisable->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 16.Ikona kolumny greckich pozycja
		pMemoryStr->WriteBuffer(ID_GRECWORDITEM_COLUMN_DIS, ARRAYSIZE(ID_GRECWORDITEM_COLUMN_DIS));							//Zapis do strumienia danych
		pMemoryStr->Position = 0;																					//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);																//Wczytanie danych ze strumienia do objektu, klasy TIcon
		GsReadBibleTextData::_GsImgListDataDisable->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 17.Ikona przełącznika ulubionego wersetu
		pMemoryStr->WriteBuffer(ID_SELECTFAV_VERSET_DIS, ARRAYSIZE(ID_SELECTFAV_VERSET_DIS));							//Zapis do strumienia danych
		pMemoryStr->Position = 0;																					//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);																//Wczytanie danych ze strumienia do objektu, klasy TIcon
		GsReadBibleTextData::_GsImgListDataDisable->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 18.Ikona zapisywania
		pMemoryStr->WriteBuffer(ID_SAVEICON_DIS, ARRAYSIZE(ID_SAVEICON_DIS));							//Zapis do strumienia danych
		pMemoryStr->Position = 0;																					//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);																//Wczytanie danych ze strumienia do objektu, klasy TIcon
		GsReadBibleTextData::_GsImgListDataDisable->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 19.Ikona usuwania
		pMemoryStr->WriteBuffer(ID_DELETEICON_DIS, ARRAYSIZE(ID_DELETEICON_DIS));							//Zapis do strumienia danych
		pMemoryStr->Position = 0;																					//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);																//Wczytanie danych ze strumienia do objektu, klasy TIcon
		GsReadBibleTextData::_GsImgListDataDisable->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 20.Ikona do selekcji textu
		pMemoryStr->WriteBuffer(ID_VIEWSELECTTEXT_DIS, ARRAYSIZE(ID_VIEWSELECTTEXT_DIS));							//Zapis do strumienia danych
		pMemoryStr->Position = 0;																					//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);																//Wczytanie danych ze strumienia do objektu, klasy TIcon
		GsReadBibleTextData::_GsImgListDataDisable->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 21.Ikona do wyłącznie czytania teksty
		pMemoryStr->WriteBuffer(ID_VIEWONLYREADTEXT_DIS, ARRAYSIZE(ID_VIEWONLYREADTEXT_DIS));							//Zapis do strumienia danych
		pMemoryStr->Position = 0;																					//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);																//Wczytanie danych ze strumienia do objektu, klasy TIcon
		GsReadBibleTextData::_GsImgListDataDisable->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 22.Ikona do rozpoczęcia edycji
		pMemoryStr->WriteBuffer(ID_EDITTEXT_DIS, ARRAYSIZE(ID_EDITTEXT_DIS));							//Zapis do strumienia danych
		pMemoryStr->Position = 0;																					//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);																//Wczytanie danych ze strumienia do objektu, klasy TIcon
		GsReadBibleTextData::_GsImgListDataDisable->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 23.Ikona do wyświetlania informacji o przekładach
		pMemoryStr->WriteBuffer(ID_INFOSTRANSLATES_DIS, ARRAYSIZE(ID_INFOSTRANSLATES_DIS));							//Zapis do strumienia danych
		pMemoryStr->Position = 0;																					//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);																//Wczytanie danych ze strumienia do objektu, klasy TIcon
		GsReadBibleTextData::_GsImgListDataDisable->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
	}
	__finally
	{
		//--- Zwolnienie objektu, klasy TIcon i TMemoryStream
		if(pIcon) {delete pIcon; pIcon = nullptr;}
		if(pMemoryStr) {delete pMemoryStr; pMemoryStr = nullptr;}
	}
}
//---------------------------------------------------------------------------
void __fastcall GsReadBibleTextData::GsFreeGlobalImageList()	//Likwidacja zmiennych klasy
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	///
}
//---------------------------------------------------------------------------
UnicodeString __fastcall GsReadBibleTextData::GetVersionMainClass()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(!GsReadBibleTextData::pGsReadBibleTextClass) throw(Exception("Nie dokonano inicjalizacji objektu GsReadBibleTextClass"));
	//---
	GlobalVar::Global_ustrVerGsReadBibleTextClass = GsReadBibleTextData::pGsReadBibleTextClass->GetVersionClass();
	return GlobalVar::Global_ustrVerGsReadBibleTextClass;
}
//---------------------------------------------------------------------------
void __fastcall GsReadBibleTextData::InitMyBible(TForm *MainWindow)
/**
	OPIS METOD(FUNKCJI): Inicjalizacja pracy z biblioteką do analizy Pisma Świętego
	OPIS ARGUMENTÓW: TForm *MainWindow - Wskaźnik na główne okno
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	GsReadBibleTextData::InitListColors(); //Inicjalizacja listy kolorów
	GsReadBibleTextData::InitHistoryList(); //Metoda inicjuje zmienne dotyczące historii [30-07-2023]
	GsReadBibleTextData::SetupVariables(); //Ustawienie zmiennych dla klasy
	//---
	if(GsReadBibleTextData::pGsReadBibleTextClass) throw(Exception("Objekt GsReadBibleTextClass jest już zainicjowany"));
	if(GlobalVar::Global_custrGetDataDir.IsEmpty()) throw(Exception("Brak ścieżki dostępu do katalogu z tekstami biblijnymi"));
	//---
	GlobalVar::Global_HSListAllFavoritiesVers = new THashedStringList(); //String lista do wszystkich ulubionych wesrsetów
	if(!GlobalVar::Global_HSListAllFavoritiesVers) throw(Exception("Błąd inicjalizacji objektu THashedStringList"));
	if(TFile::Exists(GlobalVar::Global_custrPathFileFavoriteVers))
		{GlobalVar::Global_HSListAllFavoritiesVers->LoadFromFile(GlobalVar::Global_custrPathFileFavoriteVers, TEncoding::UTF8);} //Wczytanie listy ulubionych wersetów
	else {GlobalVar::Global_HSListAllFavoritiesVers->SaveToFile(GlobalVar::Global_custrPathFileFavoriteVers, TEncoding::UTF8);}
	//---
	GsReadBibleTextData::GsInitGlobalImageList(MainWindow);	 //Inicjalizacja listy ikon
	GsReadBibleTextClass *_pGsReadBibleTextClass = new GsReadBibleTextClass(GlobalVar::Global_custrGetDataDir);
	if(!_pGsReadBibleTextClass) throw(Exception("Błąd inicjalizacji objektu GsReadBibleTextClass"));

	GsReadBibleTextData::pGsReadBibleTextClass = _pGsReadBibleTextClass;
	GsReadBibleTextData::GetVersionMainClass(); //Wersja biblioteki GsReadBibleTextClass
	//---
	TComponent *Component=nullptr;
	for(int i=0; i<MainWindow->ComponentCount; ++i)
	{
		Component = MainWindow->Components[i];
		if(Component && Component->ClassNameIs("TTaskbar")) break;
		Component = nullptr;
	}
	//GsReadBibleTextData::_GsTaskBar = pTaskBar;	//Wskaźnik na objekt, klasy TTaskBar
	if(Component) GsReadBibleTextData::_GsTaskBar = dynamic_cast<TTaskbar *>(Component); //23.12.2018
	else throw(Exception("Brak komponentu klasy TTaskbar"));
	//parametr inicjalizacji biblioteki
	GsReadBibleTextData::IsInitLibrary = true; //Czy została zainicjowana bibliteka (moduł)
}
//---------------------------------------------------------------------------
void __fastcall GsReadBibleTextData::InitListColors()
/**
	OPIS METOD(FUNKCJI): Inicjalizacja listy kolorów
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	GlobalVar::Global_ItemsColor = new TStringList(); //Inicjalizacja listy kolorów do wyboru
	if(!GlobalVar::Global_ItemsColor) throw(Exception("Błąd inicjalizacji objektu TStringList"));

	GlobalVar::Global_ItemsColor->AddObject("clWebWheat", reinterpret_cast<TObject*>(clWebWheat));
	GlobalVar::Global_ItemsColor->AddObject("clWebBurlywood", reinterpret_cast<TObject*>(clWebBurlywood));
	GlobalVar::Global_ItemsColor->AddObject("clWebLinen", reinterpret_cast<TObject*>(clWebLinen));
	GlobalVar::Global_ItemsColor->AddObject("clWebLemonChiffon", reinterpret_cast<TObject*>(clWebLemonChiffon));
	GlobalVar::Global_ItemsColor->AddObject("clWebDarkOrange", reinterpret_cast<TObject*>(clWebDarkOrange));
	GlobalVar::Global_ItemsColor->AddObject("clWebDarkRed", reinterpret_cast<TObject*>(clWebDarkRed));
	GlobalVar::Global_ItemsColor->AddObject("clWebCoral", reinterpret_cast<TObject*>(clWebCoral));
	GlobalVar::Global_ItemsColor->AddObject("clWebGold", reinterpret_cast<TObject*>(clWebGold));
	GlobalVar::Global_ItemsColor->AddObject("clWebRosyBrown", reinterpret_cast<TObject*>(clWebRosyBrown));
	GlobalVar::Global_ItemsColor->AddObject("clWebForestGreen", reinterpret_cast<TObject*>(clWebForestGreen));
	GlobalVar::Global_ItemsColor->AddObject("clWebChartreuse", reinterpret_cast<TObject*>(clWebChartreuse));
	GlobalVar::Global_ItemsColor->AddObject("clWebSeaGreen", reinterpret_cast<TObject*>(clWebSeaGreen));
	GlobalVar::Global_ItemsColor->AddObject("clWebMediumAquamarine", reinterpret_cast<TObject*>(clWebMediumAquamarine));
	GlobalVar::Global_ItemsColor->AddObject("clWebLightCyan", reinterpret_cast<TObject*>(clWebLightCyan));
	GlobalVar::Global_ItemsColor->AddObject("clWebCornFlowerBlue", reinterpret_cast<TObject*>(clWebCornFlowerBlue));
	GlobalVar::Global_ItemsColor->AddObject("clWebIndigo", reinterpret_cast<TObject*>(clWebIndigo));
	GlobalVar::Global_ItemsColor->AddObject("clWebRed", reinterpret_cast<TObject*>(clWebRed));
	GlobalVar::Global_ItemsColor->AddObject("clWebLightSkyBlue", reinterpret_cast<TObject*>(clWebLightSkyBlue));
	GlobalVar::Global_ItemsColor->AddObject("clWebDarkBlue", reinterpret_cast<TObject*>(clWebDarkBlue));
	GlobalVar::Global_ItemsColor->AddObject("clWebCyan", reinterpret_cast<TObject*>(clWebCyan));
	GlobalVar::Global_ItemsColor->AddObject("clWebDarkTurquoise", reinterpret_cast<TObject*>(clWebDarkTurquoise));
	GlobalVar::Global_ItemsColor->AddObject("clWebMediumVioletRed", reinterpret_cast<TObject*>(clWebMediumVioletRed));
	GlobalVar::Global_ItemsColor->AddObject("clWebAqua", reinterpret_cast<TObject*>(clWebAqua));
	GlobalVar::Global_ItemsColor->AddObject("clWebRoyalBlue", reinterpret_cast<TObject*>(clWebRoyalBlue));
	GlobalVar::Global_ItemsColor->AddObject("clWebMidnightBlue", reinterpret_cast<TObject*>(clWebMidnightBlue));
	GlobalVar::Global_ItemsColor->AddObject("clWebDarkViolet", reinterpret_cast<TObject*>(clWebDarkViolet));
	GlobalVar::Global_ItemsColor->AddObject("clWebDarkMagenta", reinterpret_cast<TObject*>(clWebDarkMagenta));
	GlobalVar::Global_ItemsColor->AddObject("clWebDeepPink", reinterpret_cast<TObject*>(clWebDeepPink));
	GlobalVar::Global_ItemsColor->AddObject("clWebMediumSlateBlue", reinterpret_cast<TObject*>(clWebMediumSlateBlue));
	GlobalVar::Global_ItemsColor->AddObject("clWebSteelBlue", reinterpret_cast<TObject*>(clWebSteelBlue));
	GlobalVar::Global_ItemsColor->AddObject("clWebSlateBlue", reinterpret_cast<TObject*>(clWebSlateBlue));
	GlobalVar::Global_ItemsColor->AddObject("clWebDarkSlategray", reinterpret_cast<TObject*>(clWebDarkSlategray));
}
//---------------------------------------------------------------------------
void __fastcall GsReadBibleTextData::SetupVariables()
/**
	OPIS METOD(FUNKCJI): Ustawienie zmiennych dla klasy
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	int //Kolory
			iColorFavVers = GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_ColorsSection_Main, GlobalVar::GlobalIni_ColorFavoritesVers, clYellow),
			iColorCommentVers = GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_ColorsSection_Main, GlobalVar::GlobalIni_ColorCommentVers, clLime),
			iColorBackgroundText = GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_ColorsSection_Main, GlobalVar::GlobalIni_ColorBackgroundText, clSkyBlue),
			iColorNameFullTranslate = GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_ColorsSection_Main, GlobalVar::GlobalIni_ColorNameFullTranslates, clFuchsia),
			iColorAdressFullTranslates = GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_ColorsSection_Main, GlobalVar::GlobalIni_ColorAdressVersFullTranslates, clRed),
			iColorBackgroundMarkComment = GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_ColorsSection_Main, GlobalVar::GlobalIni_ColorBackgroundMarkerComment, clYellow),
			iColorBorderFavoritiesVers = GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_ColorsSection_Main, GlobalVar::GlobalIni_ColorBorderFavoritiesVers, clRed),
				//Kolor nazwy oryginalnego tłumaczenia
			iColorOryginalTranslates = GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_ColorsSection_Main, GlobalVar::GlobalIni_ColorOryginalTranslates, clMaroon),
			iColorAdressOryg = GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_ColorsSection_Main, GlobalVar::GlobalIni_ColorAdressOryginalTranslate, clBlue),
			iColorNameOryginalTranslate = GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_ColorsSection_Main, GlobalVar::GlobalIni_ColorNameOryginalTranslate, clRed),
			//Others
			iSizeFontMain = GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_OthersSection, GlobalVar::GlobalIni_OtherSizeFontMain, 12),
			iSizeAdressFont = GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_OthersSection, GlobalVar::GlobalIni_OtherSizeFontAdress, 9),
			iSizeTranslatesFont = GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_OthersSection, GlobalVar::GlobalIni_OtherSizeFontNameTranslators, 9);
				//Czcionki
	UnicodeString ustr_FontNameMain = GlobalVar::Global_ConfigFile->ReadString(GlobalVar::GlobalIni_OthersSection, GlobalVar::GlobalIni_FontNameMain, "Times New Roman"),
								ustr_FontNameAdress = GlobalVar::Global_ConfigFile->ReadString(GlobalVar::GlobalIni_OthersSection, GlobalVar::GlobalIni_FontNameAdress, "Times New Roman"),
								ustr_FontNameTranslators = GlobalVar::Global_ConfigFile->ReadString(GlobalVar::GlobalIni_OthersSection, GlobalVar::GlobalIni_FontNameTranslators, "Times New Roman");
	//--- Style dla wyświetlanych tekstów [18-04-2024]
	bool bIsDisplayBackgroundImage = GlobalVar::Global_ConfigFile->ReadBool(GlobalVar::GlobalIni_FlagsSection_Main, GlobalVar::GlobalIni_IsDisplayBackgroundImage, false);
	//Kolor podkładu głównego tekstu [18-04-2024]
	UnicodeString _BackGroundMainText, _ConvertPathImage;
	//Przeksztaucenie ścieżek dostępu Windows na Unix [18-04-2024]
	_ConvertPathImage = StringReplace(GlobalVar::Global_custrPathImageBackgroundMainText, "\\", "\\\\", TReplaceFlags() << rfReplaceAll);
	if(bIsDisplayBackgroundImage) //[18-04-2024]
	//Podkład pod głównym tekstem jako grafika domyślna (w przyszłości bedzie wybór)
	{
		_BackGroundMainText = Format("body {background-image: url(\"%s\");\n\tfont-size:%upt;\n\tfont-family:%s;}\n",
			ARRAYOFCONST((_ConvertPathImage, iSizeFontMain, ustr_FontNameMain)));
	}
	else
	//Podkład pod głównym tekstem jako jednolity tekst, lub grafika
	{
		_BackGroundMainText = Format("body {background-color: %s;\n\tfont-size:%upt;\n\tfont-family:%s;}\n",
			ARRAYOFCONST((RGBToWebColorStr(iColorBackgroundText), iSizeFontMain, ustr_FontNameMain)));
	}
  //---
	UnicodeString		//Styl dla głównego tekstu
								_GlobalText = Format(".styleText {color: #000000;font-size:%upt;font-family:%s;}\n",
									ARRAYOFCONST((iSizeFontMain, ustr_FontNameMain))),
									//Styl dla ulubionych wersetów
								_FavoriteStyle = Format(".styleFavorite {background-color: %s;border: 1px solid %s}\n",
									ARRAYOFCONST((RGBToWebColorStr(iColorFavVers), RGBToWebColorStr(iColorBorderFavoritiesVers)))),
									//Styl .css dla zaznaczania wersetów z komentarzem, podkład i kolor znacznika.
								_CommentStyle = Format( ".styleComment {font-family:%s;font-weight: 900; text-decoration: underline; background-color: %s ;color: %s;}\n",
									ARRAYOFCONST((ustr_FontNameMain, RGBToWebColorStr(iColorBackgroundMarkComment), RGBToWebColorStr(iColorCommentVers)))),
									//Kolor nazwy przekładu, dla pełnego tłumaczenia
								_ColorNameFullTranslate = Format(".styleTranslates {color: %s;font-size:%upt;font-family:%s;}\n",
									ARRAYOFCONST((RGBToWebColorStr(iColorNameFullTranslate), iSizeTranslatesFont, ustr_FontNameTranslators))),
									//Kolor adresu dla pełnych tłumaczeń
								_ColorAdressFullTranslates = Format(".styleColorAdressTranslates {color: %s; font-size:%upt;font-family:%s;}\n", ARRAYOFCONST((RGBToWebColorStr(iColorAdressFullTranslates), iSizeAdressFont, ustr_FontNameAdress))),
									//Styl dla tekstu oryginalnego
								_VersOryginalText = Format(".styleOrygin {color: %s;font-size:%upt;font-family:%s;}\n",
									ARRAYOFCONST((RGBToWebColorStr(iColorOryginalTranslates), iSizeFontMain, ustr_FontNameMain))),
									//Styl dla nazwy tłumaczenia oryginalnego
								_VersOryginalName = Format(".styleOrygTrans {color: %s;font-size:9pt;font-family:%s;}\n",
									ARRAYOFCONST((RGBToWebColorStr(iColorNameOryginalTranslate), ustr_FontNameTranslators))),
									//Styl dla adresu oryginalnego tłumaczenia
								_VersOryginalAdress = Format(".styleVersOryg {color: %s; font-size:%upt;font-family:%s;}\n",
									ARRAYOFCONST((RGBToWebColorStr(iColorAdressOryg), iSizeAdressFont, ustr_FontNameAdress)));
	//--- Domyślne zawartosci nagłówków kodu html, dla wyświetlania tekstów wersetów w głównym oknie, oknie wyszukiwań, oraz oknie wyboru wersetu

	GsReadBibleTextData::GsHTMLHeaderText = UnicodeString("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">\n") +
																												"<html>\n<head>\n" +
																												"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n" +
																												GsReadBibleTextData::GsHTMLTitle + "\n" + //[03-08-2023]
																												//"<title>Wybrany rozdział, dla dostępnych tłumaczeń</title>\n" +
																												"<style type=\"text/css\">\n" +
																												_ColorAdressFullTranslates +
																												_VersOryginalAdress +
																												_ColorNameFullTranslate +
																												_GlobalText +
																												".styleNoTranslate {color: #FF0000;font-size:16pt;font-family:Times New Roman;}\n" + //Informacja o braku księgi
																												_VersOryginalText +
																												_VersOryginalName +
																												_FavoriteStyle + //Kolor zaznaczenie ulubionego wersetu
																												_CommentStyle + //Kolor zaznaczania wersetu z komentarzem
																												_BackGroundMainText +
																												"</style>\n</head>\n\n<body>\n";
	GsReadBibleTextData::GsHTMLHeaderSearch = UnicodeString("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">\n") +
																												"<html>\n<head>\n" +
																												"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">" +
																												"<title>Wyniki wyszukiwania</title>" +
																												"<style type=\"text/css\">" +
																												_ColorAdressFullTranslates +
																												_ColorNameFullTranslate +
																												_GlobalText +
																												".styleNoTranslate {color: #FF0000;font-size:16pt;font-family:Times New Roman;}" +	//Informacja o braku księgi
																												".styleFound {background-color: #FFFF00;}" +
																												"body {background-color:#33CCCC;font-size:12pt;font-family:Times New Roman;}" +
																												"</style>\n</head>\n<body>\n";
	GsReadBibleTextData::GsHTMLHeaderDisplayVer = UnicodeString("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">\n") +
																												"<html>\n<head>" +
																												"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">" +
																												"<title>Wyswietlanie pojedyńczego werstu</title>" +
																												"<style type=\"text/css\">" +
																												_ColorAdressFullTranslates +
																												_ColorNameFullTranslate +
																												_GlobalText +
																												".styleNoTranslate {color: #FF0000;font-size:16pt;font-family:Times New Roman;}" + //Informacja o braku księgi
																												".styleFound {background-color: #FFFF00;}" +
																												"body {background-color:#FCD9BA;font-size:12pt;font-family:Times New Roman;}" +
																												"</style>\n</head>\n<body>";
	//--- Aktualizacja wyglądu strony, po zmianie konfiguracji kolorów aplikacji
	if(GsReadBibleTextData::_GsPageControl) //Istnieje zakładka
	{
		//Uaktualnienie wyświetlania aktualnego rozdziału, z zaznaczonymi, lub nie, ulubionymi wersetami
		GsTabSheetClass *pGsTabSheetClass = dynamic_cast<GsTabSheetClass *>(GsReadBibleTextData::_GsPageControl->ActivePage); //Aktualna zakładka
		if(pGsTabSheetClass) GsReadBibleTextData::pGsReadBibleTextClass->DisplayAllTextInHTML(pGsTabSheetClass->pWebBrowser);//Powtórne wczytanie tekstu rozdziału
	}
}
//---------------------------------------------------------------------------
void __fastcall GsReadBibleTextData::CloseMyBible()
/**
	OPIS METOD(FUNKCJI): Zamknięcie bilioteki do analizy Pisma Świętego
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//--- Zamykanie listy z kolorami
	if(GlobalVar::Global_ItemsColor)
		{delete GlobalVar::Global_ItemsColor; GlobalVar::Global_ItemsColor = nullptr;}
	//--- Zamykanie string listy z ulubionymi wersetami
	if(GlobalVar::Global_HSListAllFavoritiesVers)
	{
		GlobalVar::Global_HSListAllFavoritiesVers->SaveToFile(GlobalVar::Global_custrPathFileFavoriteVers, TEncoding::UTF8);
		delete GlobalVar::Global_HSListAllFavoritiesVers; GlobalVar::Global_HSListAllFavoritiesVers = nullptr;
	}
	//Zapis zaktualizowanego pliku historii, oraz usuwanie THashedStringListy z historią [30-07-2023]
	GlobalVar::Global_HListHistoryChapterOpen->SaveToFile(GlobalVar::Global_custrPathHistory, TEncoding::UTF8);
	if(GlobalVar::Global_HListHistoryChapterOpen)
		{delete GlobalVar::Global_HListHistoryChapterOpen; GlobalVar::Global_HListHistoryChapterOpen = nullptr;}
	//--- Zamykanie głownej klasy
	if(GsReadBibleTextData::pGsReadBibleTextClass)
	{
		delete GsReadBibleTextData::pGsReadBibleTextClass;
		GsReadBibleTextData::pGsReadBibleTextClass = nullptr;
	}
	else
	{
		throw(Exception("Objekt GsReadBibleTextClass NIE JEST jeszcze zainicjowany, dlatego nie będzie zamknięty!"));
	}
	GsReadBibleTextData::IsInitLibrary = false; //Czy została zainicjowana bibliteka (moduł)
}
//---------------------------------------------------------------------------
void __fastcall GsReadBibleTextData::CreateTreeBooks(TWinControl* _OwnerParent, TPageControl *_PageControl,
			int _iWidth)
/**
	OPIS METOD(FUNKCJI): Stworzenie drzewa ksiąg i innych objektów biblioteki
	OPIS ARGUMENTÓW: TWinControl* _OwnerParent - Właściciel objektu, który będzie jednocześnie przodkiem. Na tym objekcie będzie wyświetlane drzewo ksiąg biblijnych.
									 TPageControl *_PageControl - Wskaźnik na objekt zakładek, gdzie będzie w zakładkach wyświetlany tekst biblijny
									 int _iWidth - szerokość drzewa ksiąg biblijnych, domyślnie 260.
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(!GsReadBibleTextData::pGsReadBibleTextClass)
		throw(Exception("Nie dokonano inicjalizacji objektu GsReadBibleTextClass"));
	//---
	GsTreeBibleClass *pGsTreeBibleClass = new GsTreeBibleClass(_OwnerParent, _PageControl);
	if(!pGsTreeBibleClass) throw(Exception("Błąd inicjalizacji objektu GsTreeBibleClass"));
	_PageControl->Images = GsReadBibleTextData::_GsImgListData;
	//---Stworzenie drzewa ksiąg biblijnych
	pGsTreeBibleClass->Parent = _OwnerParent;
	pGsTreeBibleClass->Align = alClient;
	pGsTreeBibleClass->Width = _iWidth;
	GsReadBibleTextData::pGsTreeBibleClass = pGsTreeBibleClass;
}
//---------------------------------------------------------------------------
unsigned char __fastcall GsReadBibleTextData::CountTranslates()
/**
	OPIS METOD(FUNKCJI): Metoda zwraca ilość tłumaczeń
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(!GsReadBibleTextData::pGsReadBibleTextClass) throw(Exception("Nie dokonano inicjalizacji objektu GsReadBibleTextClass"));
	return GsReadBibleTextData::pGsReadBibleTextClass->GetCountTranslates();
}
//---------------------------------------------------------------------------
void __fastcall GsReadBibleTextData::GetInfoNameTranslate(const unsigned char i, UnicodeString &NameTranslate)
/**
	OPIS METOD(FUNKCJI): Zwraca nazwę tłumaczenia o numerze i
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(!GsReadBibleTextData::pGsReadBibleTextClass) throw(Exception("Nie dokonano inicjalizacji objektu GsReadBibleTextClass"));
	GsReadBibleTextData::pGsReadBibleTextClass->_GetInfoNameTranslate(i, NameTranslate);
}
//---------------------------------------------------------------------------
void __fastcall GsReadBibleTextData::GetNameIndependentTranslate(const int i, UnicodeString &NameTranslate)
/**
	OPIS METOD(FUNKCJI): Zwraca nazwę tłumaczenia niezależnie od jego statusu (aktywny, lub nie) //[09-12-2023]
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  if(!GsReadBibleTextData::pGsReadBibleTextClass) throw(Exception("Nie dokonano inicjalizacji objektu GsReadBibleTextClass"));
	GsReadBibleTextData::pGsReadBibleTextClass->_GetNameIndependentTranslate(i, NameTranslate);
}
//---------------------------------------------------------------------------
void __fastcall GsReadBibleTextData::WriteCurrentSheetText(const UnicodeString custrPath)
/**
	OPIS METOD(FUNKCJI): Zapisuje zawartość aktualnej zakładki
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(!GsReadBibleTextData::pGsReadBibleTextClass) throw(Exception("Nie dokonano inicjalizacji objektu GsReadBibleTextClass"));
	GsReadBibleTextData::pGsReadBibleTextClass->SaveCurrentSheetText(custrPath);
}
//---------------------------------------------------------------------------
void __fastcall GsReadBibleTextData::GetTextHTMLCurrentSheet(UnicodeString &_ustrTextHTML)
/**
	OPIS METOD(FUNKCJI): Metoda wypełnią kodem html, zmienną UnicodeString, z aktualnej zakładki
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(!GsReadBibleTextData::pGsReadBibleTextClass) throw(Exception("Nie dokonano inicjalizacji objektu GsReadBibleTextClass"));
	GsTabSheetClass *pGsTabSheetClass = static_cast<GsTabSheetClass *>(GsReadBibleTextData::_GsPageControl->ActivePage);
	if(!pGsTabSheetClass) return;
	//---
	pGsTabSheetClass->_GetHTMLText(_ustrTextHTML);
}
//---------------------------------------------------------------------------
GsReadBibleTextItem *__fastcall GsReadBibleTextData::GetTranslate(const unsigned char cucNumberTrans)
/**
	OPIS METOD(FUNKCJI): Metoda zwraca wskaźnik na klasę wybranego tłumaczenia
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(!GsReadBibleTextData::pGsReadBibleTextClass) throw(Exception("Nie dokonano inicjalizacji objektu GsReadBibleTextClass"));
	return GsReadBibleTextData::pGsReadBibleTextClass->GetTranslateClass(cucNumberTrans);
}
//---------------------------------------------------------------------------
THashedStringList *__fastcall GsReadBibleTextData::GetSelectBoksInTranslate(GsReadBibleTextItem *pGsReadBibleTextItem, const signed char scIndexBook)
/**
	OPIS METOD(FUNKCJI): Wyodrębnienie konkretnej księgi(sciIndex), z wybranej struktury tłumaczenia (GetTranslate)
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(!GsReadBibleTextData::pGsReadBibleTextClass) throw(Exception("Nie dokonano inicjalizacji objektu GsReadBibleTextClass"));
	return pGsReadBibleTextItem->GetSelectBooks(scIndexBook);
}
//---------------------------------------------------------------------------
unsigned int __fastcall GsReadBibleTextData::GetCountVer(const int iNumberTrans, const signed char scIndexBook, const unsigned char cucChapt)
/**
	OPIS METOD(FUNKCJI): Metoda zwraca ilość wersetów, dla danego tłumaczenie, księgi i rozdziału
	OPIS ARGUMENTÓW: const int iNumberTrans - numer tłumaczenia
									 const signed char scIndexBook - numer księgi
									 const unsigned int uiChapt - numer rozdziału, zaczynając od 0
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(!GsReadBibleTextData::pGsReadBibleTextClass) throw(Exception("Nie dokonano inicjalizacji objektu GsReadBibleTextClass"));
	//---
	GsReadBibleTextItem *pGsReadBibleTextItem = GsReadBibleTextData::GetTranslate(iNumberTrans); //Metoda zwraca wskaźnik na klasę wybranego tłumaczenia
	if(!pGsReadBibleTextItem) throw(Exception("Błąd funkcji GsReadBibleTextData::GetTranslate()"));
	THashedStringList *pHashedStringList = GsReadBibleTextData::GetSelectBoksInTranslate(pGsReadBibleTextItem, scIndexBook); //Wyodrębnienie konkretnej księgi(sciIndex), z wybranej struktury tłumaczenia (GetTranslate)
	if(!pHashedStringList) throw(Exception("Błąd funkcji GsReadBibleTextData::GetSelectBoksInTranslate()")); //TUTAJ!!!
	unsigned int uiVers=0;

	for(int i=0; i<pHashedStringList->Count; ++i)
	{
		if(static_cast<unsigned char>(pHashedStringList->Strings[i].SubString(4, 3).ToInt()) == cucChapt+1)
		{
			uiVers++;
		}
	}
	return uiVers;
}
//---------------------------------------------------------------------------
void __fastcall GsReadBibleTextData::GetSelectVerAllTranslates(const unsigned char cucBook, const unsigned char cucChapt, const unsigned char cucVers, THashedStringList *_HSListVers)
/**
	OPIS METOD(FUNKCJI): Metoda zwraca listę wybranego wersetu, dla wszystkich, dostępnych tłumaczeń
	OPIS ARGUMENTÓW: const unsigned char cucBook - księga
									 const unsigned char cucChapt - rozdział
									 const unsigned char cucVers - werset
									 THashedStringList *_HSListVers - wskaźnik na string listę, w której zostaną umieszczone wersety
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(!GsReadBibleTextData::pGsReadBibleTextClass) throw(Exception("Nie dokonano inicjalizacji objektu GsReadBibleTextClass"));
	//---
	_HSListVers->Clear();
	unsigned char uiTranslates = GsReadBibleTextData::CountTranslates();
	int iReadVers;
	bool bVerifyvers=false;
	for(unsigned char i=0; i<uiTranslates; ++i)
	{
		GsReadBibleTextItem *pGsReadBibleTextItem = GsReadBibleTextData::GetTranslate(i);
		if(pGsReadBibleTextItem)
		{
			THashedStringList *pHSListBook = GsReadBibleTextData::GetSelectBoksInTranslate(pGsReadBibleTextItem, cucBook);
			//Błąd!!!
			if(pHSListBook)
			{
				for(int i=0; i<pHSListBook->Count; ++i)
				{
					if(pHSListBook->Strings[i].SubString(4, 3).ToInt() == cucChapt)
					{
						//bVerifyvers = TryStrToInt(pHSListBook->Strings[i].SubString(7, 3), iReadVers);
						iReadVers = pHSListBook->Strings[i].SubString(7, 3).ToIntDef(0); //Odczyt numeru wersetu
						if(iReadVers == cucVers)
						{
							_HSListVers->AddObject(pHSListBook->Strings[i].SubString(11, GlobalVar::Global_MaxlengthVers), pHSListBook->Objects[i]);
						}
						else if(iReadVers == 0)
						{
							_HSListVers->AddObject(pHSListBook->Strings[i].SubString(11, GlobalVar::Global_MaxlengthVers), pHSListBook->Objects[i]);
						}
					} //if(pHSListBook->Strings[i].SubString(7, 3).ToInt() == cucVers)
				} //for(int i=0; i<pHSListBook->Count; ++i)
			} //if(pHSListBook)
		} //if(pGsReadBibleTextItem)
	} //for(unsigned char i=0; i<uiTranslates; ++i)
}
//---------------------------------------------------------------------------
void __fastcall GsReadBibleTextData::GetTextVersOfAdress(const unsigned char cucBook, const unsigned char cucChapt, const unsigned char cucVers,
	const unsigned char cucTrans, UnicodeString &ustrText)
/**
	OPIS METOD(FUNKCJI): Metoda zwraca string wybranego wersetu(ustrText), dla wszystkich, dostępnych tłumaczeń
	OPIS ARGUMENTÓW: const unsigned char cucBook - księga
									 const unsigned char cucChapt - rozdział
									 const unsigned char cucVers - werset
									 UnicodeString &ustrText - adres dla umieszczenie tekstu
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(!GsReadBibleTextData::pGsReadBibleTextClass) throw(Exception("Nie dokonano inicjalizacji objektu GsReadBibleTextClass"));
	//---
	GsReadBibleTextItem *pGsReadBibleTextItem = GsReadBibleTextData::GetTranslate(cucTrans);
	if(pGsReadBibleTextItem)
	{
		THashedStringList *pHSListBook = GsReadBibleTextData::GetSelectBoksInTranslate(pGsReadBibleTextItem, cucBook);
		if(pHSListBook)
		{
			for(int i=0; i<pHSListBook->Count; ++i)
			{
				if((pHSListBook->Strings[i].SubString(4, 3).ToInt() == cucChapt) && (pHSListBook->Strings[i].SubString(7, 3).ToInt() == cucVers))
				{
					ustrText = pHSListBook->Strings[i].SubString(11, GlobalVar::Global_MaxlengthVers);
				}
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall GsReadBibleTextData::LoadFirstChapt(const unsigned char cucBook)
/**
	OPIS METOD(FUNKCJI): Otwiera pierwszy rozdział wybranej księgi
	OPIS ARGUMENTÓW: const unsigned char cucChapt - numer od 0, wybranej księgi
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(!GsReadBibleTextData::pGsReadBibleTextClass) throw(Exception("Nie dokonano inicjalizacji objektu GsReadBibleTextClass"));
	//---
	unsigned char ucBook;
	//Korekcja wybranej pozycji z traya i przystosowania jej do pozycji w objekcie, klasy GsTreeBibleClass.
	//A następnie uczynienie jej aktywnej
	ucBook = GsReadBibleTextData::GetConvertIdToTreeView(cucBook);
	//Wyłuskanie wskażnika na objekt, klasy GsTreeBibleClass a następnie uaktywnienie odpowiedniej pozycji.
	//GsTreeNodeClass *Node = dynamic_cast<GsTreeNodeClass *>(GsReadBibleTextData::pGsTreeBibleClass->Items[0].Item[ucBook]); //Wskaźnik na klasę drzewa ksiąg bibliinych
	TTreeNode *Node = GsReadBibleTextData::pGsTreeBibleClass->Items->Item[ucBook]; //Wskaźnik na klasę drzewa ksiąg bibliinych
	if(Node) Node->Selected = true; else return; //Aktywacja odpowiedniej pozycji
	//---
	GsReadBibleTextData::pGsTreeBibleClass->DblClick(); //Symulacja podwójnego kliknięcia
}
//---------------------------------------------------------------------------
unsigned char __fastcall GsReadBibleTextData::GetConvertIdToTreeView(const unsigned char cucID)
/**
	OPIS METOD(FUNKCJI): Tłumaczenie "płaskich" identyfikatorów, na pozycje w objekcie, klasy GsTreeBibleClass
	OPIS ARGUMENTÓW: const unsigned char cucID - numer od 0, inentyfikatora, który ma zostać skonwertowany
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	unsigned char ucResult=0;
	if((cucID >= GsReadBibleTextData::GsPairsGroupBible[en_GrSearch_Old].ucStartRange) && //0
		 (cucID <= GsReadBibleTextData::GsPairsGroupBible[en_GrSearch_Old].ucStopRange)) ucResult = cucID + 2; //38
	else if((cucID >= GsReadBibleTextData::GsPairsGroupBible[en_GrSearch_New].ucStartRange) && //39
					(cucID <= GsReadBibleTextData::GsPairsGroupBible[en_GrSearch_New].ucStopRange)		 //65
				 ) ucResult = cucID + 3;
	else if((cucID >= GsReadBibleTextData::GsPairsGroupBible[en_GrSearch_Apocr].ucStartRange) && //66
					(cucID <= GsReadBibleTextData::GsPairsGroupBible[en_GrSearch_Apocr].ucStopRange)		 //72
				 ) ucResult = cucID + 4;
	//---
	return ucResult;
}
//---------------------------------------------------------------------------
TProgressBar *__fastcall GsReadBibleTextData::GetCurrentNamberChaptOnSheet()
/**
	OPIS METOD(FUNKCJI): Metoda zwraca wskaźnik na progresbar miejsca aktualnego rozdziału, w odniesieniu do aktualnej księgi
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	GsTabSheetClass *pGsTabSheetClass = dynamic_cast<GsTabSheetClass *>(GsReadBibleTextData::_GsPageControl->ActivePage);
	//---
	return pGsTabSheetClass->pProgressBar;
}
//---------------------------------------------------------------------------
void __fastcall GsReadBibleTextData::GetAdressFromId(UnicodeString &_ustrResult, int _iBook, int _iChapt, int _iVers)
/**
	OPIS METOD(FUNKCJI): Konwersja z podanych informacji typu int, numeru księgi, rozdziału i wersetu, na ciąg identyfikacyjny (001001001)
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	_ustrResult = Format("%.3u%.3u%.3u", ARRAYOFCONST((_iBook, _iChapt, _iVers)));//"";
}
//---------------------------------------------------------------------------
void __fastcall GsReadBibleTextData::OpenSelectBookAndChapter(int _iBook, int _iChapt)
/**
	OPIS METOD(FUNKCJI): Otwarcie zakładki i wczytanie konkretnej księgi i rozdziału
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	int iBook;
	if((_iBook < 1) || (_iBook > 73)) return;

	if((_iBook >= 0) && (_iBook < 40)) iBook = _iBook + 1;
	if((_iBook >= 40) && (_iBook < 67)) iBook = _iBook + 2;
	if((_iBook >= 67) && (_iBook < 74)) iBook = _iBook + 3;
	//---
	if(GsReadBibleTextData::pGsTreeBibleClass->Selected == NULL)
		{GsReadBibleTextData::pGsTreeBibleClass->Selected = GsReadBibleTextData::pGsTreeBibleClass->Items->Item[iBook];}
	GsTabSheetClass *pGsTabSheetClass = new GsTabSheetClass(GsReadBibleTextData::_GsPageControl);	 //Przyporządkowanie zakładki do klasy TPageControl odbywa się konstruktorze klasy
	if(!pGsTabSheetClass) throw(Exception("Nie można zainicjować klasy GsTabSheetClass"));
	//NUMER TŁUMACZENIA LICZYMY OD ZERA. NUMER KSIĘGI LICZYMY OD ZERA. NUMER ROZDZIAŁU LICZYMY OD ZERA !!!
	//Stworzenie listy (_ListAllTrChap) wszystkich tłumaczeń konkretnej księgi (pGsTreeNodeClass->ucIndexBook) i konkretnego rozdziału (pItem->Tag)
	GsReadBibleTextData::pGsReadBibleTextClass->GetAllTranslatesChapter(_iBook-1, _iChapt-1);
	//Następnie wyświetlenie wszystkich tłumaczeń (DisplayAllTextInHTML), na podstawie wcześniej utworzonej listy dla konkretnej ksiegi, i konkretnego rozdziału
	GsReadBibleTextData::pGsReadBibleTextClass->DisplayAllTextInHTML(pGsTabSheetClass->pWebBrowser);
}
//---------------------------------------------------------------------------
TList *__fastcall GsReadBibleTextData::GetListAllTrChap()
/**
	OPIS METOD(FUNKCJI): Metoda udostępnia aktualna listę tekstów wszystkich tłumaczeń z wybranego rozdziału
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	return GsReadBibleTextData::pGsReadBibleTextClass->_ListAllTrChap; //Lista klasy THashedStringList, zawierających tekst wszystkich dostępnych tłumaczeń, z wybranego rodziału.
}
//---------------------------------------------------------------------------
UnicodeString __fastcall GsReadBibleTextData::DisplayExceptTextInHTML(TWebBrowser *_pWebBrowser, const int iSelectTranslate,
			const UnicodeString ustrInputStartStop, const DataDisplayTextAnyBrowser &DataDisplay)
/**
	OPIS METOD(FUNKCJI): Metoda wyświetla zakres wersetów z wybranego tłmaczenia w dowolnym objekcie, klasy TWebBrowser
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	MyObjectVers *pMyObjectVers=nullptr;
	int iLicz=0, iStart=0, iStop=0, iTemps=0, iLastOffsetVers=0;
	THashedStringList *pHSListText=nullptr;
	const int ciExceptText=18, ciExceptChapter=12, ciExceptOneChapter=6;
	UnicodeString ustrStartStop = ReplaceText(ustrInputStartStop, " ", ""), //Usunięcie wszystkich spacji
								ustrStartVers, ustrStopVers, ustrTemps, ustrRet;

	try
	{
		try
		{
			GsReadBibleTextItem *pGsReadBibleTextItem = GsReadBibleTextData::GetTranslate(iSelectTranslate); //Metoda zwraca wskaźnik na klasę wybranego tłumaczenia
			if(!pGsReadBibleTextItem) {throw(Exception("Błąd metody sReadBibleTextData::GetTranslate()"));}

			switch(ustrStartStop.Length())
			//Formatowanie ciągu wyjściowego dla wyodrębnienia zakresu tekstu z całego tekstu księgi.
			//wejściowym stringiem jest string pozbawiony spacji.
			//Format wyjściowy zawsze będzie miał format dla pary: 9 znaków - 9 zanków
			{
				case ciExceptText:
					//Granice dotyczą pełnych adresów wersetów (99)
					ustrStartVers=ustrStartStop.SubString(1, 9); //Uzyskanie adresu startowegp
					ustrStopVers=ustrStartStop.SubString(10, 9);
					iLastOffsetVers = 0;
					break;
				//---
				case ciExceptChapter:
					//Granice dotyczą adresów całych rozdziałów (66)
					ustrStartVers=ustrStartStop.SubString(1, 6); //Uzyskanie adresu startowegp
					ustrStartVers+="001";												 //Dodanie do adresu startowego informacji pierwszego wersetu
					ustrStopVers=ustrStartStop.SubString(7, 6);	 //Uzyskanie adresu końcowego
						//---
					iTemps = ustrStopVers.SubString(4, 3).ToInt() + 1; //Wyciągnięcie z adresu końcowego, numeru rozdziału i zwiększenie go o 1
					//Utworzenie kompletnego końcowego adresu, numer księgi niezmieniany + numer rozdziału zwiększony o 1 + pierwszy werset rozdziału
					ustrStopVers = ustrStopVers.SubString(1, 3) + Format("%.3u", ARRAYOFCONST((iTemps))) + "001";
					iLastOffsetVers = -1;												 //Odjąć jedną pozycje końcowego wskażnika na tekst
					break;
				//---
				case ciExceptOneChapter:
					//Tylko jeden cału rozdział (6)
					ustrStartVers=ustrStartStop.SubString(1, 6); //Uzyskanie adresu startowegp
					ustrStartVers+="001";												 //Dodanie do adresu startowego informacji pierwszego wersetu
					ustrStopVers = ustrStartVers;								 //Skopiowanie startowego adresu do końcowego adresu
						//---
					iTemps = ustrStopVers.SubString(4, 3).ToInt() + 1; //Wyciągnięcie z adresu końcowego, numeru rozdziału i zwiększenie go o 1	 !!!
					//Utworzenie kompletnego końcowego adresu, numer księgi niezmieniany + numer rozdziału zwiększony o 1 + pierwszy werset rozdziału
					ustrStopVers = ustrStopVers.SubString(1, 3) + Format("%.3u", ARRAYOFCONST((iTemps))) + "001";
					iLastOffsetVers = -1; //Odjąć jedną pozycje końcowego wskażnika na tekst
					break;
				//---
				default:
					throw(Exception("Niewłaściwy format wejściowy"));
			}

			//Werset końcowy jest dalej niż początkowy, lub adresy początku i końca są niewłaściwego formatu
			if( (ustrStopVers.ToInt() < ustrStartVers.ToInt()) || (ustrStartVers.Length() != 9) || (ustrStopVers.Length()!= 9) )
				{throw(Exception("Niewłaściwy format danych wejściowych"));}
			pHSListText = new THashedStringList();
			if(!pHSListText) throw(Exception("Błąd inicjalizacji objektu THashedStringList"));

			if(pGsReadBibleTextItem)
			{
				THashedStringList *pSelectBook = pGsReadBibleTextItem->GetSelectBooks(ustrStartVers.SubString(1, 3).ToIntDef(1) - 1); //Metoda zwraca wskaźnik na konkretną księge

				while(pSelectBook->Strings[iLicz].SubString(1, 9) != ustrStartVers)
				{
					//if((iLicz >= pSelectBook->Count-1) || (pSelectBook->Strings[iLicz].SubString(1, 9).ToInt() > ustrStartVers.ToInt()))
					if(pSelectBook->Strings[iLicz].SubString(1, 9).ToInt() > ustrStartVers.ToInt())
					{
						throw(Exception("Końcowy adres tekstu zbyt duży"));
					}
					iLicz++;
					if(iLicz > pSelectBook->Count-1) break;
				}
				iStart = iLicz;
				iLicz++;

				while(pSelectBook->Strings[iLicz].SubString(1, 9) != ustrStopVers)
				{
					//if((iLicz >= pSelectBook->Count-1) || (pSelectBook->Strings[iLicz].SubString(1, 9).ToInt() > ustrStopVers.ToInt()))
					if(pSelectBook->Strings[iLicz].SubString(1, 9).ToInt() > ustrStopVers.ToInt())
					{
						throw(Exception("Końcowy adres tekstu zbyt duży"));
					}
					iLicz++;
					if(iLicz > pSelectBook->Count-1) break;
				}
				iStop = iLicz + 1 + iLastOffsetVers; //Wskaźnik na ostatni werset regulowany zależnie od formatu zakresu wybranego tekst

				for(int i=iStart; i<iStop; ++i)
				{
					pMyObjectVers = dynamic_cast<MyObjectVers *>(pSelectBook->Objects[i]);
					pHSListText->AddObject(pSelectBook->Strings[i].SubString(11, 500), pSelectBook->Objects[i]);
				}

			} //if(pGsReadBibleTextItem)
			//---
			for(int i=0; i<pHSListText->Count; ++i) //Tworzenie stringu wyjściowego, czystego tekstu
			//for(int i=0; i<2; ++i) //Tworzenie stringu wyjściowego, czystego tekstu //Tymczasowo
			{
				ustrRet += pHSListText->Strings[i] + " ";
			}

			TTabSheet *pTabSheet = dynamic_cast<TTabSheet *>(_pWebBrowser->TOleControl::Parent);
			if(pTabSheet)
			//Jeśli przodkiem objektu, klasy TWebBrowser, jest objekt klasy TTabSheet, to wyswietl informacje o zakresie wersetuów na uchwycie zakładki
			{
				MyObjectVers *pMyObjectStart = static_cast<MyObjectVers *>(pHSListText->Objects[0]),
										 *pMyObjectStop = static_cast<MyObjectVers *>(pHSListText->Objects[pHSListText->Count - 1]);

				if(pMyObjectStart && pMyObjectStop)
				{
					//Wyświetlenie zakresu na zakładkach
					pTabSheet->Caption = Format("%s %d:%d - %s %d:%d", ARRAYOFCONST((GsReadBibleTextData::GsInfoAllBooks[ustrStartVers.SubString(1, 3).ToInt() - 1].ShortNameBook,
						pMyObjectStart->ucChapt, pMyObjectStart->ucVers,
						GsReadBibleTextData::GsInfoAllBooks[ustrStopVers.SubString(1, 3).ToInt() - 1].ShortNameBook,
						pMyObjectStop->ucChapt, pMyObjectStop->ucVers)));
				}
			}
			GsReadBibleTextData::pGsReadBibleTextClass->_ViewSListBibleToHTML(_pWebBrowser, pHSListText, DataDisplay);
		}
		catch(Exception &e)
		{
			MessageBox(NULL, e.Message.c_str(), TEXT("Błąd aplikacji"), MB_OK | MB_ICONERROR | MB_TASKMODAL);
		}
	}
	__finally
	{
		if(pHSListText) {delete pHSListText; pHSListText = nullptr;}
	}
	return ustrRet;
}
//---------------------------------------------------------------------------
void GsReadBibleTextData::InitHistoryList()
/**
	OPIS METOD(FUNKCJI): Metoda inicjuje zmienne dotyczące historii [30-07-2023]
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//----- String lista histori otwieranych rozdziałow księg biblijnych
	GlobalVar::Global_HListHistoryChapterOpen = new THashedStringList();
	if(!GlobalVar::Global_HListHistoryChapterOpen) throw(Exception("Błąd inicjalizacji objektu THashedStringList"));
	//Odczyt pliku historii
	if(TFile::Exists(GlobalVar::Global_custrPathHistory))
	{
		GlobalVar::Global_HListHistoryChapterOpen->LoadFromFile(GlobalVar::Global_custrPathHistory, TEncoding::UTF8);
	}
}
//---------------------------------------------------------------------------
void GsReadBibleTextData::AddItemHistoryList(const UnicodeString _ustrTextItem)
/**
	OPIS METOD(FUNKCJI): Metoda dodajaca informacje o otwartym rozdziale do listy historii
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(!GlobalVar::Global_HListHistoryChapterOpen) throw(Exception("Nie zainicjowana lista histori (THashedStringList)"));
	UnicodeString ustrbDateNow = FormatDateTime("yyyy-mm-dd hh-nn-ss", Now());	//Aktualna data i czas
	GlobalVar::Global_HListHistoryChapterOpen->Insert(0, Format("%s=%s", ARRAYOFCONST((_ustrTextItem, ustrbDateNow))));
}
//---------------------------------------------------------------------------
void GsReadBibleTextData::GetCurentText(UnicodeString &_ustrText)
/**
	OPIS METOD(FUNKCJI): Metoda wyświetla tekst aktualnej zakładki [20-08-2023]
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(!GsReadBibleTextData::pGsReadBibleTextClass) throw(Exception("Nie dokonano inicjalizacji objektu GsReadBibleTextClass"));
	GsTabSheetClass *pGsTabSheetClass = static_cast<GsTabSheetClass *>(GsReadBibleTextData::_GsPageControl->ActivePage);
	if(pGsTabSheetClass)
	{
		pGsTabSheetClass->_GetText(_ustrText);
	}
}
//---------------------------------------------------------------------------
void GsReadBibleTextData::GetCurentListText(THashedStringList *_pHSList)
/**
	OPIS METOD(FUNKCJI): Metoda zwraca surową listę aktualnej zakładki [25-08-2023]
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(!GsReadBibleTextData::pGsReadBibleTextClass) throw(Exception("Nie dokonano inicjalizacji objektu GsReadBibleTextClass"));
	GsTabSheetClass *pGsTabSheetClass = static_cast<GsTabSheetClass *>(GsReadBibleTextData::_GsPageControl->ActivePage);
	if(pGsTabSheetClass)
	{
		pGsTabSheetClass->_GetListText(_pHSList);
	}
}
//---------------------------------------------------------------------------

