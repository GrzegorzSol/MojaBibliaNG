#include <vcl.h>
#pragma hdrstop

#include "uViewAllResourcesWindow.h"
#include "uGlobalVar.h"
#include <System.IOUtils.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TViewAllResourcesWindow *ViewAllResourcesWindow;
/*
#if defined(_DEBUGINFO_)
	GsDebugClass::WriteDebug(Format("", ARRAYOFCONST(( ))));
#endif
*/
//---------------------------------------------------------------------------
__fastcall TViewAllResourcesWindow::TViewAllResourcesWindow(TComponent* Owner)
	: TForm(Owner)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENT�W:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  
}
//---------------------------------------------------------------------------
void __fastcall TViewAllResourcesWindow::FormClose(TObject *Sender, TCloseAction &Action)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENT�W:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TViewAllResourcesWindow::FormCreate(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENT�W:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->pGsViewAllResourcesClass = new GsViewAllResourcesClass(this);
	if(!this->pGsViewAllResourcesClass) throw(Exception("B��d inicjalizacji objektu, klasy GsViewAllResourcesClass"));
	this->pGsViewAllResourcesClass->Parent = this;
	this->pGsViewAllResourcesClass->Align = alClient;
	//---
	this->pGsViewAllResourcesClass->OnSelectItem = this->_OnSelectItem;
}
//---------------------------------------------------------------------------
void __fastcall TViewAllResourcesWindow::FormDestroy(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENT�W:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  //
}
//---------------------------------------------------------------------------
void __fastcall TViewAllResourcesWindow::_OnSelectItem(System::TObject* Sender, TListItem* Item, bool Selected)
/**
	OPIS METOD(FUNKCJI): Wybrana zosta�a pozycja z listy
	OPIS ARGUMENT�W:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	UnicodeString  ustrSelectItem;
	int iBook, iChap, iVers;

	if(Item->GroupID == enGroup_Translate)
	{
			ustrSelectItem = TPath::ChangeExtension(Item->Caption, GsReadBibleTextData::GsExtendNoAsteriskTextInfoTranslate);
			if(TFile::Exists(ustrSelectItem))
			{
				this->REditInfoSelectItem->Lines->LoadFromFile(ustrSelectItem);
			}
	}
	else if(Item->GroupID == enGroup_Graphics)
	{
		ustrSelectItem = Format("�cie�ka dost�pu do pliku graficznego: %s", ARRAYOFCONST((Item->Caption))) + "\nPodgl�d pliku graficznego jest dost�pny w g��wnym oknie, w zak�adce po lewej stronie, zatytu�owanej :\"Grafika i Multimedia\"." +
										 "Po wybraniu tej zak�adki, b�dzie dost�pna lista wszystkich plik�w graficznych, kt�rych �cie�ki zosta�y zarejestrowane w g��wnych ustawieniach aplikacji." +
										 "Pojedy�cze klikni�cie na wybrany plik z listy, powoduje jego wy�wietlenie w ma�ym podgl�dzie na dole listy, gdy klikniemy podw�jnie, plik zostanie " +
										 "wy�wietlony w swoich oryginalnych rozmiarach w noej zak�adce w g��wnym oknie, z mo�liwo�ci� przewijania jego zawarto�ci.";
		this->REditInfoSelectItem->Lines->Text = ustrSelectItem;
	}
	else if(Item->GroupID == enGroup_CoomentFiles || Item->GroupID == enGroup_FavVers)
	{
			ustrSelectItem = Item->Caption;
			iBook = ustrSelectItem.SubString(1, 3).ToInt()-1;
			iChap = ustrSelectItem.SubString(4, 3).ToInt();
			iVers = ustrSelectItem.SubString(7, 3).ToInt();
			this->REditInfoSelectItem->Lines->Text = Format("%s %d:%d", ARRAYOFCONST((GsReadBibleTextData::GsInfoAllBooks[iBook].FullNameBook, iChap, iVers)));
  }
}
//---------------------------------------------------------------------------
