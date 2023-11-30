#pragma hdrstop

#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "GsSchemeVersClass.h"
#include "uGlobalVar.h"
#include "MyBibleLibrary\GsReadBibleTextdata.h"
#include <Strsafe.h>
#pragma package(smart_init)

//---------------------------------------------------------------------------
/*
#if defined(_DEBUGINFO_)
	GsDebugClass::WriteDebug(Format("", ARRAYOFCONST(( ))));
#endif
*/
/*
	Repaint() 	Zgodnie z implementacją w TWinControl, Repaint wywołuje metodę Invalidate,
							a następnie metodę Update, aby ponownie zamalować kontrolkę.
	Update() 		Aktualizacja powoduje tylko ponowne malowanie obszarów kontrolki, które zostały uznane za nieaktualne.
							Aby wymusić natychmiastowe ponowne malowanie całej kontrolki, wywołaj metodę Repaint.
							Aby powiadomić kontrolkę, że jest nieaktualna (bez wymuszania natychmiastowego ponownego malowania),
							wywołaj metodę Invalidate.
*/

enum {
			//--- Numery identyfikacyjne kolorów
			enColorNum_Line=0,
			enColorNum_Active,
			enColorNum_InActive,
			enColorNum_Rot,
			enColorNum_Count
		 };
TColor ColorObject[enColorNum_Count];
int iWidthLine=2; //Szerokość lini

