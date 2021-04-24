#include <vcl.h>
#pragma hdrstop

#include "uSelectVersWindow.h"
#include "uGlobalVar.h"
#include <System.IOUtils.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
/*
#if defined(_DEBUGINFO_)
	GsDebugClass::WriteDebug(Format("", ARRAYOFCONST(( ))));
	GsDebugClass::WriteDebug("");
#endif
MessageBox(NULL, TEXT("Test"), TEXT("Informacje aplikacji"), MB_OK | MB_ICONINFORMATION | MB_TASKMODAL);
*/
TSelectVersWindow *SelectVersWindow;
//---------------------------------------------------------------------------
__fastcall TSelectVersWindow::TSelectVersWindow(TComponent* Owner, const unsigned char _cucStartBook, const unsigned char _cucStartChapt,
																								const unsigned char _cucStarVers, bool bSelectComment)
	: TForm(Owner), _InputCucStartBook(_cucStartBook), _InputCucStartChapt(_cucStartChapt), _InputCucStarVers(_cucStarVers), _InputBSelectComment(bSelectComment)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW: TComponent* Owner - Właściciel objektu.
									 const unsigned char _cucStartBook - Numer księgi (od zera).
									 const unsigned char _cucStartChapt - Numer rozdziału (od zera).
									 const unsigned char _cucStarVers - Numer wersetu (od jednego).
									 bool bSelectComment - czy kliknąłeś na lpozycje w liście komentarzy, w głównym oknie,
									 											 by otworzyś werset związany z tym komentarzem w oknie wyboru wersetów
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//Sprawdzenie i ewentualne stworzenie katalogu z plikami komentarzy
	if(!TDirectory::Exists(GlobalVar::Global_custrPathDirComments)) TDirectory::CreateDirectory(GlobalVar::Global_custrPathDirComments);

}
//---------------------------------------------------------------------------
void __fastcall TSelectVersWindow::FormCreate(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//Ominięcie błedu z domyślnie wywołaną księgą apokryficzną, w przyszłości MUSI być błąd usunięty w sposób bardziej elegancki
	unsigned char ucStartBook;//=0;
	//if(_cucStartBook < 66) ucStartBook = _cucStartBook; else ucStartBook = 0;
	if(this->_InputCucStartBook < 66) ucStartBook = _InputCucStartBook; else ucStartBook = 0;
	//---
	this->_pGsPanelSelectVers = new GsPanelSelectVers(this, ucStartBook, this->_InputCucStartChapt, this->_InputCucStarVers, this->_InputBSelectComment);
	if(!this->_pGsPanelSelectVers) throw(Exception("Nie dokonano inicjalizacji objektu GsPanelSelectVers"));
	this->_pGsPanelSelectVers->Parent = this;
	this->_pGsPanelSelectVers->Align = alClient;
}
//---------------------------------------------------------------------------
void __fastcall TSelectVersWindow::FormClose(TObject *Sender, TCloseAction &Action)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TSelectVersWindow::FormShow(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//this->_pGsPanelSelectVers->IsVisibleSetTranslate = false; //Wybór tłumaczenia niewidoczny. MUSI być wywołany w metodzie OnShow(), okna!!!
	//this->_pGsPanelSelectVers->IsVisibleIONoteEditors = false; //Czy mają być wyświetlane w edytorze notatek przyciski zapisu i odczytu.
	//this->_pGsPanelSelectVers->DisplayStart();
	/*
	KOLEJNOŚĆ WYWOŁYWANIA:
		1.GsPanelSelectVers::_SetupDisplayTranslate() -> GsPanelSelectVers::FIsSetTranslate
		2.GsBarSelectVers::_SetupDisplayTranslate() -> GsBarSelectVers::FIsSetTranslate
	*/
}
//---------------------------------------------------------------------------
void __fastcall TSelectVersWindow::FormActivate(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->_pGsPanelSelectVers->IsVisibleSetTranslate = false; //Wybór tłumaczenia niewidoczny. MUSI być wywołany w metodzie OnShow(), okna!!!
	//this->_pGsPanelSelectVers->IsVisibleIONoteEditors = false; //Czy mają być wyświetlane w edytorze notatek przyciski zapisu i odczytu.
	//this->_pGsPanelSelectVers->DisplayStart();
	/*
	KOLEJNOŚĆ WYWOŁYWANIA:
		1.GsPanelSelectVers::_SetupDisplayTranslate() -> GsPanelSelectVers::FIsSetTranslate
		2.GsBarSelectVers::_SetupDisplayTranslate() -> GsBarSelectVers::FIsSetTranslate
	*/
}
//---------------------------------------------------------------------------


