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
	this->ImageDisplayResource->Height = this->PanelDisplay->Height;
	this->ImageDisplayResource->Width = this->ImageDisplayResource->Height;
	this->ImageDisplayResource->Left = this->PanelDisplay->Width / 2 - (this->ImageDisplayResource->Width / 2);
  this->ImageDisplayResource->Top = 0;
	//this->ImageDisplayResource->Margins->Left
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
	this->_pGsViewAllResourcesClass = new GsViewAllResourcesClass(this);
	if(!this->_pGsViewAllResourcesClass) throw(Exception("B³¹d inicjalizacji objektu, klasy GsViewAllResourcesClass"));
	this->_pGsViewAllResourcesClass->Parent = this;
	this->_pGsViewAllResourcesClass->Align = alClient;
	//---
	this->_pGsViewAllResourcesClass->OnSelectItem = this->_OnSelectItem;
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
	///
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

	try
	{
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
			//Podgl¹d grafiki
			this->_DisplayImage(Item->Caption);
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
	catch(...)
	{
    MessageBox(NULL, TEXT("B³¹d podczas wczytywania zasobów"), TEXT("B³¹d aplikacji"), MB_OK | MB_ICONERROR | MB_TASKMODAL);
  }
}
//---------------------------------------------------------------------------
void __fastcall TViewAllResourcesWindow::PanelDisplayResize(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TPanel *pPanel = dynamic_cast<TPanel *>(Sender);
	if(!pPanel) return;
	//---
	if(this->_pWICImage)
	{
		this->ImageDisplayResource->Height = this->PanelDisplay->Height - 4;
		this->ImageDisplayResource->Width = this->fFactorProp * this->ImageDisplayResource->Height;
		this->ImageDisplayResource->Left = this->PanelDisplay->Width / 2 - (this->ImageDisplayResource->Width / 2);
		this->ImageDisplayResource->Top = this->PanelDisplay->Height / 2 - (this->ImageDisplayResource->Height / 2);
	}
}
//---------------------------------------------------------------------------
void __fastcall TViewAllResourcesWindow::_DisplayImage(const UnicodeString _pathImages)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	UnicodeString  ustrSelectItem;

	try
	{
    this->_pWICImage = new TWICImage();
		if(!this->_pWICImage) throw(Exception("B³¹d inicjalizacji objektu TWICImage"));
		//---
		this->_pWICImage->LoadFromFile(_pathImages);
		this->fFactorProp = (float)this->_pWICImage->Width / (float)this->_pWICImage->Height;
		this->ImageDisplayResource->Picture->Assign(this->_pWICImage);
		this->PanelDisplay->OnResize(this->PanelDisplay);

		ustrSelectItem = Format("Œcie¿ka dostêpu do pliku graficznego: \"%s\" - Rozmiar: %d x %d", ARRAYOFCONST((_pathImages, this->_pWICImage->Width, this->_pWICImage->Height)));
		this->REditInfoSelectItem->Lines->Text = ustrSelectItem;
	}
	__finally
	{
		if(this->_pWICImage) {delete this->_pWICImage; this->_pWICImage = nullptr;}
	}
}
//---------------------------------------------------------------------------