/****************************************************************************
*					 Klasa całkowicie PRYWATNA GsCoreBibleScheme,											*
*										 pochodna TCustomPanel.																	*
*****************************************************************************/
__fastcall GsCoreBibleScheme::GsCoreBibleScheme(TComponent* Owner) : TCustomPanel(Owner)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->Font->Quality = TFontQuality::fqClearType;
}
//---------------------------------------------------------------------------
__fastcall GsCoreBibleScheme::~GsCoreBibleScheme()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
}
/****************************************************************************
*					 Klasa całkowicie PRYWATNA GsChildBibleScheme,										*
*										 pochodna GsCoreBibleScheme.														*
*****************************************************************************/
__fastcall GsChildBibleScheme::GsChildBibleScheme(TComponent* Owner, PReadWriteDataObject _PReadWriteDataObject) : GsCoreBibleScheme(Owner)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW: PReadWriteDataObject _PReadWriteDataObject - Czy object jest tworzony (_PReadWriteDataObject=0 - domyślnie), czy wczytywany (_PReadWriteDataObject != 0)
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//Inicjalizacja listy potomków
	this->_ListChildren = new TList();
	if(!this->_ListChildren) throw(Exception("Nie dokonano inicjalizacji objektu TList"));
	//---
	this->Font->Quality = TFontQuality::fqClearType;
	this->StyleElements = TStyleElements();
	this->_SListVers = new THashedStringList(); //Lista wersetów ze wszystkich tłumaczeñ
	if(!this->_SListVers) throw(Exception("Nie dokonano inicjalizacji objektu THashedStringList"));
	//---
	this->DoubleBuffered = true;
	this->ParentColor = false;
	this->ParentBackground = false;
	this->ParentCtl3D = false;
	this->BevelOuter = bvNone;
	this->BorderStyle = bsSingle;
	this->Color = ColorObject[enColorNum_Active];
	this->Ctl3D = false;
	this->ShowHint = true;
	this->StyleElements = TStyleElements();
	if(_PReadWriteDataObject) this->_IDChild = _PReadWriteDataObject->RW_ID; else this->_IDChild = Random(INT_MAX);
	//this->ID64Child = (__int64)this->_IDChild * (__int64)Random(INT_MAX);
	this->_Level = 0; //Poziom
}
//---------------------------------------------------------------------------
__fastcall	GsChildBibleScheme::~GsChildBibleScheme()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	int iIndex;
	for(int i=0; i<this->_ListChildren->Count; i++)
	//Kasowanie wszystkich potomków
	{
		GsChildBibleScheme *pGsChildBibleScheme = static_cast<GsChildBibleScheme *>(this->_ListChildren->Items[i]);
		//if(!pGsChildBibleScheme) throw(Exception("Błąd wyłuskania objektu, klasy GsChildBibleScheme"));
		if(pGsChildBibleScheme)
		{
			//Kasowanie potomka z listy głównej
			iIndex = this->_DrawPanelScheme->_GsChildBibleSchemeList->IndexOf(pGsChildBibleScheme);
			if(iIndex > -1) this->_DrawPanelScheme->_GsChildBibleSchemeList->Delete(iIndex);
			//Wlaściwe kasowanie potomka
			delete pGsChildBibleScheme; pGsChildBibleScheme = nullptr;
		}
	}
	delete this->_ListChildren; this->_ListChildren = nullptr; //Kasowanie listy potomków, po ich usunięciu
	//Kasowanie objektu z listy głównej
	iIndex = this->_DrawPanelScheme->_GsChildBibleSchemeList->IndexOf(this);
	if(iIndex > -1) this->_DrawPanelScheme->_GsChildBibleSchemeList->Delete(iIndex);

	if(this->_SListVers) {delete this->_SListVers; this->_SListVers = nullptr;} //Lista wersetów ze wszystkich tłumaczeñ
}
//---------------------------------------------------------------------------
void __fastcall GsChildBibleScheme::CreateWnd()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	GsCoreBibleScheme::CreateWnd();
	//Własny kod.
	//Wyłuskanie wskaźnika na objekt do rysowania
	this->_DrawPanelScheme = dynamic_cast<GsDrawPanelBibleScheme *>(this->Parent);
	if(!this->_DrawPanelScheme) throw(Exception("Błąd wyluskania wskaźnika na objekt, klasy GsDrawPanelBibleScheme"));
	//Wyłuskanie na objekt, klasy TScrollBox
	this->_pGsScrollBibleScheme = dynamic_cast<GsScrollBibleScheme *>(this->_DrawPanelScheme->Parent);
	if(!this->_pGsScrollBibleScheme) throw(Exception("Błąd wyluskania wskaźnika na objekt, klasy GsScrollBibleScheme"));
	//Wyłuskanie wskaźnika na główny objekt, klasy
	this->_pGsMasterBibleScheme = dynamic_cast<GsMasterBibleScheme *>(this->_pGsScrollBibleScheme->Parent);
	if(!this->_pGsMasterBibleScheme) throw(Exception("Błąd wyluskania wskaźnika na objekt, klasy GsMasterBibleScheme"));
	//---
	this->Caption = this->_pGsMasterBibleScheme->_pGsBarSelectVers->GetSelectVers();
	this->Width = this->Canvas->TextWidth(this->Caption) + 24;
	this->Height = this->Canvas->TextHeight(this->Caption) + 24;
	this->_pGsMasterBibleScheme->_pGsBarSelectVers->SetSListVers(this->_SListVers); //Wypełnienie listy wszystkimi tłumaczeniami danego wersetu.
	//Wypelnianie pól adresu wersetu
	this->_pGsMasterBibleScheme->_pGsBarSelectVers->GetSelectAdress(this->_ucBook, this->_ucChapt, this->_ucVers, this->_ucTrans);
	//Podpowiedź w formie zawartości wersetucodeString
	this->Hint = Format("%s\n\"%s\"", ARRAYOFCONST((this->Caption, this->_SListVers->Strings[this->_ucTrans])));
}
//---------------------------------------------------------------------------
void __fastcall GsChildBibleScheme::DestroyWnd()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//Własny kod.
	GsCoreBibleScheme::DestroyWnd();
}
//---------------------------------------------------------------------------
void __fastcall GsChildBibleScheme::MouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if((Button == mbLeft) || (Button == mbRight))
	{
		this->_GetStartX = X;
		this->_GetStartY = Y;
		this->_StartMove = true;
		if(this->_DrawPanelScheme->_pSelectObject != this)
		{
			this->_DrawPanelScheme->_pSelectObject->Color = ColorObject[enColorNum_InActive]; //Dezaktywacja poprzedniego objektu
			this->_DrawPanelScheme->_pSelectObject = this;						//Objekt kliknięty, staje się aktualny
			if(this->_DrawPanelScheme->_pRootObject == this)
				this->_DrawPanelScheme->_pSelectObject->Color = ColorObject[enColorNum_Rot];	 //Zmiana koloru tła aktualnego objektu
			else this->_DrawPanelScheme->_pSelectObject->Color = ColorObject[enColorNum_Active];	 //Zmiana koloru tła , aktualnego objektu
		}
		this->_DrawPanelScheme->_pRootObject->Color = ColorObject[enColorNum_Rot];
		this->_ViewSelectObject();
		this->_SelectTreeObject();
	}
}
//---------------------------------------------------------------------------
void __fastcall GsChildBibleScheme::_ViewSelectObject()
/**
	OPIS METOD(FUNKCJI): Wyświetlenie wersetu wybranego objektu
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	UnicodeString _ustrVers;
	GsReadBibleTextData::GetTextVersOfAdress(this->_ucBook, this->_ucChapt+1, this->_ucVers, this->_ucTrans, _ustrVers);
	this->_pGsMasterBibleScheme->_pVersDisplayText->Caption = Format("%s \"%s\"", ARRAYOFCONST((this->Caption, _ustrVers))); //Wybrany werset
}
//---------------------------------------------------------------------------
void __fastcall GsChildBibleScheme::_SelectTreeObject()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	GsTreeBibleScheme *pGsTreeBibleScheme = dynamic_cast<GsTreeBibleScheme *>(this->_NodeObjectScheme->TreeView);
	if(!pGsTreeBibleScheme) throw(Exception("Błąd wyłuskania objektu, klasy GsTreeBibleScheme"));

	this->_NodeObjectScheme->Selected = true;
	pGsTreeBibleScheme->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall GsChildBibleScheme::MouseUp(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->_StartMove = false; //Koniec przesuwania
}
//---------------------------------------------------------------------------
void __fastcall GsChildBibleScheme::MouseMove(System::Classes::TShiftState Shift, int X, int Y)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(!this->_PrevObjectScheme) return; //Nie przesuwaj korzenia
	if(this->_StartMove)
	{
		this->Left += (X - this->_GetStartX);
		this->Top += (Y - this->_GetStartY);
		//--- Odświerzenie głównego okna, w celu odrysowania wszystkich objektów
		this->_DrawPanelScheme->Invalidate();
	}
}
//---------------------------------------------------------------------------

/****************************************************************************
*					 Klasa całkowicie PRYWATNA GsDrawPanelBibleScheme,								*
*										 pochodna TCustomPanel.																	*
*****************************************************************************/
__fastcall GsDrawPanelBibleScheme::GsDrawPanelBibleScheme(TComponent* Owner) : TCustomPanel(Owner)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->Font->Quality = TFontQuality::fqClearType;
	this->DoubleBuffered = true;
	this->StyleElements = TStyleElements();
	this->AutoSize = true;
	this->BevelOuter = bvNone;
	this->_GsChildBibleSchemeList = new TList();
	if(!this->_GsChildBibleSchemeList) throw(Exception("Nie dokonano inicjalizacji objektu TList"));
}
//---------------------------------------------------------------------------
__fastcall GsDrawPanelBibleScheme::~GsDrawPanelBibleScheme()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//--- Likwidowanie listy objektów, klasy GsChildBibleScheme
	if(this->_pRootObject)
	//Usuwany główny korzeń, a wraz z nim wszyscy jego potomkowie
	{
		delete this->_pRootObject; this->_pRootObject = nullptr;
	}
	if(this->_GsChildBibleSchemeList) {delete this->_GsChildBibleSchemeList; this->_GsChildBibleSchemeList = nullptr;}
}
//---------------------------------------------------------------------------
void __fastcall GsDrawPanelBibleScheme::CreateWnd()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TCustomPanel::CreateWnd();
	//Własny kod.
	TWinControl *pParentWControl = dynamic_cast<TWinControl *>(this->Parent);
	if(pParentWControl)
	{
		this->Left = (pParentWControl->Width / 2) - (this->Width / 2);
	}
  this->Top = 24;
	GsMasterBibleScheme *pGsMasterBibleScheme = static_cast<GsMasterBibleScheme *>(this->Parent->Parent);
	//if(!pGsMasterBibleScheme) throw(Exception("Błąd wyłuskania objektu, klasy GsMasterBibleScheme"));
	if(pGsMasterBibleScheme)
	{
		this->_pGsMasterBibleScheme = pGsMasterBibleScheme;
		this->_pGsTreeBibleScheme = pGsMasterBibleScheme->_pGsTreeBibleScheme;
	}
}
//---------------------------------------------------------------------------
void __fastcall GsDrawPanelBibleScheme::DestroyWnd()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//Własny kod.
	TCustomPanel::DestroyWnd();
}
//---------------------------------------------------------------------------
void __fastcall GsDrawPanelBibleScheme::Paint()
/**
	OPIS METOD(FUNKCJI): Wirtualna metoda odrysowywania klasy
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TCustomPanel::Paint();
	//Własny kod
	GsChildBibleScheme *pGsChildBibleScheme=nullptr, *pPrevObjectScheme=nullptr;
	for(int i=0; i<this->_GsChildBibleSchemeList->Count; i++)
	{
		pGsChildBibleScheme = static_cast<GsChildBibleScheme *>(this->_GsChildBibleSchemeList->Items[i]);
		if(!pGsChildBibleScheme) throw(Exception("Błąd wyłuskania objektu, klasy GsChildBibleScheme"));
		pPrevObjectScheme = pGsChildBibleScheme->_PrevObjectScheme;
		//if((this->_pSelectObject != pGsChildBibleScheme) && !this->bIsAllRefresh) continue;
		//--- Odrysowanie objektu i połączen
		if(pPrevObjectScheme && pGsChildBibleScheme->_DrawPanelScheme)
		{
      //Rysowanie połączenia z przodkiem
			this->Canvas->Pen->Width = iWidthLine;
			this->Canvas->Pen->Color = ColorObject[enColorNum_Line];
			this->Canvas->MoveTo(pGsChildBibleScheme->Left + (pGsChildBibleScheme->Width / 2), pGsChildBibleScheme->Top);
			this->Canvas->LineTo(pPrevObjectScheme->Left + (pPrevObjectScheme->Width / 2),
				pPrevObjectScheme->Top + pPrevObjectScheme->Height);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall GsDrawPanelBibleScheme::_WMErasebackground(TWMEraseBkgnd &Message)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  Message.Result = 1;
}
//---------------------------------------------------------------------------
void __fastcall GsDrawPanelBibleScheme::MouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->_pGsMasterBibleScheme->_OnNoAccept(this->_pGsMasterBibleScheme);
}
//---------------------------------------------------------------------------
void __fastcall GsDrawPanelBibleScheme::KeyUp(System::Word &Key, System::Classes::TShiftState Shift)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	#if defined(_DEBUGINFO_)
		GsDebugClass::WriteDebug("KeyUp");
	#endif
}
//---------------------------------------------------------------------------
void __fastcall GsDrawPanelBibleScheme::_AddNewObject()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	int _left=0, _top=100;
	//this->bIsAllRefresh = true;
	GsChildBibleScheme *pGsChildBibleScheme=nullptr, *prevGsChildBibleScheme=nullptr; //Domyślnie to korzeń

	pGsChildBibleScheme = new GsChildBibleScheme(this);
	if(!pGsChildBibleScheme) throw(Exception("Błąd inicjalizacji objektu GsChildBibleScheme"));
	pGsChildBibleScheme->Parent = this;

	if(this->_GsChildBibleSchemeList->Count > 0) //Tylko jeden korzeń!
	{
		//if(this->_pRootObject) this->_pRootObject->Color = ColorObject[enColorNum_Rot];
		prevGsChildBibleScheme = this->_pSelectObject;
		//Ustawienie pól na poprzedni objekt
		pGsChildBibleScheme->_PrevObjectScheme = prevGsChildBibleScheme; //Poprzedni objekt, to objekt wybrany
		prevGsChildBibleScheme->_NextObjectScheme = pGsChildBibleScheme; //Następny objekt
		prevGsChildBibleScheme->_ListChildren->Add(pGsChildBibleScheme); //Dodanie aktualnego objektu, do list potomków, przodka
		pGsChildBibleScheme->_Level = prevGsChildBibleScheme->_Level + 1;

		//_left += prevGsChildBibleScheme->Left + 10;
		_top = prevGsChildBibleScheme->Top + prevGsChildBibleScheme->Height + 24;
		//Tworzenie potomków w drzewie
		TTreeNode *childNode = this->_pGsTreeBibleScheme->Items->AddChildObject(prevGsChildBibleScheme->_NodeObjectScheme, pGsChildBibleScheme->Caption, nullptr);
		pGsChildBibleScheme->_NodeObjectScheme = childNode;
	}
	else //Dodawanie korzenia
	{
		this->_pRootObject = pGsChildBibleScheme;		//Okno głównego korzenia
		this->_pRootObject->Color = ColorObject[enColorNum_Rot];
		//Tworzenie korzenia drzewa
		TTreeNode *nodeMainRoot = this->_pGsTreeBibleScheme->Items->AddObject(NULL, pGsChildBibleScheme->Caption, nullptr);
		if(!nodeMainRoot) throw(Exception("Błąd inicjalizacji klasy AddObject"));
		pGsChildBibleScheme->_NodeObjectScheme = nodeMainRoot;
	}
	//
	this->_pGsTreeBibleScheme->FullExpand(); //Całkowicie rozwiniete drzewo
	this->_pGsTreeBibleScheme->Items->GetFirstNode()->MakeVisible();

	pGsChildBibleScheme->Top = _top; pGsChildBibleScheme->Left = _left;
	//this->bIsAllRefresh = false;

	if(this->_pSelectObject) {this->_pSelectObject->Color = ColorObject[enColorNum_InActive];} //Kolor nieaktywny dla poprzedniego objektu
	this->_pSelectObject = pGsChildBibleScheme;	//Aktualnie aktywny nowo dodany objekt
	pGsChildBibleScheme->_ViewSelectObject();

	this->_GsChildBibleSchemeList->Add(pGsChildBibleScheme); //Dodanie do głównej listy objektów

	this->Invalidate(); //Całe odświerzenie

	this->_pRootObject->Color = ColorObject[enColorNum_Rot];
}
//---------------------------------------------------------------------------
void __fastcall GsDrawPanelBibleScheme::_DeleteObject()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(this->_pSelectObject)	//Aktualnie aktywny objekt
	{
		int iResult = MessageBox(NULL, TEXT("Czy rzeczywiście chcesz skasować objekt razem ze wszystkimi jego pochodnymi?"), TEXT("Pytanie aplikacji"), MB_YESNO | MB_ICONWARNING | MB_TASKMODAL | MB_DEFBUTTON2);
		if(iResult == IDNO) return;

		TTreeNode *_pNode = this->_pSelectObject->_NodeObjectScheme;
		GsTreeBibleScheme *pTrView = static_cast<GsTreeBibleScheme *>(_pNode->TreeView);

		if(this->_pSelectObject!=this->_pRootObject)
		//Nie jest korzeniem i posiada przodków
		{
			GsChildBibleScheme *pParent = this->_pSelectObject->_PrevObjectScheme;
			if(pParent)
			{
				int iIndexParent = pParent->_ListChildren->IndexOf(this->_pSelectObject);
				if(iIndexParent > -1)
				{
					//Kasowanie objektu z listy przodka
					pParent->_ListChildren->Delete(iIndexParent);
				}
			}
			delete this->_pSelectObject; this->_pSelectObject = nullptr;
			this->_pSelectObject = this->_pRootObject;
		}
		else
		//Skasowanie korzenia
		{
			//this->ActDeleteLink->Enabled = false;
			delete this->_pRootObject; this->_pRootObject = nullptr;
			this->_pSelectObject = nullptr;
		}
		if(pTrView) _pNode->Delete();

		//this->Caption = Format("%s. Ilość objektów: %u", ARRAYOFCONST((ustrCaptionWindow, this->_GsChildBibleSchemeList->Count)));
		if(this->_pRootObject)
		{
		}
		this->Repaint();
	}
	else
	{
		MessageBox(NULL, TEXT("Nie wybrałeś objektu do skasowania"), TEXT("Informacja aplikacji"), MB_OK | MB_ICONINFORMATION | MB_TASKMODAL);
	}

}
//---------------------------------------------------------------------------
bool __fastcall GsDrawPanelBibleScheme::_OpenProjectObject()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//int left=0, top=0;
	GsChildBibleScheme *pGsChildBibleScheme, *prevGsChildBibleScheme;
	bool bReturn=false;
	//---
	TFileStream *pOpenFile;//=0;
	PReadWriteDataObject pDataToOpen;//=0;
	UnicodeString _ustrVers;
	//---
	TOpenDialog *pOpenDialog = new TOpenDialog(this);
	if(!pOpenDialog) throw(Exception("Błąd inicjalizacji objektu TOpenDialog"));

	pOpenDialog->Title = "Podaj nazwę projektu do odczytu";
	pOpenDialog->Filter =	 "Pliki projektu schematu(*.svp)|*.SVP|Każdy plik (*.*)|*.*"; //Może dać do globalnej zmiennej?
	pOpenDialog->Options << ofHideReadOnly << ofPathMustExist << ofFileMustExist;
	pOpenDialog->InitialDir = GlobalVar::Global_custrGetExeDir; //Katalog aplikacji
	pOpenDialog->DefaultExt = "svp";

	try
	{
		try
		{
			if(pOpenDialog->Execute()) //Element został wybrany
			{
				this->_pGsTreeBibleScheme->Items->Clear();
				//Wykasowanie całej zawartości schematu, ze wszystkimi aktualnymi objektami
				delete this->_pRootObject; this->_pRootObject = nullptr; //Niszczenie rozpoczyna siê od korzenia
				this->_pSelectObject = nullptr;
				pOpenFile = new TFileStream(pOpenDialog->FileName, fmOpenRead);
				if(!pOpenFile) throw(Exception("Błąd inicjalizacji objektu TFileStream"));
				int iSizeFile = pOpenFile->Size, //Wielkość pliku
						iSizeStructData = sizeof(ReadWriteDataObject); //Wielkość struktury
				//Struktura pomocnicza pojedyńczego objektu
				pDataToOpen = new ReadWriteDataObject();
				if(!pDataToOpen) throw(Exception("Nie dokonano inicjalizacji objektu ReadWriteDataObject"));
				for(int i=0; i<iSizeFile; i+=iSizeStructData)
				//for(int i=0; i<iSizeStructData; i+=iSizeStructData) //Tymczasowo, odczytywany tylko korzeñ
				{
					ZeroMemory(pDataToOpen, iSizeStructData); //Wyczyszczenie struktury ReadWriteDataObject, do zapisu i odczytu objektów
					pOpenFile->ReadBuffer(pDataToOpen, iSizeStructData);
					//--- Stworzenie objektu
					pGsChildBibleScheme = new GsChildBibleScheme(this, pDataToOpen);
					if(!pGsChildBibleScheme) throw(Exception("Błąd inicjalizacji objektu GsChildBibleScheme"));
					pGsChildBibleScheme->Parent = this;
					//--- Typ objektu: korzeń, lub potomstwo
					if(pDataToOpen->RW_IDListParent == -1) //Korzeñ
					{
						this->_pRootObject = pGsChildBibleScheme;		//To jest korzeń
						this->_pRootObject->Color = ColorObject[enColorNum_Rot]; //Kolor korzenia
            //Tworzenie korzenia drzewa
						TTreeNode *nodeMainRoot = this->_pGsTreeBibleScheme->Items->AddObject(NULL, pGsChildBibleScheme->Caption, nullptr);
						if(!nodeMainRoot) throw(Exception("Błąd inicjalizacji klasy AddObject"));
						pGsChildBibleScheme->_NodeObjectScheme = nodeMainRoot;
					}
					else if(pDataToOpen->RW_IDListParent > -1)//Potomstwo
					{
						//Wyłuskiwanie adresu przodka, po ijego odczytanym indeksie z globalnej listy objektów
						prevGsChildBibleScheme = static_cast<GsChildBibleScheme *>(this->_GsChildBibleSchemeList->Items[pDataToOpen->RW_IDListParent]);
						if(prevGsChildBibleScheme)
						{
							//Ustawienie pól na poprzedni objekt
							pGsChildBibleScheme->_PrevObjectScheme = prevGsChildBibleScheme;
							prevGsChildBibleScheme->_ListChildren->Add(pGsChildBibleScheme); //Dodanie aktualnego objektu, do list potomków, przodka
              //Tworzenie potomków w drzewie
							TTreeNode *childNode = this->_pGsTreeBibleScheme->Items->AddChildObject(prevGsChildBibleScheme->_NodeObjectScheme, pGsChildBibleScheme->Caption, nullptr);
							pGsChildBibleScheme->_NodeObjectScheme = childNode;
						}
					}
					this->_pGsTreeBibleScheme->FullExpand(); //Całkowicie rozwiniete drzewo
					this->_pGsTreeBibleScheme->Items->GetFirstNode()->MakeVisible();
					//---
					pGsChildBibleScheme->Top = pDataToOpen->RW_Top; pGsChildBibleScheme->Left = pDataToOpen->RW_Left;
					pGsChildBibleScheme->Caption = pDataToOpen->RW_AdressVers; //Werset
					pGsChildBibleScheme->_NodeObjectScheme->Text = pGsChildBibleScheme->Caption;
					//Składniki adresu
					pGsChildBibleScheme->_ucBook = pDataToOpen->RW_Book;
					pGsChildBibleScheme->_ucChapt = pDataToOpen->RW_Chapt;
					pGsChildBibleScheme->_ucVers = pDataToOpen->RW_Vers;
					pGsChildBibleScheme->_ucTrans = pDataToOpen->RW_Trans;
					//Podpowiedź w formie zawartości wersetu codeString
					GsReadBibleTextData::GetTextVersOfAdress(pGsChildBibleScheme->_ucBook, pGsChildBibleScheme->_ucChapt+1, pGsChildBibleScheme->_ucVers, pGsChildBibleScheme->_ucTrans, _ustrVers);
					pGsChildBibleScheme->Hint = Format("%s\n\"%s\"", ARRAYOFCONST((pGsChildBibleScheme->Caption, _ustrVers)));

					if(this->_pSelectObject) {this->_pSelectObject->Color = ColorObject[enColorNum_InActive];} //Kolor nieaktywny dlapoprzedniego objektu
					this->_pSelectObject = pGsChildBibleScheme;	//Aktualnie aktywny nowo dodany objekt
					this->_GsChildBibleSchemeList->Add(pGsChildBibleScheme); //Dodanie do g³ównej listy objektów
				}

				//this->Caption = Format("%s. Ilość objektów: %u", ARRAYOFCONST((ustrCaptionWindow, this->_GsChildBibleSchemeList->Count)));
				this->Invalidate(); //Całe odświerzenie
				if(pDataToOpen) {delete pDataToOpen; pDataToOpen = nullptr;}
				if(pOpenFile) {delete pOpenFile; pOpenFile = nullptr;}
				bReturn = true;
			}
		}
		catch(const Exception& e)
		{
			MessageBox(NULL, Format("Błąd otwarcia pliku, do odczytu, o nazwie: %s", ARRAYOFCONST((pOpenDialog->FileName))).c_str(), TEXT("Błąd aplikacji"), MB_OK | MB_ICONERROR | MB_TASKMODAL);
		}
	}
	__finally
	{
		if(pOpenDialog) {delete pOpenDialog; pOpenDialog = nullptr;}
    //Automatycznie zaznaczony pierwszy element w drzewie
		this->_pGsTreeBibleScheme->Selected = this->_pGsTreeBibleScheme->Items->GetFirstNode();
    this->_pGsTreeBibleScheme->Click();
	}
	return bReturn;
}
//---------------------------------------------------------------------------
void __fastcall GsDrawPanelBibleScheme::_SaveProjectObjectToFile()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TFileStream *pSaveFile;//=0;
	PReadWriteDataObject pDataToSave;//=0;
	//---
	TSaveDialog *pSaveDialog = new TSaveDialog(this);
	if(!pSaveDialog) throw(Exception("Błąd inicjalizacji objektu TSaveDialog"));
	pSaveDialog->Title = "Podaj nazwę projektu do zapisu";
	pSaveDialog->Filter =	 "Pliki projektu schematu(*.svp)|*.SVP|Każdy plik (*.*)|*.*"; //Może daĉ do globalnej zmiennej?
	pSaveDialog->Options << ofOverwritePrompt << ofHideReadOnly;
	pSaveDialog->InitialDir = GlobalVar::Global_custrGetExeDir; //Katalog aplikacji
	pSaveDialog->DefaultExt = "svp";

	//---
	try
	{
		try
		{
			if(this->_pRootObject)
			//Jeśli istnieje główny korzeñ
			{
				if(pSaveDialog->Execute())
				{
					pSaveFile = new TFileStream(pSaveDialog->FileName, fmCreate);
					if(!pSaveFile) throw(Exception("Błąd inicjalizacji objektu TFileStream"));
					int iSizeStructData = sizeof(ReadWriteDataObject); //Wielkoĉ struktury
					//Struktura pomocnicza pojedyñczego objektu
					pDataToSave = new ReadWriteDataObject();
					if(!pDataToSave) throw(Exception("Nie dokonano inicjalizacji objektu ReadWriteDataObject"));
					//---
					for(int i=0; i<this->_GsChildBibleSchemeList->Count; i++)
					{
						GsChildBibleScheme *pChild = static_cast<GsChildBibleScheme *>(this->_GsChildBibleSchemeList->Items[i]);
						if(pChild)
						{
							ZeroMemory(pDataToSave, iSizeStructData); //Wyczyszczenie struktury ReadWriteDataObject, do zapisu i odczytu objektów
							//Wypełnienie struktury danych do zapisu
							pDataToSave->RW_ID = pChild->_IDChild; //Numer identyfikacyjny
							pDataToSave->RW_IDList = i;						//Pozycja w globalnej liście objektu _GsChildBibleSchemeList, klasy TList
							pDataToSave->RW_Left = pChild->Left; pDataToSave->RW_Top = pChild->Top; //Wspólrzędne objektu
							pDataToSave->RW_IDListParent = -1;		//Domyślnie objekt nie ma przodka, więc jest korzeniem
							if(pChild->_PrevObjectScheme) //Jeśli objekt posiada przodka, czyli nie jest korzeniem
							{
								//Indeks przodka w głównej liście
								pDataToSave->RW_IDListParent = this->_GsChildBibleSchemeList->IndexOf(pChild->_PrevObjectScheme);
							}
							StringCchCopy(pDataToSave->RW_AdressVers, SIZE_ADDR_VERS-1, pChild->Caption.c_str()); //Skopiowanie adresu wersetu, objektu
							//Składniki adresu
							pDataToSave->RW_Book = pChild->_ucBook;
							pDataToSave->RW_Chapt = pChild->_ucChapt;
							pDataToSave->RW_Vers = pChild->_ucVers;
							pDataToSave->RW_Trans = pChild->_ucTrans;
							pSaveFile->WriteBuffer(pDataToSave, sizeof(ReadWriteDataObject)); //Główny zapis struktury pomocniczej objektu
						}
					}
					if(pDataToSave) {delete pDataToSave; pDataToSave = nullptr;}
					if(pSaveFile) {delete pSaveFile; pSaveFile = nullptr;}
				}
			}
		}
		catch(const Exception& e)
		{
			MessageBox(NULL, Format("Błąd otwarcia pliku, do zapisu, o nazwie: %s", ARRAYOFCONST((pSaveDialog->FileName))).c_str(), TEXT("Błąd aplikacji"), MB_OK | MB_ICONERROR | MB_TASKMODAL);
		}
	}
	__finally
	{
		if(pSaveDialog) {delete pSaveDialog; pSaveDialog = nullptr;}
	}
}
//---------------------------------------------------------------------------
void __fastcall GsDrawPanelBibleScheme::_ViewProjectDocument()
/**
	OPIS METOD(FUNKCJI): Metoda zapisuje projekt jako plik dokumentu rtf
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(this->_GsChildBibleSchemeList->Count==0) return;
	//---
	TStringStream *pStringStream = new TStringStream("", TEncoding::UTF8, true);
	if(!pStringStream) throw(Exception("Błąd inicjalizacji objektu TStringStream"));

	UnicodeString _ustrVers;
	const UnicodeString GlobalHeaderRtf = UnicodeString("{\\urtf1\\ansi\\ansicpg1250\\deff0\\nouicompat\\deflang1045{\\fonttbl{\\f0\\fnil\\fcharset238 Calibri;}{\\f1\\fnil\\fcharset0 Calibri;}}") +
																		 "{\\colortbl ;\\red0\\green0\\blue0;\\red255\\green0\\blue0;\\red255\\green0\\blue255;}" +
																		 "{\\*\\generator Msftedit 5.41.21.2510;}\\viewkind4\\uc1" +
																		 "\\pard\\sa200\\sl276\\slmult1\\cf3\\fs32\\b Dokument projektu, schematu logicznego wersetów, wykonany w aplikacji Moja Biblia NG\\cf0\\b0\\f1\\fs22\\lang21\\par\\fs28",
											//---
											custrAdressVersRtf = "\\f1\\line\\cf2\\b",
											custrVersRtf = "\\cf1\\b0\\f0",
											custrEndVersRtf = "\\cf2\\b\\f1";

	try
	{
		pStringStream->WriteString(GlobalHeaderRtf);
		for(int i=0; i<this->_GsChildBibleSchemeList->Count; i++)
		{
			GsChildBibleScheme *pChild = static_cast<GsChildBibleScheme *>(this->_GsChildBibleSchemeList->Items[i]);
			if(pChild)
			{
				GsReadBibleTextData::GetTextVersOfAdress(pChild->_ucBook, pChild->_ucChapt+1, pChild->_ucVers, pChild->_ucTrans, _ustrVers);
				pStringStream->WriteString(Format("%s %s %s \"%s\" %s" ,ARRAYOFCONST((custrAdressVersRtf, pChild->Caption, custrVersRtf, _ustrVers, custrEndVersRtf))));
			}
		}
		pStringStream->WriteString("}");
		pStringStream->Position = 0;

		//GsMasterBibleScheme *pGsMasterBibleScheme = Gl_pGsMasterBibleScheme;
		GsMasterBibleScheme *pGsMasterBibleScheme = static_cast<GsMasterBibleScheme *>(this->Parent->Parent);
		if(pGsMasterBibleScheme)
		{
			//Wczytanie z objektu TStringStream, do objektu, klasy pGsEditorClass
			pGsMasterBibleScheme->_pGsEditorClass->LoadEditorFromStream(pStringStream);
		}
	}
	__finally
	{
		if(pStringStream) {delete pStringStream; pStringStream = nullptr;}
	}
}
//---------------------------------------------------------------------------
void __fastcall GsDrawPanelBibleScheme::_SetObjectName()
/**
	OPIS METOD(FUNKCJI): Zmiana wersety przypoządkowanego do objektu
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	GsChildBibleScheme *pGsChildBibleScheme = this->_pSelectObject;
	GsScrollBibleScheme *pGsScrollBibleScheme = static_cast<GsScrollBibleScheme *>(this->Parent);
  GsMasterBibleScheme *pGsMasterBibleScheme = nullptr;

	if(pGsScrollBibleScheme)
		{pGsMasterBibleScheme = static_cast<GsMasterBibleScheme *>(pGsScrollBibleScheme->Parent);}


	if(pGsMasterBibleScheme)
	{
		if(pGsChildBibleScheme)
		{
			pGsChildBibleScheme->Caption = pGsMasterBibleScheme->_pGsBarSelectVers->GetSelectVers();
			pGsChildBibleScheme->_NodeObjectScheme->Text = pGsChildBibleScheme->Caption;
			pGsChildBibleScheme->_SListVers->Clear(); //Lista wersetów ze wszystkich tłumaczeń

			pGsMasterBibleScheme->_pGsBarSelectVers->SetSListVers(pGsChildBibleScheme->_SListVers); //Wypełnienie listy wszystkimi tłumaczeniami danego wersetu.
			//Wypelnianie pól adresu wersetu
			pGsMasterBibleScheme->_pGsBarSelectVers->GetSelectAdress(pGsChildBibleScheme->_ucBook, pGsChildBibleScheme->_ucChapt, pGsChildBibleScheme->_ucVers, pGsChildBibleScheme->_ucTrans);
			//Podpowiedź w formie zawartości wersetucodeString
			pGsChildBibleScheme->Hint = Format("%s\n\"%s\"", ARRAYOFCONST((pGsChildBibleScheme->Caption, pGsChildBibleScheme->_SListVers->Strings[pGsChildBibleScheme->_ucTrans])));

			pGsChildBibleScheme->_ViewSelectObject();
		}
	}
}
//---------------------------------------------------------------------------
/****************************************************************************
*								 Główna klasa GsScrollBibleScheme,													*
*												 pochodna TScrollBox.																*
*****************************************************************************/
__fastcall GsScrollBibleScheme::GsScrollBibleScheme(TComponent* Owner) : TScrollBox(Owner)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->Font->Quality = TFontQuality::fqClearType;
	this->DoubleBuffered = true;
	this->HorzScrollBar->Tracking = true;
	this->VertScrollBar->Tracking = true;
	//this->AutoScroll = true;
  //Stworzenie panelu do rysowania połączeń i objektów
	this->_pGsDrawPanelBibleScheme = new GsDrawPanelBibleScheme(this);
	if(!this->_pGsDrawPanelBibleScheme) throw(Exception("Błąd inicjalizacji objektu GsDrawPanelBibleScheme"));
	this->_pGsDrawPanelBibleScheme->Parent = this;
	this->StyleElements = TStyleElements();
}
//---------------------------------------------------------------------------
__fastcall GsScrollBibleScheme::~GsScrollBibleScheme()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{

}
//---------------------------------------------------------------------------
void __fastcall GsScrollBibleScheme::CreateWnd()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TScrollBox::CreateWnd();
	//Własny kod.
	this->_pGsMasterBibleScheme = static_cast<GsMasterBibleScheme *>(this->Parent);
}
//---------------------------------------------------------------------------
void __fastcall GsScrollBibleScheme::DestroyWnd()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//Własny kod.
	TScrollBox::DestroyWnd();
}
//---------------------------------------------------------------------------
void __fastcall GsScrollBibleScheme::MouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->_pGsMasterBibleScheme->_OnNoAccept(this->_pGsMasterBibleScheme);
}
/****************************************************************************
*													Klasa GsMasterBibleScheme,												*
*														pochodna TCustomPanel.													*
*****************************************************************************/
__fastcall GsMasterBibleScheme::GsMasterBibleScheme(TComponent* Owner) : TCustomPanel(Owner)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	Randomize();	//Uruchomienie generatora liczb losowych.
	//---
	this->DoubleBuffered = true;
	this->Font->Quality = TFontQuality::fqClearType;
	this->StyleElements = TStyleElements();
  this->_SListOldConfig = new TStringList(); //Przechowywanie ustawień, podczas uruchomienia okna konfiguracji
	if(!this->_SListOldConfig) throw(Exception("Błąd funkcji TStringList"));
  //--- Zachowanie pierwotnych ustawień z bufora pliku ini, do TStringListy
	GlobalVar::Global_ConfigFile->GetStrings(this->_SListOldConfig);

	ColorObject[enColorNum_Line] = (TColor)GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_SetupsSchemeVers, GlobalVar::GlobalIni_SetSchemeColorLine, clBlue);
	ColorObject[enColorNum_Active] = (TColor)GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_SetupsSchemeVers, GlobalVar::GlobalIni_SetSchemeColorSelect, clAqua);
	ColorObject[enColorNum_InActive] = clCream;
	ColorObject[enColorNum_Rot] = (TColor)GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_SetupsSchemeVers, GlobalVar::GlobalIni_SetSchemeColorRot, clYellow);
	iWidthLine = GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_SetupsSchemeVers, GlobalVar::GlobalIni_SetSchemeWidthLine, 2);
}
//---------------------------------------------------------------------------
__fastcall GsMasterBibleScheme::~GsMasterBibleScheme()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  if(this->_SListOldConfig) {delete this->_SListOldConfig; this->_SListOldConfig = nullptr;} //Przechowywanie ustawień, podczas uruchomienia okna konfiguracji
}
//---------------------------------------------------------------------------
void __fastcall GsMasterBibleScheme::CreateWnd()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TCustomPanel::CreateWnd();
	//Własny kod
	this->_pGsBarSelectVers = new GsBarSelectVers(this);
	if(!this->_pGsBarSelectVers) throw(Exception("Błąd inicjalizacji objektu GsBarSelectVers"));
	this->_pGsBarSelectVers->Parent = this;
	this->_pGsBarSelectVers->Align = alTop;
	//Utworzenie objektu, klasy do scrollowania i stworzenie panelu do rysowania połączeń i objektów, który
	//znajduje sie na objekcie this->_pGsBarSelectVers
	this->_pGsScrollBibleScheme = new GsScrollBibleScheme(this);
	if(!this->_pGsScrollBibleScheme) throw(Exception("Błąd inicjalizacji objektu GsScrollBibleScheme"));
	this->_pGsScrollBibleScheme->Parent = this;
	this->_pGsScrollBibleScheme->Align = alClient;
	//---
	this->_pGsDrawPanelBibleScheme = this->_pGsScrollBibleScheme->_pGsDrawPanelBibleScheme;
	//---
	this->_pSplitter = new TSplitter(this);
	if(!this->_pSplitter) throw(Exception("Błąd inicjalizacji objektu TSplitter"));
	this->_pSplitter->Parent = this;
	this->_pSplitter->Align = alBottom;
	this->_pSplitter->Color = clCream;
	this->_pSplitter->Height = 6;
	this->_pSplitter->Beveled = true;
	//---
	this->_pVersDisplayText = new TLabel(this); //Wyświetlenie wybranego wersetu
	if(!this->_pVersDisplayText) throw(Exception("Błąd inicjalizacji objektu TLabel"));
	this->_pVersDisplayText->Parent = this;
	this->_pVersDisplayText->Align = alBottom;
	this->_pVersDisplayText->Color = clCream;
	this->_pVersDisplayText->AutoSize = true;
	this->_pVersDisplayText->WordWrap = true;
	this->_pVersDisplayText->Font->Color = clGreen;
	this->_pVersDisplayText->Font->Style = TFontStyles() << fsBold;
	this->_pVersDisplayText->Font->Size = 11;
	this->_pVersDisplayText->Caption = "Tu bedzie sie pojawiał tekst objektu z wersetem biblijnym";
	//---
	this->_pGsEditorClass = new GsEditorClass(this);
	if(!this->_pGsEditorClass) throw(Exception("Błąd inicjalizacji objektu GsEditorClass"));
	this->_pGsEditorClass->Parent = this;
	this->_pGsEditorClass->Align = alBottom;
	this->_pGsEditorClass->Height = this->Parent->Height / 4;
	//Wskaźnika na drzewo zależnosci
	this->_pGsTreeBibleScheme = new GsTreeBibleScheme(this);
	if(!this->_pGsTreeBibleScheme) throw(Exception("Błąd inicjalizacji objektu GsTreeBibleScheme"));
	this->_pGsTreeBibleScheme->Parent = this;
	this->_pGsTreeBibleScheme->Align = alLeft;
	this->_pGsTreeBibleScheme->Width = 200;

	this->_pGsDrawPanelBibleScheme->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall GsMasterBibleScheme::DestroyWnd()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//Własny kod.
	TCustomPanel::DestroyWnd();
}
//---------------------------------------------------------------------------
void __fastcall GsMasterBibleScheme::OpenSetupsScheme(TWinControl *pWinControl, TAction *pAction, int iLeft, int iTop)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(pWinControl)
	{
		TPanel *pPanel=nullptr;
		TLabel *pLabel=nullptr;
		this->_pAction = pAction;

		this->_pPanelSetups = new TPanel(this);
		if(!this->_pPanelSetups) throw(Exception("Błąd inicjalizacji objektu TPanel"));
		this->_pPanelSetups->Parent = pWinControl;
		this->_pPanelSetups->Top = iTop; this->_pPanelSetups->Left = iLeft;
		this->_pPanelSetups->Width = 200; this->_pPanelSetups->Height = 280;
		this->_pPanelSetups->Visible = false;

		TPanel *pPanelButtons = new TPanel(this->_pPanelSetups);
		if(!pPanelButtons) throw(Exception("Błąd inicjalizacji objektu TPanel"));
		pPanelButtons->Parent = this->_pPanelSetups;
		pPanelButtons->Align = alBottom;
		pPanelButtons->AlignWithMargins = true;

		TButton *pButtonSave = new TButton(pPanelButtons);
		if(!pButtonSave) throw(Exception("Błąd inicjalizacji objektu TPanel"));
		pButtonSave->Parent = pPanelButtons;
		pButtonSave->Align = alLeft;
		pButtonSave->AlignWithMargins = true;
    pButtonSave->Width = 100;
		pButtonSave->Margins->Left = 6; pButtonSave->Margins->Top = 6;
		pButtonSave->Margins->Bottom = 6;
		pButtonSave->Caption = "Zapisz ustawienia";
		pButtonSave->OnClick = this->_OnAccept;

		TButton *pButtonExit = new TButton(pPanelButtons);
		if(!pButtonExit) throw(Exception("Błąd inicjalizacji objektu TPanel"));
		pButtonExit->Parent = pPanelButtons;
		pButtonExit->Align = alRight;
		pButtonExit->AlignWithMargins = true;
		pButtonExit->Width = 70;
		pButtonExit->Margins->Right = 6; pButtonExit->Margins->Top = 6;
		pButtonExit->Margins->Bottom = 6;
		pButtonExit->Caption = "Anuluj";
		pButtonExit->OnClick = this->_OnNoAccept;
		//Kolor zaznaczonego wersetu
    pPanel = new TPanel(this->_pPanelSetups);
		if(!pPanel) throw(Exception("Błąd inicjalizacji objektu TPanel"));
		pPanel->Parent = this->_pPanelSetups;
		pPanel->Align = alTop;
		pPanel->AlignWithMargins = true;
		pPanel->AutoSize = true;

		pLabel =  new TLabel(pPanel);
		if(!pLabel) throw(Exception("Błąd inicjalizacji objektu TLabel"));
		pLabel->Parent = pPanel;
		pLabel->Align = alTop;
		pLabel->AlignWithMargins = true;
		pLabel->Caption = "Kolor zaznaczonego wersetu";

		this->_pCBSelect = new TColorBox(pPanel);
		if(!this->_pCBSelect) throw(Exception("Błąd inicjalizacji objektu TColorBox"));
		this->_pCBSelect->Parent = pPanel;
		this->_pCBSelect->Align = alTop;
		this->_pCBSelect->AlignWithMargins = true;
		this->_pCBSelect->OnGetColors = this->_ColorBoxGetColors;
		this->_pCBSelect->Style = TColorBoxStyle() << cbStandardColors << cbExtendedColors << cbPrettyNames << cbCustomColors;

		//Kontrolki koloru głównego wersetu
		pPanel = new TPanel(this->_pPanelSetups);
		if(!pPanel) throw(Exception("Błąd inicjalizacji objektu TPanel"));
		pPanel->Parent = this->_pPanelSetups;
		pPanel->Align = alTop;
		pPanel->AlignWithMargins = true;
		pPanel->AutoSize = true;

		pLabel = new TLabel(pPanel);
		if(!pLabel) throw(Exception("Błąd inicjalizacji objektu TLabel"));
		pLabel->Parent = pPanel;
		pLabel->Align = alTop;
		pLabel->AlignWithMargins = true;
		pLabel->Caption = "Kolor głownego wersetu";

		this->_pCBRoot = new TColorBox(pPanel);
		if(!this->_pCBRoot) throw(Exception("Błąd inicjalizacji objektu TColorBox"));
		this->_pCBRoot->Parent = pPanel;
		this->_pCBRoot->Align = alTop;
		this->_pCBRoot->AlignWithMargins = true;
		this->_pCBRoot->OnGetColors = this->_ColorBoxGetColors;
		this->_pCBRoot->Style = TColorBoxStyle() << cbStandardColors << cbExtendedColors << cbPrettyNames << cbCustomColors;
		//Kontrolki koloru lini
		pPanel = new TPanel(this->_pPanelSetups);
		if(!pPanel) throw(Exception("Błąd inicjalizacji objektu TPanel"));
		pPanel->Parent = this->_pPanelSetups;
		pPanel->Align = alTop;
		pPanel->AlignWithMargins = true;
		pPanel->AutoSize = true;

		pLabel =  new TLabel(pPanel);
		if(!pLabel) throw(Exception("Błąd inicjalizacji objektu TLabel"));
		pLabel->Parent = pPanel;
		pLabel->Align = alTop;
		pLabel->AlignWithMargins = true;
		pLabel->Caption = "Kolor lini na wykresie";

		this->_pCBLine = new TColorBox(pPanel);
		if(!this->_pCBLine) throw(Exception("Błąd inicjalizacji objektu TColorBox"));
		this->_pCBLine->Parent = pPanel;
		this->_pCBLine->Align = alTop;
		this->_pCBLine->AlignWithMargins = true;
		this->_pCBLine->OnGetColors = this->_ColorBoxGetColors;
		this->_pCBLine->Style = TColorBoxStyle() << cbStandardColors << cbExtendedColors << cbPrettyNames << cbCustomColors;
		//Kontrolki ustwiania szerokości lini
    pPanel = new TPanel(this->_pPanelSetups);
		if(!pPanel) throw(Exception("Błąd inicjalizacji objektu TPanel"));
		pPanel->Parent = this->_pPanelSetups;
		pPanel->Align = alTop;
		pPanel->AlignWithMargins = true;
		pPanel->AutoSize = true;

    pLabel =  new TLabel(pPanel);
		if(!pLabel) throw(Exception("Błąd inicjalizacji objektu TLabel"));
		pLabel->Parent = pPanel;
		pLabel->Align = alTop;
		pLabel->AlignWithMargins = true;
		pLabel->Caption = "Szerokość lini";

		this->_pSpinEdit = new TSpinEdit(pPanel);
		if(!this->_pSpinEdit) throw(Exception("Błąd inicjalizacji objektu TSpinEdit"));
		this->_pSpinEdit->Parent = pPanel;
		this->_pSpinEdit->Align = alTop;
		this->_pSpinEdit->AlignWithMargins = true;
		this->_pSpinEdit->MinValue = 1;
    this->_pSpinEdit->MaxValue = 6;

		//Odczyt konfiguracji
		this->_pCBLine->Selected = ColorObject[enColorNum_Line];
		this->_pCBRoot->Selected = ColorObject[enColorNum_Rot];
		this->_pCBSelect->Selected = ColorObject[enColorNum_Active];
		this->_pSpinEdit->Value = iWidthLine;
	}
}
//---------------------------------------------------------------------------
void __fastcall GsMasterBibleScheme::VisibleSetupsScheme(bool bVisible)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(this->_pPanelSetups) this->_pPanelSetups->Visible = bVisible;
}
//---------------------------------------------------------------------------
void __fastcall GsMasterBibleScheme::_OnAccept(System::TObject* Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//Zapis konfiguracji
	ColorObject[enColorNum_Line] = this->_pCBLine->Selected;
	ColorObject[enColorNum_Active] = this->_pCBSelect->Selected;
	ColorObject[enColorNum_Rot] = this->_pCBRoot->Selected;
	iWidthLine = this->_pSpinEdit->Value;

	GlobalVar::Global_ConfigFile->WriteInteger(GlobalVar::GlobalIni_SetupsSchemeVers, GlobalVar::GlobalIni_SetSchemeColorLine, this->_pCBLine->Selected);
	GlobalVar::Global_ConfigFile->WriteInteger(GlobalVar::GlobalIni_SetupsSchemeVers, GlobalVar::GlobalIni_SetSchemeColorRot, this->_pCBRoot->Selected);
	GlobalVar::Global_ConfigFile->WriteInteger(GlobalVar::GlobalIni_SetupsSchemeVers, GlobalVar::GlobalIni_SetSchemeColorSelect, this->_pCBSelect->Selected);
	GlobalVar::Global_ConfigFile->WriteInteger(GlobalVar::GlobalIni_SetupsSchemeVers, GlobalVar::GlobalIni_SetSchemeWidthLine, this->_pSpinEdit->Value);

	this->_pAction->Checked = false;
	this->VisibleSetupsScheme(false);
  this->_pGsDrawPanelBibleScheme->Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall GsMasterBibleScheme::_OnNoAccept(System::TObject* Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  this->_pAction->Checked = false;
	this->VisibleSetupsScheme(false);
	//Odczytanie starych ustawień do bufora, pliku ini, z TStringListy
	GlobalVar::Global_ConfigFile->SetStrings(this->_SListOldConfig);
}
//---------------------------------------------------------------------------
TWinControl * __fastcall GsMasterBibleScheme::FGetSelectObject()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TWinControl *pRet = nullptr;

	pRet = this->_pGsDrawPanelBibleScheme->_pSelectObject;

	return pRet;
}
//---------------------------------------------------------------------------
void __fastcall GsMasterBibleScheme::_ColorBoxGetColors(TCustomColorBox *Sender, TStrings *Items)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	Items->AddStrings(GlobalVar::Global_ItemsColor);
}
//---------------------------------------------------------------------------
/****************************************************************************
*													Klasa GsTreeBibleScheme,													*
*														pochodna TCustomTreeView.												*
*****************************************************************************/
__fastcall GsTreeBibleScheme::GsTreeBibleScheme(TComponent* Owner) : TCustomTreeView(Owner)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  this->DoubleBuffered = true;
	this->Font->Quality = TFontQuality::fqClearType;
	this->StyleElements = TStyleElements();
	this->ReadOnly = true;
  this->Color = clCream;
}
//---------------------------------------------------------------------------
__fastcall GsTreeBibleScheme::~GsTreeBibleScheme()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{

}
//---------------------------------------------------------------------------
void __fastcall GsTreeBibleScheme::CreateWnd()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TIcon *pIcon=nullptr;
	TMemoryStream *pMemoryStr=nullptr;

	TCustomTreeView::CreateWnd();
	//Własny kod
	this->_pImageList = new TImageList(this);
	if(!this->_pImageList) throw(Exception("Błąd inicjalizacji objektu TImage"));
	this->_pImageList->ColorDepth = cd32Bit;		 //Głębia kolorów przyszłych obrazków
	this->_pImageList->DrawingStyle = dsTransparent;

	try
	{
    pIcon = new TIcon();
		if(!pIcon) throw(Exception("Błąd metody TIcon"));
		pMemoryStr = new TMemoryStream();
		if(!pMemoryStr) throw(Exception("Błąd metody TMemoryStream"));
		//--0--
    pMemoryStr->WriteBuffer(chDataImageNodes, ARRAYSIZE(chDataImageNodes)); //Zapis do strumienia danych
		pMemoryStr->Position = 0;															//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);										//Wczytanie danych ze strumienia do objektu, klasy TIcon
		this->_pImageList->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();

		this->Images = this->_pImageList;
	}
	__finally
	{
    //--- Zwolnienie objektu, klasy TIcon i TMemoryStream
		if(pIcon) {delete pIcon; pIcon = nullptr;}
		if(pMemoryStr) {delete pMemoryStr; pMemoryStr = nullptr;}
  }
}
//---------------------------------------------------------------------------
void __fastcall GsTreeBibleScheme::DestroyWnd()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  //Własny kod.
	TCustomTreeView::DestroyWnd();
}
//---------------------------------------------------------------------------
void __fastcall GsTreeBibleScheme::Click()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	GsChildBibleScheme *pGsChildBibleScheme=nullptr;
	TList *pList=nullptr;
	GsMasterBibleScheme *pGsMasterBibleScheme = static_cast<GsMasterBibleScheme *>(this->Parent);
	GsDrawPanelBibleScheme *pGsDrawPanelBibleScheme = pGsMasterBibleScheme->_pGsDrawPanelBibleScheme;

	TTreeNode *pNode = this->Selected; //Wybrany węzeł
	if(pNode)
	{
		//Wyłuskany wskaźnik na objekt, klasy GsDrawPanelBibleScheme
		if(pGsDrawPanelBibleScheme)
		{
			pList = pGsDrawPanelBibleScheme->_GsChildBibleSchemeList; //Lista wszystkich objektów, klasy GsChildBibleScheme

			for(int i=0; i<pList->Count; i++)
			{
				pGsChildBibleScheme = static_cast<GsChildBibleScheme *>(pList->Items[i]);

				if(pGsDrawPanelBibleScheme->_pRootObject == pGsChildBibleScheme)
					pGsChildBibleScheme->Color = ColorObject[enColorNum_Rot];
				else pGsChildBibleScheme->Color = ColorObject[enColorNum_InActive];

				//Wyłuskanie zaznaczonej pozycji z drzewa
				if(pGsChildBibleScheme->_NodeObjectScheme == pNode)
				{
					pGsDrawPanelBibleScheme->_pSelectObject = pGsChildBibleScheme; //Ustawienie aktualnego objektu
					pGsChildBibleScheme->Color = ColorObject[enColorNum_Active]; //Aktywizacja objektu
					//Wyświetlenie zawartości wersetu zaznaczonego w drzewie
					pGsChildBibleScheme->_ViewSelectObject();
				}
      }
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall GsTreeBibleScheme::MouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	GsMasterBibleScheme *pGsMasterBibleScheme = static_cast<GsMasterBibleScheme *>(this->Parent);
	if(pGsMasterBibleScheme)
		{pGsMasterBibleScheme->_OnNoAccept(pGsMasterBibleScheme);}
}
//---------------------------------------------------------------------------
void __fastcall GsTreeBibleScheme::KeyUp(System::Word &Key, System::Classes::TShiftState Shift)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TTreeNode *pSelected = this->Selected;
	if(pSelected)
	{
		this->Click();
  }
}
//---------------------------------------------------------------------------
void __fastcall GsTreeBibleScheme::GetImageIndex(TTreeNode* Node)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  //--- Przyporządkowanie grafik, korzeniu i gałęziom drzewa ksiąg biblijnych
	Node->ImageIndex = 0;
	Node->SelectedIndex = 0;
}
//---------------------------------------------------------------------------

