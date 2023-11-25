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

static GsDrawPanelBibleScheme *Gl_pDrawPanelScheme=nullptr; //Objekt klasy GsDrawPanelBibleScheme, na którym objekt jest rysowany
static GsScrollBibleScheme *Gl_pGsScrollBibleScheme=nullptr; //Objekt, klasy GsScrollBibleScheme
static GsMasterBibleScheme *Gl_pGsMasterBibleScheme=nullptr; //Główny objekt klasy GsMasterBibleScheme
static GsTreeBibleScheme *Gl_pGsTreeBibleScheme=nullptr;  //Klasa drzewa
static GsBarSelectVers *Gl_pGsBarSelectVers=nullptr;
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
	this->ListChildren = new TList();
	if(!this->ListChildren) throw(Exception("Nie dokonano inicjalizacji objektu TList"));
	//---
	this->Font->Quality = TFontQuality::fqClearType;
	this->StyleElements = TStyleElements();
	this->SListVers = new THashedStringList(); //Lista wersetów ze wszystkich tłumaczeñ
	if(!this->SListVers) throw(Exception("Nie dokonano inicjalizacji objektu THashedStringList"));
	//---
	this->DoubleBuffered = true;
	this->ParentColor = false;
	this->ParentBackground = false;
	this->ParentCtl3D = false;
	this->BevelOuter = bvNone;
	this->BorderStyle = bsSingle;
	this->Color = ColorObject[enColorNum_Active];
	this->Ctl3D = false;
	this->ParentObjectScheme = nullptr; //Wskaźnik na przodka, domyślnie to korzeń
	this->ShowHint = true;
	this->StyleElements = TStyleElements();
	if(_PReadWriteDataObject) this->IDChild = _PReadWriteDataObject->RW_ID; else this->IDChild = Random(INT_MAX);
	//this->ID64Child = (__int64)this->IDChild * (__int64)Random(INT_MAX);
	this->Level = 0; //Poziom
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
	for(int i=0; i<this->ListChildren->Count; i++)
	//Kasowanie wszystkich potomków
	{
		GsChildBibleScheme *pGsChildBibleScheme = static_cast<GsChildBibleScheme *>(this->ListChildren->Items[i]);
		if(pGsChildBibleScheme)
		{
			//Kasowanie potomka z listy głównej
			iIndex = this->DrawPanelScheme->_GsChildBibleSchemeList->IndexOf(pGsChildBibleScheme);
			if(iIndex > -1) this->DrawPanelScheme->_GsChildBibleSchemeList->Delete(iIndex);
			//Wlaściwe kasowanie potomka
			delete pGsChildBibleScheme; pGsChildBibleScheme = nullptr;
		}
	}
	delete this->ListChildren; this->ListChildren = nullptr; //Kasowanie listy potomków, po ich usunięciu
	//Kasowanie objektu z listy głównej
	iIndex = this->DrawPanelScheme->_GsChildBibleSchemeList->IndexOf(this);
	if(iIndex > -1) this->DrawPanelScheme->_GsChildBibleSchemeList->Delete(iIndex);

	if(this->SListVers) {delete this->SListVers; this->SListVers = nullptr;} //Lista wersetów ze wszystkich tłumaczeñ
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
	this->DrawPanelScheme = Gl_pDrawPanelScheme;
	//Wyłuskanie na objekt, klasy TScrollBox
	this->pGsScrollBibleScheme = Gl_pGsScrollBibleScheme;
	//Wyłuskanie wskaźnika na główny objekt, klasy
	this->pGsMasterBibleScheme = Gl_pGsMasterBibleScheme;
	//---
	this->Caption = this->pGsMasterBibleScheme->_pGsBarSelectVers->GetSelectVers();
	this->Width = this->Canvas->TextWidth(this->Caption) + 4;
	this->Height = this->Canvas->TextHeight(this->Caption) + 4;
	this->pGsMasterBibleScheme->_pGsBarSelectVers->SetSListVers(this->SListVers); //Wypełnienie listy wszystkimi tłumaczeniami danego wersetu.
	//Wypelnianie pól adresu wersetu
	this->pGsMasterBibleScheme->_pGsBarSelectVers->GetSelectAdress(this->ucBook, this->ucChapt, this->ucVers, this->ucTrans);
	//Podpowiedź w formie zawartości wersetucodeString
	this->Hint = Format("%s\n\"%s\"", ARRAYOFCONST((this->Caption, this->SListVers->Strings[this->ucTrans])));
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
		this->GetStartX = X;
		this->GetStartY = Y;
		this->StartMove = true;
		if(this->DrawPanelScheme->_pSelectObject != this)
		{
			this->DrawPanelScheme->_pSelectObject->Color = ColorObject[enColorNum_InActive]; //Dezaktywacja poprzedniego objektu
			this->DrawPanelScheme->_pSelectObject = this;						//Objekt kliknięty, staje się aktualny
			if(this->DrawPanelScheme->_pRootObject == this)
				this->DrawPanelScheme->_pSelectObject->Color = ColorObject[enColorNum_Rot];	 //Zmiana koloru tła aktualnego objektu
			else this->DrawPanelScheme->_pSelectObject->Color = ColorObject[enColorNum_Active];	 //Zmiana koloru tła , aktualnego objektu
		}
		this->DrawPanelScheme->_pRootObject->Color = ColorObject[enColorNum_Rot];
		this->ViewSelectObject();
	 	this->SelectTreeObject();
	}
}
//---------------------------------------------------------------------------
void __fastcall GsChildBibleScheme::ViewSelectObject()
/**
	OPIS METOD(FUNKCJI): Wyświetlenie wersetu wybranego objektu
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	UnicodeString _ustrVers;
	GsReadBibleTextData::GetTextVersOfAdress(this->ucBook, this->ucChapt+1, this->ucVers, this->ucTrans, _ustrVers);
	this->pGsMasterBibleScheme->_pVersDisplayText->Caption = Format("%s \"%s\"", ARRAYOFCONST((this->Caption, _ustrVers))); //Wybrany werset
}
//---------------------------------------------------------------------------
void __fastcall GsChildBibleScheme::SelectTreeObject()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	GsTreeBibleScheme *pGsTreeBibleScheme = dynamic_cast<GsTreeBibleScheme *>(this->_node->TreeView);
	if(!pGsTreeBibleScheme) throw(Exception("Błąd wyłuskania objektu, klasy GsTreeBibleScheme"));
	this->_node->Selected = true;
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
	this->StartMove = false; //Koniec przesuwania
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
	if(!this->ParentObjectScheme) return; //Nie przesuwaj korzenia
	if(this->StartMove)
	{
		this->Left += (X - this->GetStartX);
		this->Top += (Y - this->GetStartY);
		//--- Odświerzenie głównego okna, w celu odrysowania wszystkich objektów
		//this->DrawPanelScheme->Repaint();
		this->DrawPanelScheme->Invalidate();
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
	this->_pGsTreeBibleScheme = Gl_pGsTreeBibleScheme;
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
	GsChildBibleScheme *pGsChildBibleScheme=nullptr, *pParentGsChildBibleScheme=nullptr;
	for(int i=0; i<this->_GsChildBibleSchemeList->Count; i++)
	{
		pGsChildBibleScheme = static_cast<GsChildBibleScheme *>(this->_GsChildBibleSchemeList->Items[i]);
		if(!pGsChildBibleScheme) throw(Exception("Błąd wyłuskania objektu, klasy GsChildBibleScheme"));
		pParentGsChildBibleScheme = pGsChildBibleScheme->ParentObjectScheme;
		//--- Odrysowanie objektu i połączen
		if(pParentGsChildBibleScheme && pGsChildBibleScheme->DrawPanelScheme)
		{
      //Rysowanie połączenia z przodkiem
			this->Canvas->Pen->Width = iWidthLine;
			this->Canvas->Pen->Color = ColorObject[enColorNum_Line];
			this->Canvas->MoveTo(pGsChildBibleScheme->Left + (pGsChildBibleScheme->Width / 2), pGsChildBibleScheme->Top);
			this->Canvas->LineTo(pParentGsChildBibleScheme->Left + (pParentGsChildBibleScheme->Width / 2),
				pParentGsChildBibleScheme->Top + pParentGsChildBibleScheme->Height);
		}
	}
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
	int left=0, top=100;

	GsChildBibleScheme *pGsChildBibleScheme=nullptr, *prevGsChildBibleScheme=nullptr; //Domyślnie to korzeń

	pGsChildBibleScheme = new GsChildBibleScheme(this);
	if(!pGsChildBibleScheme) throw(Exception("Błąd inicjalizacji objektu GsChildBibleScheme"));
	pGsChildBibleScheme->Parent = this;

	if(this->_GsChildBibleSchemeList->Count > 0) //Tylko jeden korzeń!
	{
		//if(this->_pRootObject) this->_pRootObject->Color = ColorObject[enColorNum_Rot];
		prevGsChildBibleScheme = this->_pSelectObject;
		//Ustawienie pól na poprzedni objekt
		pGsChildBibleScheme->ParentObjectScheme = prevGsChildBibleScheme;
		prevGsChildBibleScheme->ListChildren->Add(pGsChildBibleScheme); //Dodanie aktualnego objektu, do list potomków, przodka
		pGsChildBibleScheme->Level = prevGsChildBibleScheme->Level + 1;

		left = prevGsChildBibleScheme->Left + 10; top = prevGsChildBibleScheme->Top + prevGsChildBibleScheme->Height + 16;
		//Tworzenie potomków w drzewie
		TTreeNode *childNode = this->_pGsTreeBibleScheme->Items->AddChildObject(prevGsChildBibleScheme->_node, pGsChildBibleScheme->Caption, nullptr);
		pGsChildBibleScheme->_node = childNode;
	}
	else //Dodawanie korzenia
	{
		this->_pRootObject = pGsChildBibleScheme;		//Okno głównego korzenia
		this->_pRootObject->Color = ColorObject[enColorNum_Rot];
		//Tworzenie korzenia drzewa
		TTreeNode *nodeMainRoot = this->_pGsTreeBibleScheme->Items->AddObject(NULL, pGsChildBibleScheme->Caption, nullptr);
		if(!nodeMainRoot) throw(Exception("Błąd inicjalizacji klasy AddObject"));
		pGsChildBibleScheme->_node = nodeMainRoot;
	}
	//
	this->_pGsTreeBibleScheme->FullExpand(); //Całkowicie rozwiniete drzewo
	this->_pGsTreeBibleScheme->Items->GetFirstNode()->MakeVisible();

	pGsChildBibleScheme->Top = top; pGsChildBibleScheme->Left = left;
	if(this->_pSelectObject) {this->_pSelectObject->Color = ColorObject[enColorNum_InActive];} //Kolor nieaktywny dla poprzedniego objektu
	this->_pSelectObject = pGsChildBibleScheme;	//Aktualnie aktywny nowo dodany objekt
  pGsChildBibleScheme->ViewSelectObject();

	this->_GsChildBibleSchemeList->Add(pGsChildBibleScheme); //Dodanie do głównej listy objektów
	//this->Caption = Format("%s. Ilość objektów: %u", ARRAYOFCONST((ustrCaptionWindow, this->_GsChildBibleSchemeList->Count)));
	//this->ActDeleteLink->Enabled = true;
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

		TTreeNode *_pNode = this->_pSelectObject->_node;
		GsTreeBibleScheme *pTrView = static_cast<GsTreeBibleScheme *>(_pNode->TreeView);

		if(this->_pSelectObject!=this->_pRootObject)
		//Nie jest korzeniem i posiada przodków
		{
			GsChildBibleScheme *pParent = this->_pSelectObject->ParentObjectScheme;
			if(pParent)
			{
				int iIndexParent = pParent->ListChildren->IndexOf(this->_pSelectObject);
				if(iIndexParent > -1)
				{
					//Kasowanie objektu z listy przodka
					pParent->ListChildren->Delete(iIndexParent);
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
						pGsChildBibleScheme->_node = nodeMainRoot;
					}
					else if(pDataToOpen->RW_IDListParent > -1)//Potomstwo
					{
						//Wyłuskiwanie adresu przodka, po ijego odczytanym indeksie z globalnej listy objektów
						prevGsChildBibleScheme = static_cast<GsChildBibleScheme *>(this->_GsChildBibleSchemeList->Items[pDataToOpen->RW_IDListParent]);
						if(prevGsChildBibleScheme)
						{
							//Ustawienie pól na poprzedni objekt
							pGsChildBibleScheme->ParentObjectScheme = prevGsChildBibleScheme;
							prevGsChildBibleScheme->ListChildren->Add(pGsChildBibleScheme); //Dodanie aktualnego objektu, do list potomków, przodka
              //Tworzenie potomków w drzewie
							TTreeNode *childNode = this->_pGsTreeBibleScheme->Items->AddChildObject(prevGsChildBibleScheme->_node, pGsChildBibleScheme->Caption, nullptr);
							pGsChildBibleScheme->_node = childNode;
						}
					}
					this->_pGsTreeBibleScheme->FullExpand(); //Całkowicie rozwiniete drzewo
					this->_pGsTreeBibleScheme->Items->GetFirstNode()->MakeVisible();
					//---
					pGsChildBibleScheme->Top = pDataToOpen->RW_Top; pGsChildBibleScheme->Left = pDataToOpen->RW_Left;
					pGsChildBibleScheme->Caption = pDataToOpen->RW_AdressVers; //Werset
					pGsChildBibleScheme->_node->Text = pGsChildBibleScheme->Caption;
					//Składniki adresu
					pGsChildBibleScheme->ucBook = pDataToOpen->RW_Book;
					pGsChildBibleScheme->ucChapt = pDataToOpen->RW_Chapt;
					pGsChildBibleScheme->ucVers = pDataToOpen->RW_Vers;
					pGsChildBibleScheme->ucTrans = pDataToOpen->RW_Trans;
					//Podpowiedź w formie zawartości wersetu codeString
					GsReadBibleTextData::GetTextVersOfAdress(pGsChildBibleScheme->ucBook, pGsChildBibleScheme->ucChapt+1, pGsChildBibleScheme->ucVers, pGsChildBibleScheme->ucTrans, _ustrVers);
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
		//this->ActDeleteLink->Enabled = true;
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
							pDataToSave->RW_ID = pChild->IDChild; //Numer identyfikacyjny
							pDataToSave->RW_IDList = i;						//Pozycja w globalnej liście objektu _GsChildBibleSchemeList, klasy TList
							pDataToSave->RW_Left = pChild->Left; pDataToSave->RW_Top = pChild->Top; //Wspólrzędne objektu
							pDataToSave->RW_IDListParent = -1;		//Domyślnie objekt nie ma przodka, więc jest korzeniem
							if(pChild->ParentObjectScheme) //Jeśli objekt posiada przodka, czyli nie jest korzeniem
							{
								//Indeks przodka w głównej liście
								pDataToSave->RW_IDListParent = this->_GsChildBibleSchemeList->IndexOf(pChild->ParentObjectScheme);
							}
							StringCchCopy(pDataToSave->RW_AdressVers, SIZE_ADDR_VERS-1, pChild->Caption.c_str()); //Skopiowanie adresu wersetu, objektu
							//Składniki adresu
							pDataToSave->RW_Book = pChild->ucBook;
							pDataToSave->RW_Chapt = pChild->ucChapt;
							pDataToSave->RW_Vers = pChild->ucVers;
							pDataToSave->RW_Trans = pChild->ucTrans;
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
				GsReadBibleTextData::GetTextVersOfAdress(pChild->ucBook, pChild->ucChapt+1, pChild->ucVers, pChild->ucTrans, _ustrVers);
				pStringStream->WriteString(Format("%s %s %s \"%s\" %s" ,ARRAYOFCONST((custrAdressVersRtf, pChild->Caption, custrVersRtf, _ustrVers, custrEndVersRtf))));
			}
		}
		pStringStream->WriteString("}");
		pStringStream->Position = 0;

		GsMasterBibleScheme *pGsMasterBibleScheme = Gl_pGsMasterBibleScheme;
		if(pGsMasterBibleScheme)
		{
			//Wczytanie z objektu TStringStream, do objektu, klasy pGsEditorClass
			pGsMasterBibleScheme->pGsEditorClass->LoadEditorFromStream(pStringStream);
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

	if(Gl_pGsScrollBibleScheme)
	{
		if(Gl_pGsMasterBibleScheme)
		{
			if(pGsChildBibleScheme)
			{
				pGsChildBibleScheme->Caption = Gl_pGsBarSelectVers->GetSelectVers();
				pGsChildBibleScheme->_node->Text = pGsChildBibleScheme->Caption;
				pGsChildBibleScheme->SListVers->Clear(); //Lista wersetów ze wszystkich tłumaczeń
				Gl_pGsBarSelectVers->SetSListVers(pGsChildBibleScheme->SListVers); //Wypełnienie listy wszystkimi tłumaczeniami danego wersetu.
				//Wypelnianie pól adresu wersetu
				Gl_pGsBarSelectVers->GetSelectAdress(pGsChildBibleScheme->ucBook, pGsChildBibleScheme->ucChapt, pGsChildBibleScheme->ucVers, pGsChildBibleScheme->ucTrans);
        //Podpowiedź w formie zawartości wersetucodeString
				pGsChildBibleScheme->Hint = Format("%s\n\"%s\"", ARRAYOFCONST((pGsChildBibleScheme->Caption, pGsChildBibleScheme->SListVers->Strings[pGsChildBibleScheme->ucTrans])));

				pGsChildBibleScheme->ViewSelectObject();
			}
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
	Gl_pGsMasterBibleScheme = this; //Główny objekt klasy GsMasterBibleScheme.
	this->_pGsBarSelectVers = new GsBarSelectVers(this);
	if(!this->_pGsBarSelectVers) throw(Exception("Błąd inicjalizacji objektu GsBarSelectVers"));
	this->_pGsBarSelectVers->Parent = this;
	this->_pGsBarSelectVers->Align = alTop;
	Gl_pGsBarSelectVers = this->_pGsBarSelectVers;
	//Utworzenie objektu, klasy do scrollowania i stworzenie panelu do rysowania połączeń i objektów, który
	//znajduje sie na objekcie this->_pGsBarSelectVers
	this->_pGsScrollBibleScheme = new GsScrollBibleScheme(this);
	if(!this->_pGsScrollBibleScheme) throw(Exception("Błąd inicjalizacji objektu GsScrollBibleScheme"));
	this->_pGsScrollBibleScheme->Parent = this;
	this->_pGsScrollBibleScheme->Align = alClient;
	Gl_pGsScrollBibleScheme = this->_pGsScrollBibleScheme; //Objekt, klasy GsScrollBibleScheme
	//---
	this->_pGsDrawPanelBibleScheme = this->_pGsScrollBibleScheme->_pGsDrawPanelBibleScheme;
	Gl_pDrawPanelScheme = this->_pGsScrollBibleScheme->_pGsDrawPanelBibleScheme; //Objekt klasy GsDrawPanelBibleScheme, na którym objekt jest rysowany
	//---
	this->pSplitter = new TSplitter(this);
	if(!this->pSplitter) throw(Exception("Błąd inicjalizacji objektu TSplitter"));
	this->pSplitter->Parent = this;
	this->pSplitter->Align = alBottom;
	this->pSplitter->Color = clCream;
	this->pSplitter->Height = 6;
	this->pSplitter->Beveled = true;
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
	this->pGsEditorClass = new GsEditorClass(this);
	if(!this->pGsEditorClass) throw(Exception("Błąd inicjalizacji objektu GsEditorClass"));
	this->pGsEditorClass->Parent = this;
	this->pGsEditorClass->Align = alBottom;
	this->pGsEditorClass->Height = this->Parent->Height / 4;
	//Wskaźnika na drzewo zależnosci
	this->_pGsTreeBibleScheme = new GsTreeBibleScheme(this);
	if(!this->_pGsTreeBibleScheme) throw(Exception("Błąd inicjalizacji objektu GsTreeBibleScheme"));
	this->_pGsTreeBibleScheme->Parent = this;
	this->_pGsTreeBibleScheme->Align = alLeft;
	this->_pGsTreeBibleScheme->Width = 200;
	Gl_pGsTreeBibleScheme = this->_pGsTreeBibleScheme;  //Klasa drzewa
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

		this->pCBSelect = new TColorBox(pPanel);
		if(!this->pCBSelect) throw(Exception("Błąd inicjalizacji objektu TColorBox"));
		this->pCBSelect->Parent = pPanel;
		this->pCBSelect->Align = alTop;
		this->pCBSelect->AlignWithMargins = true;
		this->pCBSelect->OnGetColors = this->_ColorBoxGetColors;
		this->pCBSelect->Style = TColorBoxStyle() << cbStandardColors << cbExtendedColors << cbPrettyNames << cbCustomColors;

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

		this->pCBRoot = new TColorBox(pPanel);
		if(!this->pCBRoot) throw(Exception("Błąd inicjalizacji objektu TColorBox"));
		this->pCBRoot->Parent = pPanel;
		this->pCBRoot->Align = alTop;
		this->pCBRoot->AlignWithMargins = true;
		this->pCBRoot->OnGetColors = this->_ColorBoxGetColors;
		this->pCBRoot->Style = TColorBoxStyle() << cbStandardColors << cbExtendedColors << cbPrettyNames << cbCustomColors;
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

		this->pCBLine = new TColorBox(pPanel);
		if(!this->pCBLine) throw(Exception("Błąd inicjalizacji objektu TColorBox"));
		this->pCBLine->Parent = pPanel;
		this->pCBLine->Align = alTop;
		this->pCBLine->AlignWithMargins = true;
    this->pCBLine->OnGetColors = this->_ColorBoxGetColors;
		this->pCBLine->Style = TColorBoxStyle() << cbStandardColors << cbExtendedColors << cbPrettyNames << cbCustomColors;
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
		this->pCBLine->Selected = ColorObject[enColorNum_Line];
		this->pCBRoot->Selected = ColorObject[enColorNum_Rot];
		this->pCBSelect->Selected = ColorObject[enColorNum_Active];
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
	ColorObject[enColorNum_Line] = this->pCBLine->Selected;
	ColorObject[enColorNum_Active] = this->pCBSelect->Selected;
	ColorObject[enColorNum_Rot] = this->pCBRoot->Selected;
	iWidthLine = this->_pSpinEdit->Value;

	GlobalVar::Global_ConfigFile->WriteInteger(GlobalVar::GlobalIni_SetupsSchemeVers, GlobalVar::GlobalIni_SetSchemeColorLine, this->pCBLine->Selected);
	GlobalVar::Global_ConfigFile->WriteInteger(GlobalVar::GlobalIni_SetupsSchemeVers, GlobalVar::GlobalIni_SetSchemeColorRot, this->pCBRoot->Selected);
	GlobalVar::Global_ConfigFile->WriteInteger(GlobalVar::GlobalIni_SetupsSchemeVers, GlobalVar::GlobalIni_SetSchemeColorSelect, this->pCBSelect->Selected);
	GlobalVar::Global_ConfigFile->WriteInteger(GlobalVar::GlobalIni_SetupsSchemeVers, GlobalVar::GlobalIni_SetSchemeWidthLine, this->_pSpinEdit->Value);

	this->_pAction->Checked = false;
	this->VisibleSetupsScheme(false);
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

	TTreeNode *pNode = this->Selected; //Wybrany węzeł
	if(pNode)
	{
		//Wyłuskany wskaźnik na objekt, klasy GsDrawPanelBibleScheme
		if(Gl_pDrawPanelScheme)
		{
			pList = Gl_pDrawPanelScheme->_GsChildBibleSchemeList; //Lista wszystkich objektów, klasy GsChildBibleScheme

			for(int i=0; i<pList->Count; i++)
			{
				pGsChildBibleScheme = static_cast<GsChildBibleScheme *>(pList->Items[i]);

				if(Gl_pDrawPanelScheme->_pRootObject == pGsChildBibleScheme)
					pGsChildBibleScheme->Color = ColorObject[enColorNum_Rot];
				else pGsChildBibleScheme->Color = ColorObject[enColorNum_InActive];

				//Wyłuskanie zaznaczonej pozycji z drzewa
				if(pGsChildBibleScheme->_node == pNode)
				{
					Gl_pDrawPanelScheme->_pSelectObject = pGsChildBibleScheme; //Ustawienie aktualnego objektu
					pGsChildBibleScheme->Color = ColorObject[enColorNum_Active]; //Aktywizacja objektu
					//Wyświetlenie zawartości wersetu zaznaczonego w drzewie
					pGsChildBibleScheme->ViewSelectObject();
				}
      }
		}
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

