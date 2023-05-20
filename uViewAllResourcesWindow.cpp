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

  this->_pDisplayWindow = new TForm(this);
	if(!this->_pDisplayWindow) throw(Exception("B³¹d inicjalizacji objektu TForm"));

  this->_pDisplayWindow->Width = Screen->Width;
	this->_pDisplayWindow->Height = Screen->Height;
	this->_pDisplayWindow->Left = 0; this->_pDisplayWindow->Top = 0;
	this->_pDisplayWindow->BorderStyle = bsNone;
	this->_pDisplayWindow->KeyPreview = true;
	this->_pDisplayWindow->OnKeyPress = this->_OnKeyPress;
	this->_pDisplayWindow->StyleElements = TStyleElements();
	this->_pDisplayWindow->Color = clBlack;

	this->_pImageScr = new TImage(this->_pDisplayWindow);
	if(!this->_pImageScr) throw(Exception("B³¹d inicjalizacji objektu TImage"));
	this->_pImageScr->Parent = this->_pDisplayWindow;
	this->_pImageScr->Stretch = true;
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
	if(this->_pDisplayWindow) {delete this->_pDisplayWindow; this->_pDisplayWindow = nullptr;}
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
	DataItemResources *pDataItemResources = static_cast<DataItemResources *>(Item->Data);

	try
	{
		if(Item->GroupID == enGroup_Translate)
		//T³umaczenia
		{
			ustrSelectItem = TPath::ChangeExtension(Item->Caption, GsReadBibleTextData::GsExtendNoAsteriskTextInfoTranslate);
			if(TFile::Exists(ustrSelectItem))
			{
				this->REditInfoSelectItem->Lines->LoadFromFile(ustrSelectItem);
			}
		}
		else if(Item->GroupID == enGroup_Graphics)
    //Podgl¹d grafiki
		{
			this->_DisplayImage(Item->Caption);
		}
		else if(Item->GroupID == enGroup_CoomentFiles || Item->GroupID == enGroup_FavVers)
    //Ulubione wersety i wersety z komentarzem
		{
			this->_DisplaySelectVersAllTrans(pDataItemResources);
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
	this->ImageDisplayResource->Height = this->PanelDisplay->Height - 4;
	this->ImageDisplayResource->Width = this->fFactorProp * this->ImageDisplayResource->Height;
	this->ImageDisplayResource->Left = this->PanelDisplay->Width / 2 - (this->ImageDisplayResource->Width / 2);
	this->ImageDisplayResource->Top = this->PanelDisplay->Height / 2 - (this->ImageDisplayResource->Height / 2);
}
//---------------------------------------------------------------------------
void __fastcall TViewAllResourcesWindow::_DisplaySelectVersAllTrans(const DataItemResources *pDataItemResources)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	const UnicodeString GlobalSizeFontText = "\\fs28",
										GlobalHeaderRtf = UnicodeString("{\\rtf1\\ansi\\deff0{\\fonttbl{\\f0\\fnil\\fcharset238{\\*\\fname Arial;}Arial CE;}{\\f1\\fnil Arial;}}") +
																		 "{\\colortbl ;\\red0\\green0\\blue0;\\red255\\green0\\blue0;\\red0\\green200\\blue0;\\red0\\green0\\blue255;}" +
																		 "{\\*\\generator Msftedit 5.41.21.2510;}\\viewkind4\\uc1\\pard\\sa200\\sl276\\slmult1\\qc\\tx720\\tx1440\\tx2880\\tx5760\\cf4\\lang1045\\b\\f0\\fs28 Podgl¹d wersetu z listy ulubionych, lub wersetu, który posiada komentarz\\b0\\f1\\line\\pard\\sa200\\sl276\\slmult1\\tx720\\tx1440\\tx2880\\tx5760\\cf1\\b" + GlobalSizeFontText,
										GlobalAdressVersRtf = "\\f1\\line\\cf2\\b",
										GlobalVersRtf = "\\cf1\\b0\\f0",
										GlobalNameTransRtf = "\\cf4\\f1",
										GlobalEndVersRtf = "\\cf1\\f1",
										GlobalSizeNameTransRtf = "\\fs20";

	TStringStream *pStringStream = new TStringStream("", TEncoding::ANSI, true);
	//TStringStream *pStringStream = new TStringStream("", TEncoding::UTF8, true);
	if(!pStringStream) throw(Exception("B³¹d inicjalizacji objektu TStringStream"));

	pStringStream->WriteString(GlobalHeaderRtf);


	for(int iLicz=0; iLicz<pDataItemResources->HSListGetAllTransVers->Count; iLicz++)
	{
		GsReadBibleTextItem *GsReadBibleTextItem = GsReadBibleTextData::GetTranslate(iLicz);
    //Zawartoœæ wersetów tylko dla polskich t³umaczeñ
		if(GsReadBibleTextItem->enTypeTranslate != enTypeTr_Full) continue;
		if(!pDataItemResources->HSListGetAllTransVers->Strings[iLicz].IsEmpty())
		{
			pStringStream->WriteString(Format("%s %s " ,ARRAYOFCONST((GlobalAdressVersRtf, pDataItemResources->ustrInfoResource))));
			pStringStream->WriteString(Format("%s %s" ,ARRAYOFCONST((GlobalVersRtf, pDataItemResources->HSListGetAllTransVers->Strings[iLicz]))));
    }
	}

	pStringStream->WriteString(Format("%s" ,ARRAYOFCONST((GlobalSizeFontText))));
	pStringStream->WriteString("}");
	pStringStream->Position = 0;
	this->REditInfoSelectItem->Lines->LoadFromStream(pStringStream);

	if(pStringStream) {delete pStringStream; pStringStream = nullptr;}
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
	TWICImage *pWICImage=nullptr;

	try
	{
		pWICImage = new TWICImage();
		if(!pWICImage) throw(Exception("B³¹d inicjalizacji objektu TWICImage"));
		//---
		pWICImage->LoadFromFile(_pathImages);
		this->fFactorProp = (float)pWICImage->Width / (float)pWICImage->Height;
		this->ImageDisplayResource->Picture->Assign(pWICImage);
		this->PanelDisplay->OnResize(this->PanelDisplay);

		ustrSelectItem = Format("Œcie¿ka dostêpu do pliku graficznego: \"%s\" - Rozmiar: %d x %d", ARRAYOFCONST((_pathImages, pWICImage->Width, pWICImage->Height)));
		this->REditInfoSelectItem->Lines->Text = ustrSelectItem;
	}
	__finally
	{
		if(pWICImage) {delete pWICImage; pWICImage = nullptr;}
	}
}
//---------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// 						 	OTWARCIE PE£NOEKRANOWEGO PODGLADU WYBRANEJ                 //
//										GRAFIKI I JEGO PRYWATNE METODY                       //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////
void __fastcall TViewAllResourcesWindow::ImageDisplayResourceDblClick(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Wyœwietlenie w formie pe³no ekranowej wybranej grafiki
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TImage *pImg = dynamic_cast<TImage *>(Sender);
	if(!pImg) return;
	//---
	TWICImage *pWICImg=nullptr;
	TListItem* Item = this->_pGsViewAllResourcesClass->Items->Item[this->_pGsViewAllResourcesClass->ItemIndex];
	UnicodeString _ustrCurrentPathImage = Item->Caption;
	//---
	try
	{
		pWICImg = new TWICImage();
		if(!pWICImg) throw(Exception("B³¹d inicjalizacji objektu TWICImage"));

		pWICImg->LoadFromFile(_ustrCurrentPathImage);
		float fSizeFactorWH = (float)pWICImg->Width / (float)pWICImg->Height, //Proporcje szerokoœci do wysokoœci, wczytanej grafiki
					fSizeFactorHW = (float)pWICImg->Height / (float)pWICImg->Width; //Proporcje wysokoœci do szerokoœci, wczytanej grafiki
		//--- Sprawdzanie wysokoœci grafiki
		if(pWICImg->Height > this->_pDisplayWindow->ClientHeight)
			{this->_pImageScr->Height = this->_pDisplayWindow->ClientHeight;}
		else
			{this->_pImageScr->Height = pWICImg->Height;}
		this->_pImageScr->Width = fSizeFactorWH * this->_pImageScr->Height;
		//--- Sprawdzanie szerokoœci grafiki
//		if(pWICImg->Width > this->_pDisplayWindow->ClientWidth)
//			{this->_pImageScr->Width = this->_pDisplayWindow->ClientWidth;}
//		else
//			{this->_pImageScr->Width = pWICImg->Width;}
//		this->_pImageScr->Height = fSizeFactorHW * this->_pImageScr->Width;
		//---

		this->_pImageScr->Left = this->_pDisplayWindow->ClientWidth / 2 - (this->_pImageScr->Width / 2);
		this->_pImageScr->Top = this->_pDisplayWindow->ClientHeight / 2 - (this->_pImageScr->Height / 2);
		this->_pImageScr->Picture->Assign(pWICImg); //Skopiwanie bitmapy wczytanej grafiki do bitmapy objektu, klasy TImage

		this->_pDisplayWindow->Show();
	}
	__finally
	{
		if(pWICImg) {delete pWICImg; pWICImg = nullptr;}
	}
}
//---------------------------------------------------------------------------
void __fastcall TViewAllResourcesWindow::_OnKeyPress(TObject *Sender, System::WideChar &Key)
/**
	OPIS METOD(FUNKCJI): Naciœniêto jaki kolwiek klawisz w oknie do podgl¹du wybranej grafiki, w formie pe³no ekranowej
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TForm *pForm = dynamic_cast<TForm *>(Sender);
	if(!pForm) return;
	//---
	if(this->_pGsViewAllResourcesClass->ItemIndex == -1) return;
	//---
	switch(Key)
	{
		case vkEscape:
			pForm->Hide(); //Schowanie okna
		break;
		//---
		case vkSpace: //Nastêpna grafika
			if(this->_pGsViewAllResourcesClass->ItemIndex < this->_pGsViewAllResourcesClass->Items->Count)
			{
				this->_pGsViewAllResourcesClass->ItemIndex++;
				TListItem* Item = this->_pGsViewAllResourcesClass->Items->Item[this->_pGsViewAllResourcesClass->ItemIndex];
				if(Item->GroupID != enGroup_Graphics)
				{
					this->_pGsViewAllResourcesClass->ItemIndex--;
					break;
				}
				this->ImageDisplayResourceDblClick(this->ImageDisplayResource);
			}
		break;
		//---
		case vkBack: //Poprzednia grafika
			if(this->_pGsViewAllResourcesClass->ItemIndex > 0)
			{
				this->_pGsViewAllResourcesClass->ItemIndex--;
				TListItem* Item = this->_pGsViewAllResourcesClass->Items->Item[this->_pGsViewAllResourcesClass->ItemIndex];
				if(Item->GroupID != enGroup_Graphics)
				{
					this->_pGsViewAllResourcesClass->ItemIndex++;
					break;
				}
				this->ImageDisplayResourceDblClick(this->ImageDisplayResource);
    	}
		break;
	}
}
//---------------------------------------------------------------------------

