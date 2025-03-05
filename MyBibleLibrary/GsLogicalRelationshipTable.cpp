#pragma hdrstop

#include <Vcl.Dialogs.hpp>
#include <Strsafe.h>
#include "GsLogicalRelationshipTable.h"
#include "uGlobalVar.h"
#include "MyBibleLibrary\GsReadBibleTextdata.h"
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
GsChild *pGsChild = static_cast<GsChild *>(CommData::CDataDraw->_pGsChildrenMultiList->Items[i]);
if(pGsChild && (pGsChild != this))
*/
/****************************************************************************
* Wspólna statyczna struktura danych CommData, dostepna dla wszystkich klas *
*****************************************************************************/
struct CommData
{
	inline static GsMaster *CDataMaster=nullptr; // Główna klasa GsMasterLogicalRelationship
	inline static GsDrawChildren *CDataDraw=nullptr; // Klasa do rysowania
};
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
	int iIndexThis = CommData::CDataDraw->_pMainChildrenList->IndexOf(this);
	if(iIndexThis > -1) CommData::CDataDraw->_pMainChildrenList->Delete(iIndexThis);

//	siTempLicz++;
//  #if defined(_DEBUGINFO_)
//		GsDebugClass::WriteDebug(Format("%d -> iIndexThis: %d -> Count: %d",
//			ARRAYOFCONST((siTempLicz, iIndexThis, CommData::CDataDraw->_pMainChildrenList->Count ))));
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
	if(this == CommData::CDataDraw->_pRootObject)
		// Root nie zmienia koloru?
		{this->Color = CommData::CDataMaster->Global_ColorsSchemeTable[enColorSchemeNum_Rot];}
	else
	{
		if(this->_IsActive)
			{this->Color = CommData::CDataMaster->Global_ColorsSchemeTable[enColorSchemeNum_Active];}
		else
			{this->Color = CommData::CDataMaster->Global_ColorsSchemeTable[enColorSchemeNum_InActive];}
	}

	if(CommData::CDataMaster->Global_IsTransparent)
  // Czy malować z przezroczystością ?
		{FillRectAlpha(this->Canvas, this->ClientRect, this->Color, 150);}
	else
	{
		this->Canvas->Brush->Color = this->Color;
		this->Canvas->FillRect(this->ClientRect);
	}

	this->Canvas->Brush->Color = clBlack; //
	this->Canvas->FrameRect(this->ClientRect);

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
	if(CommData::CDataDraw->_pSelectObject != this) // Objekt kliknięty, staje się aktualny
	{
		CommData::CDataDraw->_pSelectObject = this; // Pole potrzebne do odrysowania aktualnej pozycji
																								// (kolor) w metodzie Paint(), klasy GsDrawChildren
		CommData::CDataMaster->FSelectItem = this; // Aktualnie aktywny nowo dodany objekt będący wskaźnikiem na GsChild,
																							 // pole typy __property
		CommData::CDataMaster->FSelectText = this->Text; // Tekst na pozycji, pole typy __property
	}
	//---
	if(Button == mbLeft)
	{
		if(!Shift.Contains(ssCtrl))
		// Bez Ctr
		{
			CommData::CDataDraw->_DeactivationAllItems(); // Dezaktywacja wszystkich pozycji
		}
		this->_IsActive = true;//!this->_IsActive;

		this->_GetStartX = X;
		this->_GetStartY = Y;
		this->_StartMove = true;
	}
	CommData::CDataMaster->MouseDown(Button, Shift, X, Y); // Wywołanie obsługi zdarzenie myszy dla klasy GsMaster
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
    CommData::CDataDraw->_CalculateNewDimension(this);
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
			for(int i=0; i<CommData::CDataDraw->_pMainChildrenList->Count; ++i)
			{
				GsChild *pGsChild = static_cast<GsChild *>(CommData::CDataDraw->_pMainChildrenList->Items[i]);
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
	CommData::CDataDraw->Invalidate();
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
  CommData::CDataDraw = this;
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
	for(int i=0; i<this->_pMainChildrenList->Count; ++i)
	{
		pGsChild = static_cast<GsChild *>(this->_pMainChildrenList->Items[i]);
		if(pGsChild)
		{
			pPrevChild = pGsChild->_pPrevChild;
			//--- Odrysowanie objektu i połączeń
			if(pPrevChild)
			{
				//Rysowanie połączenia z przodkiem
				this->Canvas->Pen->Width = CommData::CDataMaster->Global_iWidthLineScheme;//iWidthLine;
				this->Canvas->Pen->Color = CommData::CDataMaster->Global_ColorsSchemeTable[enColorSchemeNum_Line];//ColorObject[enColorNum_Line];
				this->Canvas->MoveTo(pGsChild->Left + (pGsChild->Width / 2), pGsChild->Top);
				this->Canvas->LineTo(pPrevChild->Left + (pPrevChild->Width / 2), pPrevChild->Top + pPrevChild->Height);
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
	CommData::CDataMaster->MouseDown(Button, Shift, X, Y); // Wywołanie obsługi zdarzenie myszy dla klasy GsMaster
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
      }
		}

		this->_pMainChildrenList->Add(pGsChild); //Dodanie do głównej listy objektów
	}
	pGsChild = static_cast<GsChild *>(this->_pMainChildrenList->Last());
	if(pGsChild)
	// Aktywacja i selekcja ostatniego elementu
	{
		this->_pSelectObject = pGsChild; // Ostatni object aktywnym
		this->_CalculateNewDimension(pGsChild);
		this->_DeactivationAllItems(); // Dezaktywacja wszystkich pozycji
		pGsChild->_IsActive = true;
	}
	//this->Invalidate(); //Całe odświerzenie

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
			}
		}

		this->_pMainChildrenList->Add(pGsChild); //Dodanie do głównej listy objektów
	}

  pGsChild = static_cast<GsChild *>(this->_pMainChildrenList->Last());
	if(pGsChild)
	// Aktywacja i selekcja ostatniego elementu
	{
		this->_pSelectObject = pGsChild; // Ostatni object aktywnym
		this->_CalculateNewDimension(pGsChild);
    this->_DeactivationAllItems(); // Dezaktywacja wszystkich pozycji
		pGsChild->_IsActive = true;
	}
	//this->Invalidate(); //Całe odświerzenie

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
__fastcall GsMaster::GsMaster(TComponent* Owner)
 : TScrollingWinControl(Owner)
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
	this->StyleElements = TStyleElements();
	this->AutoScroll = true;
	this->DoubleBuffered = true;
	this->ParentBackground = false;
  this->HorzScrollBar->Tracking = true;
	this->VertScrollBar->Tracking = true;

	// Wspólny wskaźnik na główną klase
	CommData::CDataMaster = this;
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
  // Lista dla wielokrotnego wyboru
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
	if(this->_pGsDrawChildren->_pSelectObject)	//Aktualnie aktywny objekt
	{
		if(this->_pGsDrawChildren->_pSelectObject!=this->_pGsDrawChildren->_pRootObject)
		//Nie jest korzeniem i posiada przodków
		{
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

	GsChild *pGsChild=nullptr, *prevGsChild=nullptr; //Domyślnie to korzeń

	pGsChild = new GsChild(this->_pGsDrawChildren, custrAdr, custrVers);
	if(!pGsChild) throw(Exception("Nie dokonano inicjalizacji objektu GsChildLogicalRelationship"));
	int _left = this->_pGsDrawChildren->Width / 2 - (pGsChild->Width / 2);

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
	}
	else //Dodawanie korzenia
	{
		this->_pGsDrawChildren->_pRootObject = pGsChild;		// Okno głównego korzenia
	}
	pGsChild->Top = _iTop; pGsChild->Left = _left;

	this->_pGsDrawChildren->_pSelectObject = pGsChild;	// Aktualnie aktywny nowo dodany objekt
	this->_pGsDrawChildren->_DeactivationAllItems(); // Dezaktywacja wszystkich pozycji
	pGsChild->_IsActive = true;
	this->FSelectItem = this->_pGsDrawChildren->_pSelectObject; // Aktualnie aktywny nowo dodany objekt,
																														 // pole typy __property
	this->FSelectText = custrVers; // Tekst na pozycji, pole typy __property

	this->_pGsDrawChildren->_pMainChildrenList->Add(pGsChild); //Dodanie do głównej listy objektów
	this->_pGsDrawChildren->Invalidate(); //Całe odświerzenie
	//return pGsChild;
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
  //Wykasowanie całej zawartości schematu, ze wszystkimi aktualnymi objektami
	if(this->_pGsDrawChildren->_pRootObject) {delete this->_pGsDrawChildren->_pRootObject; this->_pGsDrawChildren->_pRootObject = nullptr;} //Niszczenie rozpoczyna się od korzenia
	this->_pGsDrawChildren->_pSelectObject = nullptr;
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
//----------------------- Metody prywatne właściwości------------------------

