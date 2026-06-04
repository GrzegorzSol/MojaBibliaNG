#include <vcl.h>
#pragma hdrstop

#include "uDictGrecPolWindow.h"
#if defined(_FULLAPLIC_)
	#include "uStrongWindow.h"
#endif
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
	this->_pGsPanelDictionaryClass = new GsPanelDictionaryClass(this);
	if(!this->_pGsPanelDictionaryClass) throw(Exception("Bład funkcji GsPanelDictionaryClass"));
	this->_pGsPanelDictionaryClass->Parent = this;
	this->_pGsPanelDictionaryClass->Align = alClient;
	this->_pGsPanelDictionaryClass->OnStrongWordSelect = this->_OnClickButtonSelectWordStrong;
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
void __fastcall TDictGrecPolWindow::_OnClickButtonSelectWordStrong(System::TObject* Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TButton *pButton = dynamic_cast<TButton *>(Sender);
	if(!pButton) return;
	//---
	#if defined(_DEBUGINFO_)
		GsDebugClass::WriteDebug("_OnClickButtonSelectWordStrong");
		//GsDebugClass::WriteDebug(Format("Strong: \"%s\"", ARRAYOFCONST((pButton->Caption))));
	#endif
  #if defined(_FULLAPLIC_)
		TStrongWindow *pStrongWindow = new TStrongWindow(this, pButton->Caption);
		if(!pStrongWindow) throw(Exception("Błąd inicjalizacji objektu, klasy, okna TStrongWindow"));
		pStrongWindow->Show();
	#endif
}
//---------------------------------------------------------------------------

