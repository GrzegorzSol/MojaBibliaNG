#include <vcl.h>
#pragma hdrstop

#include "uDictGrecPolWindow.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDictGrecPolWindow *DictGrecPolWindow;
//---------------------------------------------------------------------------
__fastcall TDictGrecPolWindow::TDictGrecPolWindow(TComponent* Owner)
	: TForm(Owner)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
}
//---------------------------------------------------------------------------
void __fastcall TDictGrecPolWindow::FormClose(TObject *Sender, TCloseAction &Action)
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
void __fastcall TDictGrecPolWindow::FormCreate(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->_pGsLViewDictionaryClass = new GsLViewDictionaryClass(this);
	if(!this->_pGsLViewDictionaryClass) throw(Exception("B³¹d funkcji GsLViewDictionaryClass"));
	this->_pGsLViewDictionaryClass->Parent = this;
	this->_pGsLViewDictionaryClass->Align = alLeft;
	this->_pGsLViewDictionaryClass->Width = 480;
}
//---------------------------------------------------------------------------
void __fastcall TDictGrecPolWindow::FormDestroy(TObject *Sender)
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

