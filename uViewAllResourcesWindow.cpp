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
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  
}
//---------------------------------------------------------------------------
void __fastcall TViewAllResourcesWindow::FormClose(TObject *Sender, TCloseAction &Action)
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
void __fastcall TViewAllResourcesWindow::FormCreate(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->pGsViewAllResourcesClass = new GsViewAllResourcesClass(this);
	if(!this->pGsViewAllResourcesClass) throw(Exception("B³¹d inicjalizacji objektu, klasy GsViewAllResourcesClass"));
	this->pGsViewAllResourcesClass->Parent = this;
	this->pGsViewAllResourcesClass->Align = alClient;
	//---
	this->pGsViewAllResourcesClass->OnSelectItem = this->_OnSelectItem;
}
//---------------------------------------------------------------------------
void __fastcall TViewAllResourcesWindow::FormDestroy(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  //
}
//---------------------------------------------------------------------------
void __fastcall TViewAllResourcesWindow::_OnSelectItem(System::TObject* Sender, TListItem* Item, bool Selected)
/**
	OPIS METOD(FUNKCJI): Wybrana zosta³a pozycja z listy
	OPIS ARGUMENTÓW:
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
		ustrSelectItem = Format("Œcie¿ka dostêpu do pliku graficznego: %s", ARRAYOFCONST((Item->Caption))) + "\nPodgl¹d pliku graficznego jest dostêpny w g³ównym oknie, w zak³adce po lewej stronie, zatytu³owanej :\"Grafika i Multimedia\"." +
										 "Po wybraniu tej zak³adki, bêdzie dostêpna lista wszystkich plików graficznych, których œcie¿ki zosta³y zarejestrowane w g³ównych ustawieniach aplikacji." +
										 "Pojedyñcze klikniêcie na wybrany plik z listy, powoduje jego wyœwietlenie w ma³ym podgl¹dzie na dole listy, gdy klikniemy podwójnie, plik zostanie " +
										 "wyœwietlony w swoich oryginalnych rozmiarach w noej zak³adce w g³ównym oknie, z mo¿liwoœci¹ przewijania jego zawartoœci.";
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
