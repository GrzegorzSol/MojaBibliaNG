#pragma hdrstop

#include <Vcl.Dialogs.hpp>
#include <Strsafe.h>
#include "GsLogicalRelationshipTable.h"
#include "uGlobalVar.h"
#include "MyBibleLibrary\GsReadBibleTextdata.h"
#include <System.StrUtils.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
/*
#if defined(_DEBUGINFO_)
	GsDebugClass::WriteDebug(Format("", ARRAYOFCONST(( ))));
#endif
#if defined(_DEBUGINFO_)
	GsDebugClass::WriteDebug("");
#endif
MessageBox(NULL, TEXT("Test"), TEXT("Informacje aplikacji"), MB_OK | MB_ICONINFORMATION | MB_TASKMODAL);
GsChild *pGsChild = static_cast<GsChild *>(GlGsDrawChildren->_pGsChildrenMultiList->Items[i]);
if(pGsChild && (pGsChild != this))
*/
/****************************************************************************
* Wspólne statyczne globalne dane, dostepna dla wszystkich klas 						*
*****************************************************************************/

static GsDrawChildren *GlGsDrawChildren=nullptr;
static GsMaster *GlGsMaster=nullptr;

/****************************************************************************
*				Klasa całkowicie PRYWATNA GsCoreLogicalRelationship,								*
*										 pochodna TCustomPanel.																	*
*    Klasa jest klasą bazową dla wszystkich pozycji w "drzewie"             *
*****************************************************************************/
__fastcall GsCoreChild::GsCoreChild(TComponent* Owner) : TGraphicControl(Owner)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  this->Cursor = crSizeAll;
}
//---------------------------------------------------------------------------
__fastcall GsCoreChild::~GsCoreChild()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{

}
/****************************************************************************
*				Klasa całkowicie PRYWATNA GsChildLogicalRelationship,								*
*										 pochodna GsCoreBibleScheme.														*
*****************************************************************************/
const int ciAddHeight = 6, // Dodanie wysokości do pozycji by tekst zaczynał sie od górnego marginesu = ciAddHeight / 2
					ciAddWidth = 12; // Dodanie szerokosci do pozycji by tekst zaczynał sie od lewego marginesu = ciAddWidth / 2

//======================== KONSTRUKTORY KLASY GsChild =======================
__fastcall GsChild::GsChild(TComponent* Owner, const UnicodeString &custrAdr, const UnicodeString &custrVers)
	: GsCoreChild(Owner), _ustrNameVers(custrAdr), _ustrTextVers(custrVers)
/**
	OPIS METOD(FUNKCJI): Pierwszy konstruktor, który nie używa struktury PReadWriteDataObject, lecz argumenty są
                       wprowadzone pojedyńczo
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->_IDChild = reinterpret_cast<int>(this);
	//Inicjalizacja listy potomków
	this->_pListChildren = new TList();
	if(!this->_pListChildren) throw(Exception("Nie dokonano inicjalizacji objektu TList"));
	// Umieszczenie pozycji na przodku (właścicielu)
	this->Parent = dynamic_cast<TWinControl *>(Owner);
	if(!this->Parent) throw(Exception("Błąd tworzenia objektu, klasy GsChildLogicalRelationship"));
	this->Canvas->Font->Quality = TFontQuality::fqClearType;
	this->Canvas->Font->Size = 11;
	this->Text = Format("%s \"%s\"", ARRAYOFCONST(( _ustrNameVers, _ustrTextVers )));
	this->Hint = this->_ustrNameVers;
  this->ShowHint = true;
	this->Width = 200;

	TRect MyRect = this->ClientRect;
	this->ClientHeight = DrawText(this->Canvas->Handle, this->Text.c_str(), -1, &MyRect, DT_WORDBREAK | DT_CALCRECT) + ciAddHeight;
	this->Width += ciAddWidth;
}
//---------------------------------------------------------------------------
__fastcall GsChild::GsChild(TComponent* Owner, PReadWriteDataObject _PReadWriteDataObject)
	: GsCoreChild(Owner)
/**
	OPIS METOD(FUNKCJI): Drugi konstruktor, który używa struktury PReadWriteDataObject, w celu prawidłowego
											 odczytu zapisanej starej wersji projektu.
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	unsigned char _ucBook, _ucChapt, _ucVers, _ucTempTrans;

	//Inicjalizacja listy potomków
	this->_pListChildren = new TList();
	if(!this->_pListChildren) throw(Exception("Nie dokonano inicjalizacji objektu TList"));
	// Umieszczenie pozycji na przodku (właścicielu)
	this->Parent = dynamic_cast<TWinControl *>(Owner);
	if(!this->Parent) throw(Exception("Błąd tworzenia objektu, klasy GsChildLogicalRelationship"));
	this->Canvas->Font->Quality = TFontQuality::fqClearType;
	this->Canvas->Font->Size = 11;

	UnicodeString ustrText;
	this->_IDChild = _PReadWriteDataObject->RW_ID;

	GsReadBibleTextData::GetTextVersOfAdress(_PReadWriteDataObject->RW_Book, _PReadWriteDataObject->RW_Chapt+1,
		_PReadWriteDataObject->RW_Vers, 1, ustrText);
	this->_ustrNameVers = Format("%s %u:%u", ARRAYOFCONST((GsReadBibleTextData::GsInfoAllBooks[_PReadWriteDataObject->RW_Book].ShortNameBook,
			_PReadWriteDataObject->RW_Chapt+1, _PReadWriteDataObject->RW_Vers)));
	this->_ustrTextVers = ustrText;
	this->Text = Format("%s \"%s\"", ARRAYOFCONST((this->_ustrNameVers, this->_ustrTextVers)));
  this->ShowHint = true;
	this->Hint = this->_ustrNameVers;
	this->Width = 200;

	TRect MyRect = this->ClientRect;
	this->ClientHeight = DrawText(this->Canvas->Handle, this->Text.c_str(), -1, &MyRect, DT_WORDBREAK | DT_CALCRECT) + ciAddHeight;
	this->Width += ciAddWidth;
}
//---------------------------------------------------------------------------
__fastcall GsChild::GsChild(TComponent* Owner, PNewReadWriteDataObject _PNewReadWriteDataObject)
	: GsCoreChild(Owner)
/**
	OPIS METOD(FUNKCJI): Trzeci konstruktor, który używa struktury PNewReadWriteDataObject, w celu prawidłowego
											 odczytu zapisanej nowej wersji projektu.
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//Inicjalizacja listy potomków
	this->_pListChildren = new TList();
	if(!this->_pListChildren) throw(Exception("Nie dokonano inicjalizacji objektu TList"));
	// Umieszczenie pozycji na przodku (właścicielu)
	this->Parent = dynamic_cast<TWinControl *>(Owner);
	if(!this->Parent) throw(Exception("Błąd tworzenia objektu, klasy GsChildLogicalRelationship"));
	this->Canvas->Font->Quality = TFontQuality::fqClearType;
	this->Canvas->Font->Size = 11;

	UnicodeString ustrText;
	this->_IDChild = _PNewReadWriteDataObject->NRW_ID;
	this->_TypeObj = _PNewReadWriteDataObject->NRW_Type;
	this->_ustrNameVers = _PNewReadWriteDataObject->NRW_NameVers;
	this->_ustrTextVers = _PNewReadWriteDataObject->NRW_Text;
	this->Text = Format("%s \"%s\"", ARRAYOFCONST((this->_ustrNameVers, this->_ustrTextVers)));
	this->ShowHint = true;
  this->Hint = this->_ustrNameVers;
  this->Width = 200;

	TRect MyRect = this->ClientRect;
	this->ClientHeight = DrawText(this->Canvas->Handle, this->Text.c_str(), -1, &MyRect, DT_WORDBREAK | DT_CALCRECT) + ciAddHeight;
	this->Width += ciAddWidth;
}
//===========================================================================
__fastcall GsChild::~GsChild()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
//	static int siTempLicz;
	GsDrawChildren *pGsDrawChildren = static_cast<GsDrawChildren *>(this->Parent);

	for(int i=0; i<this->_pListChildren->Count; ++i)
	//Kasowanie wszystkich potomków
	{
		GsChild *pGsChild = static_cast<GsChild *>(this->_pListChildren->Items[i]);
		if(pGsChild)
		{
			//Wlaściwe kasowanie potomka
			delete pGsChild; pGsChild = nullptr;
    }
	}
	delete this->_pListChildren; this->_pListChildren = nullptr; //Kasowanie listy potomków, po ich usunięciu
  //Kasowanie objektu z listy głównej
	int iIndexThis = GlGsDrawChildren->_pMainChildrenList->IndexOf(this);
	if(iIndexThis > -1) GlGsDrawChildren->_pMainChildrenList->Delete(iIndexThis);

//	siTempLicz++;
//  #if defined(_DEBUGINFO_)
//		GsDebugClass::WriteDebug(Format("%d -> iIndexThis: %d -> Count: %d",
//			ARRAYOFCONST((siTempLicz, iIndexThis, GlGsDrawChildren->_pMainChildrenList->Count ))));
//	#endif
}
//---------------------------------------------------------------------------
void __fastcall GsChild::Paint()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  GsCoreChild::Paint();
	//Własny kod
	// Kolor pozycji zależnie od jej stanu
	TColor clFrameColor=clRed;
	int iWidth=1;
	const int ciDefaultWidthSelect=5;
	if(this == GlGsDrawChildren->_pRootObject)
		// Root nie zmienia koloru?
	{
		this->Color = GlGsMaster->Global_ColorsSchemeTable[enColorSchemeNum_Rot];
		// Przy zaznaczaniu objektu typu "korzeń", będzie zmieniana tylko obwódka
		if(this->_IsActive)
		{
			this->Canvas->Pen->Width = ciDefaultWidthSelect;
			clFrameColor = clRed;
		}
		else
		{
      this->Canvas->Pen->Width = 1;
			clFrameColor = clBlack;
    }
	}
	else
	{
		if(this->_IsActive)
		{
			this->Color = GlGsMaster->Global_ColorsSchemeTable[enColorSchemeNum_Active];
			this->Canvas->Pen->Width = ciDefaultWidthSelect;
			clFrameColor = clRed;
		}
		else
		{
			this->Color = GlGsMaster->Global_ColorsSchemeTable[enColorSchemeNum_InActive];
			this->Canvas->Pen->Width = 1;
			clFrameColor = clBlack;
		}
	}

	if(GlGsMaster->Global_IsTransparent)
  // Czy malować z przezroczystością ?
	{
		FillRectAlpha(this->Canvas, this->ClientRect, this->Color, 150);
	}
	else
	{
		this->Canvas->Brush->Color = this->Color;
		this->Canvas->FillRect(this->ClientRect);
		//this->Canvas->RoundRect(this->ClientRect, 10, 10);
	}
  this->Canvas->Pen->Color = clFrameColor;
	this->Canvas->Rectangle(this->ClientRect); //Obwódka o kolorze zależnym od zaznaczenia, lub nie
	// By nie rysować tekstu z podkładem, oraz by metoda Rectangle nie rysowała tła.
	this->Canvas->Brush->Style = bsClear;
	TRect MyRect(this->ClientRect); MyRect.Top = ciAddHeight / 2; MyRect.Left = ciAddWidth / 2;
	DrawText(this->Canvas->Handle, this->Text.c_str(), -1, &MyRect, DT_WORDBREAK);
}
//---------------------------------------------------------------------------
void __fastcall GsChild::MouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(GlGsDrawChildren->_pSelectObject != this) // Objekt kliknięty, staje się aktualny
	{
		GlGsDrawChildren->_pSelectObject = this; // Pole potrzebne do odrysowania aktualnej pozycji
																								// (kolor) w metodzie Paint(), klasy GsDrawChildren
		GlGsMaster->FSelectItem = this; // Aktualnie aktywny nowo dodany objekt będący wskaźnikiem na GsChild,
																							 // pole typy __property
		GlGsMaster->FSelectText = this->Text; // Tekst na pozycji, pole typy __property
	}
	//---
	if(Button == mbLeft)
	{
		GlGsMaster->_pTreeView->Select(this->_TreeNodeChild); // Zaznaczenie pozycji w objekcie klasy TTreeView

		if(!Shift.Contains(ssCtrl))
		// Lewy przycisk myszy bez Ctr
		{
			GlGsDrawChildren->_DeactivationAllItems(); // Dezaktywacja wszystkich pozycji
			GlGsMaster->_pMultiSelectTreeNodes->Clear();
		}
    // Dodanie do listy multiselect dla objektu, klasy TTreeView
		GlGsMaster->_pMultiSelectTreeNodes->Add(this->_TreeNodeChild);
    GlGsMaster->_pTreeView->Select(GlGsMaster->_pMultiSelectTreeNodes);
		this->_IsActive = true;//!this->_IsActive;

		this->_GetStartX = X;
		this->_GetStartY = Y;
		this->_StartMove = true;
	}
	if(GlGsMaster->FGetSetOnMouseDown) GlGsMaster->FGetSetOnMouseDown(this, Button, Shift, X, Y);
}
//---------------------------------------------------------------------------
void __fastcall GsChild::MouseUp(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  if(Button == mbLeft)
	{
		this->_StartMove = false; //Koniec przesuwania
    GlGsDrawChildren->_CalculateNewDimension(this);
	}
}
//---------------------------------------------------------------------------
void __fastcall GsChild::MouseMove(System::Classes::TShiftState Shift, int X, int Y)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(this->_StartMove)
	{
		if(Shift.Contains(ssCtrl))
		// Klawisz Ctr
		{
			for(int i=0; i<GlGsDrawChildren->_pMainChildrenList->Count; ++i)
			{
				GsChild *pGsChild = static_cast<GsChild *>(GlGsDrawChildren->_pMainChildrenList->Items[i]);
				if(pGsChild && (pGsChild != this) && pGsChild->_IsActive)
				{
					pGsChild->Left += (X - this->_GetStartX);
					pGsChild->Top += (Y - this->_GetStartY);
        }
			}
		}
		this->Left += (X - this->_GetStartX);
		this->Top += (Y - this->_GetStartY);
	}
	GlGsDrawChildren->Invalidate();
}
//---------------------------------------------------------------------------
/****************************************************************************
*				 Klasa całkowicie PRYWATNA GsDrawLogicalRelationship,								*
*										 pochodna TCustomPanel.																	*
*****************************************************************************/
__fastcall GsDrawChildren::GsDrawChildren(TComponent* Owner) : TCustomPanel(Owner)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->DoubleBuffered = true;
	this->_pMainChildrenList = new TList();
	if(!this->_pMainChildrenList) throw(Exception("Nie dokonano inicjalizacji objektu TList"));
	// Wspólny wskaźnik na klase do rysowania
  GlGsDrawChildren = this;
}
//---------------------------------------------------------------------------
__fastcall GsDrawChildren::~GsDrawChildren()
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
	if(this->_pMainChildrenList) {delete this->_pMainChildrenList; this->_pMainChildrenList = nullptr;}
}
//---------------------------------------------------------------------------
void __fastcall GsDrawChildren::_WMErasebackground(TWMEraseBkgnd &Message)
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
void __fastcall GsDrawChildren::CreateWnd()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  TCustomPanel::CreateWnd();
	//Własny kod
}
//---------------------------------------------------------------------------
void __fastcall GsDrawChildren::DestroyWnd()
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
void __fastcall GsDrawChildren::Paint()
/**
	OPIS METOD(FUNKCJI): Rysowanie połączeń między pozycjami
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TCustomPanel::Paint();
  //Własny kod
	GsChild *pGsChild=nullptr, *pPrevChild=nullptr;

	this->Canvas->Brush->Color = clFuchsia;
  this->Canvas->Pen->Width = GlGsMaster->Global_iWidthLineScheme;//iWidthLine;
	this->Canvas->Pen->Color = GlGsMaster->Global_ColorsSchemeTable[enColorSchemeNum_Line];//ColorObject[enColorNum_Line];

	for(int i=0; i<this->_pMainChildrenList->Count; ++i)
	{
		pGsChild = static_cast<GsChild *>(this->_pMainChildrenList->Items[i]);
		if(pGsChild)
		{
			pPrevChild = pGsChild->_pPrevChild;
			//--- Odrysowanie objektu i połączeń
			if(pPrevChild)
			{
				int iChildLeft=pGsChild->Left + (pGsChild->Width / 2),
						iPrevChild=pPrevChild->Left + (pPrevChild->Width / 2);
				//Rysowanie połączenia z przodkiem
				this->Canvas->MoveTo(iChildLeft, pGsChild->Top);
				this->Canvas->LineTo(iPrevChild, pPrevChild->Top + pPrevChild->Height);

				this->Canvas->Ellipse(TRect(iChildLeft - 6, pGsChild->Top - 6, iChildLeft + 6, pGsChild->Top + 6));
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall GsDrawChildren::MouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(GlGsMaster->FGetSetOnMouseDown) GlGsMaster->FGetSetOnMouseDown(this, Button, Shift, X, Y);
}
//---------------------------------------------------------------------------
void __fastcall GsDrawChildren::_DeactivationAllItems()
/**
	OPIS METOD(FUNKCJI): Kasowanie wszystkich aktywności
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	GsChild *pGsChild=nullptr;
	for(int i=0; i<this->_pMainChildrenList->Count; ++i)
	{
		pGsChild = static_cast<GsChild *>(this->_pMainChildrenList->Items[i]);
		if(pGsChild)
			{pGsChild->_IsActive = false;}
  }
}
//---------------------------------------------------------------------------
bool __fastcall GsDrawChildren::_OpenOldProject(TFileStream *pFileStream)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	PReadWriteDataObject pDataToOpen=nullptr;
	bool bReturn=false;
	GsChild *pGsChild=nullptr, *pPrevChild=nullptr;
	int iSizeFile = pFileStream->Size, //Wielkość pliku
			iSizeStructData = sizeof(ReadWriteDataObject), //Wielkość struktury
			iShiftLeft; // Obliczana wartość by wycentrowac wykres
	const int ciShiftAllTp = 60, // Dodatkowe przesunięcie odległości w pionie miedzy pozycjami
						ciShiftLeftRight = 160, // Przesunięcie dodatkowe w lewo lub w prawo gałęzi
						ciReference = 24; // Minimalna różnica między potomkiem a głównym węzłem,
															// by zorientoweać się, w która stronę dodatkowo przesunąć potomka.
	TTreeNode *TrNode=nullptr;

	//Struktura pomocnicza pojedyńczego objektu
	pDataToOpen = new ReadWriteDataObject();
	if(!pDataToOpen) throw(Exception("Nie dokonano inicjalizacji objektu ReadWriteDataObject"));

	for(int i=0; i<iSizeFile; i+=iSizeStructData)
	{
		SecureZeroMemory(pDataToOpen, iSizeStructData); //Wyczyszczenie struktury ReadWriteDataObject, do zapisu i odczytu objektów

		pFileStream->ReadBuffer(pDataToOpen, iSizeStructData);
		//--- Stworzenie objektu
		pGsChild = new GsChild(this, pDataToOpen);
		if(!pGsChild) throw(Exception("Błąd inicjalizacji objektu GsChild"));
		pGsChild->Parent = this;
		if(pDataToOpen->RW_IDListParent == -1) // Korzeń
			{iShiftLeft = pDataToOpen->RW_Left - (this->Width / 2) + (pGsChild->Width / 2);}
		pDataToOpen->RW_Left -= iShiftLeft; // Przesunięcie w lewo całego wykresu

		//--- Typ objektu: korzeń, lub potomstwo
		if(pDataToOpen->RW_IDListParent == -1) // Korzeń
		{
			this->_pRootObject = pGsChild;		// To jest korzeń
			pGsChild->Top = pDataToOpen->RW_Top;
			pGsChild->Left = pDataToOpen->RW_Left;
      //Tworzenie korzenia drzewa
			TrNode = GlGsMaster->_pTreeView->Items->AddObject(NULL, pGsChild->_ustrNameVers, pGsChild);
			if(!TrNode) throw(Exception("Błąd inicjalizacji klasy AddObject"));
			pGsChild->_TreeNodeChild = TrNode;
		}
		else if(pDataToOpen->RW_IDListParent > -1)// Potomstwo
		{
			//Wyłuskiwanie adresu przodka, po jego odczytanym indeksie z globalnej listy objektów
			pPrevChild = static_cast<GsChild *>(this->_pMainChildrenList->Items[pDataToOpen->RW_IDListParent]);
			if(pPrevChild)
			{
				pGsChild->_pPrevChild = pPrevChild;
				pGsChild->_Level = pPrevChild->_Level + 1;
				pPrevChild->_pListChildren->Add(pGsChild); //Dodanie aktualnego objektu, do list potomków, przodka
				// Korygowanie położenia pozycji ze wzgledu na inną zawartośc jej w nowszej wersji
				pGsChild->Top = pPrevChild->Top + pPrevChild->Height + ciShiftAllTp;
				if(pDataToOpen->RW_Left < (pPrevChild->Left - ciReference)) pGsChild->Left = pDataToOpen->RW_Left - ciShiftLeftRight;
				else if(pDataToOpen->RW_Left > (pPrevChild->Left + ciReference)) pGsChild->Left = pDataToOpen->RW_Left + ciShiftLeftRight;
				else pGsChild->Left = pDataToOpen->RW_Left;
				//Tworzenie potomków w drzewie
				TrNode = GlGsMaster->_pTreeView->Items->AddChildObject(pPrevChild->_TreeNodeChild, pGsChild->_ustrNameVers, pGsChild);
				pGsChild->_TreeNodeChild = TrNode;
      }
		}

		this->_pMainChildrenList->Add(pGsChild); //Dodanie do głównej listy objektów
	}
	GlGsMaster->_pTreeView->FullExpand(); //Całkowicie rozwiniete drzewo
	GlGsMaster->_pTreeView->Items->GetFirstNode()->MakeVisible();

	pGsChild = static_cast<GsChild *>(this->_pMainChildrenList->Last());
	if(pGsChild)
	// Aktywacja i selekcja ostatniego elementu
	{
		this->_pSelectObject = pGsChild; // Ostatni object aktywnym
		GlGsMaster->_pTreeView->Select(TrNode); // Zaznaczenie pozycji w objekcie klasy TTreeView
		GlGsMaster->_pMultiSelectTreeNodes->Add(TrNode); // Dodanie do listy multiselect dla objektu, klasy TTreeView
		GlGsMaster->FSelectText = this->_pSelectObject->Text; // Tekst na pozycji, pole typy __property
		GlGsMaster->FSelectItem = this->_pSelectObject; // Wskażnik na GsChild, pole typy __property
		this->_CalculateNewDimension(pGsChild);
		this->_DeactivationAllItems(); // Dezaktywacja wszystkich pozycji
		pGsChild->_IsActive = true;
	}
	GlGsMaster->_pTreeView->Visible = true;

	if(pDataToOpen) {delete pDataToOpen; pDataToOpen = nullptr;}
	return bReturn;
}
//---------------------------------------------------------------------------
bool __fastcall GsDrawChildren::_OpenNewProject(TFileStream *pFileStream)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	PNewReadWriteDataObject pDataToOpen=nullptr;
  bool bReturn=false;
	GsChild *pGsChild=nullptr, *pPrevChild=nullptr;
	int iSizeFile = pFileStream->Size, //Wielkość pliku
			iSizeStructData = sizeof(NewReadWriteDataObject); //Wielkość struktury
	TTreeNode *TrNode=nullptr;

	//Struktura pomocnicza pojedyńczego objektu
	pDataToOpen = new NewReadWriteDataObject();
	if(!pDataToOpen) throw(Exception("Nie dokonano inicjalizacji objektu NewReadWriteDataObject"));

	for(int i=0; i<iSizeFile; i+=iSizeStructData)
	{
		SecureZeroMemory(pDataToOpen, iSizeStructData); //Wyczyszczenie struktury ReadWriteDataObject, do zapisu i odczytu objektów

		pFileStream->ReadBuffer(pDataToOpen, iSizeStructData);
    //--- Stworzenie objektu
		pGsChild = new GsChild(this, pDataToOpen);
		if(!pGsChild) throw(Exception("Błąd inicjalizacji objektu GsChild"));
		pGsChild->Parent = this;

		pGsChild->Top = pDataToOpen->NRW_Top;
		pGsChild->Left = pDataToOpen->NRW_Left;
    //--- Typ objektu: korzeń, lub potomstwo
		if(pDataToOpen->NRW_IDListParent == -1) // Korzeń
		{
			this->_pRootObject = pGsChild;		// To jest korzeń
      //Tworzenie korzenia drzewa
			TrNode = GlGsMaster->_pTreeView->Items->AddObject(NULL, pGsChild->_ustrNameVers, pGsChild);
			if(!TrNode) throw(Exception("Błąd inicjalizacji klasy AddObject"));
			pGsChild->_TreeNodeChild = TrNode;
		}
		else if(pDataToOpen->NRW_IDListParent > -1)// Potomstwo
		{
      //Wyłuskiwanie adresu przodka, po jego odczytanym indeksie z globalnej listy objektów
			pPrevChild = static_cast<GsChild *>(this->_pMainChildrenList->Items[pDataToOpen->NRW_IDListParent]);
			if(pPrevChild)
			{
				pGsChild->_pPrevChild = pPrevChild;
        pGsChild->_Level = pPrevChild->_Level + 1;
				pPrevChild->_pListChildren->Add(pGsChild); //Dodanie aktualnego objektu, do list potomków, przodka
        //Tworzenie potomków w drzewie
				TrNode = GlGsMaster->_pTreeView->Items->AddChildObject(pPrevChild->_TreeNodeChild, pGsChild->_ustrNameVers, pGsChild);
				pGsChild->_TreeNodeChild = TrNode;
			}
		}

		this->_pMainChildrenList->Add(pGsChild); //Dodanie do głównej listy objektów
	}

  GlGsMaster->_pTreeView->FullExpand(); //Całkowicie rozwiniete drzewo
	GlGsMaster->_pTreeView->Items->GetFirstNode()->MakeVisible();

  pGsChild = static_cast<GsChild *>(this->_pMainChildrenList->Last());
	if(pGsChild)
	// Aktywacja i selekcja ostatniego elementu
	{
		this->_pSelectObject = pGsChild; // Ostatni object aktywnym
		GlGsMaster->_pTreeView->Select(TrNode); // Zaznaczenie pozycji w objekcie klasy TTreeView
    GlGsMaster->_pMultiSelectTreeNodes->Add(TrNode); // Dodanie do listy multiselect dla objektu, klasy TTreeView
    GlGsMaster->FSelectText = this->_pSelectObject->Text; // Tekst na pozycji, pole typy __property
		GlGsMaster->FSelectItem = this->_pSelectObject; // Wskażnik na GsChild, pole typy __property
		this->_CalculateNewDimension(pGsChild);
    this->_DeactivationAllItems(); // Dezaktywacja wszystkich pozycji
		pGsChild->_IsActive = true;
	}
	GlGsMaster->_pTreeView->Visible = true;

	if(pDataToOpen) {delete pDataToOpen; pDataToOpen = nullptr;}
  return bReturn;
}
//---------------------------------------------------------------------------
void __fastcall GsDrawChildren::_CalculateNewDimension(GsChild *pGsChild)
/**
	OPIS METOD(FUNKCJI): Obliczanie nowego rozmiaru
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if((pGsChild->Left + pGsChild->Width) > this->Width)
		{this->Width = pGsChild->Left + pGsChild->Width + 2;}
	if((pGsChild->Top + pGsChild->Height) > this->Height)
		{this->Height = pGsChild->Top + pGsChild->Height + 2;}
	//---
	if(pGsChild->Left < 0)
	{
		int iLeft = pGsChild->Left - 2;
		this->Width -= pGsChild->Left;
		for(int i=0; i<this->_pMainChildrenList->Count; ++i)
		{
      GsChild *pGsChild = static_cast<GsChild *>(this->_pMainChildrenList->Items[i]);
			if(pGsChild)
			{
				pGsChild->Left -= iLeft;
      }
    }
	}
	//---
	if(pGsChild->Top < 0)
	{
		int iTop = pGsChild->Top - 2;
		this->Height -= pGsChild->Top;
		for(int i=0; i<this->_pMainChildrenList->Count; ++i)
		{
      GsChild *pGsChild = static_cast<GsChild *>(this->_pMainChildrenList->Items[i]);
			if(pGsChild)
			{
				pGsChild->Top -= iTop;
      }
    }
	}
}
//---------------------------------------------------------------------------
/****************************************************************************
*							Główna klasa GsScrollLogicalRelationship,											*
*											pochodna TScrollingWinControl.												*
*****************************************************************************/
__fastcall GsMaster::GsMaster(TComponent* Owner, TTreeView *pTrView)
 : TScrollingWinControl(Owner), _pTreeView(pTrView)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	// Lista dla wielokrotnego wyboru
	this->FGsChildrensSelectList = new TList();
	if(!this->FGsChildrensSelectList) throw(Exception("Nie dokonano inicjalizacji objektu TList"));
	// Lista zaznaczonych pozycji dla multiselect, w drzewie TTreeView
	this->_pMultiSelectTreeNodes = new TList();
	if(!this->_pMultiSelectTreeNodes) throw(Exception("Nie dokonano inicjalizacji objektu TList"));

	this->StyleElements = TStyleElements();
	this->AutoScroll = true;
	this->DoubleBuffered = true;
	this->ParentBackground = false;
  this->HorzScrollBar->Tracking = true;
	this->VertScrollBar->Tracking = true;

	// Wspólny wskaźnik na główną klase
	GlGsMaster = this;
}
//---------------------------------------------------------------------------
__fastcall GsMaster::~GsMaster()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  // Lista zaznaczonych pozycji dla multiselect, w drzewie TTreeView
	if(this->_pMultiSelectTreeNodes) {delete this->_pMultiSelectTreeNodes; this->_pMultiSelectTreeNodes = nullptr;}
	// Lista dla wielokrotnego wyboru objektów GsChild
	if(this->FGsChildrensSelectList) {delete this->FGsChildrensSelectList; this->FGsChildrensSelectList = nullptr;}
}
//---------------------------------------------------------------------------
void __fastcall GsMaster::CreateWnd()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TScrollingWinControl::CreateWnd();
	//Własny kod
	//Stworzenie panelu do rysowania połączeń i objektów
	this->_pGsDrawChildren = new GsDrawChildren(this);
	if(!this->_pGsDrawChildren) throw(Exception("Błąd inicjalizacji objektu GsDrawLogicalRelationship"));
	this->_pGsDrawChildren->Parent = this;
	this->_pGsDrawChildren->DoubleBuffered = true;
  //---
	this->_pGsDrawChildren->Left = 0; this->_pGsDrawChildren->Top = 0;
	this->_pGsDrawChildren->Width = this->ClientWidth;
	this->_pGsDrawChildren->Height = this->ClientHeight;
	this->_pGsDrawChildren->BevelOuter = bvNone; // Bez widocznych granic
}
//---------------------------------------------------------------------------
void __fastcall GsMaster::DestroyWnd()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  //Własny kod.
	TScrollingWinControl::DestroyWnd();
}
//---------------------------------------------------------------------------
void __fastcall GsMaster::MouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//Jeśli istnieje zewnętrzna metoda OnMouseDown() to ją wywołaj
	if(this->FGetSetOnMouseDown) this->FGetSetOnMouseDown(this, Button, Shift, X, Y);
}
//---------------------------------------------------------------------------
bool __fastcall GsMaster::DoMouseWheel(System::Classes::TShiftState Shift, int WheelDelta, const System::Types::TPoint &MousePos)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TPoint PointComp = ScreenToClient(MousePos);
	const int ciShift = 12, // Przesunięcie kółkiem myszy
						ciOffset = 86; // Kiedy reagowac na obracanie kółkiem myszy

	bool IsVertical = (PointComp.X > (this->ClientWidth - ciOffset));
	bool IsHorizonatal = (PointComp.Y > (this->ClientHeight - ciOffset));

	if(WheelDelta < 0) // W dół
	{
		if(IsHorizonatal) this->HorzScrollBar->Position += ciShift;
		if(IsVertical) this->VertScrollBar->Position += ciShift;
	}
	else if(WheelDelta > 0) // W górę
	{
		if(IsHorizonatal) this->HorzScrollBar->Position -= ciShift;
		if(IsVertical) this->VertScrollBar->Position -= ciShift;
	}

	return true;
}
//---------------------------------------------------------------------------
bool __fastcall GsMaster::OpenProject()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  const UnicodeString ustrFileTypes[] = {"Pliki starego projektu", "*" + custrOldExtFilesScheme,
																				 "Pliki nowego projektu", "*" + custrNewExtFileScheme,
																				 "Każdy plik", "*.*"};
	bool bReturn=false;
	//---
	TFileStream *pOpenFile=nullptr;

	//---
	TFileOpenDialog *pFileOpenDialog = new TFileOpenDialog(this);
	if(!pFileOpenDialog) throw(Exception("Błąd inicjalizacji objektu TFileOpenDialog"));

	pFileOpenDialog->Title = "Podaj nazwę projektu do odczytu";
	for(int i=0; i<ARRAYSIZE(ustrFileTypes); i+=2)
	{
		TFileTypeItem *pTFileTypeItem = pFileOpenDialog->FileTypes->Add();
		pTFileTypeItem->DisplayName = ustrFileTypes[i];
		pTFileTypeItem->FileMask = ustrFileTypes[i+1];
	}

	pFileOpenDialog->Options = TFileDialogOptions() << fdoPathMustExist << fdoFileMustExist << fdoForceFileSystem;
	pFileOpenDialog->DefaultFolder = GlobalVar::Global_custrGetExeDir; //Katalog aplikacji

	try
	{
		try
		{
      if(pFileOpenDialog->Execute()) //Element został wybrany
			{
				this->_pTreeView->Items->Clear();
        this->_pMultiSelectTreeNodes->Clear(); // Wykasowanie listy zaznaczonych pozycji TreeNode, w objekcie, klasy TTreView
				UnicodeString ustrExt = TPath::GetExtension(pFileOpenDialog->FileName);
				//Wykasowanie całej zawartości schematu, ze wszystkimi aktualnymi objektami
				delete this->_pGsDrawChildren->_pRootObject; this->_pGsDrawChildren->_pRootObject = nullptr; //Niszczenie rozpoczyna się od korzenia
				this->_pGsDrawChildren->_pSelectObject = nullptr;

				pOpenFile = new TFileStream(pFileOpenDialog->FileName, fmOpenRead);
				if(!pOpenFile) throw(Exception("Błąd inicjalizacji objektu TFileStream"));

				if(ustrExt == custrOldExtFilesScheme)
					{this->_pGsDrawChildren->_OpenOldProject(pOpenFile);}
				else if(ustrExt == custrNewExtFileScheme)
					{this->_pGsDrawChildren->_OpenNewProject(pOpenFile);}

				this->Invalidate(); //Całe odświerzenie
				if(pOpenFile) {delete pOpenFile; pOpenFile = nullptr;}
				bReturn = true;
			}
			else bReturn = false;
		}
		catch(const Exception& e)
		{
			//MessageBox(NULL, Format("Błąd otwarcia pliku, do odczytu, o nazwie: %s", ARRAYOFCONST((pFileOpenDialog->FileName))).c_str(), TEXT("Błąd aplikacji"), MB_OK | MB_ICONERROR | MB_TASKMODAL);
			MessageBox(NULL, Format("Błąd: %s", ARRAYOFCONST((e.Message))).c_str(), TEXT("Błąd aplikacji"), MB_OK | MB_ICONERROR | MB_TASKMODAL);
		}
	}
	__finally
	{
		if(pFileOpenDialog) {delete pFileOpenDialog; pFileOpenDialog = nullptr;}
	}
	return bReturn;
}
//---------------------------------------------------------------------------
bool __fastcall GsMaster::SaveProject()
/**
	OPIS METOD(FUNKCJI): Zapisanie projektu
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
	STRSAFEAPI StringCchCopyA(
		[out] STRSAFE_LPSTR pszDest,
		[in] size_t cchDest,
		[in] STRSAFE_LPCSTR pszSrc);
*/
{
	const UnicodeString ustrFileTypes[] = {"Pliki projektu schematu", "*" + custrNewExtFileScheme,
																				 "Każdy plik", "*.*"};
	UnicodeString ustrPathSave;
	TFileStream *pSaveFile=nullptr;
	PNewReadWriteDataObject pDataToSave=nullptr;
	bool bReturn=false;
	//---
	TFileSaveDialog *pFileSaveDialog = new TFileSaveDialog(this);
	if(!pFileSaveDialog) throw(Exception("Błąd inicjalizacji objektu TFileSaveDialog"));
	pFileSaveDialog->Title = "Podaj nazwę projektu do zapisu";
	for(int i=0; i<ARRAYSIZE(ustrFileTypes); i+=2)
	{
		TFileTypeItem *pTFileTypeItem = pFileSaveDialog->FileTypes->Add();
		pTFileTypeItem->DisplayName = ustrFileTypes[i];
		pTFileTypeItem->FileMask = ustrFileTypes[i+1];
	}
	pFileSaveDialog->Options = TFileDialogOptions() << fdoOverWritePrompt << fdoFileMustExist;
	pFileSaveDialog->DefaultFolder = GlobalVar::Global_custrGetExeDir; //Katalog aplikacji
	pFileSaveDialog->FileName = Format("Bez nazwy%s", ARRAYOFCONST((custrNewExtFileScheme)));
	pFileSaveDialog->DefaultExtension = custrNewExtFileScheme;

	try
	{
		try
		{
			if(this->_pGsDrawChildren->_pRootObject)
			//Jeśli istnieje główny korzeń
			{
				if(pFileSaveDialog->Execute())
				{
					ustrPathSave = pFileSaveDialog->FileName;

					pSaveFile = new TFileStream(ustrPathSave, fmCreate);
					if(!pSaveFile) throw(Exception("Błąd inicjalizacji objektu TFileStream"));
					int iSizeStructData = sizeof(NewReadWriteDataObject); //Wielkość struktury
					//Struktura pomocnicza pojedyñczego objektu
					pDataToSave = new NewReadWriteDataObject();
					if(!pDataToSave) throw(Exception("Nie dokonano inicjalizacji objektu NewReadWriteDataObject"));
					//---
					for(int i=0; i<this->_pGsDrawChildren->_pMainChildrenList->Count; ++i)
					{
						GsChild *pChild = static_cast<GsChild *>(this->_pGsDrawChildren->_pMainChildrenList->Items[i]);
						if(pChild)
						{
							SecureZeroMemory(pDataToSave, iSizeStructData); //Wyczyszczenie struktury ReadWriteDataObject, do zapisu i odczytu objektów
							//Wypełnienie struktury danych do zapisu
							pDataToSave->NRW_Type = enTypeChild_Normal;
							pDataToSave->NRW_ID = pChild->_IDChild; //Numer identyfikacyjny
							pDataToSave->NRW_IDList = i;						//Pozycja w globalnej liście objektu _GsChildrenList, klasy TList
							pDataToSave->NRW_Left = pChild->Left; pDataToSave->NRW_Top = pChild->Top; //Wspólrzędne objektu
							pDataToSave->NRW_IDListParent = -1;		//Domyślnie objekt nie ma przodka, więc jest korzeniem
							if(pChild->_pPrevChild) //Jeśli objekt posiada przodka, czyli nie jest korzeniem
							{
								//Indeks przodka w głównej liście
								pDataToSave->NRW_IDListParent = this->_pGsDrawChildren->_pMainChildrenList->IndexOf(pChild->_pPrevChild);
							}

							StringCchCopy(pDataToSave->NRW_NameVers, SIZE_ADDR_VERS-1, pChild->_ustrNameVers.c_str()); //Skopiowanie adresu wersetu,
							StringCchCopy(pDataToSave->NRW_Text, NSIZE_TEXT-1, pChild->_ustrTextVers.c_str()); // Tekst

							pSaveFile->WriteBuffer(pDataToSave, sizeof(NewReadWriteDataObject)); //Główny zapis struktury pomocniczej objektu
						}
					}
					if(pDataToSave) {delete pDataToSave; pDataToSave = nullptr;}
					if(pSaveFile) {delete pSaveFile; pSaveFile = nullptr;}
					bReturn = true;
				}
			}
		}
		catch(const Exception& e)
		{
			MessageBox(NULL, Format("Błąd otwarcia pliku, do zapisu, o nazwie: \"%s\"", ARRAYOFCONST((ustrPathSave))).c_str(), TEXT("Błąd aplikacji"), MB_OK | MB_ICONERROR | MB_TASKMODAL);
		}
	}
	__finally
	{
		if(pFileSaveDialog) {delete pFileSaveDialog; pFileSaveDialog = nullptr;}
	}

	return bReturn;
}
//---------------------------------------------------------------------------
void __fastcall GsMaster::SaveToAllText(const UnicodeString &ustrPathSave)
/**
	OPIS METOD(FUNKCJI): Stworzenie pliku typu txt z zawartością wszystkich pozycji
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	GsChild *pChild=nullptr;
	TStringList *pSListFile=nullptr;

	try
	{
		pSListFile = new TStringList();
		if(!pSListFile) throw(Exception("Błąd inicjalizacji objektu TStringList"));

		if(this->_pGsDrawChildren->_pRootObject)
		{
			this->_CreateHierarchyText(this->_pGsDrawChildren->_pRootObject, pSListFile);
      pSListFile->SaveToFile(ustrPathSave, TEncoding::UTF8);
		}
	}
	__finally
	{
		if(pSListFile) {delete pSListFile; pSListFile = nullptr;}
	}
}
//---------------------------------------------------------------------------
void __fastcall GsMaster::RenameTextItem(const UnicodeString &custrNewAdr, const UnicodeString &custrNewVers)
/**
	OPIS METOD(FUNKCJI): Zmiana tekstu w wybranej pozycji
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  GsChild* pGsChild = this->_pGsDrawChildren->_pSelectObject;
	if(pGsChild)
	{
		pGsChild->_ustrNameVers = custrNewAdr;
		pGsChild->_ustrTextVers = custrNewVers;
		pGsChild->Text = Format("%s \"%s\"", ARRAYOFCONST(( custrNewAdr, custrNewVers )));
		pGsChild->Width = 200;

		TRect MyRect = pGsChild->ClientRect;
		pGsChild->ClientHeight = DrawText(pGsChild->Canvas->Handle, pGsChild->Text.c_str(), -1, &MyRect, DT_WORDBREAK | DT_CALCRECT) + ciAddHeight;
		pGsChild->Width += ciAddWidth;
	}
}
//---------------------------------------------------------------------------
void __fastcall GsMaster::DeleteObject()
/**
	OPIS METOD(FUNKCJI): Kasowanie pozycji wraz z potomstwem
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TTreeNode *_pNode=nullptr;
	if(this->_pGsDrawChildren->_pSelectObject)	//Aktualnie aktywny objekt
	{
		if(this->_pGsDrawChildren->_pSelectObject!=this->_pGsDrawChildren->_pRootObject)
		//Nie jest korzeniem i posiada przodków
		{
			_pNode = this->_pGsDrawChildren->_pSelectObject->_TreeNodeChild;
			GsChild *pParent = this->_pGsDrawChildren->_pSelectObject->_pPrevChild;
			if(pParent)
			{
				int iIndexParent = pParent->_pListChildren->IndexOf(this->_pGsDrawChildren->_pSelectObject);
        if(iIndexParent > -1)
				{
					//Kasowanie objektu z listy przodka
					pParent->_pListChildren->Delete(iIndexParent);
				}
			}
			delete this->_pGsDrawChildren->_pSelectObject; this->_pGsDrawChildren->_pSelectObject = nullptr;
			this->_pGsDrawChildren->_pSelectObject = this->_pGsDrawChildren->_pRootObject;
		}
    else
		//Skasowanie korzenia
		{
      delete this->_pGsDrawChildren->_pRootObject; this->_pGsDrawChildren->_pRootObject = nullptr;
			this->_pGsDrawChildren->_pSelectObject = nullptr;
		}
		_pNode->Delete(); // Skasowanie objektu
		this->Invalidate();
	}
}
//---------------------------------------------------------------------------
void __fastcall GsMaster::AddNewObjectScheme(const UnicodeString &custrAdr, const UnicodeString &custrVers)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  static int sbPlaseRight;
	int _iTop=20;
	const int ciVertSpace = 24, // Odległość w pionie od poprzednie elementu
						ciHorSpace = 12;  // Odległość w poziomie od poprzedniego elementu;
	TTreeNode *TrNode=nullptr;
	GsChild *pGsChild=nullptr, *prevGsChild=nullptr; //Domyślnie to korzeń

	pGsChild = new GsChild(this->_pGsDrawChildren, custrAdr, custrVers);
	if(!pGsChild) throw(Exception("Nie dokonano inicjalizacji objektu GsChildLogicalRelationship"));
	int _left = this->_pGsDrawChildren->Width / 2 - (pGsChild->Width / 2);

	this->_pTreeView->Visible = true;
	if(this->_pGsDrawChildren->_pMainChildrenList->Count > 0) //Tylko jeden korzeń!
	{
		prevGsChild = this->_pGsDrawChildren->_pSelectObject;
		//Ustawienie pól na poprzedni objekt
		pGsChild->_pPrevChild = prevGsChild; //Poprzedni objekt, to objekt wybrany
		prevGsChild->_pNextChild = pGsChild;
		// Umieszczenie nowej pozycji po prawej stronie od ostatniego "brata",
		// lub po lewj od pierwszego "brata"
		if(prevGsChild->_pListChildren->Count > 0)
		{
			// Wyłuskanie wskaźnika na ostatniego "brata" pozycji
			GsChild *pLastBr = static_cast<GsChild *>(prevGsChild->_pListChildren->Last());
			GsChild *pFirstBr = static_cast<GsChild *>(prevGsChild->_pListChildren->First());
			if(pLastBr && pFirstBr)
			{
				if(sbPlaseRight > 0)
					{_left = pLastBr->Left + pLastBr->Width + ciHorSpace;}
				else
					{_left = pFirstBr->Left - pFirstBr->Width - ciHorSpace;}
				sbPlaseRight *= -1;
			}
		}
		// Brak potomków więc nowy potomek pod w tym samym pionie co przodek
		else {sbPlaseRight = 1; }
		// Pozycjonowanie w pionie nowej pozycji
		_iTop = prevGsChild->Top + prevGsChild->Height + ciVertSpace;
		pGsChild->_Level = prevGsChild->_Level + 1; // Jeden poziom więcej
		prevGsChild->_pListChildren->Add(pGsChild); // Dodanie aktualnego objektu, do list potomków, przodka
    //Tworzenie potomków w drzewie
		TrNode = this->_pTreeView->Items->AddChildObject(prevGsChild->_TreeNodeChild, pGsChild->_ustrNameVers, pGsChild);
		pGsChild->_TreeNodeChild = TrNode;
	}
	else //Dodawanie korzenia
	{
		this->_pGsDrawChildren->_pRootObject = pGsChild;		// Okno głównego korzenia
    //Tworzenie korzenia drzewa
		TrNode = this->_pTreeView->Items->AddObject(NULL, pGsChild->_ustrNameVers, pGsChild);
		pGsChild->_TreeNodeChild = TrNode;
	}
	pGsChild->Top = _iTop; pGsChild->Left = _left;

	this->_pGsDrawChildren->_pSelectObject = pGsChild;	// Aktualnie aktywny nowo dodany objekt
	this->_pGsDrawChildren->_DeactivationAllItems(); // Dezaktywacja wszystkich pozycji
	pGsChild->_IsActive = true;
  this->_pTreeView->Select(TrNode); // Zaznaczenie pozycji w objekcie klasy TTreeView
	this->FSelectItem = this->_pGsDrawChildren->_pSelectObject; // Aktualnie aktywny nowo dodany objekt,
																														 // pole typy __property
	this->FSelectText = custrVers; // Tekst na pozycji, pole typy __property

	this->_pGsDrawChildren->_pMainChildrenList->Add(pGsChild); //Dodanie do głównej listy objektów
	this->_pGsDrawChildren->Invalidate(); //Całe odświerzenie

	this->_pTreeView->FullExpand(); //Całkowicie rozwiniete drzewo
	this->_pTreeView->Items->GetFirstNode()->MakeVisible();
}
//---------------------------------------------------------------------------
void __fastcall GsMaster::NewProject()
/**
	OPIS METOD(FUNKCJI): Nowy projekt
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->_pTreeView->Items->Clear();
	this->_pMultiSelectTreeNodes->Clear(); // Wykasowanie listy zaznaczonych pozycji TreeNode, w objekcie, klasy TTreView
	this->_pGsDrawChildren->_pCutCopyObject = nullptr; // Wyzerowanie objektu do wstawienia
	//Wykasowanie całej zawartości schematu, ze wszystkimi aktualnymi objektami
	if(this->_pGsDrawChildren->_pRootObject) {delete this->_pGsDrawChildren->_pRootObject; this->_pGsDrawChildren->_pRootObject = nullptr;} //Niszczenie rozpoczyna się od korzenia
	this->_pGsDrawChildren->_pSelectObject = nullptr;
	this->_pTreeView->Visible = false;
	this->_pGsDrawChildren->Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall GsMaster::SaveToGfx(const UnicodeString &ustrPathSave)
/**
	OPIS METOD(FUNKCJI): Zapis wykresu jako grafikę
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  Graphics::TBitmap *bmp=nullptr;
	TWICImage *pWICImage=nullptr;
	GsChild *pGsChild=nullptr, *pPrevChild=nullptr;

  bmp = new Graphics::TBitmap();
	if(!bmp) throw(Exception("Błąd inicjalizacji objektu grafiki bmp"));

	pWICImage = new TWICImage();
	if(!pWICImage) throw(Exception("Błąd inicjalizacji objektu TWICImage"));

	bmp->Canvas->Font->Quality = TFontQuality::fqClearType;
	bmp->Canvas->Font->Size = 11;
	bmp->Width = this->_pGsDrawChildren->Width;
	bmp->Height = this->_pGsDrawChildren->Height;
	bmp->PixelFormat = pf32bit;
	bmp->Canvas->Brush->Color = clWhite;
	bmp->Canvas->FillRect(TRect(0, 0, bmp->Width, bmp->Height));
	bmp->Canvas->Brush->Color = clBlack;

	this->_pGsDrawChildren->PaintTo(bmp->Canvas, 0, 0);

	TWICImageFormat myFormat=wifPng;
	if(TPath::GetExtension(ustrPathSave) == ".png") {myFormat = wifPng;}
	else if(TPath::GetExtension(ustrPathSave) == ".jpg") {myFormat = wifJpeg;}

	pWICImage->Assign(bmp);
	//pWICImage->Transparent = false;
	pWICImage->ImageFormat = myFormat;
	pWICImage->SaveToFile(ustrPathSave);

  if(pWICImage) {delete pWICImage; pWICImage = nullptr;}
	if(bmp) {delete bmp; bmp = nullptr;}
}
//---------------------------------------------------------------------------
void __fastcall GsMaster::CutCopyToPaste()
/**
	OPIS METOD(FUNKCJI): Skopiowanie zaznaczonego elementu
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->_pGsDrawChildren->_pCutCopyObject = this->_pGsDrawChildren->_pSelectObject;
}
//---------------------------------------------------------------------------
bool __fastcall GsMaster::PasteFromCopy()
/**
	OPIS METOD(FUNKCJI): Wstawienie skopiowanego elementu
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TList *pListCutCopyObject = this->_pGsDrawChildren->_pCutCopyObject->_pListChildren; // Wskaźnik na liste potomków objektu wstawianego
	GsChild *pChild=nullptr;
	// Błąd gdy spełniony jest jeden z warunków:
	// 1. Objekt do przeniesienia jest pusty(nullptr)
	// 2.Objekt do przeniesienia jest tym samym objektem co objekt przeznaczenia.
	// 3.Objekt do przeniesienia jest potomkiem objektu przeznaczenia
	if(!this->_pGsDrawChildren->_pCutCopyObject ||
		 (this->_pGsDrawChildren->_pSelectObject == this->_pGsDrawChildren->_pCutCopyObject) ||
		 (this->_pGsDrawChildren->_pSelectObject == this->_pGsDrawChildren->_pCutCopyObject->_pPrevChild))
	{
//    #if defined(_DEBUGINFO_)
//			GsDebugClass::WriteDebug("Taki sam!");
//		#endif
		this->_pGsDrawChildren->_pCutCopyObject = nullptr;
		return false;
	}
	// Zabezpieczenie by nowym przodkiem nie był potomek
	bool bIsFind = this->_FindObjectInTree( this->_pGsDrawChildren->_pSelectObject, this->_pGsDrawChildren->_pCutCopyObject);
//	#if defined(_DEBUGINFO_)
//		GsDebugClass::WriteDebug(Format("bIsFind: %d", ARRAYOFCONST(( (int)bIsFind))));
//	#endif
	if(bIsFind)
	{
		this->_pGsDrawChildren->_pCutCopyObject = nullptr;
		return false;
	}
	//---
	if(this->_pGsDrawChildren->_pCutCopyObject)
	{
		GsChild *pGsChildCutCopyParent = this->_pGsDrawChildren->_pCutCopyObject->_pPrevChild, // Wskażnik na przodka
						*pGsChildNewParentSelect = this->_pGsDrawChildren->_pSelectObject; // Nowy przodek, to objekt wybrany
		if(!pGsChildCutCopyParent) return false;
		TList *pListParent = pGsChildCutCopyParent->_pListChildren; // Lista potomków, przodka
		int iIndex = pListParent->IndexOf(this->_pGsDrawChildren->_pCutCopyObject); // Wyszukanie na tej liście objektu do wstawienia
		if(iIndex == -1) return false;
    //return;
		pListParent->Delete(iIndex); // Wykasowanie z listy potomków, poprzedniego przodka
		//---
		TList *pListNew = pGsChildNewParentSelect->_pListChildren; // Wskaźnik na listę potomków, nowego przodka
		pListNew->Add(this->_pGsDrawChildren->_pCutCopyObject); // Dodanie do listy potomków, nowego przodka
		this->_pGsDrawChildren->_pCutCopyObject->_pPrevChild = pGsChildNewParentSelect; // Ustawienie wskaźnika na przodka, na nowego przodka
		// Nowe położenia
		int iLeftMove = pGsChildNewParentSelect->Left - pGsChildCutCopyParent->Left,
				iTopMove = pGsChildNewParentSelect->Top - pGsChildCutCopyParent->Top;

		this->_pGsDrawChildren->_pCutCopyObject->Left += iLeftMove;
		this->_pGsDrawChildren->_pCutCopyObject->Top += iTopMove;
		for(int i=0; i<pListCutCopyObject->Count; ++i)
		{
			pChild = static_cast<GsChild *>(pListCutCopyObject->Items[i]);
			if(pChild)
			{
				pChild->Left += iLeftMove;
				pChild->Top += iTopMove;
			}
    }

		TTreeNode *pTNode = this->_pGsDrawChildren->_pCutCopyObject->_TreeNodeChild;
		pTNode->MoveTo(pGsChildNewParentSelect->_TreeNodeChild, naAddChild);
		this->_pTreeView->FullExpand(); //Całkowicie rozwiniete drzewo

		this->_pGsDrawChildren->Invalidate(); //Całe odświerzenie
		return true;
	}
	return false;
}
//----------------------------- Metody prywatne -----------------------------
void __fastcall GsMaster::_CreateHierarchyText(const GsChild *pChild, TStrings *pStrings)
/**
	OPIS METOD(FUNKCJI): Tworzenie zchierarchizowanego tekstu. Metoda działa wywołując sama siebie
											 idąc po kolejnych gałęziach hierarchii
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	GsChild *pChildChild=nullptr;

	pStrings->Add(Format("%s%s \"%s\"", ARRAYOFCONST((DupeString("\t", pChild->_Level), pChild->_ustrNameVers, pChild->_ustrTextVers))));
	for(int i=0; i<pChild->_pListChildren->Count; ++i)
	{
		pChildChild = static_cast<GsChild *>(pChild->_pListChildren->Items[i]);
		if(pChildChild)
		{
			this->_CreateHierarchyText(pChildChild, pStrings);
		}
	}
}
//---------------------------------------------------------------------------
bool __fastcall GsMaster::_FindObjectInTree(const GsChild *pChildForComparison, GsChild *pChild)
/**
	OPIS METOD(FUNKCJI): Wyszukiwanie objektu zaczynająć w hierarchi od pChild,
											 Metoda idzie po drzewie i gałęziach wywołując sama siebie, porównując
											 object pChildForComparison, z kolejnymi objektami w drzewie. Jeśli
											 objekt zostanie znaleziony, metoda przerywa poszukiwania i zwraca true.
	OPIS ARGUMENTÓW: const GsChild *pChildForComparison - objekt wyszukiwany
									 GsChild *pChild - Gałąż , w której wyszukuje się objektu pChildForComparison
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	static int iLevel; // Głębokość wyszukiwania
	GsChild *pChildChild=nullptr;
	bool bWasItFound=false; // Czy znaleziono taki sam objekt?
	// Szukanie w objektach potomnych
	for(int i=0; i<pChild->_pListChildren->Count; ++i)
	{
    pChildChild = static_cast<GsChild *>(pChild->_pListChildren->Items[i]);
		if(pChildChild)
		{
			if(pChildChild == pChildForComparison) return true;
      iLevel++;
			this->_FindObjectInTree(pChildForComparison, pChildChild); // Szukaj w gałęzich potomka
		}
  }

	return bWasItFound;
}
//----------------------- Metody prywatne właściwości------------------------
void __fastcall GsMaster::FSetChildSelect(GsChild *pGsChild)
/**
	OPIS METOD(FUNKCJI): Zmiana pozycji zaznaczenia
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	// Ustawienie właściwosci __proprties
	this->FSelectItem = pGsChild;
	this->FSelectText = pGsChild->Text;
	// Wskaznik z argumenty staje się objektem aktywnym
	this->_pGsDrawChildren->_pSelectObject = pGsChild;
  // Modyfikacja niezbędnych danych
	this->_pGsDrawChildren->_DeactivationAllItems(); // Wykasowanie wszystkich aktywacji pozycji
	pGsChild->_IsActive = true; // Wskaźnik z argumentu staje się aktywną pozycją
  this->_pGsDrawChildren->Invalidate();
}
//---------------------------------------------------------------------------

